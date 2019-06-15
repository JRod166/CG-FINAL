#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Proyectil.h"

class Enemigo
{
public:
    pair<float,float> centro; //x,y
    pair<float,float> origen;
    int tipo;
    map<int, float> mov_type;/// [0] go_horizontal
                            /// [1] go_vertical
                            /// [2] lap_horizontal
                            /// [3] lap_vertical
    int radio_hitbox;
    int vidas;
    float velocidad;
    float ii;
    float r;
    float s_frecuency;
    int state;
    pair<int,int> e_state;
    Enemigo(float pos_x, float pos_y, int type);
    void mover(pair<float, float> pos_player); //x and y == pos player
    Proyectil disparar();
    void dibujar();
};

#endif
