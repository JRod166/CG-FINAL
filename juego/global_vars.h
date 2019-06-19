#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <bits/stdc++.h>
//#include <windows.h> //for windows
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>

#include <GL/glut.h>
#include <FreeImage.h>
#include <math.h>
#include <iostream>

using namespace std;

extern float delay_time;
extern float lim_x;
extern float lim_y;
extern int time_p;
extern int timebase;
extern int reload_time;
extern float default_guided_lifetime;
extern float normal_vector(float x, float y);
//Estado de las teclas(presionada o no)
extern bool up_pressed ;
extern bool down_pressed ;
extern bool left_pressed ;
extern bool right_pressed ;
extern bool fire_pressed ;
extern GLuint reimu;
extern GLuint fairy;
extern GLuint bullet;
extern GLuint bg;
extern int reimustate;
extern int reimu_time;

#endif
