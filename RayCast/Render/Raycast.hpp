#include "../Global.hpp"
#include <GLFW/glfw3.h>

void ray_cast(int *wall_size, int (&world_map)[MAP_WIDTH][MAP_HEIGH], const float player_x, const float player_y,
              float angle_direction);
void projection_to_screen(GLfloat *vertices, int *wall_size);
// float vertical_distance();
// float horizontal_distance();
