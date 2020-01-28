#pragma once

#include "Component.h"
#include "Actor.h"

class CircleComponent : public Component {
public:
	CircleComponent(class Actor* temp);

	void setCenterPoint(Vector2* temp);

	void setRadius(float temp) { radius = temp; }

	Vector2 getCenterPoint() { return centerPoint; }

	float getRadius() { return radius; }

	bool Intercept(class CircleComponent* temp);

private:
	Vector2 centerPoint;
	float radius;

};