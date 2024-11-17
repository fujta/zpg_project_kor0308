#include "Material.h"

Material::Material(Light* lightContext)
{
	ra = 1.0f;
	rd = 1.0f;
	rs = 1.0f;

	this->lightContext = lightContext;
}

Material::Material(float ra, float rd, float rs, Light* lightContext)
{
	this->ra = ra;
	this->rd = rd;
	this->rs = rs;

	this->lightContext = lightContext;
}

Material::~Material()
{
}

float Material::getRa()
{
	return ra;
}

float Material::getRd()
{
	return rd;
}

float Material::getRs()
{
	return rs;
}

void Material::setRa(float ra)
{
	this->ra = ra;

	lightContext->notifyObservers();
}

void Material::setRd(float rd)
{
	this->rd = rd;

	lightContext->notifyObservers();
}

void Material::setRs(float rs)
{
	this->rs = rs;

	lightContext->notifyObservers();
}

