#include "board.h"

typedef struct Board {
	unsigned int piece[8][8];
	unsigned int turn;
	unsigned int winner;
} Board;

static Board board;

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

void BD_Load() {

	FILE* file = fopen(BD_SAVEFILE, "r");

	// Board pieces
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			
			char buff = fgetc(file);

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
				printf("Wrong savefile format\n");
				return;
			}
			}

			buff = fgetc(file);

			if (buff != ' ' ) {
				
				if (x < 7) {
					printf("Wrong savefile format\n");
					return;
				}
				else if (buff != '\n') {
					printf("Wrong savefile format\n");
					return;
				}

			}

		}

	}

	// Turn
	{
		char string[6];
		fgets(string, 6, file);
		char turn = fgetc(file);
		board.turn = (turn == 'w') ? (BD_WHITE_TEAM) : (BD_BLACK_TEAM);
	}

	// Winner
	board.winner = BD_CHECKER_NONE;

	fclose(file);

}

void BD_Save() {

	FILE* file = fopen(BD_SAVEFILE, "w");

	// Board pieces
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {

			switch (board.piece[y][x]) {
			case BD_CHECKER_NONE: {
				fputc('x',file);
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
				fputc(' ',file);
			}

		}
		fputc('\n',file);
	}

	// Turn
	char turn = (board.turn == (BD_WHITE_TEAM)) ? 'w' : 'b';
	fprintf(file,"turn: %c\n", turn);

	fclose(file);

}

unsigned int BD_GetPiece(int x, int y) {
	return board.piece[y][x];
}

