#include "../Global.hpp"
#include "../World.cpp"
#include <GLFW/glfw3.h>

class Walls
{
    int wall_height[SCREEN_WIDTH];
    GLfloat vertices[4 * SCREEN_WIDTH];

  public:
    void ray_cast();
};
