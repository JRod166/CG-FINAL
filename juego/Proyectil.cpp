#include "Proyectil.h"


///PROYECTILES: comportamiento de estos
Proyectil::Proyectil(float x, float y, int type, float dir_x, float dir_y)
{
    centro.first = x;
    centro.second = y;
    tipo = type;
    direccion = make_pair(dir_x,dir_y);
    if(tipo==1) //proyectiles del jugador
    {
      radio_hitbox = 1;
      velocidad = 300;
    }
    else if(tipo==2) //proyectiles de enmigos tipo 2
    {
        radio_hitbox = 1;
        velocidad = 50;
    }
    else if(tipo==3) //proyectiles de enemigos tipo 3
    {
        radio_hitbox = 1;
        velocidad = 100;
    }
    else if (tipo == 4) //proyectiles enemigos de tipo 4
    {
      radio_hitbox = 1;
      velocidad = 150;
    }
    else if (tipo==5)
    {
      radio_hitbox = 3;
      velocidad= 175;
    }
    else if(tipo==10)
    {
      radio_hitbox=100;
      velocidad=50;
    }
}

void Proyectil::mover(float x, float y)
{
  //proyectiles del jugador
  if(tipo==1)
  {
      centro.second += velocidad * delay_time;
  }
  //proyectiles de enmigos de tipo 1
  else if(tipo==2)
  {
      centro.second -= velocidad * delay_time;
  }
  //proyectiles de enemigos de tipo 3
  else if(tipo==3)
  {
      float normal = normal_vector( direccion.first , direccion.second );
      centro.first += velocidad * direccion.first * delay_time / normal;
      centro.second += velocidad * direccion.second * delay_time / normal;
  }
  //proyectiles de enmigos de tipo 4
  else if(tipo == 4 or tipo == 5)
  {
      float dist_x = x - centro.first;
      float dist_y = y - centro.second;
      float normal = normal_vector( dist_x , dist_y );
      if( normal > 30) //si esta mas de 20 de distancia, persiguen al jugador
      {
          direccion.first = dist_x;
          direccion.second = dist_y;
      }
      else //si no, dejan de perseguir y se vuelven de tipo 3
      {
          tipo = 3;
      }
      centro.second = centro.second + (velocidad * direccion.second * delay_time / normal);
      centro.first = centro.first + (velocidad * direccion.first * delay_time / normal);
  }
  else if(tipo==10)
  {
    if(radio_hitbox>1)
    {
      radio_hitbox-=delay_time*100;
    }
    else{
      tipo=1;
    }
  }
}

void Proyectil::dibujar()
{
  glBindTexture(GL_TEXTURE_2D,bullet);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
  glEnable(GL_BLEND);//utilizar transparencia
  float x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  int factor=tipo-1;
  if(tipo>4)
  {
    factor=rand()%4;
  }
  glBegin(GL_QUADS);
  glTexCoord2f(0.25*factor,0);
  glVertex3f(x+radio_hitbox*3, y-radio_hitbox*3,-2); //bottom-right
  glTexCoord2f(0.25*factor,1);
  glVertex3f(x+radio_hitbox*3, y+radio_hitbox*3,-2); //top-right
  glTexCoord2f(0.25*(factor+1),1);
  glVertex3f(x-radio_hitbox*3, y+radio_hitbox*3,-2); //top-left
  glTexCoord2f(0.25*(factor+1),0);
  glVertex3f(x-radio_hitbox*3, y-radio_hitbox*3,-2); //bottom-left
  glEnd();
  glDisable(GL_BLEND);
}
