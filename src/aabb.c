#include "aabb.h"

bool intersects(AABB a, AABB b) {
	return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		   (a.min.y <= b.max.y && a.max.y >= b.min.y);
}