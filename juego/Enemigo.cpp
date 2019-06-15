#include "Enemigo.h"

///Enemigo: PLantilla de los enemigos
//Constructor
Enemigo::Enemigo(float x, float y, int type)
{
  centro.first = x;
  centro.second = y;
  origen = centro;
  tipo = type;
  r = 99;
  ii = 0; // ii is the pos of the enemy based on a circle
  if(tipo==2)
  {
    radio_hitbox = 3;
  }
  else if(tipo==3)
  {
    radio_hitbox = 5;
  }
  else if(tipo==4)
  {
    radio_hitbox = 10;
  }
  else if(tipo == 5){
    radio_hitbox = 5;
  }
  vidas = 5;
  velocidad = 15;
}
//El enemigo dispara un proyectil
Proyectil Enemigo::disparar()
{
  //proyectiles_enemigos.push_back(Proyectil(centro.first,centro.second,tipo));
  return Proyectil(centro.first,centro.second,tipo);
}

//Dibujar enemigo
void Enemigo::dibujar()
{
  int state = e_state.first;
  glBindTexture(GL_TEXTURE_2D,fairy);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
  glEnable(GL_BLEND);//utilizar transparencia
  int factor=tipo-1;
  float x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  glTexCoord2f(0.5+0.5*state,0.333333*factor);
  glVertex3f(x+radio_hitbox*3, y-radio_hitbox*3,1); //bottom-right
  glTexCoord2f(0.5+0.5*state,0.333333*(factor+1));
  glVertex3f(x+radio_hitbox*3, y+radio_hitbox*3,1); //top-right
  glTexCoord2f(0+0.5*state,0.333333*(factor+1));
  glVertex3f(x-radio_hitbox*3, y+radio_hitbox*3,1); //top-left
  glTexCoord2f(0+0.5*state,0.333333*factor);
  glVertex3f(x-radio_hitbox*3, y-radio_hitbox*3,1); //bottom-left
  glEnd();
  glDisable(GL_BLEND);
}

///Mover enemigos
void Enemigo::mover(pair<float, float> pos_player) {
  if(mov_type[0] != 0)
  {
    centro.first += mov_type[0] * velocidad * delay_time;
  }
  if (mov_type[1] != 0) {
    centro.second += mov_type[1] * velocidad * delay_time;
  }
  if (mov_type[2] != 0 && mov_type[3] != 0) {
    int num_segments = 360;
    float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
    float x = r * cosf(theta) * mov_type[2];//calculate the x component
    float y = r * sinf(theta) * mov_type[3];//calculate the y component
    centro.first = origen.first + x; // x + 0
    centro.second = origen.second + y; // top looping
    ii+=delay_time*velocidad;

  }

  /* massacre_mode por corregir
  else if(tipo == 5) {
    float dist_x = pos_player.first - centro.first;
    float dist_y = pos_player.second - centro.second;
    float normal = normal_vector( dist_x , dist_y );
    pair<float, float> direccion;
    if( normal > 100) //si esta mas de 20 de distancia, persiguen al jugador
    {
      direccion.first = dist_x;
      direccion.second = dist_y;
      origen = pos_player;

    }
    else //si no, dejan de perseguir y se vuelven de tipo 3
    {
      tipo = 6;
    }
    centro.second = centro.second + (velocidad * direccion.second * delay_time / normal);
    centro.first = centro.first + (velocidad * direccion.first * delay_time / normal);
  }
  else if (tipo == 6) {
    int num_segments = 360;
    float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
    float x = r * cosf(theta);//calculate the x component
    float y = r * sinf(theta);//calculate the y component
    centro.first = origen.first + x; // x + 0
    centro.second += origen.second + y; // top looping
    ii++;
    float dist_x = x - centro.first;
    float dist_y = y - centro.second;
    float normal = normal_vector( dist_x , dist_y );
    if (normal > 100) {
      ii = 0;
      tipo = 5;
    }
  }
  */
}
