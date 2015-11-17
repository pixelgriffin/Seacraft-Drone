#ifndef INFOMGR_H
#define	INFOMGR_H

#include <OgreVector3.h>
#include <enums.h>
#include <IMEnemy.h>
#include <IMTerrain.h>
#include "mgr.h"
#include "SquadMgr.h"
#include "IMParams.h"

namespace FastEcslent {
    class Engine;
    class Entity;
    class InfoMgr : public Mgr {
    public:
    	InfoMgr(Engine *eng);
        ~InfoMgr();
        
        void registerEntity(Entity* ent);
		virtual void init();
		virtual void tick(double dtime);

		IMEnemy* getIMEnemy(Side s);

		int getFrameCount(){return this->frame;};

		IMParams getRedParams(){return redParams;};
		IMParams getBlueParams(){return blueParams;};

		SquadMgr *squadmgr_red, *squadmgr_blue;
    private:
		int frame;
		double dt;
		IMEnemy   *eIM_red, *eIM_blue;
		IMTerrain *tIM_red, *tIM_blue;

		IMParams redParams;
		IMParams blueParams;
    };
}

#endif

