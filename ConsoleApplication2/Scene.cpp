#include "Scene.h"
#include "Graphics.h"

GraphicsEngine sceneEngine;

void Scene::InitScene()
{
	buffer1 = std::vector<std::vector<ColoredChar>>(sceneEngine.HEIGHT, std::vector<ColoredChar>(sceneEngine.WIDTH));
	buffer2 = std::vector<std::vector<ColoredChar>>(sceneEngine.HEIGHT, std::vector<ColoredChar>(sceneEngine.WIDTH));
	currentBuffer = &buffer1;
	nextBuffer = &buffer2;
}
