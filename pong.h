

#define BALL_MAX_SPEED 2
#define BALL_X_SPEED 1
#define BALL_Y_SPEED 1
#define PADDLE_LENGTH 4



struct pong_ball{
	unsigned int y; 
	unsigned int x;
	int y_velocity;  // 1 for right, -1 for left
	int x_velocity;
	};


struct paddle{
	unsigned int y;
	unsigned int x;
	unsigned int score;
};


