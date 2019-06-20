#include "Juego.h"

Player *el_jugador = new Player(0,0);
vector<Proyectil> mis_proyectiles;
vector<Proyectil> proyectiles_enemigos;
vector<Enemigo> enemigos;
int currently_lvl = 1;
float level_it = 0;
long long phase=7;
vector<Item> items;
int cont_phase=0;

void nivel_1() {
  //creamos unos enmigos de prueba
  cout<<level_it<<endl;
  if (level_it == 0 && cont_phase==0) {
    cont_phase++;
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 100, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -5);
    }
    enemigos.push_back(Enemigo(-100, -350,3));
    go_vertical(enemigos[enemigos.size() - 1], 10);
    enemigos.push_back(Enemigo(100, -350,4));
    go_vertical(enemigos[enemigos.size() - 1], 10);
  }
  else if(level_it >= phase && cont_phase==1) {
    cont_phase++;
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 100, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 5);
    }
    enemigos.push_back(Enemigo(-100, 350, 3));
    go_vertical(enemigos[enemigos.size() - 1], -10);
    enemigos.push_back(Enemigo(100, 350, 4));
    go_vertical(enemigos[enemigos.size() - 1], -10);
  }
  else if(level_it >= phase * 2 && cont_phase==2) {
    cont_phase++;
    enemigos.push_back(Enemigo(-100, -350,3));
    go_vertical(enemigos[enemigos.size() - 1], 10);
    enemigos.push_back(Enemigo(100, -350,4));
    go_vertical(enemigos[enemigos.size() - 1], 10);
    enemigos.push_back(Enemigo(-100, 350, 3));
    go_vertical(enemigos[enemigos.size() - 1], -10);
    enemigos.push_back(Enemigo(100, 350, 4));
    go_vertical(enemigos[enemigos.size() - 1], -10);
  }
  else if(level_it >= phase * 3 && cont_phase==3) {
    cont_phase++;
    gen_meteor_rain(20);
  }
  else if(level_it >= phase * 4 && cont_phase==4) {
    cont_phase++;
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 100, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 100, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 150, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 150, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 200, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 200, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
    }

  }
  else if(level_it >=( phase * 4 + 400) && cont_phase==5) {
    cont_phase++;
    enemigos.clear();
    proyectiles_enemigos.clear();
  }
  else if (level_it >= (phase * 5 + 100) && cont_phase==6) {

  }
  else if (level_it >= phase * 10 && cont_phase==7) {
    currently_lvl++;
    level_it = 0;
    enemigos.clear();
    return;
  }
  level_it+=delay_time;
  //cout << "npt: " << next_part_time << " dt: " << delay_time << endl;
  //cout << next_part_time << endl;
  //cout << delay_time << endl;
}
///Funciones generadoras de enemigos
void gen_meteor(pair<float, float> inicio, pair<float, float> final) {
  enemigos.push_back(Enemigo(inicio.first, inicio.second, 10));
  go_horizontal(enemigos[enemigos.size() - 1], (final.first - inicio.first) / 100);
  go_vertical(enemigos[enemigos.size() - 1], (final.second - inicio.second) / 100);
}

void gen_meteor_rain(int meteors) {
  pair<float, float> inicio, final;
  inicio.second = 350;
  final.second = -350;
  srand(0);
  for (int i = 0; i < meteors; i++) {
    inicio.first = rand() % 700 - 350;
    final.second = rand() % 700 - 350;
    gen_meteor(inicio, final);
    inicio.second += 5;
  }
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
