#ifndef PROYECTIL_H
#define PROYECTIL_H
#include "global_vars.h"

using namespace std;

class Proyectil
{
public:
    pair<float,float> centro; //x,y
    int radio_hitbox;
    int tipo; //determina el movimiento del proyectil
    float velocidad;
    pair<float,float> direccion;
    Proyectil(float x, float y, int type);
    void mover(float, float);
    void dibujar();
};

#endif
