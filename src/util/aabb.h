#ifndef SRC_UTIL_AABB_H
#define SRC_UTIL_AABB_H

#include "util/vector.h"
#include <stdbool.h>

typedef struct AABB {
	Vector2 min, max;
} AABB;

bool intersects(AABB a, AABB b);

bool inside(AABB outer, AABB inner);

bool pointInside(AABB aabb, Vector2 p);

#endif // SRC_UTIL_AABB_H