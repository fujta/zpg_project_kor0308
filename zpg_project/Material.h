#pragma once
#include "Light.h"

class Light;

class Material
{
private:
	float ra;
	float rd;
	float rs;

	Light* lightContext;

public:
	Material(Light* lightContext);
	Material(float ra, float rd, float rs, Light* lightContext);
	~Material();

	float getRa();
	float getRd();
	float getRs();
	void setRa(float ra);
	void setRd(float rd);
	void setRs(float rs);
};

