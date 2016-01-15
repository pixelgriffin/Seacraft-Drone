
#include "SquadMgr.h"
#include <vector>
#include <algorithm>
#include "engine.h"
#include "MicroAspect.h"
#include "infoMgr.h"
#include <stdlib.h>
#include <timer.h>
#include <utils.h>

using namespace FastEcslent;
using namespace std;

SquadMgr::SquadMgr(Engine *eng, InfoMgr *inforMgr, Side s):side(s){
	this->engine = eng;
	this->im = inforMgr;

	//this->player = Player;

	this->needsregroup = false;
	if(this->side == RED){
		params = GA::getInstance()->getRedParams();
	}else{
		params = GA::getInstance()->getBlueParams();
	}

	A = params.A * 1000;            //Attraction
	B = params.B * 10000;           //Nearby repulsion
	m = params.m * 0.3;            //Nearby repulsion
	n = params.n * 0.3;            //Attraction

	//The rest of the params are converted in microAspect.cpp

	repulsionThreshold = 1500;

	state = SquadState::Idle;
	this->target = NULL;
}

double SquadMgr::getPotentialA() {
	return A;
}

double SquadMgr::getPotentialB() {
	return B;
}

double SquadMgr::getPotentialM() {
	return m;
}

double SquadMgr::getPotentialN() {
	return n;
}

void SquadMgr::loadUnits(){
	for(int i=0;i<this->engine->entityMgr->nEnts;i++){
		Entity* ent = this->engine->entityMgr->ents[i];
		if(ent->entityId.side == this->side){
			this->addUnit(ent);
		}else if(ent->entityId.side != this->side && ent->entityId.side != NEUTRAL){
			this->addEnemy(ent);
		}
	}
}

void SquadMgr::removeUnits(){
	for(int i=0;i<this->engine->entityMgr->nEnts;i++){
		Entity* ent = this->engine->entityMgr->ents[i];
		if(ent->entityState != ALIVE){
			onUnitDestroy(ent);
		}
	}
}

void SquadMgr::addEnemy(Entity* unit){
	this->enemySet.insert(unit);
}

void SquadMgr::addUnit(Entity* unit){
	MicroAspect *m = new MicroAspect(unit, this, this->side);
	this->unitSet.insert(unit);
	this->microAspectSet.insert(m);
	this->unitToMicroAspectMap[unit] = m;
}

void SquadMgr::onUnitDestroy(Entity* unit){
	if(this->unitToMicroAspectMap.find(unit) != this->unitToMicroAspectMap.end()){
		MicroAspect *m = this->unitToMicroAspectMap[unit];
		this->unitSet.erase(unit);
		this->unitToMicroAspectMap.erase(unit);
		this->microAspectSet.erase(m);
		delete m;
	}else if(this->enemySet.find(unit) != this->enemySet.end()){
		this->enemySet.erase(unit);
	}
}

void SquadMgr::onFrame(){

	if(this->im->getFrameCount() == 8){
		loadUnits();
	}

	//attack
	if(this->im->getFrameCount() > 10){
		this->removeUnits();
		this->setTarget();
		this->refreshGroupPosition();
		this->onFire();
	}
}

void SquadMgr::onFire(){
	for(set<MicroAspect*>::const_iterator i=this->microAspectSet.begin();i!=this->microAspectSet.end();++i)
	{
		(*i)->onFire(this->enemySet);
	}
}

Entity* SquadMgr::setTarget(){
	if(centerX > 0 && centerY > 0 && centerZ > 0){
		Ogre::Vector3 cc(centerX, centerY, centerZ);
		double minDist = 1000000;
		Entity* e;
		for(int i=0;i<this->engine->entityMgr->nEnts;i++){
			Entity* ent = this->engine->entityMgr->ents[i];

			if(ent->entityId.side == this->side) continue;

			double dist = ent->pos.distance(cc);
			if(dist< minDist){
				e = ent;
			}
			this->target = e;
		}
		return e;

	}else{
		this->target = NULL;
		return NULL;
	}
}


void SquadMgr::refreshGroupPosition(){
	if(this->unitSet.size() == 0){
		centerX = 0;
		centerY = 0;
		centerZ = 0;
		radius = 1;
		return;
	}
	int totalX = 0;
	int totalY = 0;
	int totalZ = 0;

	for (set<Entity*>::iterator i = this->unitSet.begin();i!= this->unitSet.end();i++){
		totalX += (*i)->pos.x;
		totalY += (*i)->pos.y;
		totalZ += (*i)->pos.z;
	}

	centerX = totalX/this->unitSet.size();
	centerY = totalY/this->unitSet.size();
	centerZ = totalZ/this->unitSet.size();

	Ogre::Vector3 cc(centerX, centerY, centerZ);

	int dist = 0;
	for (set<Entity*>::iterator i = this->unitSet.begin();i!= this->unitSet.end();i++){
		dist += (*i)->pos.distance(cc);
	}

	radius = dist/this->unitSet.size();
}

