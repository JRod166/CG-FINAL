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
float bool_it=0;

void nivel_1() {
  //cout<<cont_phase<<endl;
  //creamos unos enmigos de prueba
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
      enemigos.push_back(Enemigo(-350 - i * 20, 125, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 150, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 175, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 200, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 225, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
    }

  }
  else if(level_it >=( phase * 4 + 10) && cont_phase==5) {
    cont_phase++;
    enemigos.clear();
    proyectiles_enemigos.clear();
  }
  else if (level_it >= (phase * 5 ) && cont_phase==6) {
    items.push_back(Item(-200,200,1));
    items.push_back(Item(-100,200,2));
    items.push_back(Item(100,200,3));
    items.push_back(Item(200,200,4));
    cont_phase++;
  }
  else if (level_it >= phase * 6 && cont_phase==7) {
    currently_lvl++;
    cont_phase=0;
    level_it = -delay_time;
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

void nivel_2()
{
  if (level_it == 0 && cont_phase==0) {
    cont_phase++;
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 100, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -5);
      if(i%2==0)
      {
        go_vertical(enemigos[enemigos.size()-1],-1);
      }
    }
    enemigos.push_back(Enemigo(-100, -350,3));
    go_vertical(enemigos[enemigos.size() - 1], 10);
    go_horizontal(enemigos[enemigos.size()-1],3);
    enemigos.push_back(Enemigo(100, -350,4));
    go_vertical(enemigos[enemigos.size() - 1], 10);
    go_horizontal(enemigos[enemigos.size()-1],-3);
  }
  else if(level_it >= phase && cont_phase==1) {
    cont_phase++;
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 100, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 5);
      if(i%2==0)
      {
        go_vertical(enemigos[enemigos.size()-1],-1);
      }
    }
    enemigos.push_back(Enemigo(-100, 350, 3));
    go_vertical(enemigos[enemigos.size() - 1], -10);
    go_horizontal(enemigos[enemigos.size()-1],3);
    enemigos.push_back(Enemigo(100, 350, 4));
    go_horizontal(enemigos[enemigos.size()-1],-3);
    go_vertical(enemigos[enemigos.size() - 1], -10);
  }
  else if(level_it >= phase * 2 && cont_phase==2) {
    cont_phase++;
    gen_meteor_rain(10);
    enemigos.push_back(Enemigo(-100, -350,3));
    go_vertical(enemigos[enemigos.size() - 1], 10);
    go_horizontal(enemigos[enemigos.size()-1],3);
    enemigos.push_back(Enemigo(100, -350,4));
    go_vertical(enemigos[enemigos.size() - 1], 10);
    go_horizontal(enemigos[enemigos.size()-1],-3);
    enemigos.push_back(Enemigo(-100, 350, 3));
    go_vertical(enemigos[enemigos.size() - 1], -10);
    go_horizontal(enemigos[enemigos.size()-1],-3);
    enemigos.push_back(Enemigo(100, 350, 4));
    go_vertical(enemigos[enemigos.size() - 1], -10);
    go_horizontal(enemigos[enemigos.size()-1],3);
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
      if(i%2==0)
      {
        go_vertical(enemigos[enemigos.size()-1],-2);
      }
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 125, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
      if(i%3==0)
      {
        go_vertical(enemigos[enemigos.size()-1],-2);
      }
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 150, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -6);
      if(i%4==0)
      {
        go_vertical(enemigos[enemigos.size()-1],-2);
      }
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 175, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
      if(i%5==0)
      {
        go_vertical(enemigos[enemigos.size()-1],-2);
      }
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(350 + i * 20, 200, 2));
      go_horizontal(enemigos[enemigos.size() - 1], -6);
    }
    for (int i = 0; i < 10; i++) {
      enemigos.push_back(Enemigo(-350 - i * 20, 225, 2));
      go_horizontal(enemigos[enemigos.size() - 1], 6);
    }

  }
  else if(level_it >=( phase * 4 + 10) && cont_phase==5) {
    cont_phase++;
    enemigos.clear();
    proyectiles_enemigos.clear();
  }
  else if (level_it >= (phase * 5 ) && cont_phase==6) {
    items.push_back(Item(-200,200,1));
    items.push_back(Item(-100,200,2));
    items.push_back(Item(100,200,3));
    items.push_back(Item(200,200,4));
    cont_phase++;
  }
  else if (level_it >= phase * 6 && cont_phase==7) {
    currently_lvl++;
    cont_phase=0;
    level_it = -delay_time;
    enemigos.clear();
    return;
  }
  level_it+=delay_time;
}

