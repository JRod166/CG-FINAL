#ifndef JUEGO_H
#define JUEGO_H

#include "Player.h"
#include "Enemigo.h"

extern Player *el_jugador;
extern vector<Proyectil> mis_proyectiles;
extern vector<Proyectil> proyectiles_enemigos;
extern vector<Enemigo> enemigos;
extern int currently_lvl;
extern int next_part_time;
extern float np_average_time;
extern long long level_it;

extern void clear_hash(Enemigo &my_enemy);
extern void go_horizontal(Enemigo &my_enemy, float direction);
extern void go_vertical(Enemigo &my_enemy, float direction);
extern void go_lap_hor_ver(Enemigo &my_enemy, float hor, float ver);
extern void go_zig_zag_ver(Enemigo &my_enemy, bool is_right, float hor, float ver);
extern void go_zig_zag_hor(Enemigo &my_enemy, bool is_up, float hor, float ver);
extern void massacre_mode(Enemigo &my_enemy); /// por corregir

extern void nivel_1();

#endif
