#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Proyectil.h"

class Enemigo
{
public:
    pair<float,float> centro; //x,y
    pair<float,float> origen;
    int tipo;
    int radio_hitbox;
    int vidas;
    float velocidad;
    float ii;
    float r;
    int state;
    Enemigo(float pos_x, float pos_y, int type);
    void mover(pair<float, float> pos_player); //x and y == pos player
    Proyectil disparar(float dir_x=0, float dir_y=0);
    void dibujar();
};

#endif
