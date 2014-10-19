#pragma once
#include "DrawTarget.h"

class Camera : public DrawTarget
{
public:
	Camera(DrawTarget& next, float width, float height) :
		next(next),
		pos({ 0.f, 0.f }),
		toCenter({ width / 2.f, height / 2.f })
	{}

	void Draw(Drawable& obj) override{
		obj.Transform(Mat3::Translation(-pos));
		next.Draw(obj);
	}

	void MoveTo(Vec2 pos){
		this->pos = pos - toCenter;
	}

private:
	DrawTarget& next;
	Vec2 pos;
	Vec2 toCenter;
};

