#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

#define VECTOR2_ONE ((Vector2){1, 1})

typedef struct Vector2 {
	int x, y;
} Vector2;

Vector2 multiply(Vector2 a, Vector2 b);

Vector2 add(Vector2 a, Vector2 b);

Vector2 subtract(Vector2 a, Vector2 b);

Vector2 divide(Vector2 a, Vector2 b);

Vector2 modulate(Vector2 a, Vector2 b);

Vector2 rotate90(Vector2 v);
Vector2 rotate180(Vector2 v);
Vector2 rotate270(Vector2 v);

#endif // SRC_VECTOR_H_