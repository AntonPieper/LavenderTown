#include "cursor.h"
#include "util/aabb.h"
#include "util/vector.h"

bool cursorInsideBounds(Cursor cursor, AABB bounds) {
	return pointInside(bounds, cursor);
}