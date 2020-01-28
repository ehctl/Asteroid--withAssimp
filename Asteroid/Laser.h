#include "Asteroid.h"

class Laser : public Actor {
public:
	Laser(class Game* game,float lifeTime);

	~Laser() {}

	void Update(float deltaTime);

	bool Intercept(class Asteroid* temp);

private: 
	float lifeTime;

};