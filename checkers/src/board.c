#include "board.h"

typedef struct Board {
	unsigned int piece[8][8];
	unsigned int possible_moves[8][8];
	unsigned int turn;
	unsigned int winner;
} Board;

static Board board;

// ===================

void BD_CheckPossibleMoves();
unsigned int BD_CheckMoveType(int src_x, int src_y, int dst_x, int dst_y);

// ===================

void BD_New() {

	board.turn = BD_WHITE_TEAM;
	board.winner = BD_NONE_CHECKER;

	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++)
			board.possible_moves[y][x] = 0;

	// row 1
	board.piece[0][0] = BD_NONE_CHECKER;
	board.piece[0][1] = BD_BLACK_CHECKER;
	board.piece[0][2] = BD_NONE_CHECKER;
	board.piece[0][3] = BD_BLACK_CHECKER;
	board.piece[0][4] = BD_NONE_CHECKER;
	board.piece[0][5] = BD_BLACK_CHECKER;
	board.piece[0][6] = BD_NONE_CHECKER;
	board.piece[0][7] = BD_BLACK_CHECKER;

	// row 2
	board.piece[1][0] = BD_BLACK_CHECKER;
	board.piece[1][1] = BD_NONE_CHECKER;
	board.piece[1][2] = BD_BLACK_CHECKER;
	board.piece[1][3] = BD_NONE_CHECKER;
	board.piece[1][4] = BD_BLACK_CHECKER;
	board.piece[1][5] = BD_NONE_CHECKER;
	board.piece[1][6] = BD_BLACK_CHECKER;
	board.piece[1][7] = BD_NONE_CHECKER;

	// row 3
	board.piece[2][0] = BD_NONE_CHECKER;
	board.piece[2][1] = BD_BLACK_CHECKER;
	board.piece[2][2] = BD_NONE_CHECKER;
	board.piece[2][3] = BD_BLACK_CHECKER;
	board.piece[2][4] = BD_NONE_CHECKER;
	board.piece[2][5] = BD_BLACK_CHECKER;
	board.piece[2][6] = BD_NONE_CHECKER;
	board.piece[2][7] = BD_BLACK_CHECKER;

	// row 4
	board.piece[3][0] = BD_NONE_CHECKER;
	board.piece[3][1] = BD_NONE_CHECKER;
	board.piece[3][2] = BD_NONE_CHECKER;
	board.piece[3][3] = BD_NONE_CHECKER;
	board.piece[3][4] = BD_NONE_CHECKER;
	board.piece[3][5] = BD_NONE_CHECKER;
	board.piece[3][6] = BD_NONE_CHECKER;
	board.piece[3][7] = BD_NONE_CHECKER;

	// row 5
	board.piece[4][0] = BD_NONE_CHECKER;
	board.piece[4][1] = BD_NONE_CHECKER;
	board.piece[4][2] = BD_NONE_CHECKER;
	board.piece[4][3] = BD_NONE_CHECKER;
	board.piece[4][4] = BD_NONE_CHECKER;
	board.piece[4][5] = BD_NONE_CHECKER;
	board.piece[4][6] = BD_NONE_CHECKER;
	board.piece[4][7] = BD_NONE_CHECKER;

	// row 6
	board.piece[5][0] = BD_WHITE_CHECKER;
	board.piece[5][1] = BD_NONE_CHECKER;
	board.piece[5][2] = BD_WHITE_CHECKER;
	board.piece[5][3] = BD_NONE_CHECKER;
	board.piece[5][4] = BD_WHITE_CHECKER;
	board.piece[5][5] = BD_NONE_CHECKER;
	board.piece[5][6] = BD_WHITE_CHECKER;
	board.piece[5][7] = BD_NONE_CHECKER;

	// row 7
	board.piece[6][0] = BD_NONE_CHECKER;
	board.piece[6][1] = BD_WHITE_CHECKER;
	board.piece[6][2] = BD_NONE_CHECKER;
	board.piece[6][3] = BD_WHITE_CHECKER;
	board.piece[6][4] = BD_NONE_CHECKER;
	board.piece[6][5] = BD_WHITE_CHECKER;
	board.piece[6][6] = BD_NONE_CHECKER;
	board.piece[6][7] = BD_WHITE_CHECKER;

	// row 8
	board.piece[7][0] = BD_WHITE_CHECKER;
	board.piece[7][1] = BD_NONE_CHECKER;
	board.piece[7][2] = BD_WHITE_CHECKER;
	board.piece[7][3] = BD_NONE_CHECKER;
	board.piece[7][4] = BD_WHITE_CHECKER;
	board.piece[7][5] = BD_NONE_CHECKER;
	board.piece[7][6] = BD_WHITE_CHECKER;
	board.piece[7][7] = BD_NONE_CHECKER;

}

