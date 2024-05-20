#include <iostream>
#include <vector>
#include <string>

#include "funciones.h"

using namespace std;

class SuperTank{
    int x, y;
    int vida;
    char direccion;
    char detener;

    vector<string>tank_arriba = {
       {"AwC"},
       {"YHY"},
       {"BXD"}
    };
    vector<string>tank_abajo = {
       {"AXC"},
       {"YHY"},
       {"BsD"}
    };
    vector<string> tank_derecha = {
       {"AXC"},
       {"YHd"},
       {"BXD"}
    };
    vector<string>tank_izquierda = {
       {"AXC"},
       {"aHY"},
       {"BXD"}
    };

public:
    SuperTank(int _x, int _y, int _vida, char _direccion);

    void setX(int);
    int X(){ return x; }

    void setY(int);
    int Y(){ return y; }

    void setDireccion(char);
    char getDireccion(){ return direccion; }

    void setVida(int);
    int getVida(){ return vida; }

    void setDetener(char);
    char getDetener(){ return detener; }

    void moverCordenadas(char);
    void borrar();
    void pintar(std::vector<string>& matriz, int);
    void explotar();
    void pintarConDireccion(int);

};

class Tank: public SuperTank
{
	int puntos;
	bool disparar;
public:
	Tank(int _x, int _y, int _vida, char _direccion, int _puntos): SuperTank(_x, _y, _vida, _direccion){
        setPuntos(_puntos);
	}
    bool getDisparar(){ return disparar; }
    void setDisparar(){ disparar = false; }
    void setPuntos(int _Puntos);
	void pintar_corazones();
	void restar_corazones();
	void mover();
	void pintar_puntos(int score);
};


class ENEMY: public SuperTank {
public:
	ENEMY(): SuperTank(Coord_X_Random(), 6, 1, direccionRadom('x')){}
	char direccionRadom(char);
	int Coord_X_Random();
	void mover();
	int random();
};


class Bala{
	int x, y;
	char tecla;
public:
	Bala(int _x, int _y, char _tecla): x(_x), y(_y), tecla(_tecla){}
	int X(){ return x; }
	int Y(){ return y; }
	char getTecla(){ return tecla; }
	void borrar();
	void mover();
	bool fuera();
};

