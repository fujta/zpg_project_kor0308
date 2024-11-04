#pragma once
#include <string>
#include "Light.h"

class BlinnLight : public Light
{
public:
	std::string getFragmentShaderName();
};

