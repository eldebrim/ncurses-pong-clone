#include "pong.h"
#include "time.h"
#include "math.h"
#include <stdlib.h>


int pad_collision(struct paddle pad, struct pong_ball ball)
{
	if ((ball.y >= pad.y && ball.y <= pad.y + PADDLE_LENGTH) && ball.x == pad.x - 1){
		return TRUE;
	} else {	
		return FALSE;
	}

}




void return_ball(struct paddle pad, struct pong_ball *ball)
{
	if (pad.y == (*ball).y) {
		(*ball).y_velocity = BALL_Y_SPEED;
		(*ball).x_velocity *= -1;
	} else if (pad.y + PADDLE_LENGTH -1 == (*ball).y) {
		(*ball).y_velocity = BALL_Y_SPEED * -1;
		(*ball).x_velocity *= -1;
	} else {
		(*ball).y_velocity = 0;
		(*ball).x_velocity *= -1;
	}
}



void update_score(struct paddle *pad, struct pong_ball *ball, const int max_y, const int max_x)
{ 
	char score_buffer[2];
	(*pad).score++;
	(*ball).x = max_x/2;
	(*ball).y = max_y/2;
	napms(500);
}




int main()
{
	int max_y, max_x, input, score_y, score_x;
	char score_buffer[2];
	struct paddle pad_1, pad_2;
	struct pong_ball ball;
	
	initscr();   	/* Initialize ncurses */ 
	keypad(stdscr, TRUE);	/* Enable keypad */
	noecho(); 	/* Do not echo input */
	nodelay(stdscr, TRUE);	/* No delay in getch() function */
	curs_set(0);  /* hide cursor */
	getmaxyx(stdscr, max_y, max_x);	
	pad_1.y = max_y/2;
	pad_1.x = 2;
	pad_1.score = 0;
	pad_2.y = max_y/2;
	pad_2.x = max_x-2;
	pad_2.score = 0;
	ball.y = max_y/2;
	ball.x = max_x/2;
	ball.y_velocity = BALL_Y_SPEED;
	ball.x_velocity = BALL_X_SPEED;
	score_y = max_y/4;
	score_x = max_x/3;
	//score_win = newwin

	input = wgetch(stdscr);
	while(input != 'q' && (pad_1.score < 10 && pad_2.score < 10)) {
		// User input for paddle movement
		if (input == 'w' && pad_1.y > 0) {
			pad_1.y -= 1;
		} else if(input == 's' && pad_1.y + PADDLE_LENGTH < max_y) {
			pad_1.y += 1;
		} else if (input == KEY_UP && pad_2.y > 0) {
			pad_2.y -= 1;
		} else if(input == KEY_DOWN && pad_2.y + PADDLE_LENGTH < max_y) {
			pad_2.y += 1;
		}
		
		werase(stdscr);
		// check for ball collision with screen borders or paddles
		if (pad_collision(pad_1, ball)) { 
			return_ball(pad_1, &ball);
		} else if (pad_collision(pad_2, ball)) {
			return_ball(pad_2, &ball);
		} else if (ball.y <= 1 || ball.y >= max_y-1) {
			ball.y_velocity *= -1;
		} else if (ball.x <= 0) {
			update_score(&pad_2, &ball, max_y, max_x);
		} else if (ball.x >= max_x) {
			update_score(&pad_1, &ball, max_y, max_x);
		}
	
		napms(40);	/* Wait 40 milliseconds */
		ball.y += ball.y_velocity;
		ball.x += ball.x_velocity;
		mvaddch(ball.y, ball.x, 'o');
		mvwvline(stdscr, pad_1.y, pad_1.x, '|', PADDLE_LENGTH);
		mvwvline(stdscr, pad_2.y, pad_2.x, '|', PADDLE_LENGTH);
		mvwvline(stdscr, 0, max_x/2, '|', max_y);
		sprintf(score_buffer, "%d", pad_1.score);   
		mvwaddstr(stdscr, score_y, score_x, score_buffer);  /* Print pad 1 score */
		sprintf(score_buffer, "%d", pad_2.score);
		mvwaddstr(stdscr, score_y, max_x - score_x, score_buffer);  /* Print pad 2 score */
		wrefresh(stdscr);
		input = wgetch(stdscr);
	}
	endwin();
	return 0;

}
