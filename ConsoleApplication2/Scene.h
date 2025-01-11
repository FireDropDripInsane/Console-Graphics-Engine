#pragma once
#include <vector>
#include "utils.h"

class Scene
{
public:
	std::vector<std::vector<ColoredChar>> buffer1, buffer2;
	std::vector<std::vector<ColoredChar>>* currentBuffer;
	std::vector<std::vector<ColoredChar>>* nextBuffer;

	void InitScene();
};