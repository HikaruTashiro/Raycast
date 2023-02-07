#include <GLFW/glfw3.h>
#include "../Global.h"
#include "../World.cpp"

class Walls
{
    int wall_height[SCREEN_WIDTH];
    GLfloat vertices[4 * SCREEN_WIDTH];
    public:
        void ray_cast();
};
