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

void colisionesTankesBalas(Tank &tankUser, list<ENEMY*> &tankEnemi, list<Bala*> &balaUser, list<Bala*> &balaEnemi);

void moverEnemigos(list<ENEMY*> &enemigos, int cont);
void balasMoverAndFuera(list<Bala*> &balas);


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

        moverEnemigos(E, cont);   //Itera y mueve objetos enemy, recive cont (int) para modificar direccion de objetos enemy.

        //itero lista enemy, disparo si contador es igual a 10.
		for(itE = E.begin(); itE != E.end(); itE++){
			if(cont == 10){ //condicion para que disparen los objetos enemy.
                B_enemy.push_back(new Bala((*itE)->X()+1, (*itE)->Y()+1, (*itE)->getDireccion()));
			}
        }

        if(T.getDisparar()){
            B.push_back(new Bala(T.X()+1, T.Y()+1, T.getDireccion() ));  //creo nuevo obj bala y le doy trayectoria
            T.setDisparar();  //metodo miembro que cambia disparar a false.
        }

        balasMoverAndFuera(B);
        balasMoverAndFuera(B_enemy);

        colisionesTankesBalas(T, E, B, B_enemy);

        for(itB = B.begin(); itB != B.end(); ){

            if(stage_uno[(*itB)->X()][(*itB)->Y()] == 'H'){
                stage_uno[(*itB)->X()][(*itB)->Y()] = '_';
                (*itB)->borrar();
                delete *itB;
                B.remove(*itB);
                break;

			}else{
                itB++;
			}
		}
        //reinicio contador
        if(cont == 13) cont = 0;



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

//funcion que itera listas enemy E, bala B, bala B_enemy y busca colisiones entre estos objetos;
void colisionesTankesBalas(Tank &tankUser, list<ENEMY*> &tankesEnemi, list<Bala*> &balasUser, list<Bala*> &balasEnemi){

    for(auto bala: balasUser){
        for(auto enemi: tankesEnemi){
            if(colision(enemi, bala)){
                enemi->explotar();
                delete enemi;
                tankesEnemi.remove(enemi);

                bala->borrar();
                delete bala;
                balasUser.remove(bala);
                break;
            }
        }
    }
    for(auto bala: balasEnemi){
        if(colision(&tankUser, bala)){
            tankUser.explotar();
            tankUser.restar_corazones();
            //falta logica de reaparicion del objeto tank
            bala->borrar();
            delete bala;
            balasEnemi.remove(bala);
        }
    }
    //se puede buscar colision entre objetos bala pero falta mejorar la logica!
}


//funcion que mueve y cambia direccion de objetos enemy!
void moverEnemigos(list<ENEMY*> &enemigos, int cont){
    for(auto enemigo: enemigos){
        enemigo->mover();
        if(cont == 12)
            enemigo->setDireccion(enemigo->direccionRadom('x'));
    }
}

void balasMoverAndFuera(list<Bala*> &balas){
    for(auto bala: balas){
        bala->mover();
        if(bala->fuera()){
            bala->borrar();
            delete bala; // Eliminar el objeto Bala de la lista B
            balas.remove(bala);
        }
    }
}

