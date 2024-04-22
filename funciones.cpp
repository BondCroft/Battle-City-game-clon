#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include <iostream>

#include "funciones.h"
#include "stages.h"


void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}

void ocultarCursor(){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(hCon, &cci);
}

void setColor(int color){
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),color);
}

bool esMovimientoValido(int x, int y){
    if(stage_uno[y][x] == '_') return true;
    return false;
}
