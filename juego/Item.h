#ifndef ITEM_H
#define ITEM_H

#include "Proyectil.h"

class Item
{
public:
    pair<float,float> centro; //x,y
    int radio_hitbox;
    int tipo;
    float velocidad;

    Item(float pos_x, float pos_y, int type);
    void mover();
    void dibujar();
};

#endif
