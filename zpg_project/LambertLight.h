#pragma once
#include <string>
#include "Light.h"

class LambertLight : public Light
{
public:
	std::string getFragmentShaderName();
};

