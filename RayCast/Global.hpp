#define MAP_WIDTH 24
#define MAP_HEIGH 24
#define BLOCK_SIZE 64
#define FOV 60
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define DISTANCE_TO_SCREEN SCREEN_WIDTH *sqrt(3.0)
// DISTANCE_TO_SCREEN = SCREEN_WIDTH / tangent(FOV / 2)
#define ANGLE_INCREMENT FOV / (float)SCREEN_WIDTH
// ANGLE_INCREMENT = FOV / SCREEN_WIDTH
#define PI 3.14159265358979323846f
#define TO_RADIANTS PI / 180.0f