#include <string>
#include <windows.h>

#include "BattleCity.h"
#include "funciones.h"

#define shot   110
#define up     119
#define left   97
#define right  100
#define down   115

SuperTank::SuperTank(int _x, int _y, int _vida, char _direccion){
    setX(_x);
    setY(_y);
    setVida(_vida);
    setDireccion(_direccion);
}
//Fata ajustar que no caiga dentro de los obstaculos del mapa.
void SuperTank::setX(int eje_x){
    if(eje_x > 1 && eje_x < 42){
        x = eje_x;
    }else
        x = 1;
}

void SuperTank::setY(int eje_y){
    if(eje_y > 1 && eje_y < 42){
        y = eje_y;
    }else
        y = 1;
}

void SuperTank::setVida(int _vida){
    if(_vida >= 0 && _vida <= 3){
        vida = _vida;
    }
}

void SuperTank::moverCordenadas(char letra){

    switch(letra){
    case up:
        y--;
        break;
    case down:
        y++;
        break;
    case left:
        x--;
        break;
    case right:
        x++;
        break;
    default:
        break;
    }
}

void SuperTank::setDireccion(char tecla){
    if(tecla == up || tecla == right || tecla == down || tecla == left){
        direccion = tecla;
    }
}

void SuperTank::borrar(){
	gotoxy(x, y);   printf ("   ");
	gotoxy(x, y+1); printf ("   ");
	gotoxy(x, y+2); printf ("   ");
}

void SuperTank::explotar(){
    vida--;
    gotoxy(x, y);   printf(" * ");
    gotoxy(x, y+1); printf("***");
    gotoxy(x, y+2); printf(" * ");
    Sleep(200);
    borrar();
    gotoxy(x, y); 	printf("* *");
    gotoxy(x, y+1); printf(" * ");
    gotoxy(x, y+2); printf("* *");
    Sleep(200);
    borrar();
}

void SuperTank::pintarConDireccion(int color){

    switch(this->getDireccion()){
    case up:
        this->pintar(tank_arriba, color);
        break;
    case down:
        this->pintar(tank_abajo, color);
        break;
    case left:
        this->pintar(tank_izquierda, color);
        break;
    case right:
        this->pintar(tank_derecha, color);
        break;
    default:
        break;
    }
}

void SuperTank::pintar(std::vector<string>& matriz, int color){
    int t_fila = 3, t_columna = 3;
    for(int i = 0; i < t_fila; i++){
        for(int j = 0; j < t_columna; j++){

            setColor(color);
            gotoxy(j+x, i+y);
            if(matriz[i][j] == 'A')cout<<char(201);
            if(matriz[i][j] == 'B')cout<<char(200);
            if(matriz[i][j] == 'C')cout<<char(187);
            if(matriz[i][j] == 'D')cout<<char(188);
            if(matriz[i][j] == 'X')cout<<char(205);
            if(matriz[i][j] == 'Y')cout<<char(186);
            if(matriz[i][j] == 'H')cout<<char(254);
            if(matriz[i][j] == 'a')cout<<char(185);
            if(matriz[i][j] == 's')cout<<char(203);
            if(matriz[i][j] == 'w')cout<<char(202);
            if(matriz[i][j] == 'd')cout<<char(204);
        }
        std::cout << std::endl;
    }
}
