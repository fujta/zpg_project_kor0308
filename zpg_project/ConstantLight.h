#pragma once
#include <string>
#include "Light.h"

class ConstantLight : public Light
{
public:
	std::string getFragmentShaderName();
};

