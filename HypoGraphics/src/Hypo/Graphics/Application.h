#pragma once

#include <iostream>
#include "Hypo/Graphics/Exports.h"
class HYPO_GRAPHICS_API Application
{
public:
	Application();

	void render();
	int shaderProgram;
	unsigned int VBO, VAO, EBO;
};