bool BD_Load() {

	FILE* file = fopen(BD_SAVEFILE, "r");

	if (file == NULL) {
		return false;
	}

	// Board pieces
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			
			char buff = fgetc(file);

			if ( (y % 2 == 0 && x % 2 == 0) || (x % 2 == 1 && y % 2 == 1) ) {
				if (buff != 'x') {
					printf("save.txt:%d:%d Wrong savefile format. Colored fields must be empty\n", y, x * 2);
					return false;
				}
			}

			switch (buff) {
			case 'w': {
				board.piece[y][x] = BD_WHITE_CHECKER;
				break;
			}
			case 'W': {
				board.piece[y][x] = BD_WHITE_KING_CHECKER;
				break;
			}
			case 'b': {
				board.piece[y][x] = BD_BLACK_CHECKER;
				break;
			}
			case 'B': {
				board.piece[y][x] = BD_BLACK_KING_CHECKER;
				break;
			}
			case 'x': {
				board.piece[y][x] = BD_NONE_CHECKER;
				break;
			}
			default: {
				printf(
				"save.txt:%d:%d Wrong savefile format. Possible charackters are:\n"
				"'w' - white checker\n"
				"'W' - white king checker\n"
				"'b' - black checker\n"
				"'B' - black king checker\n"
				"'x' - empty field\n",y,x*2);
				return false;
			}
			}

			buff = fgetc(file);

			if (buff != ' ' ) {
				
				if (x < 7) {
					printf("save.txt:%d:%d Wrong savefile format\n", y, x * 2+1);
					return false;
				}
				else if (buff != '\n') {
					printf("save.txt:%d:%d Wrong savefile format\n", y, x * 2+1);
					return false;
				}

			}

		}

	}

// Turn
	{
	char string[7];
	fgets(string, 7, file);
	char turn = fgetc(file);
	board.turn = (turn == 'w') ? (BD_WHITE_TEAM) : (BD_BLACK_TEAM);
	}

	// Winner
	board.winner = BD_NONE_CHECKER;

	fclose(file);

	return true;
}

void BD_Save() {

	FILE* file = fopen(BD_SAVEFILE, "w");

	// Board pieces
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {

			switch (board.piece[y][x]) {
			case BD_NONE_CHECKER: {
				fputc('x', file);
				break;
			}
			case BD_WHITE_CHECKER: {
				fputc('w', file);
				break;
			}
			case BD_BLACK_CHECKER: {
				fputc('b', file);
				break;
			}
			case BD_WHITE_KING_CHECKER: {
				fputc('W', file);
				break;
			}
			case BD_BLACK_KING_CHECKER: {
				fputc('B', file);
				break;
			}
			}

			if (x < 7) {
				fputc(' ', file);
			}

		}
		fputc('\n', file);
	}

	// Turn
	char turn = (board.turn == (BD_WHITE_TEAM)) ? 'w' : 'b';
	fprintf(file, "turn: %c\n", turn);

	fclose(file);

}

unsigned int BD_GetPiece(int x, int y) {
	return board.piece[y][x];
}

unsigned int BD_GetTurn() {
	return board.turn;
}

void BD_Move(int src_x, int src_y, int dst_x, int dst_y) {

	BD_CheckPossibleMoves();

	if (src_x < 0 || src_x > 7 || src_y < 0 || src_y > 7
		|| dst_x < 0 || dst_x > 7 || dst_y < 0 || dst_y > 7) {
		return;
	}

	if (!((board.turn) & board.piece[src_y][src_x])) {
		return;
	}

	int move_type = BD_CheckMoveType(src_x, src_y, dst_x, dst_y);

	if (!((board.possible_moves[src_y][src_x]) & move_type)) {
		return;
	}

	if ((BD_MOVES)&move_type) {
		board.piece[dst_y][dst_x] = board.piece[src_y][src_x];
		board.piece[src_y][src_x] = BD_NONE_CHECKER;
	}
	else {
		board.piece[dst_y][dst_x] = board.piece[src_y][src_x];
		board.piece[(src_y + dst_y) / 2][(src_x + dst_x) / 2] = BD_NONE_CHECKER;
		board.piece[src_y][src_x] = BD_NONE_CHECKER;
	}

	if ( (BD_WHITE_TEAM)&board.piece[dst_y][dst_x] && dst_y == 0 ) {
		board.piece[dst_y][dst_x] = BD_WHITE_KING_CHECKER;
	}
	else if ((BD_BLACK_TEAM)&board.piece[dst_y][dst_x] && dst_y == 7) {
		board.piece[dst_y][dst_x] = BD_BLACK_KING_CHECKER;
	}

	board.turn = (board.turn == (BD_WHITE_TEAM)) ? (BD_BLACK_TEAM) : (BD_WHITE_TEAM);

}

