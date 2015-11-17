/*
 * main.cpp
 *
 *  Created on: Nov 20, 2011
 *      Author: sushil
 */

#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <getopt.h>
#include <stdlib.h>
#include <iostream>

#include <engine.h>
#include <entityMgr.h>

#include <options.h>
#include <ctime>
#include "IMParams.h"
#include <sstream>
#include <cstdlib>

using namespace FastEcslent;
using namespace std;

//extern void gfxManager();
pair<IMParams, IMParams> makeParams(int argc, char*argv[]){
	string s = argv[1];
	string delimiter = ",";
	int array[28];

	size_t pos = 0;
	int index = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    array[index++] = atoi(s.substr(0, pos).c_str());
	    s.erase(0, pos + delimiter.length());
	}
	array[index] = atoi(s.c_str());


	IMParams param1;
	param1.UnitValue      = array[0];
	param1.UnitRadius     = array[1];
	param1.TerrainValue   = array[2];
	param1.TerrainRadius  = array[3];

	param1.A = array[4];
	param1.B = array[5];

	param1.m = array[6];
	param1.n = array[7];

	param1.m_freeze      = array[8];
	param1.m_kitingRange = array[9];
	param1.m_targetNearby= array[10];
	param1.m_kitingDist  = array[11];
	param1.m_hpfocus     = array[12];
	param1.m_hpkiting    = array[13];


	IMParams param2;
	param2.UnitValue      = array[14];
	param2.UnitRadius     = array[15];
	param2.TerrainValue   = array[16];
	param2.TerrainRadius  = array[17];

	param2.A = array[18];
	param2.B = array[19];

	param2.m = array[20];
	param2.n = array[21];

	param2.m_freeze      = array[22];
	param2.m_kitingRange = array[23];
	param2.m_targetNearby= array[24];
	param2.m_kitingDist  = array[25];
	param2.m_hpfocus     = array[26];
	param2.m_hpkiting    = array[27];

	return pair<IMParams, IMParams> (param1,param2);
}

Options makeOptions(int argc, char*argv[]){
	Options options;

	options.enableNetworking = false;
	options.networkPort      = 54321;
	options.isServer         = true;

	options.gameNumber = 4;
	options.side = RED;
	options.player = ONE;


	options.runAsEvaluator = true;
	options.instanceId = random();

	options.tacticalAI = true;


	options.enableInteraction = false;

	options.enableGfx = true;
	options.runDebugTests = false;

	options.speedup = 10.0; //300.0; //10.0;
    
    options.levelType = _64x64;


	return options;
}

int main(int argc, char *argv[]){
//	srandom(time(NULL));
	srandom(0.1);
	pair<IMParams, IMParams> microparams = makeParams(argc, argv);
	GA::getInstance()->setParams(microparams.first, microparams.second);

	Options options = makeOptions(argc, argv);

	Engine *engine = new Engine(random(), options);

	//Construct all the managers
	engine->constructManagers();
	//Initialize all the managers
	engine->init();
	//Launch game (1. gameMgr load game; 2. Run network)
	engine->loadLevel();
	//Run game
	engine->run();
	//Unload game
	engine->releaseLevel();
	//Stop game
	engine->stop();

	delete engine;

	return 0;
}


/*
	NetThread *net;
	if(options.enableNetworking){
		net = new NetThread(engine);
		net->init();
		net->start();
	}

	GfxThread *gfx;
	if(options.enableGfx){
		gfx = new GfxThread(engine);
		gfx->init();
		gfx->start();
	}
	sleep(2.0); //wait for graphics thread to get going, start gets the thread running



	while (!engine->quit) {
		engine->loadLevel();
		engine->run();
	}

	if (options.enableNetworking){
		net->join();
	}

	if (options.enableGfx) {
		//gfx->stop();
		gfx->join();

	}

*/

