#include "cursor.h"
#include "aabb.h"
#include "vector.h"

bool cursorInsideBounds(Cursor cursor, AABB bounds) {
	return pointInside(bounds, cursor);
}