#pragma once

#include "../graphics/objects/Camera.h"
#include "../graphics/objects/models/models.h"

#include <vector>

class World
{
public:
	World();

	void start();
	void update();
	void render() const;
	void truncate();

	Camera* getCamera() const;
private:
	Plane* mandelbrotPlane;
	Plane* fadePlane;
	Camera* camera;
	Object* parent;
	std::vector<Cube*> cubes;
};