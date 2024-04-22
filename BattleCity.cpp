#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>
#include<time.h>
#include<vector>
#include <iostream>

#include "BattleCity.h"
#include "funciones.h"
#include "stages.h"

using namespace std;

#define shot   110
#define up     119
#define left   97
#define right  100
#define down   115



void Tank::setPuntos(int _puntos){
    puntos = _puntos;
}

void Tank::pintar_corazones(){

    gotoxy(30, 1); printf("Salud: ");
    gotoxy(36, 1); printf("       ");

	for(int i = 0; i < getVida(); i++){
		gotoxy(37+i, 1); printf("%c", 3);
    }
}

void Tank::restar_corazones(){
    int vida = getVida();
    vida--;
    setVida(vida);
}

void Tank::pintar_puntos(int score){
	puntos += score;
	gotoxy(44, 2); printf("Puntaje: %d", puntos);
}

//movemos el tanke reconociendo las teclas q se pulsan.
void Tank::mover(){

	if(_kbhit()){
		char tecla = getch();
		setDireccion(tecla);
		borrar();
		switch(tecla){
        case up:
            if(esMovimientoValido(X(), Y()-1) && esMovimientoValido(X()+1, Y()-1) && esMovimientoValido(X()+2, Y()-1)){
                moverCordenadas(tecla);
            }
            break;
        case down:
            if(esMovimientoValido(X(), Y()+3) && esMovimientoValido(X()+1, Y()+3) && esMovimientoValido(X()+2, Y()+3)){
                moverCordenadas(tecla);
            }
            break;
        case left:
            if(esMovimientoValido(X()-1, Y()) && esMovimientoValido(X()-1, Y()+1) && esMovimientoValido(X()-1, Y()+2)){
                moverCordenadas(tecla);
            }
            break;
        case right:
            if(esMovimientoValido(X()+3, Y()) && esMovimientoValido(X()+3, Y()+1) && esMovimientoValido(X()+3, Y()+2)){
                moverCordenadas(tecla);
            }
            break;
        default:
            break;
		}
        pintarConDireccion(4);

        if(tecla == shot) disparar = true;
	}
}

//Metodos de la clase ENEMY!!

int ENEMY::Coord_X_Random(){
    int posicion = random();
    if(posicion == 1)
        return 7;
    else if(posicion == 2 || posicion == 4)
        return 25;
    else
        return 41;
}

//Muevo objetos 'ENEMY' de forma random.
void ENEMY::mover(){

    char sentido = getDireccion();
    pintarConDireccion(7);
	borrar();

    switch(sentido){
        case up:
            if(esMovimientoValido(X(), Y()-1) && esMovimientoValido(X()+1, Y()-1) && esMovimientoValido(X()+2, Y()-1)){
                moverCordenadas(sentido);
            }else{
                setDireccion(direccionRadom(up));
            }
            break;
        case down:
            if(esMovimientoValido(X(), Y()+3) && esMovimientoValido(X()+1, Y()+3) && esMovimientoValido(X()+2, Y()+3)){
                moverCordenadas(sentido);
            }else{
                setDireccion(direccionRadom(up));
            }
            break;
        case left:
            if(esMovimientoValido(X()-1, Y()) && esMovimientoValido(X()-1, Y()+1) && esMovimientoValido(X()-1, Y()+2)){
                moverCordenadas(sentido);
            }else{
                setDireccion(direccionRadom(up));
            }
            break;
        case right:
            if(esMovimientoValido(X()+3, Y()) && esMovimientoValido(X()+3, Y()+1) && esMovimientoValido(X()+3, Y()+2)){
                moverCordenadas(sentido);
            }else{
                setDireccion(direccionRadom(up));
            }
            break;
        default:
            break;
    }
	pintarConDireccion(7);
}
//Valor aleatorio(entre 1 y 4).
int ENEMY::random(){

	return rand()% 4 + 1;
}
//A partir de numeros aleatorios devuelve valores char (UP DOWN RIGHT LEFT) que sirven para redireccionar el tanke
//recibe un parametro (up down left right) que le indica que valor no tiene que devolver
//para que devuelva los cuatro valores de direccion se le pasa 'x' como argumento.
char ENEMY::direccionRadom(char valor){

    int aleatorio;

    if(valor == 'x'){
        aleatorio = random();
        if(aleatorio == 1)
            return up;
        else if(aleatorio == 2)
            return right;
        else if(aleatorio == 3)
            return down;
        else return left;
    }else{
        aleatorio = rand()% 3+1;
        if(valor == up){
            if(aleatorio == 1) return right;
            if(aleatorio == 2) return down;
            if(aleatorio == 3) return left;
        }
        if(valor == right){
            if(aleatorio == 1) return up;
            if(aleatorio == 2) return down;
            if(aleatorio == 3) return left;
        }
        if(valor == down){
            if(aleatorio == 1) return right;
            if(aleatorio == 2) return up;
            if(aleatorio == 3) return left;
        }
        if(valor == left){
            if(aleatorio == 1) return right;
            if(aleatorio == 2) return down;
            if(aleatorio == 3) return up;
        }
    }
}

//implementacion de la clase BALA

bool Bala::fuera(){
	if(esMovimientoValido(x, y)) return false;
	return true;
}
//muevo el objeto BALA.
void Bala::mover(){

		borrar();
		if( tecla == 'w') y--;
		if( tecla == 'd') x++;
		if( tecla == 's') y++;
		if( tecla == 'a') x--;
		gotoxy(x, y); printf("*");
}

void Bala::borrar(){
    gotoxy(x, y); printf(" ");
}
