#include "vector.h"

Vector2 rotate90(Vector2 v) { return (Vector2){v.y, -v.x}; }
Vector2 rotate180(Vector2 v) { return (Vector2){-v.x, -v.y}; }
Vector2 rotate270(Vector2 v) { return (Vector2){-v.y, v.x}; }