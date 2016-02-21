#pragma once

#include <vector>

#include <bullet\\src\\btBulletDynamicsCommon.h>
#include <glm\\glm.hpp>

class PhysicsEngine {
private:
	btDynamicsWorld* m_World;
	btDispatcher* m_Dispatcher;
	btCollisionConfiguration* m_CollisionConfig;
	btBroadphaseInterface* m_Broadphase;
	btConstraintSolver* m_Solver;

	std::vector<btRigidBody*> m_RigidedBodies;

	float m_DefaultFriction = 5.0f;
	float m_DefaultRollingFriction = 5.0f;
	float m_DefaultRestitution = 0.75f;
public:
	PhysicsEngine();
	~PhysicsEngine();

	btRigidBody* CreateSphere(glm::vec3 position, glm::vec3 rotation, float radius, float mass);
	btRigidBody* CreateCylinder(glm::vec3 position, glm::vec3 rotation, float radius, float height, float mass);
	btRigidBody* CreateCone(glm::vec3 position, glm::vec3 rotation, float radius, float height, float mass);
	btRigidBody* CreateBox(glm::vec3 position, glm::vec3 rotation, float width, float height, float depth, float mass);

	btRigidBody* CreateTerrainMap(glm::vec3 position, float heights[]);

	void Simulate(float delta);
};

