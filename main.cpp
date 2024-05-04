#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>
#include<time.h>

#define shot   110
#define up     119
#define left   97
#define right  100
#define down   115

using namespace std;

#include "BattleCity.h"
#include "stages.h"
#include "funciones.h"


template<size_t ROW, size_t COLS>
void pintarMatrizCaracteres(char (&matriz)[ROW][COLS], int color_n);

bool colision(SuperTank* tank, Bala* bala);
bool colisionEntreBalas(Bala* bala_A, Bala* bala_B);
void moverEnemigos(list<ENEMY*> &enemigos, int cont);


//funcion principal.
int main(){
	//declaro variables
	int cont = 0;
	vector<Bala*> deleteBalas; //vector de punteros a objetos bala de la lista B.
	//vector<Bala*> deleteBalasEmy; //vector de punteros a objetos bala de la lista ENEMY.

	srand(time(NULL));

	//ocultarCursor();
    pintarMatrizCaracteres(stage_uno, 3);

	//creo un objeto TANK con coredenadas x, y(int), numero de vidas(int), direccion(char) y puntos(int).
	Tank T(25, 26, 3, up, 0);
    Tank* punteroATank = &T; //puntero a T utilizado para pasar como parametro a funcion colision().

	//creo una lista del objeto 'ENEMY' y su iterador.
	list<ENEMY*> E;
	list<ENEMY*>::iterator itE;

	//creo varios objetos 'ENEMY' con coordenadas x, y(int), vidas(int), direccion(char).
	for(int i = 0; i < 3; i++){
		E.push_back(new ENEMY());
	}

	//creo una lista de la clase 'balas'y su iterador. Solo las usa el usuario
	list<Bala*> B;
	list<Bala*>::iterator itB;

    //iterador balas enemigas
	list<Bala*> B_enemy;
	list<Bala*>::iterator itB_enemy;

	//llamo a la funcion de la clase 'TANK'.
	//T.pintar_corazones();
	T.pintar_puntos(0);
    T.pintarConDireccion(4);
	bool game_over = false;

    T.pintar_puntos(0);

	while(!game_over){

        T.mover();

        moverEnemigos(E, cont);

        //itero lista enemy, disparo si contador es igual a 10, reinicio contador. y busco colision con objeto bala.
		for(itE = E.begin(); itE != E.end(); itE++){
			if(cont == 10){ //condicion para que disparen los objetos enemy.
                B_enemy.push_back(new Bala((*itE)->X()+1, (*itE)->Y()+1, (*itE)->getDireccion()));
			}

            if(B.size() > 0){ //si hay al menos un objeto bala busca la colision con el objeto enemy
                for(itB = B.begin(); itB != B.end(); ){
                    if(colision(*itE, *itB)){

                        (*itE)->explotar();
                        delete *itE;
                        itE = E.erase(itE);

                        T.pintar_puntos(10);

                        deleteBalas.push_back(*itB);
                        break;

                    }else{
                        ++itB;
                    }
                }
            }
		}

        if(T.getDisparar()){
            B.push_back(new Bala(T.X()+1, T.Y()+1, T.getDireccion() ));  //creo nuevo obj bala y le doy trayectoria
            T.setDisparar();  //metodo miembro que cambia disparar a false.
        }
        //muevo cada objeto de la lista Bala
        //si un elemento de la lista BALA llega al limite lo borro y encadeno la lista con el elemento anterior.
        for(itB = B.begin(); itB != B.end(); ){
            (*itB)-> mover();

			if((*itB)->fuera()){
                deleteBalas.push_back(*itB);
			}else
                if(stage_uno[(*itB)->X()][(*itB)->Y()] == 'H'){
                    stage_uno[(*itB)->X()][(*itB)->Y()] = '_';
                    deleteBalas.push_back(*itB);
			}else{
                itB++;
			}
		}

		//muevo cada objeto de la lista B_enemy.
		//itero y busco colicion entre objeto Tank y lista de objetos Bala Enemy (B_enemy) Tambien busco si B_enemy sale fuera.
		for(itB_enemy = B_enemy.begin(); itB_enemy != B_enemy.end(); ){
            (*itB_enemy)->mover();
            if(colision(punteroATank, *itB_enemy) || (*itB_enemy)->fuera()){
                if(colision(punteroATank, *itB_enemy)){
                    T.explotar();
                    //logica posterior a la perdida de vida
                    T.restar_corazones();
                }
                deleteBalas.push_back(*itB_enemy);
                break;

            }else{
                ++itB_enemy;
            }
        }
        if(cont == 13) cont = 0;
		//colicion entre objeto bala y objeto enemy


		//busco colision entre objetos bala
		for(itB = B.begin(); itB != B.end(); ++itB){
            for(itB_enemy = B_enemy.begin(); itB_enemy != B_enemy.end(); ++itB_enemy){
                if(colisionEntreBalas(*itB, *itB_enemy)){

                    deleteBalas.push_back(*itB);
                    deleteBalas.push_back(*itB_enemy);
                    break;
                }
            }
        }

        for (auto it = deleteBalas.begin(); it != deleteBalas.end(); ++it) {
        // Buscar el puntero en la lista B y eliminar el objeto Bala correspondiente
            for (auto itB = B.begin(); itB != B.end(); ++itB) {

                if (*it == *itB) { // Comparar los punteros para encontrar coincidencias
                    (*itB)->borrar();
                    delete *itB; // Eliminar el objeto Bala de la lista B
                    itB = B.erase(itB); // Eliminar el puntero de la lista B y actualizar el iterador
                    break; // Salir del bucle interno
                }
            }
            for (auto itB_enemy = B_enemy.begin(); itB_enemy != B_enemy.end(); ++itB_enemy){
                //(*itB_enemy)->mover();
                if(*it == *itB_enemy){
                    (*itB_enemy)->borrar();
                    delete *itB_enemy;
                    itB_enemy = B_enemy.erase(itB_enemy);
                    break;
                }
            }
        }
        deleteBalas.clear();

        if(E.size() < 3) E.push_back(new ENEMY());
		//incremento el contador q suma los movimientos de objetos 'ENEMY'.
		cont++;

		if(T.getVida() == 0){
            gotoxy(30, 30); printf("GAME OVER");
            game_over = true;
		}
        T.pintar_corazones();
		Sleep(50);
	}
	return 0;
}