bool SquadMgr::isSquadInCombat(){

	for (set<Entity*>::iterator i = this->unitSet.begin();i!= this->unitSet.end();i++){
		if((*i)->weapon->isEntityAttacking()){
			return true;
		}
	}

	return false;
}

bool SquadMgr::isSquadMoving(){
	for (set<MicroAspect*>::iterator i = this->microAspectSet.begin();i!= this->microAspectSet.end();i++){
		if((*i)->isUnitMoving()){
			return true;
		}
	}
	return false;
}


void SquadMgr::potentialMove(Entity* unit, Ogre::Vector3* target, int dist)
{
	UnitAI* ai     = static_cast<UnitAI*>(unit->getAspect(UNITAI));
	//PotentialMove* move = createPotentialMoveForEnt(unit, *target);

	if(unit->entityType != DRONE)
	{
		PotentialMove* move = createPotentialMoveForEnt(unit, *target);
		ai->setCommand(move);
	}
	else
	{
		Potential3DMove* move = createPotential3DMoveForEnt(unit, *target);
		ai->setCommand(move);
	}
}

double SquadMgr::getSquadScore()
{
	double f1 = fightScore();
	double f2 = moveScore();
	double noMoveScore = ((this->engine->gameMgr->startingNumberOfDrones * this->engine->gameMgr->droneCost) -
				(this->engine->gameMgr->startingNumberOfTurrets * this->engine->gameMgr->turretCost));
	if(closeTo(f1, noMoveScore+1000)){
		return 2000-f2;

	} else {
		return f1;
	}

}



double SquadMgr::moveScore(){
	double totalDist = 0.0;
	for (set<Entity*>::iterator i = this->unitSet.begin(); i != this->unitSet.end(); i++){
		for (set<Entity*>::iterator j = this->enemySet.begin(); j != this->enemySet.end(); j++){
			Entity *f = *i;
			Entity *e = *j;
			totalDist += (f->pos - e->pos).length();
		}
	}
	return totalDist/(this->unitSet.size() * this->enemySet.size());
}

double SquadMgr::fightScore(){

	//int droneCost = 150;
	//int turretCost = 150;
	//int fu = this->unitSet.size();
	//int eu = this->enemySet.size();
	//int du = fu - eu;

////	double score = fu/*du*/*unitscore;
//	double score = fu * droneCost;
//
//	double enemyScore = eu * turretCost;
//
//	score += -enemyScore;
	double score;
	double friendFitness = 0.0;
	//double fumhp = 0.00001, fuhp = 0.00001, eumhp = 0.00001, euhp = 0.00001;

	for (set<Entity*>::iterator i = this->unitSet.begin(); i != this->unitSet.end(); i++)
	{
	   Entity* t = *i;
//	   fumhp += t->hitpointsmax;
//	   fuhp += t->hitpoints;

	   friendFitness += (this->engine->gameMgr->droneCost * t->hitpoints/t->hitpointsmax);


	}
	double enemyFitness = 0.0f;
	for (set<Entity*>::iterator i = this->enemySet.begin(); i != this->enemySet.end(); i++)
		{
		   Entity* t = *i;
	//	   eumhp += t->hitpointsmax;
	//	   euhp += t->hitpoints;
		   enemyFitness += (this->engine->gameMgr->turretCost * (t->hitpoints/t->hitpointsmax));
		}

	score = friendFitness - enemyFitness;

	score += (engine->gameMgr->startingNumberOfTurrets - this->enemySet.size()) * (1.0 - this->im->getFrameCount()/this->im->maxFrames);

////	score += (uhp/umhp + (1 - ehp/emhp)) * 100;
//
//	double frame = this->im->getFrameCount();
//	//Time score is the within [0-1) * marine score
//	double timescore =  unitscore * (1.0 - frame/300000.0);    //250 is the set longest time in one game
//
//	if(score < 0) timescore = -score + 1;//timescore *= -1;  //when the enemy win, time score is negative
//	if (eu == 0) score += timescore;
//
//	if(eu > 0 && fu > 0){    //didn't fight at all, punish
//		//score -= eu* unitscore;
//		score = 1;
//	}

	//std::cout << score << std::endl;
 	return score + GA::getInstance()->positiveFitnessFactor;
}

int SquadMgr::getSquadScore2()
{
	int eunitscore = 200;
	int funitscore = 150;
	int eu = 30 - this->enemySet.size();
	int fu = 5  - this->unitSet.size();

	return eu*eunitscore - fu*funitscore;
}

int SquadMgr::getSquadDestroyScore()
{
	double myscore = 0;//BWAPI::Broodwar->self()->getKillScore();
	double enscore = 0;//BWAPI::Broodwar->enemy()->getKillScore();
	return myscore - enscore;
}
