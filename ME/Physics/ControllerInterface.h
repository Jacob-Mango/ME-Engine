#pragma once

#ifndef BT_CHARACTER_CONTROLLER_INTERFACE_H
#define BT_CHARACTER_CONTROLLER_INTERFACE_H

#include <bullet\\src\\btBulletDynamicsCommon.h>

class btCollisionShape;
class btRigidBody;
class btCollisionWorld;

class btCharacterControllerInterface : public btActionInterface
{
public:
	btCharacterControllerInterface() {};
	virtual ~btCharacterControllerInterface() {};

	virtual void	setWalkDirection(const btVector3& walkDirection) = 0;
	virtual void	setVelocityForTimeInterval(const btVector3& velocity, btScalar timeInterval) = 0;
	virtual void	reset(btCollisionWorld* collisionWorld) = 0;
	virtual void	warp(const btVector3& origin) = 0;

	virtual void	preStep(btCollisionWorld* collisionWorld) = 0;
	virtual void	playerStep(btCollisionWorld* collisionWorld, btScalar dt) = 0;
	virtual bool	canJump() const = 0;
	virtual void	jump() = 0;

	virtual bool	onGround() const = 0;
	virtual void	setUpInterpolate(bool value) = 0;
};

#endif //BT_CHARACTER_CONTROLLER_INTERFACE_H

