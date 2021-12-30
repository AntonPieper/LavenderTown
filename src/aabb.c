#include "aabb.h"

bool intersects(AABB a, AABB b) {
	return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		   (a.min.y <= b.max.y && a.max.y >= b.min.y);
}

bool inside(AABB outer, AABB inner) {
	return (inner.min.x >= outer.min.x && inner.min.y >= outer.min.y) &&
		   (inner.max.x <= outer.max.x && inner.max.y <= outer.max.y);
}

bool pointInside(AABB aabb, Vector2 p) {
	return (p.x <= aabb.max.x && p.x >= aabb.min.x) &&
		   (p.y <= aabb.max.y && p.y >= aabb.min.y);
}