#pragma once
#include "Polyclosed.h"

class Map{
public:
	Map(const std::string filename) :
		model(filename)
	{}

	Polyclosed::Drawable getDrawable() const{
		return model.getDrawable();
	}

private:
	//Structural
	Polyclosed model;
};