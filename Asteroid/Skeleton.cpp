#include "Skeleton.h"
#include "pugixml.hpp"
#include <fstream>
#include <sstream>
#include "Game.h"

Skeleton::Skeleton(Game* game) {
	game->addSkeleton(this);

}