template<size_t ROW, size_t COLS>
void pintarMatrizCaracteres(char (&matriz)[ROW][COLS], int color_n){

    for(size_t i = 0; i < ROW; i++){
        for(size_t j = 0; j < COLS; j++){

            gotoxy(j, i);

            setColor(color_n);

            switch(matriz[i][j])
            {
            case 'A':
                std::cout << char(201);
                break;
            case 'B':
                std::cout << char(200);
                break;
            case 'C':
                std::cout << char(187);
                break;
            case 'D':
                std::cout << char(188);
                break;
            case 'X':
                std::cout << char(205);
                break;
            case 'Y':
                std::cout << char(186);
                break;
            case 'H':
                std::cout << char(219);
                break;
            case 'a':
                std::cout << char(185);
                break;
            case 's':
                std::cout << char(203);
                break;
            case 'd':
                std::cout << char(204);
                break;
            case 'w':
                std::cout << char(202);
                break;
            case '_':
                std::cout << char(32);
                break;
            default:
                break;
            }
        }
    }
}

//Funcion que detecta colisiones segun coordenadas x y, acepta objetos Tank o Enemy como primer argumnto
//y objetos Bala como segundo argumento. retorna true o false.
bool colision(SuperTank* tank, Bala* bala){
    int BX = bala->X();
    int BY = bala->Y();
    int TX = tank->X();
    int TY = tank->Y();

    if(BX >= TX && BX <= TX+2 && BY >= TY && BY <= TY+2){
        return true;
    }
    return false;
}

bool colisionEntreBalas(Bala* bala_A, Bala* bala_B){
    int AX = bala_A->X();
    int AY = bala_A->Y();
    int BX = bala_B->X();
    int BY = bala_B->Y();
    //modificar para que se de la colision en casilleros lindantes.
    if(BX == AX && BY == AY){
        return true;
    }
    return false;
}

void moverEnemigos(list<ENEMY*> &enemigos, int cont){
    for(auto enemigo: enemigos){
        enemigo->mover();
        if(cont == 12)
            enemigo->setDireccion(enemigo->direccionRadom('x'));
    }
}