void nivel_3()
{
  if (level_it == 0 && cont_phase==0) {
    enemigos.push_back(Enemigo(380,100,5));
    go_horizontal(enemigos[0], -5);
    cont_phase++;
  }
  else if(enemigos.size()==0 && level_it>0)
  {
    for(int i=0;i<20;i++)
    {
      items.push_back(Item(rand()%500-250,270+rand()%20,rand()%4+1));
    }
    currently_lvl++;
  }
  else if(level_it >= phase && cont_phase==1) {
    cont_phase++;
    go_horizontal(enemigos[0], 3);
  }
  else if(level_it >= phase * 2 && cont_phase==2) {
    go_zig_zag_hor(enemigos[0],1,-3,5);
    if(level_it >= (phase * 2)+1)
    {
      go_zig_zag_hor(enemigos[0],0,-3,5);
    }
     if(level_it >= (phase * 2)+2)
    {
      go_zig_zag_hor(enemigos[0],1,-3,5);
    }
     if(level_it >= (phase * 2)+3)
    {
      go_zig_zag_hor(enemigos[0],0,-3,5);
    }
     if(level_it >= (phase * 2)+4)
    {
      go_zig_zag_hor(enemigos[0],1,-3,5);
    }
     if(level_it >= (phase * 2)+5)
    {
      go_zig_zag_hor(enemigos[0],0,-3,5);
    }
     if(level_it >= (phase * 2)+6)
    {
      go_zig_zag_hor(enemigos[0],1,-3,5);
      cont_phase++;
    }
  }

  else if(level_it >= phase * 3 && cont_phase==3) {
    go_lap_hor_ver(enemigos[0],20,-20);
    if(level_it >= (phase * 3)+1)
    {
      clear_hash(enemigos[0]);
      go_vertical(enemigos[0],20);
    }
     if(level_it >= (phase * 3)+2)
    {
      clear_hash(enemigos[0]);
    }
     if(level_it >= (phase * 3)+3)
    {
      go_lap_hor_ver(enemigos[0],-20,-20);
    }
     if(level_it >= (phase * 3)+4)
    {
      clear_hash(enemigos[0]);
      go_vertical(enemigos[0],20);
    }
     if(level_it >= (phase * 3)+5)
    {
      clear_hash(enemigos[0]);
    }
     if(level_it >= (phase * 3)+6)
    {
      clear_hash(enemigos[0]);
      go_horizontal(enemigos[0],10);
      cont_phase++;
    }
  }
  else if(level_it >= phase * 4 && cont_phase==4) {
    clear_hash(enemigos[0]);
    if(level_it >= (phase * 4)+1 && bool_it==0)
    {
      bool_it++;
      for(int i=0;i<30;i++)
      {
        proyectiles_enemigos.push_back(Proyectil(-280+i*20,280,2));
      }
    }
     if(level_it >= (phase * 4)+2 && bool_it==1)
    {
      bool_it++;
      for(int i=0;i<30;i++)
      {
        proyectiles_enemigos.push_back(Proyectil(-280+i*20,280,2));
      }
    }
     if(level_it >= (phase * 4)+3 && bool_it==2)
    {
      bool_it++;
      for(int i=0;i<30;i++)
      {
        proyectiles_enemigos.push_back(Proyectil(-280+i*20,280,2));
      }
    }
     if(level_it >= (phase * 4)+4 && bool_it==3)
    {
      bool_it++;
      for(int i=0;i<30;i++)
      {
        proyectiles_enemigos.push_back(Proyectil(-280+i*20,280,4));
      }
    }
     if(level_it >= (phase * 4)+5 && bool_it==4)
    {
      bool_it++;
      for(int i=0;i<30;i++)
      {
        proyectiles_enemigos.push_back(Proyectil(-280+i*20,280,4));
      }
    }
     if(level_it >= (phase * 4)+6 && bool_it==5)
    {
      bool_it++;
      for(int i=0;i<30;i++)
      {
        proyectiles_enemigos.push_back(Proyectil(-280+i*20,280,4));
      }
      cont_phase++;
    }

  }
  else if(level_it >=( phase * 4 + 10) && cont_phase==5) {
    cont_phase++;
    go_vertical(enemigos[0],-10);
  }
  else if (level_it >= (phase * 5 ) && cont_phase==6) {
    cont_phase++;
  }
  else if (level_it >= phase * 6 && cont_phase==7) {
    currently_lvl++;
    cont_phase=0;
    level_it = -delay_time;
    enemigos.clear();
    return;
  }
  level_it+=delay_time;
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
  if (!is_up)
  {
    ver=ver*-1;
  }
  my_enemy.mov_type[1] = ver;
}

void massacre_mode(Enemigo &my_enemy) { /// por corregir
  return;
}
