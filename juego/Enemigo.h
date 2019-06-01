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
    int ii;
    float r;
    Enemigo(float pos_x, float pos_y, int type);
    void mover(float x, float y); //x and y == pos player
    Proyectil disparar();
    void dibujar(int);
};

#endif
