
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_TICTACTOE_PLAYERS					2
#define GS_TICTACTOE_BOARD_WIDTH				3
#define GS_TICTACTOE_BOARD_HEIGHT				3

enum gs_tictactoe_space_state
{
	// invalid space state
	gs_tictactoe_space_invalid = -1,

	// states visible to both players
	gs_tictactoe_space_open,	// space is open
	gs_tictactoe_space_o,		// space is taken by O player
	gs_tictactoe_space_x,		// space is taken by X player
};
const char states[8] = { 'A','B','C','D','E','F','G','H' };


#ifndef __cplusplus
typedef		enum gs_tictactoe_space_state		gs_tictactoe_space_state;
#endif	// !__cplusplus

// tic-tac-toe game state
typedef		unsigned char						gs_tictactoe_index;
typedef		gs_tictactoe_space_state			gs_tictactoe[GS_TICTACTOE_BOARD_WIDTH][GS_TICTACTOE_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_TICTACTOE_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_TICTACTOE_BOARD_WIDTH,GS_TICTACTOE_BOARD_HEIGHT)


inline gs_tictactoe_space_state gs_tictactoe_getSpaceState(gs_tictactoe const game, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_space_state gs_tictactoe_setSpaceState(gs_tictactoe game, gs_tictactoe_space_state const state, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_index gs_tictactoe_reset(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_tictactoe_space_open;
	total = (xpos * ypos);
	return total;
}

inline void gs_tictactoe_display(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos;
	printf("X 1 2 3 4 5");
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
	{
		printf("\n");
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
		{	
			//printf(states[game[xpos][ypos]]);
			printf("| ");
		}
	//printf("\n");
	}
	printf("\n");
}

inline void playRound(gs_tictactoe game)
{
	int inputx,inputy;
	gs_tictactoe_index xpos, ypos; 
	gs_tictactoe_display(game);
	//printf("\n");
	printf("Choose a row: 0 = top row, 1 = middle row and 2 = bottom row: ");
	scanf("%d", &inputx);
	printf("Choose a column: 0 = left, 1 = middle and 2 = right: ");
	scanf("%d", &inputy);
	xpos = inputx;
	ypos = inputy;
	gs_tictactoe_getSpaceState(game, xpos, ypos);
	if (gs_tictactoe_getSpaceState(game, xpos, ypos) == gs_tictactoe_space_invalid)
		printf("Invalid location");
	while (gs_tictactoe_getSpaceState(game, xpos, ypos) == gs_tictactoe_space_invalid) {
		printf("\n");
		printf("Choose a row: 0 = top row, 1 = middle row and 2 = bottom row: ");
		scanf("%d", &inputx);
		printf("Choose a column: 0 = left, 1 = middle and 2 = right: ");
		scanf("%d", &inputy);
		xpos = inputx;
		ypos = inputy;
		gs_tictactoe_getSpaceState(game, xpos, ypos);
		if (gs_tictactoe_getSpaceState(game, xpos, ypos) == gs_tictactoe_space_invalid)
			printf("Invalid location");
	}
	gs_tictactoe_setSpaceState(game, gs_tictactoe_space_x, xpos, ypos);
	//gs_tictactoe_display(game);
}
inline void playAI(gs_tictactoe game)
{
	int randomx, randomy;
	gs_tictactoe_index xpos, ypos;
	randomx = rand() % 3;
	randomy = rand() % 3;
	xpos = randomx;
	ypos = randomy;
	while (gs_tictactoe_getSpaceState(game, xpos, ypos) == gs_tictactoe_space_invalid) {
		randomx = rand() % 3;
		randomy = rand() % 3;
		xpos = randomx;
		ypos = randomy;
	}
	gs_tictactoe_setSpaceState(game, gs_tictactoe_space_x, randomx, randomy);

}

inline int gs_tictactoe_result(gs_tictactoe game)
{

}
//-----------------------------------------------------------------------------
// DEFINITIONS

int launchTicTacToe()
{
	time_t t;
	srand((unsigned) time(&t));
	gs_tictactoe game = { 0 };
	gs_tictactoe_reset(game);
	int result = 0;
	
	while (result < 1)
	{
		//gs_tictactoe_display(game);
		playRound(game);
		playAI(game);
		gs_tictactoe_display(game);
		//result = 1;

	}

	return 0;
}



//-----------------------------------------------------------------------------
