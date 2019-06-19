#ifndef PLAYER_H
#define PLAYER_H

#include "Proyectil.h"

class Player
{
public:
    pair<float,float> centro; //x,y
    int radio_hitbox;
    int vidas;
    int score;
    float velocidad;
    bool disparo_upgrade;

    Player(float pos_x, float pos_y);
    void reset();
    void mover();
    Proyectil disparar();
    void dibujar();
};

#endif