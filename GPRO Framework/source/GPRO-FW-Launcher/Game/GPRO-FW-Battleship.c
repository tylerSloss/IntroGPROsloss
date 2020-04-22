
#include <stdio.h>
//#include <string>
#include <stdlib.h>


//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_BATTLESHIP_PLAYERS				2
#define GS_BATTLESHIP_BOARD_WIDTH			10
#define GS_BATTLESHIP_BOARD_HEIGHT			10

enum gs_battleship_space_state
{
	// invalid space state
	gs_battleship_space_invalid = -1,

	// bsStates visible to both players
	gs_battleship_space_open,			// space is open and unguessed
	gs_battleship_space_miss,			// space was guessed and missed
	gs_battleship_space_hit,			// space was guessed and hit

	// bsStates hidden from opponent player
	gs_battleship_space_patrol2,		// 2-unit patrol boat
	gs_battleship_space_submarine3,		// 3-unit submarine
	gs_battleship_space_destroyer3,		// 3-unit destroyer
	gs_battleship_space_battleship4,	// 4-unit battleship
	gs_battleship_space_carrier5,		// 5-unit carrier
};

const char bsStates[8] = { 'O', 'm', 'H', 'P', 'S', 'D', 'B', 'C' };
const int rowTotal = 10;
const char yPositions[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
const char directions[4] = { 'U', 'D', 'L', 'R' };
#ifndef __cplusplus
typedef		enum gs_battleship_space_state	gs_battleship_space_state;
#endif	// !__cplusplus

// battleship game state
typedef		unsigned char					gs_battleship_index;
typedef		gs_battleship_space_state		gs_battleship[GS_BATTLESHIP_PLAYERS][GS_BATTLESHIP_BOARD_WIDTH][GS_BATTLESHIP_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,z,w,h,d)		(x < w && y < h && z < d)
#define GS_BATTLESHIP_VALID(p,x,y)				GS_VALIDATE_COORDINATE(x,y,p,GS_BATTLESHIP_BOARD_WIDTH,GS_BATTLESHIP_BOARD_HEIGHT,GS_BATTLESHIP_PLAYERS)


inline gs_battleship_space_state gs_checkers_getSpaceState(gs_battleship const game, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos]);
	return gs_battleship_space_invalid;
}

inline gs_battleship_space_state gs_checkers_setSpaceState(gs_battleship game, gs_battleship_space_state const state, gs_battleship_index const player, gs_battleship_index const xpos, gs_battleship_index const ypos)
{
	if (GS_BATTLESHIP_VALID(player, xpos, ypos))
		return (game[player][xpos][ypos] = state);
	return gs_battleship_space_invalid;
}

inline gs_battleship_index gs_battleship_reset(gs_battleship game)
{
	gs_battleship_index player, xpos, ypos, total;
	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
				game[player][xpos][ypos] = gs_battleship_space_open;
	total = (player * xpos * ypos);
	return total;
}

inline int gs_battleship_win(gs_battleship game)
{
	int winner = 0;
	int ships;
	gs_battleship_index player, xpos, ypos, total;
	for (player = 0; player < GS_BATTLESHIP_PLAYERS; ++player)
	{
		ships = 0;

		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos) {
			for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos) {
				if (gs_checkers_getSpaceState(game,player,xpos,ypos) > 2) {
					ships++;
				}
			}
		}
		if (ships < 1) {

			winner = player + 1;
		}
	}
		return winner;
	
}

