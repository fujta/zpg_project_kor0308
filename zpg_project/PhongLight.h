#pragma once
#include <string>
#include "Light.h"

class PhongLight : public Light
{
public:
	std::string getFragmentShaderName();
};

