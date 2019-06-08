#include "Juego.h"

Player *el_jugador = new Player(0,0);
vector<Proyectil> mis_proyectiles;
vector<Proyectil> proyectiles_enemigos;
vector<Enemigo> enemigos;
int currently_part = 0;
int next_part_time = 0;
float np_average_time = 40;

void nivel_1() {
  //creamos unos enmigos de prueba
  if (next_part_time <= 0) {
    cout << "Secuencia " << currently_part << endl;
    if (currently_part == 0) {
      for (size_t i = 0; i < 10; i++) {
        enemigos.push_back(Enemigo(350 + i * 20, 100, 2));
      }
      enemigos.push_back(Enemigo(-100,250,3));
      enemigos.push_back(Enemigo(100,250,4));
      currently_part++;
      next_part_time = int(np_average_time/delay_time);
    }
    else if (currently_part == 1) {
      for (size_t i = 0; i < 10; i++) {
        enemigos.push_back(Enemigo(-350 - i * 20, 100, 2));
      }
      enemigos.push_back(Enemigo(-100, -100, 3));
      enemigos.push_back(Enemigo(100, -100, 4));
      currently_part++;
      next_part_time = int(np_average_time/delay_time);
    }
    else if (currently_part == 2) {
      enemigos.push_back(Enemigo(-100,250,3));
      enemigos.push_back(Enemigo(100,250,4));
      enemigos.push_back(Enemigo(-100, -100, 3));
      enemigos.push_back(Enemigo(100, -100, 4));
      currently_part++;
      next_part_time = int(np_average_time/delay_time);
    }
  }
  else {
    next_part_time--;
  }
  //cout << "npt: " << next_part_time << " dt: " << delay_time << endl;
  //cout << next_part_time << endl;
  //cout << delay_time << endl;
}
