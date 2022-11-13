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

	FILE* file = fopen(BD_SAVEFILE,"w");
	if (file == NULL) {
		printf("Can't create new savefile\n");
		return;
	}

	// b - black checker
	// B - black king checker
	// w - white checker
	// W - white king checker

	const char* content =	
	"x b x b x b x b\n"
	"b x b x b x b x\n"
	"x b x b x b x b\n"
	"x x x x x x x x\n"
	"x x x x x x x x\n"
	"w x w x w x w x\n"
	"x w x w x w x w\n"
	"w x w x w x w x\n"
	"turn: w\n";

	fprintf(file, content);
	fclose(file);

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
				board.piece[y][x] = BD_CHECKER_NONE;
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
	board.winner = BD_CHECKER_NONE;

	fclose(file);

	return true;
}

void BD_Save() {

	FILE* file = fopen(BD_SAVEFILE, "w");

	// Board pieces
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {

			switch (board.piece[y][x]) {
			case BD_CHECKER_NONE: {
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
		board.piece[src_y][src_x] = BD_CHECKER_NONE;
	}
	else {
		board.piece[dst_y][dst_x] = board.piece[src_y][src_x];
		board.piece[(src_y + dst_y) / 2][(src_x + dst_x) / 2] = BD_CHECKER_NONE;
		board.piece[src_y][src_x] = BD_CHECKER_NONE;
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

			if (board.piece[y][x] == BD_CHECKER_NONE) {
				continue;
			}

			unsigned int enemy_team = ((BD_WHITE_TEAM)&board.piece[y][x]) ? (BD_BLACK_TEAM) : (BD_WHITE_TEAM);

			// NE
				// Move
			if ( !(y - 1 < 0 || x + 1 > 7) ) {
				if (board.piece[y - 1][x + 1] == BD_CHECKER_NONE &&
					( (BD_WHITE_TEAM) & board.piece[y][x] || (BD_KINGS) & board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_NE;
				}
			}
				// Strike
			if (!(y - 2 < 0 || x + 2 > 7)) {
				if (board.piece[y - 2][x + 2] == BD_CHECKER_NONE && 
					(enemy_team) & board.piece[y - 1][x + 1]) {
					board.possible_moves[y][x] += BD_STRIKE_NE;
				}
			}

			// NW
				// Move
			if (!(y - 1 < 0 || x - 1 < 0)) {
				if (board.piece[y - 1][x - 1] == BD_CHECKER_NONE &&
					((BD_WHITE_TEAM)&board.piece[y][x] || (BD_KINGS)&board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_NW;
				}
			}
				// Strike
			if (!(y - 2 < 0 || x - 2 < 0)) {
				if (board.piece[y - 2][x - 2] == BD_CHECKER_NONE &&
					(enemy_team)&board.piece[y - 1][x - 1]) {
					board.possible_moves[y][x] += BD_STRIKE_NW;
				}
			}

			// SE
				// Move
			if (!(y + 1 > 7 || x + 1 > 7)) {
				if (board.piece[y + 1][x + 1] == BD_CHECKER_NONE &&
					((BD_BLACK_TEAM)&board.piece[y][x] || (BD_KINGS)&board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_SE;
				}
			}
				// Strike
			if (!(y + 2 > 7 || x + 2 > 7)) {
				if (board.piece[y + 2][x + 2] == BD_CHECKER_NONE &&
					(enemy_team)&board.piece[y + 1][x + 1]) {
					board.possible_moves[y][x] += BD_STRIKE_SE;
				}
			}

			// SW
				// Move
			if (!(y + 1 > 7 || x - 1 < 0)) {
				if (board.piece[y + 1][x - 1] == BD_CHECKER_NONE &&
					((BD_BLACK_TEAM)&board.piece[y][x] || (BD_KINGS)&board.piece[y][x])) {
					board.possible_moves[y][x] += BD_MOVE_SW;
				}
			}
				// Strike
			if (!(y + 2 > 7 || x - 2 < 0)) {
				if (board.piece[y + 2][x - 2] == BD_CHECKER_NONE &&
					(enemy_team)&board.piece[y + 1][x - 1]) {
					board.possible_moves[y][x] += BD_STRIKE_SW;
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
		return BD_STRIKE_NW;
	else if (t_x == 2 && t_y == -2)
		return BD_STRIKE_SW;
	else if (t_x == -2 && t_y == 2)
		return BD_STRIKE_NE;
	else if (t_x == -2 && t_y == -2)
		return BD_STRIKE_SE;
	else
		return 0;

}

