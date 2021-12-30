#ifndef SRC_AABB_H_
#define SRC_AABB_H_

#include "vector.h"
#include <stdbool.h>

typedef struct AABB {
	Vector2 min, max;
} AABB;

bool intersects(AABB a, AABB b);

bool inside(AABB outer, AABB inner);

bool pointInside(AABB aabb, Vector2 p);

#endif // SRC_AABB_H_