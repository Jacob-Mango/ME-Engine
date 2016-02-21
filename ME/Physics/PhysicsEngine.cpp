#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {
	m_CollisionConfig = new btDefaultCollisionConfiguration();
	m_Dispatcher = new btCollisionDispatcher(m_CollisionConfig);
	m_Broadphase = new btDbvtBroadphase();
	m_Solver = new btSequentialImpulseConstraintSolver();
	m_World = new btDiscreteDynamicsWorld(m_Dispatcher, m_Broadphase, m_Solver, m_CollisionConfig);
	m_World->setGravity(btVector3(0.0f, -9.18f, 0.0f));
}

PhysicsEngine::~PhysicsEngine() {
	for (int i = 0; i < m_RigidedBodies.size(); i++) {
		m_World->removeCollisionObject(m_RigidedBodies[i]);
		btMotionState* motionState = m_RigidedBodies[i]->getMotionState();
		btCollisionShape* shape = m_RigidedBodies[i]->getCollisionShape();
		delete m_RigidedBodies[i];
		delete shape;
		delete motionState;
	}
	delete m_Dispatcher;
	delete m_CollisionConfig;
	delete m_Solver;
	delete m_Broadphase;
	delete m_World;
}

btRigidBody* PhysicsEngine::CreateSphere(glm::vec3 position, glm::vec3 rotation, float radius, float mass) {
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(position.x, position.y, position.z));
	btQuaternion qx = btQuaternion(btVector3(1, 0, 0), rotation.x);
	btQuaternion qy = btQuaternion(btVector3(0, 1, 0), rotation.y);
	btQuaternion qz = btQuaternion(btVector3(0, 0, 1), rotation.z);
	t.setRotation(qx);
	btSphereShape* shape = new btSphereShape(radius);
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0)
		shape->calculateLocalInertia(mass, inertia);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, inertia);
	btRigidBody* body = new btRigidBody(info);
	body->setFriction(m_DefaultFriction);
	body->setRollingFriction(m_DefaultRollingFriction);
	body->setRestitution(m_DefaultRestitution);
	m_World->addRigidBody(body);
	m_RigidedBodies.push_back(body);
	return body;
}

btRigidBody* PhysicsEngine::CreateCylinder(glm::vec3 position, glm::vec3 rotation, float radius, float height, float mass) {
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(position.x, position.y, position.z));
	btQuaternion qx = btQuaternion(btVector3(1, 0, 0), rotation.x);
	btQuaternion qy = btQuaternion(btVector3(0, 1, 0), rotation.y);
	btQuaternion qz = btQuaternion(btVector3(0, 0, 1), rotation.z);
	t.setRotation(qx);
	btCylinderShape* shape = new btCylinderShape(btVector3(radius, height / 2.0, radius / 2.0));
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0)
		shape->calculateLocalInertia(mass, inertia);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, inertia);
	btRigidBody* body = new btRigidBody(info); 
	body->setFriction(m_DefaultFriction);
	body->setRollingFriction(m_DefaultRollingFriction);
	body->setRestitution(m_DefaultRestitution);
	m_World->addRigidBody(body);
	m_RigidedBodies.push_back(body);
	return body;
}

btRigidBody* PhysicsEngine::CreateCone(glm::vec3 position, glm::vec3 rotation, float radius, float height, float mass) {
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(position.x, position.y, position.z));
	btQuaternion qx = btQuaternion(btVector3(1, 0, 0), rotation.x);
	btQuaternion qy = btQuaternion(btVector3(0, 1, 0), rotation.y);
	btQuaternion qz = btQuaternion(btVector3(0, 0, 1), rotation.z);
	t.setRotation(qx);
	btConeShape* shape = new btConeShape(radius * 2, height);
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0)
		shape->calculateLocalInertia(mass, inertia);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, inertia);
	btRigidBody* body = new btRigidBody(info);
	body->setFriction(m_DefaultFriction);
	body->setRollingFriction(m_DefaultRollingFriction);
	body->setRestitution(m_DefaultRestitution);
	m_World->addRigidBody(body);
	m_RigidedBodies.push_back(body);
	return body;
}

btRigidBody* PhysicsEngine::CreateBox(glm::vec3 position, glm::vec3 rotation, float width, float height, float depth, float mass) {
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(position.x, position.y, position.z));
	btQuaternion qx = btQuaternion(btVector3(1, 0, 0), rotation.x);
	btQuaternion qy = btQuaternion(btVector3(0, 1, 0), rotation.y);
	btQuaternion qz = btQuaternion(btVector3(0, 0, 1), rotation.z);
	t.setRotation(qx);
	btBoxShape* shape = new btBoxShape(btVector3(width / 2.0, height / 2.0, depth / 2.0));
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0)
		shape->calculateLocalInertia(mass, inertia);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, inertia);
	btRigidBody* body = new btRigidBody(info);
	body->setFriction(m_DefaultFriction);
	body->setRollingFriction(m_DefaultRollingFriction);
	body->setRestitution(m_DefaultRestitution);
	m_World->addRigidBody(body);
	m_RigidedBodies.push_back(body);
	return body;
}

btRigidBody* PhysicsEngine::CreateTerrainMap(glm::vec3 position, float heights[]) {
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(position.x, position.y, position.z));
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* body = new btRigidBody(info);
	body->setFriction(m_DefaultFriction);
	body->setRollingFriction(m_DefaultRollingFriction);
	body->setRestitution(m_DefaultRestitution);
	m_World->addRigidBody(body);
	m_RigidedBodies.push_back(body);
	return body;
}

void PhysicsEngine::Simulate(float delta) {
	m_World->stepSimulation(1 / 30.0);
}