#include "global_vars.h"

float delay_time = 0.0001;
float lim_x = 245;
float lim_y = 245;
int time_p = 0;
int timebase = 0;
int reload_time = 0;
float default_guided_lifetime = 30;

bool up_pressed = false;
bool down_pressed = false;
bool left_pressed = false;
bool right_pressed = false;
bool fire_pressed = false;
GLuint reimu,fairy,bullet,bg;
int reimustate=0;
/*  0=static
1=Shoot
2=Left move
3=right move
*/
int reimu_time=0;

float normal_vector(float x, float y)
{
    return sqrt( pow(x,2) + pow(y,2) );
}
