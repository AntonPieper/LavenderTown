#ifndef SRC_CURSOR_H
#define SRC_CURSOR_H

#include "util/aabb.h"
#include "util/vector.h"

typedef Vector2 Cursor;

///
/// \returns a cursor that is inside the given bounds
///
bool cursorInsideBounds(Cursor cursor, AABB bounds);

#endif // SRC_CURSOR_H