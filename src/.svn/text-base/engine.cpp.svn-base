/*
 * engine.cpp
 *
 *  Created on: Nov 20, 2011
 *      Author: sushil
 */

#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

#include <utils.h>

#include <timer.h>

//#include <entityMgr.h>
#include <engine.h>

using namespace std;

		FastEcslent::Engine::Engine(int instId, Options opts) {
			instanceId = instId;
			options = opts;
			quit = false;
			this->gameState = GAME;
			this->startTime = getCurrentTime();
		}

		FastEcslent::Engine::~Engine(){
			delete selectionMgr;
			delete distanceMgr;
			delete gameMgr;
			delete groupMgr;
			delete entityMgr;
		}

void FastEcslent::Engine::constructManagers() {
	entityMgr = new EntityMgr(this, options);
	selectionMgr = new SelectionMgr(this, options);
	weaponMgr    = new WeaponMgr(this, options);

	gameMgr   = new GameMgr(this, options);
    
    levelMgr = new LevelMgr(this, options);
    infoMgr  = new InfoMgr(this);

	//optional managers
	if(options.tacticalAI) {
		distanceMgr = new DistanceMgr(this, options);
		groupMgr    = new GroupMgr(this, options);
	}

	//optional threads
	if(options.enableNetworking) net = new NetThread(this);
	if(options.enableGfx)        gfx = new GfxThread(this);

	//construct others
}
void FastEcslent::Engine::init() {
	selectionTimer = new FastEcslent::MilliSecondTimer(200.0f);
	distanceTimer   = new FastEcslent::MilliSecondTimer(500.0f);

	sleepInterval = new boost::posix_time::milliseconds(300);

	entityMgr->init();
	selectionMgr->init();
	weaponMgr->init();

	gameMgr->init();
    
    levelMgr->init();
    infoMgr->init();

	if (options.tacticalAI) {
		distanceMgr->init();
		groupMgr->init();
	}

	//optional threads
	if (options.enableNetworking) net->init();
	if (options.enableGfx)        {
		gfx->init();
		gameState = LOBBY;
	}
}

void FastEcslent::Engine::loadLevel(){
	if (options.enableNetworking) net->run();
	if (options.enableGfx)        {
		gfx->run();
		//wait until lobby setting finished
		while(!gfx->gimPtr || this->gameState == LOBBY){
			boost::this_thread::sleep(*sleepInterval);
		}
	}

	gameMgr->loadLevel();
	//sleep(2.0); //
	return;
}

void FastEcslent::Engine::releaseLevel(){
	//optional
	if (options.enableNetworking) net->stopAndJoin();
	if (options.enableGfx) 		  gfx->join();

	return;
}

void FastEcslent::Engine::stop(){
	//
	//std::cout << "Engine stopping" << std::endl;
	return;
}

void FastEcslent::Engine::tickAll(float dt){
	entityMgr->tick(dt);
	selectionMgr->tick(dt);
	weaponMgr->tick(dt);

	gameMgr->tick(dt);
    infoMgr->tick(dt);
	// tick other managers
    
	//optional Managers must be ticked
	if (options.tacticalAI) {
		distanceMgr->tick(dt);
		groupMgr->tick(dt);
	}
	//Threads are not ticked

}

void FastEcslent::Engine::run(){
	//unsigned long int frame = 0;
	float dt = 0.0005; //1.0f/60.0f;
	double runTime = 0.0f;
	ptime oldTime = getCurrentTime();
	ptime newTime;
	time_duration diff;
	double speedup = options.speedup;

	float dtime = 0.0;
	while (runTime < 5000000.0 && !this->quit){

		tickAll(dtime * speedup); // tick all managers

		//update times
		runTime += dt;

		newTime = getCurrentTime();
		diff = newTime - oldTime;
		oldTime = newTime;
		dtime = diff.total_microseconds() * 0.000001f; //inseconds
		/*
		if(options.runDebugTests){
			runTests();
		}
		*/
		/*
		if (frame%1000 == 0) {
			//cout << "Frame: " << frame << " Number of collisions: " << distanceMgr->collisionTotal << endl;
			this->selectionMgr->dump();
		}
		frame++;
		*/

	}
	cout << endl << "Finished, running. Dumping first entity..." << endl;
	entityMgr->dumpOne(0);
	//cout << " Number of collisions: " << distanceMgr->collisionTotal << endl;
	this->quit = true;


}

void FastEcslent::Engine::runTests(){
	int entIndex;
	Entity** selected;


	//test distance mgr
	if(options.tacticalAI){
		if(distanceTimer->hasFired()){
			distanceMgr->dumpAll();
		}
	}

	//test selection

	if(selectionTimer->hasFired()){
		entIndex = random()% this->entityMgr->nEnts;
		cout << "Unselected: " << entIndex << endl;
		this->selectionMgr->unselect(entIndex);
		selected = this->selectionMgr->getSelectedEnts();
		cout << "Selected: ";
		for(int i = 0; i < this->selectionMgr->getNSelectedEnts(); i++){
			cout << "(" << selected[i]->entityId.id << ": " << selected[i]->isSelected << ") ";
		}
		cout << endl;
	}
	//cout << "Iteration: " << n++ << endl;;
	//std::cout << "dtime: " << dtime << std::endl;

}




