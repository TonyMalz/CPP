#pragma once
#include "Polyclosed.h"

class Ship{
public:
	Ship(const std::string filename, Vec2 position = { 0.f, 0.f }) :
		model(filename),
		position(position),
		initialPosition(position),
		velocity({0.f,0.f})
	{}

	Polyclosed::Drawable getDrawable() const{
		auto d = model.getDrawable();
		d.Transform(Mat3::Translation(position) * Mat3::Rotation(angle));
		return d;
	}

	void Update(){
		// decrease rotational speed if no current spin is applied
		if (angleAccelDirection == 0.f)
		{
			float absVel = abs(angleVelocity) - constAngleAcceleration*0.5f;
			if (absVel < 0.f)
				angleVelocity = 0.f;
			else 
				angleVelocity = absVel * (angleVelocity < 0.0 ? -1.f : 1.f);
		}

		// add rotational speed
		angleVelocity += constAngleAcceleration * angleAccelDirection;
		angle += angleVelocity;
		//keep angle within 2 PI
		angle = fmodf(angle, 2.f * PI);
		
		//calc current velocity vector and update position
		velocity += Vec2{ 0.f, -1.f }.Rotate(angle) * acceleration * thrust;
		position += velocity;
	}

	void FocusOn(Camera& cam) const{
		cam.MoveTo(position);
	}

	//control
	void Thrust(){
		thrust = 1.f;
	}
	void StopThrusting(){
		thrust = 0.f;
	}

	void Spin(float direction){
		angleAccelDirection = direction;
	}
	void StopSpinnig(float direction ){
		if (angleAccelDirection == direction)
		{
			angleAccelDirection = 0.f;
		}
	}

	void Reset(){
		position = initialPosition;
		angle = 0.f;
		velocity = { 0.f, 0.f };
		thrust = 0.f;
		angleVelocity = 0.f;
		angleAccelDirection = 0.f;
	}

private:
	//Structural
	Polyclosed model;

	//linear
	Vec2 position;
	Vec2 initialPosition;
	Vec2 velocity;
	const float acceleration = 0.02f;
	float thrust = 0.f;
	//bool isThrusting = false;

	//angular
	float angle=0.f;
	float angleVelocity=0.f;
	const float constAngleAcceleration = 0.001f;
	float angleAccelDirection = 0.f;

};