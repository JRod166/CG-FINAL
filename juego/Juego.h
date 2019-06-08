#ifndef JUEGO_H
#define JUEGO_H

#include "Player.h"
#include "Enemigo.h"

extern Player *el_jugador;
extern vector<Proyectil> mis_proyectiles;
extern vector<Proyectil> proyectiles_enemigos;
extern vector<Enemigo> enemigos;
extern int currently_part;
extern int next_part_time;
extern float np_average_time;

extern void nivel_1();

#endif
