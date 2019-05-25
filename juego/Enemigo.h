#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Proyectil.h"

class Enemigo
{
public:
    pair<float,float> centro; //x,y
    int tipo;
    int radio_hitbox;
    int vidas;
    float velocidad;

    Enemigo(float pos_x, float pos_y, int type);
    void mover(int direccion);
    Proyectil disparar();
    void dibujar(int);
};

#endif
