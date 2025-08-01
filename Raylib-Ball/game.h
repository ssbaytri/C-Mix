#include <raylib.h>
#include <stdbool.h>

typedef struct
{
    int x;
    int y;
    float size;
    int vel;
} Ball;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} Platform;
