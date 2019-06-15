#include "Juego.h"

Player *el_jugador = new Player(0,0);
vector<Proyectil> mis_proyectiles;
vector<Proyectil> proyectiles_enemigos;
vector<Enemigo> enemigos;
int currently_lvl = 1;
long long level_it = 0;

void nivel_1() {
  //creamos unos enmigos de prueba
  if (currently_lvl == 1) {
    if (level_it == 0) {
      for (size_t i = 0; i < 10; i++) {
        enemigos.push_back(Enemigo(350 + i * 20, 100, 2));
        go_horizontal(enemigos[enemigos.size() - 1], -7);
      }
      enemigos.push_back(Enemigo(-100, -350,3));
      go_vertical(enemigos[enemigos.size() - 1], 10);
      enemigos.push_back(Enemigo(100, -350,4));
      go_vertical(enemigos[enemigos.size() - 1], 10);
    }
    else if(level_it == 210) {
      for (size_t i = 0; i < 10; i++) {
        enemigos.push_back(Enemigo(-350 - i * 20, 100, 2));
        go_horizontal(enemigos[enemigos.size() - 1], 7);
      }
      enemigos.push_back(Enemigo(-100, 350, 3));
      go_vertical(enemigos[enemigos.size() - 1], -10);
      enemigos.push_back(Enemigo(100, 350, 4));
      go_vertical(enemigos[enemigos.size() - 1], -10);
    }
    else if(level_it == 500) {
      enemigos.push_back(Enemigo(-100, -350,3));
      go_vertical(enemigos[enemigos.size() - 1], 10);
      enemigos.push_back(Enemigo(100, -350,4));
      go_vertical(enemigos[enemigos.size() - 1], 10);
      enemigos.push_back(Enemigo(-100, 350, 3));
      go_vertical(enemigos[enemigos.size() - 1], -10);
      enemigos.push_back(Enemigo(100, 350, 4));
      go_vertical(enemigos[enemigos.size() - 1], -10);
    }
    else if(level_it == 700) {

    }
    else if(level_it == 1000) {

    }
    else if(level_it == 2950) {
      enemigos.clear();
    }
    else if (level_it == 3000) {

    }
    else if (level_it == 3600) {
      currently_lvl++;
      enemigos.clear();
    }
    level_it++;
  }
  //cout << "npt: " << next_part_time << " dt: " << delay_time << endl;
  //cout << next_part_time << endl;
  //cout << delay_time << endl;
}

////enemy default functions
void clear_hash(Enemigo &my_enemy) {
  for (int i = 0; i < 10; i++) {
    my_enemy.mov_type[i] = 0;
  }
  return;
}
void go_horizontal(Enemigo &my_enemy, float direction) {
  my_enemy.mov_type[0] = direction;
}

void go_vertical(Enemigo &my_enemy, float direction) {
  my_enemy.mov_type[1] = direction;
}

void go_lap_hor_ver(Enemigo &my_enemy, float hor, float ver) {
  my_enemy.mov_type[0] = hor;
  my_enemy.mov_type[1] = ver;
}

void go_zig_zag_ver(Enemigo &my_enemy, bool is_right, float hor, float ver) {
  my_enemy.mov_type[0] = hor * is_right;
  my_enemy.mov_type[1] = ver;
}

void go_zig_zag_hor(Enemigo &my_enemy, bool is_up, float hor, float ver) {
  my_enemy.mov_type[0] = hor;
  my_enemy.mov_type[1] = ver * is_up;
}

void massacre_mode(Enemigo &my_enemy) { /// por corregir
  return;
}
