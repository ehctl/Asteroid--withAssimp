#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"

Component::Component(class Actor* temp)
	:mOwner(temp)
{
	temp->addComponent(this);
}

Component::~Component() {
	mOwner->removeComponent(this);
}
