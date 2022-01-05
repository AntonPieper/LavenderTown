#include "vector.h"

Vector2 multiply(Vector2 a, Vector2 b) {
	return (Vector2){a.x * b.x, a.y * b.y};
}

Vector2 add(Vector2 a, Vector2 b) { return (Vector2){a.x + b.x, a.y + b.y}; }

Vector2 subtract(Vector2 a, Vector2 b) {
	return (Vector2){a.x - b.x, a.y - b.y};
}

Vector2 divide(Vector2 a, Vector2 b) { return (Vector2){a.x / b.x, a.y / b.y}; }

Vector2 modulate(Vector2 a, Vector2 b) {
	return (Vector2){a.x % b.x, a.y % b.y};
}

Vector2 rotate90(Vector2 v) { return (Vector2){v.y, -v.x}; }
Vector2 rotate180(Vector2 v) { return (Vector2){-v.x, -v.y}; }
Vector2 rotate270(Vector2 v) { return (Vector2){-v.y, v.x}; }