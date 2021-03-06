#ifndef SRC_UTIL_VECTOR_H
#define SRC_UTIL_VECTOR_H

#define VECTOR2_ONE ((Vector2){1, 1})

typedef struct Vector2 {
	int x, y;
} Vector2;

Vector2 rotate90(Vector2 v);
Vector2 rotate180(Vector2 v);
Vector2 rotate270(Vector2 v);

#endif // SRC_UTIL_VECTOR_H