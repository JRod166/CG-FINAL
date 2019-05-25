#include "Player.h"
///PLAYER: Clase que controla al jugador
//Constructor del jugador
Player::Player(float x, float y)
{
    centro.first = x;
    centro.second = y;
    radio_hitbox = 3;
    velocidad = 100;
    vidas = 3;
    score = 0;
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
    return Proyectil(centro.first,centro.second,1);
}

void Player::dibujar()
{
  glBindTexture(GL_TEXTURE_2D,reimu);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
  glEnable(GL_BLEND);//utilizar transparencia
  float x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  switch (reimustate)
  {
    case (0): //static
      glTexCoord2f(0.111111,1-0.186047);
      glVertex3f(x+16, y-18,-1);   //bottom-right
      glTexCoord2f(0.111111,1);
      glVertex3f(x+16, y+18,-1); //top-right
      glTexCoord2f(0,1);
      glVertex3f(x-16, y+18,-1); //top-left
      glTexCoord2f(0,1-0.186047);
      glVertex3f(x-16, y-18,-1); //bottom-left
      break;
    case (1): //Shoot
      glTexCoord2f(0.407407,1-0.186047);
      glVertex3f(x+16, y-18,-1);   //bottom-right
      glTexCoord2f(0.407407,1);
      glVertex3f(x+16, y+18,-1); //top-right
      glTexCoord2f(0.296296,1);
      glVertex3f(x-16, y+18,-1); //top-left
      glTexCoord2f(0.296296,1-0.186047);
      glVertex3f(x-16, y-18,-1); //bottom-left
      break;
    case (2): //left
      glTexCoord2f(0.592593,1-0.372093);
      glVertex3f(x+16, y-18,-1);   //bottom-right
      glTexCoord2f(0.592593,1-0.186047);
      glVertex3f(x+16, y+18,-1); //top-right
      glTexCoord2f(0.50,1-0.186047);
      glVertex3f(x-16, y+18,-1); //top-left
      glTexCoord2f(0.50,1-0.372093);
      glVertex3f(x-16, y-18,-1); //bottom-left
      break;
    case (3): //right
    glTexCoord2f(0.592593,1-0.558140);
    glVertex3f(x+16, y-18,-1);   //bottom-right
    glTexCoord2f(0.592593,1-0.372093);
    glVertex3f(x+16, y+18,-1); //top-right
    glTexCoord2f(0.50,1-0.372093);
    glVertex3f(x-16, y+18,-1); //top-left
    glTexCoord2f(0.50,1-0.558140);
    glVertex3f(x-16, y-18,-1); //bottom-left
      break;
  }
  glEnd();
  glDisable(GL_BLEND);
}