bool BD_IsGameOver() {

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ( (board.turn) & board.piece[y][x] && board.possible_moves[y][x] > 0) {
				return false;
			}
		}
	}

	board.winner = ((board.turn) == (BD_WHITE_TEAM)) ? (BD_BLACK_TEAM) : (BD_WHITE_TEAM);

	return true;

}

unsigned int BD_GetWinner() {
	return board.winner;
}

// ===================

void BD_CheckPossibleMoves() {

	// Reset
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			board.possible_moves[y][x] = 0;
		}
	}

	for (int y = 0; y < 8; y++) {

		for (int x = 0; x < 8; x++) {

			if (board.piece[y][x] == BD_NONE_CHECKER) {
				continue;
			}

			unsigned int enemy_team = ((BD_WHITE_TEAM)&board.piece[y][x]) ? (BD_BLACK_TEAM) : (BD_WHITE_TEAM);

			// NE
				// Move
			if ( !(y - 1 < 0 || x + 1 > 7) ) {
				if (board.piece[y - 1][x + 1] == BD_NONE_CHECKER &&
					( (BD_WHITE_TEAM) & board.piece[y][x] || (BD_KINGS) & board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_NE;
				}
			}
				// Capture
			if (!(y - 2 < 0 || x + 2 > 7)) {
				if (board.piece[y - 2][x + 2] == BD_NONE_CHECKER && 
					(enemy_team) & board.piece[y - 1][x + 1]) {
					board.possible_moves[y][x] += BD_CAPTURE_NE;
				}
			}

			// NW
				// Move
			if (!(y - 1 < 0 || x - 1 < 0)) {
				if (board.piece[y - 1][x - 1] == BD_NONE_CHECKER &&
					((BD_WHITE_TEAM)&board.piece[y][x] || (BD_KINGS)&board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_NW;
				}
			}
				// Capture
			if (!(y - 2 < 0 || x - 2 < 0)) {
				if (board.piece[y - 2][x - 2] == BD_NONE_CHECKER &&
					(enemy_team)&board.piece[y - 1][x - 1]) {
					board.possible_moves[y][x] += BD_CAPTURE_NW;
				}
			}

			// SE
				// Move
			if (!(y + 1 > 7 || x + 1 > 7)) {
				if (board.piece[y + 1][x + 1] == BD_NONE_CHECKER &&
					((BD_BLACK_TEAM)&board.piece[y][x] || (BD_KINGS)&board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_SE;
				}
			}
				// Capture
			if (!(y + 2 > 7 || x + 2 > 7)) {
				if (board.piece[y + 2][x + 2] == BD_NONE_CHECKER &&
					(enemy_team)&board.piece[y + 1][x + 1]) {
					board.possible_moves[y][x] += BD_CAPTURE_SE;
				}
			}

			// SW
				// Move
			if (!(y + 1 > 7 || x - 1 < 0)) {
				if (board.piece[y + 1][x - 1] == BD_NONE_CHECKER &&
					((BD_BLACK_TEAM)&board.piece[y][x] || (BD_KINGS)&board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_SW;
				}
			}
				// Capture
			if (!(y + 2 > 7 || x - 2 < 0)) {
				if (board.piece[y + 2][x - 2] == BD_NONE_CHECKER &&
					(enemy_team)&board.piece[y + 1][x - 1]) {
					board.possible_moves[y][x] += BD_CAPTURE_SW;
				}
			}

		}

	}

}

unsigned int BD_CheckMoveType(int src_x, int src_y, int dst_x, int dst_y) {
	
	int t_x = src_x - dst_x;
	int t_y = src_y - dst_y;

	if (t_x == 1 && t_y == 1)
		return BD_MOVE_NW;
	else if (t_x == 1 && t_y == -1)
		return BD_MOVE_SW;
	else if (t_x == -1 && t_y == 1)
		return BD_MOVE_NE;
	else if (t_x == -1 && t_y == -1)
		return BD_MOVE_SE;
	else if (t_x == 2 && t_y == 2)
		return BD_CAPTURE_NW;
	else if (t_x == 2 && t_y == -2)
		return BD_CAPTURE_SW;
	else if (t_x == -2 && t_y == 2)
		return BD_CAPTURE_NE;
	else if (t_x == -2 && t_y == -2)
		return BD_CAPTURE_SE;
	else
		return 0;

}

