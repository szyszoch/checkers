#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BD_SAVEFILE "save.txt"

// Types of checkers
#define BD_CHECKER_NONE 0x00000000u
#define BD_WHITE_CHECKER 0x00000001u
#define BD_BLACK_CHECKER 0x00000002u
#define BD_WHITE_KING_CHECKER 0x00000004u
#define BD_BLACK_KING_CHECKER 0x00000008u

#define BD_KINGS BD_WHITE_KING_CHECKER | BD_BLACK_KING_CHECKER
#define BD_WHITE_TEAM BD_WHITE_CHECKER | BD_WHITE_KING_CHECKER
#define BD_BLACK_TEAM BD_BLACK_CHECKER | BD_BLACK_KING_CHECKER

// Types of moves
#define BD_MOVE_NE 0x00000001u
#define BD_MOVE_NW 0x00000002u
#define BD_MOVE_SE 0x00000004u
#define BD_MOVE_SW 0x00000008u

#define BD_CAPTURE_NE 0x00000010u
#define BD_CAPTURE_NW 0x00000020u
#define BD_CAPTURE_SE 0x00000040u
#define BD_CAPTURE_SW 0x00000080u

#define BD_MOVES BD_MOVE_NE | BD_MOVE_NW | BD_MOVE_SE | BD_MOVE_SW
#define BD_CAPTURES BD_CAPTURE_NE | BD_CAPTURE_NW | BD_CAPTURE_SE | BD_CAPTURE_SW

void BD_New();
bool BD_Load();
void BD_Save();
unsigned int BD_GetPiece(int x, int y);
unsigned int BD_GetTurn();
void BD_Move(int src_x, int src_y, int dst_x, int dst_y);
bool BD_IsGameOver();
unsigned int BD_GetWinner();
