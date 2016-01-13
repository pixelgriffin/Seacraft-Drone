/*
 * physics3.cpp
 *
 *  Created on: July 14, 2015
 *      Author: Nathan
 */
#include <assert.h>

#include <OgreVector3.h>
#include <OgreQuaternion.h>

#include <physics.h>
#include <ent.h>
#include <utils.h>

#include "DEBUG.h"

void FastEcslent::Physics3D::init() {
	entity->desiredSpeed = entity->speed;
	entity->desiredHeading = entity->heading;
}

void FastEcslent::Physics3D::doHelmsman(double dt) {

	//avoid moving if we don't want to
	if(kInvalidFloat == entity->desiredSpeed || kInvalidFloat == entity->desiredHeading)
		return;

	DEBUG(std::cout << "Speed: " << entity->vel.length() << ", XZ-Heading: " << -atan2(entity->vel.z, entity->vel.x) << std::endl);

	//change speeds
	if(entity->speed < entity->desiredSpeed) {
		entity->speed += (entity->maxAcceleration * dt);
	} else if(entity->speed > entity->desiredSpeed) {
		entity->speed -= (entity->maxAcceleration * dt);
	}

	Ogre::Quaternion desiredRot(Ogre::Radian(entity->desiredHeading), Ogre::Vector3::UNIT_Y);

	//update information
	entity->rot 	= Ogre::Quaternion::Slerp(entity->maxRotationalSpeed * dt, entity->rot, desiredRot, true);

	entity->heading = entity->rot.getYaw(true).valueRadians();
	entity->yaw 	= entity->heading;

	entity->speed = clamp(entity->speed, entity->minSpeed, entity->maxSpeed);



	//entity->vel.x = cos(-entity->heading) * entity->speed;
	//entity->vel.y = entity->potentialVec.y * entity->speed; //fly when we need to. No heading
	//entity->vel.z = sin(-entity->heading) * entity->speed;



	Ogre::Vector3 to = entity->pos + (entity->potentialVec.normalisedCopy()* entity->maxSpeed * dt);

	//TODO variable lowest Y, tune this?
//	if(to.y < 10)
//		to.y = 10;
	to.x = clamp(to.x, 0, 2048);
	to.y = clamp(to.y, 10, 2048);
	to.z = clamp(to.z, 0, 2048);

	//a wall of x centimeters!
	//if(to.z < centimeters(25) && to.z > -centimeters(25))
	//	return;

	entity->pos = to;

	DEBUG(std::cout << "Speed: " << entity->speed << ", XZ-Heading: " << entity->heading << std::endl <<std::endl;)

	//std::cout << "3D" << std::endl;
}

void FastEcslent::Physics3D::tick(double dt) {
	//if (this->entity->entityId.side == RED)
		doHelmsman(dt);
}
