//Animation Definitions
namespace game{
	#define TIMER_INTERVAL 10
	#define WINDOW_WIDTH 500
	#define WINDOW_HEIGHT 500

	#define ACT_RATE 0.1
	#define DCT_RATE 0.06

	//Map Definitions
	#define LINES 32
	#define COLUMNS 31

	#define WALL_COLOR_R 0.0//1.0
	#define WALL_COLOR_G 0.0//0.68
	#define WALL_COLOR_B 1.0//0.78

	#define FLOOR_COLOR_R 0.20
	#define FLOOR_COLOR_G 0.58
	#define FLOOR_COLOR_B 0.32

	#define GHOST_ZONE_COLOR_R 0.78
	#define GHOST_ZONE_COLOR_G 1.0
	#define GHOST_ZONE_COLOR_B 0.1
		
	#define SCALE_SPHERE 0.2
	#define SPHERE_COLOR_R 0.2
	#define SPHERE_COLOR_G 0.2
	#define SPHERE_COLOR_B 0.2

	#define SCALE_IMORTAL_SPHERE 0.3
	#define IMORTAL_SPHERE_COLOR_R 0.8
	#define IMORTAL_SPHERE_COLOR_G 0.8
	#define IMORTAL_SPHERE_COLOR_B 0.8

	//Pacman Definitions
	#define PACMAN_EYEBROW_COLOR_R 0.0
	#define PACMAN_EYEBROW_COLOR_G 0.0
	#define PACMAN_EYEBROW_COLOR_B 0.0

	#define PACMAN_IRIS_COLOR_R 0.0
	#define PACMAN_IRIS_COLOR_G 0.0
	#define PACMAN_IRIS_COLOR_B 0.0

	#define PACMAN_BODY_COLOR_R 1.0
	#define PACMAN_BODY_COLOR_G 0.78
	#define PACMAN_BODY_COLOR_B 0.1

	#define PACMAN_EYES_COLOR_R 1.0
	#define PACMAN_EYES_COLOR_G 1.0
	#define PACMAN_EYES_COLOR_B 1.0

	#define STATE_DOWN 0
	#define STATE_RIGHT 90
	#define STATE_UP 180
	#define STATE_LEFT 270

	//Ghosts Definitions
	#define GHOST_STATE_NORMAL 0
	#define GHOST_STATE_FRIGHTENED 900
	#define PINKY_JAIL_TIME  400
	#define INKY_JAIL_TIME   800
	#define CLYDE_JAIL_TIME  1200
	#define BLINKY_COLOR_R 1.0
	#define BLINKY_COLOR_G 0.0
	#define BLINKY_COLOR_B 0.0
	#define BLINKY_START_X 14.5
	#define BLINKY_START_Y 20.0

	#define PINKY_COLOR_R 1.0
	#define PINKY_COLOR_G 0.4
	#define PINKY_COLOR_B 0.7
	#define	PINKY_START_X 14.5
	#define PINKY_START_Y 17.0

	#define INKY_COLOR_R 0.0
	#define INKY_COLOR_G 1.0
	#define INKY_COLOR_B 1.0
	#define INKY_START_X 12.30
	#define INKY_START_Y 17.0

	#define CLYDE_COLOR_R 1.0
	#define CLYDE_COLOR_G 0.8
	#define CLYDE_COLOR_B 0.0
	#define CLYDE_START_X 16.70
	#define CLYDE_START_Y 17.0
	
	#define NIGHT 0
	#define DAY	1

	//Particulas do Pacman
	#define PI 3.14159265
	#define MAX_PARTICULAS  10000
	#define frand()			((float)rand()/RAND_MAX)
}