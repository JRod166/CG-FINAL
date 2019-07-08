#include "Player.h"
///PLAYER: Clase que controla al jugador
//Constructor del jugador
Player::Player(float x, float y)
{
    centro.first = x;
    centro.second = y;
    radio_hitbox = 8;
    velocidad = 100;
    vidas = 5;
    score = 0;
    disparo_upgrade = false;
}

//Remueve todas las bonificaciones del jugador, se llama al morir
void Player::reset()
{
    centro.first = 0;
    centro.second = 0;
    radio_hitbox = 8;
    velocidad = 100;
}

//Funcion de movimiento del personaje del jugador
void Player::mover()
{
    float new_pos = 0;
    //Arriba
    if(up_pressed == true)
    {
        new_pos =  centro.second + (velocidad * delay_time);
        if( new_pos < lim_y )
        {
            centro.second = new_pos;
        }
    }
    //Abajo
    if(down_pressed == true)
    {
        new_pos =  centro.second - (velocidad * delay_time);
        if( new_pos > -(lim_y) )
        {
            centro.second = new_pos;
        }
    }
    //Izquierda
    if(left_pressed == true)
    {
        new_pos =  centro.first - (velocidad * delay_time);
        if( new_pos > -(lim_x) )
        {
            centro.first = new_pos;
        }
    }
    //Derecha
    if(right_pressed == true)
    {
        new_pos =  centro.first + (velocidad * delay_time);
        if( new_pos < lim_x )
        {
            centro.first = new_pos;
        }
    }
}

//El jugador dispara municiones
Proyectil Player::disparar()
{
    shoot.play();
    return Proyectil(centro.first,centro.second,1);
}

void Player::dibujar()
{
  glBindTexture(GL_TEXTURE_2D,reimu);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
  glEnable(GL_BLEND);//utilizar transparencia
  float x = centro.first, y = centro.second;
  float top,bottom,left,right;
  left=0.125*(int(reimu_time/250));
  right=0.125+0.125*(int(reimu_time/250));
  glBegin(GL_QUADS);
  switch (reimustate)
  {
    case (0): //static
      top=1;
      bottom=0.666666;
      break;
    case (1): //Shoot
      top=1;
      bottom=0.666666;
      break;
    case (2): //left
      top=0.666666;
      bottom=0.333333;
      break;
    case (3): //right
      top=0.333333;
      bottom=0;
      break;
  }
  glTexCoord2f(right,bottom);
  glVertex3f(x+16, y-18,-1);   //bottom-right
  glTexCoord2f(right,top);
  glVertex3f(x+16, y+18,-1); //top-right
  glTexCoord2f(left,top);
  glVertex3f(x-16, y+18,-1); //top-left
  glTexCoord2f(left,bottom);
  glVertex3f(x-16, y-18,-1); //bottom-left
  glEnd();
  glDisable(GL_BLEND);
}
