#pragma once
#include "DrawTarget.h"

class Viewport : public DrawTarget
{
public:
	Viewport(DrawTarget& next,const RectF& rect) :
		next(next),
		clip(rect)
	{}

	void Draw(Drawable& obj) override{
		obj.Transform(Mat3::Translation({ clip.left, clip.top }));
		obj.Clip(clip);
		next.Draw(obj);
	}

	float GetWidth() const{
		return clip.getWidth();
	}

	float GetHeight() const{
		return clip.getHeight();
	}

	RectF& getClip() {
		return clip;
	}

private:
	DrawTarget& next;
	RectF clip;
};

