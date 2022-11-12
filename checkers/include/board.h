#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BD_SAVEFILE "save.txt"

#define BD_CHECKER_NONE 0x00000000u
#define BD_WHITE_CHECKER 0x00000001u
#define BD_BLACK_CHECKER 0x00000002u
#define BD_WHITE_KING_CHECKER 0x00000004u
#define BD_BLACK_KING_CHECKER 0x00000008u

#define BD_WHITE_TEAM BD_WHITE_CHECKER | BD_WHITE_KING_CHECKER
#define BD_BLACK_TEAM BD_BLACK_CHECKER | BD_BLACK_KING_CHECKER

void BD_New();
bool BD_Load();
void BD_Save();
unsigned int BD_GetPiece(int x, int y);