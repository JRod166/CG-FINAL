#include "Enemigo.h"


///Enemigo: PLantilla de los enemigos
//Constructor
Enemigo::Enemigo(float x, float y, int type)
{
    centro.first = x;
    centro.second = y;
    tipo = type;
    if(tipo==2)
    {
        radio_hitbox = 3;
        velocidad = 50;
        vidas = 1;
    }
    else if(tipo==3)
    {
        radio_hitbox = 5;
        velocidad = 50;
        vidas = 2;
    }
    else if(tipo==4)
    {
        radio_hitbox = 10;
        velocidad = 50;
        vidas = 3;
    }

}
//El enemigo dispara un proyectil
Proyectil Enemigo::disparar()
{
    //proyectiles_enemigos.push_back(Proyectil(centro.first,centro.second,tipo));
    return Proyectil(centro.first,centro.second,tipo);
}

//Dibujar enemigo
void Enemigo::dibujar(int state)
{
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
