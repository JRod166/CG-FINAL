#include "Item.h"

///Item: PLantilla de los potenciadores
//Constructor
Item::Item(float x, float y, int type)
{
    centro.first = x;
    centro.second = y;
    tipo = type;
    //vida extra
    if(tipo==1)
    {
        radio_hitbox = 10;
        velocidad = 50;
    }
    //mas velocidad
    else if(tipo==2)
    {
        radio_hitbox = 10;
        velocidad = 50;
    }
    //evasion(hit_box reducido)
    else if(tipo==3)
    {
        radio_hitbox = 10;
        velocidad = 50;
    }
    //mejora del disparo
    else if(tipo==4)
    {
        radio_hitbox = 10;
        velocidad = 50;
    }
}


void Item::mover()
{
    centro.second -= velocidad * delay_time;
}


//Provisional, reemplazar con los sprites de items
void Item::dibujar()
{
  glBindTexture(GL_TEXTURE_2D,item);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
  glEnable(GL_BLEND);//utilizar transparencia
  float x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  glTexCoord2f(0.25*tipo,0);
  glVertex3f(x+radio_hitbox, y-radio_hitbox,-3-(tipo*0.1));   //bottom-right
  glTexCoord2f(0.25*tipo,1);
  glVertex3f(x+radio_hitbox, y+radio_hitbox,-3-(tipo*0.1)); //top-right
  glTexCoord2f(0.25*(tipo-1),1);
  glVertex3f(x-radio_hitbox, y+radio_hitbox,-3-(tipo*0.1)); //top-left
  glTexCoord2f(0.25*(tipo-1),0);
  glVertex3f(x-radio_hitbox, y-radio_hitbox,-3-(tipo*0.1)); //bottom-left
  glEnd();
  glDisable(GL_BLEND);
}
