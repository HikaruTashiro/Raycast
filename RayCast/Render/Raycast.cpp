#include "Raycast.hpp"
#include <cmath>
#include <math.h>

// maybe later think of implementing a lookup table, just like the finetan from Doom

void ray_cast(int* wall_size, int (&world_map)[MAP_WIDTH][MAP_HEIGH], const float player_x, const float player_y,
    float angle_direction)
{
    float v_distance = MAXFLOAT, h_distance = MAXFLOAT;
    float x_incr, y_incr;
    float x_first_horizontal, y_first_horizontal;
    float x_first_vertical, y_first_vertical;
    unsigned int block_c, block_r;
    float original_angle = angle_direction;
    float delta_angle;
    angle_direction += (float)(FOV >> 1);
    if (angle_direction > 180.0f)
        angle_direction += -360.0f;

    // std::ofstream test_file("Wallsize.txt");

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        /*HORIZONTAL*/
        if (angle_direction > 0.0f && angle_direction < 180.0f) {
            y_first_horizontal = ((int)(player_y / BLOCK_SIZE)) * BLOCK_SIZE - 1;
            y_incr = -BLOCK_SIZE;
            if (angle_direction > 90.0f) {
                delta_angle = 180.0f - angle_direction;
                x_first_horizontal = -1.0f;
                x_incr = -1.0f;
            } else {
                delta_angle = angle_direction;
                x_first_horizontal = 1.0f;
                x_incr = 1.0f;
            }
        } else {
            y_first_horizontal = ((int)(player_y / BLOCK_SIZE)) * BLOCK_SIZE + BLOCK_SIZE;
            y_incr = BLOCK_SIZE;
            if (angle_direction < -90.0f) {
                delta_angle = angle_direction + 180.0f;
                x_first_horizontal = -1.0f;
                x_incr = -1.0f;
            } else {
                delta_angle = -angle_direction;
                x_first_horizontal = 1.0f;
                x_incr = 1.0f;
            }
        }

        x_incr *= BLOCK_SIZE / tan(delta_angle * TO_RADIANTS);
        x_first_horizontal *= abs(player_y - y_first_horizontal) / std::tan(delta_angle * TO_RADIANTS);
        x_first_horizontal += player_x;
        block_r = (unsigned int)(y_first_horizontal / BLOCK_SIZE);
        block_c = (unsigned int)(x_first_horizontal / BLOCK_SIZE);

        // test_file << "***** Value i --> " << i << " *****" << '\n';
        // test_file << "Horizontal Check\n\n";
        // test_file << "x_incr: " << x_incr << '\n';
        // test_file << "y_incr: " << y_incr << '\n';
        // test_file << "block_c: " << block_c << '\n';
        // test_file << "block_r: " << block_r << '\n';
        // test_file << "x_first_horizontal: " << x_first_horizontal << '\n';
        // test_file << "y_first_horizontal: " << y_first_horizontal << '\n' << '\n';

        while (block_c < MAP_WIDTH && block_r < MAP_HEIGH && !world_map[block_r][block_c]) {
            x_first_horizontal += x_incr;
            y_first_horizontal += y_incr;
            block_r = (unsigned int)(y_first_horizontal / BLOCK_SIZE);
            block_c = (unsigned int)(x_first_horizontal / BLOCK_SIZE);
        }

        /*VERTICAL*/
        if ((angle_direction > -90.0f && angle_direction < 90.0f)) {
            x_first_vertical = ((int)(player_x / BLOCK_SIZE)) * BLOCK_SIZE + BLOCK_SIZE;
            x_incr = BLOCK_SIZE;
            if (angle_direction > 0.0f) {
                y_first_vertical = -1.0f;
                y_incr = -1.0f;
            } else {
                y_first_vertical = 1.0f;
                y_incr = 1.0f;
            }
        } else {
            x_first_vertical = ((int)(player_x / BLOCK_SIZE)) * BLOCK_SIZE - 1;
            x_incr = -BLOCK_SIZE;
            if (angle_direction > 90.0f) {
                y_first_vertical = -1.0f;
                y_incr = -1.0f;
            } else {
                y_first_vertical = 1.0f;
                y_incr = 1.0f;
            }
        }

        y_incr *= BLOCK_SIZE * tan(delta_angle * TO_RADIANTS);
        y_first_vertical *= abs(player_x - x_first_vertical) * std::tan(delta_angle * TO_RADIANTS);
        y_first_vertical += player_y;
        block_r = (unsigned int)(y_first_vertical / BLOCK_SIZE);
        block_c = (unsigned int)(x_first_vertical / BLOCK_SIZE);

        // test_file << "Vertical Check\n\n";
        // test_file << "x_incr: " << x_incr << '\n';
        // test_file << "y_incr: " << y_incr << '\n';
        // test_file << "block_c: " << block_c << '\n';
        // test_file << "block_r: " << block_r << '\n';
        // test_file << "x_first_vertical: " << x_first_vertical << '\n';
        // test_file << "y_first_vertical: " << y_first_vertical << '\n' << '\n';

        while (block_c < MAP_WIDTH && block_r < MAP_HEIGH && !world_map[block_r][block_c]) {
            x_first_vertical += x_incr;
            y_first_vertical += y_incr;
            block_r = (unsigned int)(y_first_vertical / BLOCK_SIZE);
            block_c = (unsigned int)(x_first_vertical / BLOCK_SIZE);
        }

        /*Determine Vertical and Horizontal Distance to Point*/
        v_distance = cos((original_angle - angle_direction) * TO_RADIANTS) * std::sqrt((player_x - x_first_vertical) * (player_x - x_first_vertical) + (player_y - y_first_vertical) * (player_y - y_first_vertical));
        h_distance = cos((original_angle - angle_direction) * TO_RADIANTS) * std::sqrt((player_x - x_first_horizontal) * (player_x - x_first_horizontal) + (player_y - y_first_horizontal) * (player_y - y_first_horizontal));

        // test_file << "Distances:\n";
        // test_file << "v_distance: " << v_distance << '\n';
        // test_file << "h_distance: " << h_distance << '\n';
        // test_file << "--------------------------------\n\n";

        /*Compare Distances*/
        if (v_distance > h_distance)
            wall_size[i] = (BLOCK_SIZE * DISTANCE_TO_SCREEN) / h_distance;
        else
            wall_size[i] = (BLOCK_SIZE * DISTANCE_TO_SCREEN) / v_distance;

        angle_direction -= ANGLE_INCREMENT;
        if (angle_direction < -180.0f)
            angle_direction += 360.0f;
    }

    // test_file.close();
}

void projection_to_screen(GLfloat* vertices, int* wall_size)
{
    int j;
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        j = i * 4;
        vertices[j] = ((float)(i - (SCREEN_WIDTH >> 1))) / (SCREEN_WIDTH >> 1);
        vertices[j + 1] = -floor(wall_size[i] >> 1) / (SCREEN_WIDTH >> 1);
        vertices[j + 2] = ((float)i - (SCREEN_WIDTH >> 1)) / (SCREEN_WIDTH >> 1);
        vertices[j + 3] = floor(wall_size[i] >> 1) / (SCREEN_WIDTH >> 1);
    }
}