inline void gs_battleship_print_player(gs_battleship game, int nPlayer) //prints for the player's view
{
	gs_battleship_index player, xpos, ypos, total;
	player = nPlayer;
	printf("Your board: \n\n");
	printf("X  0 1 2 3 4 5 6 7 8 9 \n");
	for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
	{
		printf("%c",yPositions[ypos]);
		printf("  ");
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
		{
			printf("%c",bsStates[game[player][xpos][ypos]]);
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

inline void gs_battleship_print_opponent(gs_battleship game, int nPlayer) //prints as the opponent
{
	gs_battleship_index player, xpos, ypos, total;
	player = nPlayer;
	printf("X  0 1 2 3 4 5 6 7 8 9\n");
	for (ypos = 0; ypos < GS_BATTLESHIP_BOARD_HEIGHT; ++ypos)
	{
		printf("%c",yPositions[ypos]);
		printf("  ");
		for (xpos = 0; xpos < GS_BATTLESHIP_BOARD_WIDTH; ++xpos)
		{
			if (game[player][xpos][ypos] > 2)
			{
				printf("%c",bsStates[gs_battleship_space_open]);
			}
			else
			{
				printf("%c",bsStates[game[player][xpos][ypos]]);
			}
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

inline int row_to_int(char row)
{
	int i = 0;
	while (i < rowTotal && yPositions[i] != row)
	{
		i++;
	}
	if (i > rowTotal)
	{
		return 0;
	}
	return i;
}

inline int direction_to_int(char direction)
{
	int i = 0;
	while (i < 4 && directions[i] != direction)
	{
		i++;
	}
	if (i > 4)
	{
		return 0;
	}
	return i;
}

inline void gs_battleship_fire(gs_battleship game, char row, int column, int player)
{
	int rowInt = row_to_int(row);

	if (game[player][column][rowInt] > 2)
	{
		printf("\n Hit at: ");
		printf("%c",row);
		printf("%d",column);
		gs_checkers_setSpaceState(game, gs_battleship_space_hit, player, column, rowInt);
		printf("\n");
	}
	else
	{
		printf("\n Miss at: ");
		printf("%c", row);
		printf("%d", column);
		gs_checkers_setSpaceState(game, gs_battleship_space_miss, player, column, rowInt);
		printf("\n");
	}
}

inline void bsPlayRound(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos = 0, ypos = 'A', total;
	player = nPlayer;
	char debug;
	gs_battleship_print_player(game, player);
	system("pause");
	gs_battleship_print_opponent(game, ((player + 1) % 2));
	system("pause");
	printf("Fire at which row?");
	scanf("%c", &debug);
	scanf("%c", &ypos);
	printf("Fire at which column?");
	int column = 0;
	scanf("%d", &column);
	xpos += column;
	gs_battleship_fire(game, ypos, xpos, ((player + 1) % 2));
}

inline void bsPlayRoundAI(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos, ypos, total;
	player = nPlayer;
	int upper = 9;
	int lower = 0;
	char row = yPositions[(rand() % (upper - lower + 1) + lower)];
	int column = (rand() % (upper - lower + 1) + lower);
	while (gs_checkers_getSpaceState(game, player, column, row_to_int(row)) != gs_battleship_space_open && !gs_checkers_getSpaceState(game, player, column, row_to_int(row)) > 2)
	{
		row = yPositions[(rand() % (upper - lower + 1) + lower)];
		column = (rand() % (upper - lower + 1) + lower);
	}
	gs_battleship_fire(game, row, column, ((player + 1) % 2));
}

inline int verifyPlacement(gs_battleship game, int nPlayer, char nRow, int column, char nDirection, int length)
{
	int parse[2] = { 0, 0 };
	int parseTotal = 0;
	while (parseTotal < length)
	{
		if (game[nPlayer][column + parse[0]][row_to_int(nRow) + parse[1]] != gs_battleship_space_open)
		{
			return 0;
		}
		switch (nDirection)
		{
		case 'U':
			parse[0]--;
			break;
		case 'D':
			parse[0]++;
			break;
		case 'L':
			parse[1]--;
			break;
		default:
			parse[1]++;
		}
		parseTotal++;
	}
	return 1;
}

inline void placeCarrier(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos = 0, ypos = 'A', total;
	int length = 5;
	int inputx = 0;
	char direction = 'D';
	char debug;
	int verify = 0;
	gs_battleship_print_player(game, nPlayer);
	system("pause");
	printf("Start your Carrier at which row? ");
	scanf("%c", &ypos);
	printf("Start your Carrier on which column? ");
	scanf("%d", &inputx);
	scanf("%c", &debug);
	printf("Point your Carrier in which direction? U/D/L/R ");
	scanf("%c", &direction);
	xpos += inputx;
	verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	while (verify == 0)
	{
		printf("Invalid placement, please try again\n");
		system("pause");
		gs_battleship_print_player(game, nPlayer);
		system("pause");
		printf("Start your Carrier at which row? ");
		scanf("%c", &ypos);
		printf("Start your Carrier on which column?");
		scanf("%d", &xpos);
		scanf("%c", &debug);
		printf("Point your Carrier in which direction? U/D/L/R ");
		scanf("%c", &direction);
		xpos += inputx;
		verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	}
	int parse[2] = { 0, 0 };
	int parseTotal = 0;
	while (parseTotal < length)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_carrier5, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		switch (direction)
		{
		case 'U':
			parse[1]--;
			break;
		case 'D':
			parse[1]++;
			break;
		case 'L':
			parse[0]--;
			break;
		default:
			parse[0]++;
		}
		parseTotal++;
	}
}
inline void placeBattleship(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos = 0, ypos = 'A', total;
	int length = 4;
	int inputx = 0;
	char debug;
	char direction = 'D';
	int verify = 0;
	gs_battleship_print_player(game, nPlayer);
	system("pause");
	scanf("%c", &debug);
	printf("Start your Battleship at which row?");
	scanf("%c", &ypos);
	printf("Start your Battleship on which column?");
	scanf("%d", &inputx);
	scanf("%c", &debug);
	printf("Point your Battleship in which direction? U/D/L/R");
	scanf("%c", &direction);
	xpos += inputx;
	verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	while (verify == 0)
	{
		printf("Invalid placement, please try again");
		system("pause");
		scanf("%c", &debug);
		gs_battleship_print_player(game, nPlayer);
		system("pause");
		printf("Start your Battleship at which row?");
		scanf("%c", &ypos);
		printf("Start your Battleship on which column?");
		scanf("%d", &inputx);
		printf("Point your Battleship in which direction? U/D/L/R");
		scanf("%c", &direction);
		xpos += inputx;
		verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	}
	int parse[2] = { 0, 0 };
	int parseTotal = 0;
	while (parseTotal < length)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_battleship4, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		switch (direction)
		{
		case 'U':
			parse[1]--;
			break;
		case 'D':
			parse[1]++;
			break;
		case 'L':
			parse[0]--;
			break;
		default:
			parse[0]++;
		}
		parseTotal++;
	}
}
inline void placeDestroyer(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos = 0, ypos = 'A', total;
	int length = 3;
	int inputx = 0;
	char direction = 'D';
	char debug;
	int verify = 0;
	gs_battleship_print_player(game, nPlayer);
	system("pause");
	scanf("%c", &debug);
	printf("Start your Destroyer at which row?");
	scanf("%c", &ypos);
	printf("Start your Destroyer on which column?");
	scanf("%d", &inputx);
	scanf("%c", &debug);
	printf("Point your Destroyer in which direction? U/D/L/R");
	scanf("%c", &direction);
	xpos += inputx;
	verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	while (verify == 0)
	{
		printf("Invalid placement, please try again");
		system("pause");
		scanf("%c", &debug);
		gs_battleship_print_player(game, nPlayer);
		system("pause");
		printf("Start your Destroyer at which row?");
		scanf("%c", &ypos);
		printf("Start your Destroyer on which column?");
		scanf("%d", &inputx);
		scanf("%c", &debug);
		printf("Point your Destroyer in which direction? U/D/L/R");
		scanf("%c", &direction);
		xpos += inputx;
		verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	}
	int parse[2] = { 0, 0 };
	int parseTotal = 0;
	while (parseTotal < length)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_destroyer3, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		switch (direction)
		{
		case 'U':
			parse[1]--;
			break;
		case 'D':
			parse[1]++;
			break;
		case 'L':
			parse[0]--;
			break;
		default:
			parse[0]++;
		}
		parseTotal++;
	}
}
inline void placeSubmarine(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos = 0, ypos = 'A', total;
	int length = 3;
	int inputx = 0;
	char direction = 'D';
	char debug;
	int verify = 0;
	gs_battleship_print_player(game, nPlayer);
	system("pause");
	scanf("%c", &debug);
	printf("Start your Submarine at which row? ");
	scanf("%c", &ypos);
	printf("Start your Submarine on which column? ");
	scanf("%d", &inputx);
	scanf("%c", &debug);
	printf("Point your Submarine in which direction? U/D/L/R");
	scanf("%c", &direction);
	xpos += inputx;
	verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	while (verify == 0)
	{
		printf("Invalid placement, please try again");
		system("pause");
		gs_battleship_print_player(game, nPlayer);
		system("pause");
		scanf("%c", &debug);
		printf("Start your Submarine at which row? ");
		scanf("%c", &ypos);
		printf("Start your Submarine on which column? ");
		scanf("%d", &inputx);
		scanf("%c", &debug);
		printf("Point your Submarine in which direction? U/D/L/R ");
		scanf("%c", &direction);
		xpos += inputx;
		verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	}
	int parse[2] = { 0, 0 };
	int parseTotal = 0;
	while (parseTotal < length)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_submarine3, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		switch (direction)
		{
		case 'U':
			parse[1]--;
			break;
		case 'D':
			parse[1]++;
			break;
		case 'L':
			parse[0]--;
			break;
		default:
			parse[0]++;
		}
		parseTotal++;
	}
}
inline void placePatrolBoat(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos = 0, ypos = 'A', total;
	int length = 2;
	int inputx = 0;
	char direction = 'D';
	char debug;
	int verify = 0;
	gs_battleship_print_player(game, nPlayer);
	system("pause");
	scanf("%c", &debug);
	printf("Start your Patrol Boat at which row? ");
	scanf("%c", &ypos);
	printf("Start your Patrol Boat on which column? ");
	scanf("%d", &inputx);
	scanf("%c", &debug);
	printf("Point your Patrol Boat in which direction? U/D/L/R");
	scanf("%c", &direction);
	xpos += inputx;
	verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	while (verify == 0)
	{
		printf("Invalid placement, please try again");
		system("pause");
		scanf("%c", &debug);
		gs_battleship_print_player(game, nPlayer);
		system("pause");
		printf("Start your Patrol Boat at which row? ");
		scanf("%c", &ypos);
		printf("Start your Patrol Boat on which column? ");
		scanf("%d", &inputx);
		scanf("%c", &debug);
		printf("Point your Patrol Boat in which direction? U/D/L/R ");
		scanf("%c", &direction);
		xpos += inputx;
		verify = verifyPlacement(game, nPlayer, ypos, xpos, direction, length);
	}
	int parse[2] = { 0, 0 };
	int parseTotal = 0;
	while (parseTotal < length)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_patrol2, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		switch (direction)
		{
		case 'U':
			parse[1]--;
			break;
		case 'D':
			parse[1]++;
			break;
		case 'L':
			parse[0]--;
			break;
		default:
			parse[0]++;
		}
		parseTotal++;
	}
}

inline void buildBoard(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos, ypos, total;
	player = nPlayer;
	placeCarrier(game, nPlayer);
	placeBattleship(game, nPlayer);
	placeDestroyer(game, nPlayer);
	placeSubmarine(game, nPlayer);
	placePatrolBoat(game, nPlayer);

}

inline void buildBoardAI(gs_battleship game, int nPlayer)
{
	gs_battleship_index player, xpos = 6, ypos = 'H', total;
	int parse[2] = { 0, 0 };
	int parseTotal = 0;
	while (parseTotal < 5)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_carrier5, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		parse[1]++;
		parseTotal++;
	}
	parse[1] = 0;
	parseTotal = 0;
	xpos = 6;
	ypos = 'B';
	while (parseTotal < 4)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_battleship4, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		parse[1]++;
		parseTotal++;
	}
	parse[1] = 0;
	parseTotal = 0;
	xpos = 7;
	ypos = 'E';
	while (parseTotal < 3)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_destroyer3, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		parse[1]++;
		parseTotal++;
	}
	parse[1] = 0;
	parseTotal = 0;
	xpos = 3;
	ypos = 'G';
	while (parseTotal < 3)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_submarine3, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		parse[0]++;
		parseTotal++;
	}
	parse[0] = 0;
	parseTotal = 0;
	xpos = 3;
	ypos = 'B';
	while (parseTotal < 2)
	{
		gs_checkers_setSpaceState(game, gs_battleship_space_patrol2, nPlayer, xpos + parse[0], row_to_int(ypos) + parse[1]);
		parse[0]++;
		parseTotal++;
	}

}




//-----------------------------------------------------------------------------
// DEFINITIONS

int launchBattleship()
{
	//int testing = 0;
	gs_battleship game = { 0 };
	gs_battleship_reset(game);
	//printf("%d",testing);
	buildBoard(game, 0);
	buildBoardAI(game, 1);
	int winner = 0;
	while (winner == 0)
	{
		bsPlayRound(game, 0);
		bsPlayRoundAI(game, 1);
		winner = gs_battleship_win(game);
	}
	printf("Player ");
	printf("%d",winner);
	printf(" Wins!\n");


	return 0;
}


//-----------------------------------------------------------------------------
