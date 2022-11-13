#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BD_SAVEFILE "save.txt"

void BD_New();
bool BD_Load();
void BD_Save();
unsigned int BD_GetPiece(int x, int y);
void BD_Move(int src_x, int src_y, int dst_x, int dst_y);
