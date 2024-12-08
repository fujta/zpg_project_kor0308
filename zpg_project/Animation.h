#pragma once
#include "DrawableObject.h"

class Animation
{
public:
	virtual ~Animation() {}
	virtual void update() = 0;

	DrawableObject* getDrawableObject();

protected:
	DrawableObject* object;
};

