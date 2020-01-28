#pragma once

#include "CircleComponent.h"

CircleComponent::CircleComponent(class Actor* temp)
	:Component(temp)
	,radius(0.0f)
{
	centerPoint.x = temp->GetPosition().x;
	centerPoint.y = temp->GetPosition().y;
}	

bool CircleComponent::Intercept(class CircleComponent* temp) {
	Vector2 x;
	float y;
	x = temp->getCenterPoint() - centerPoint;
	y = temp->getRadius() + radius;

	if (x.Length() >= y) {
		return false;
	}else {
		return true;
	}
}
