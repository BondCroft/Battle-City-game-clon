#ifndef ARCHIVO_FUNCIONES_H
#define ARCHIVO_FUNCIONES_H

#include <windows.h>
// Declaración de la función

void gotoxy(int x, int y);
bool esMovimientoValido(int x, int y);
void ocultarCursor();
void setColor(int color);

#endif
