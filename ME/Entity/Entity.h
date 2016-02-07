#pragma once

#include <vector>
#include <string>

#include <glm\glm.hpp>

class Entity {
public: 
	Entity();
	~Entity();

	void update();
	void tick();
};

class EntityComponent {
protected:
	EntityComponent();
	~EntityComponent();

	virtual void update();
	virtual void tick();
};

class GravityComponent : public EntityComponent {
public:
	GravityComponent();

	void update() override;
	void tick() override;
};