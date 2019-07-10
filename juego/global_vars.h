#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <bits/stdc++.h>
//#include <windows.h> //for windows
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>

#include <string>

#include <GL/glut.h>
#include <FreeImage.h>
#include <math.h>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

using namespace std;

extern float delay_time;
extern float lim_x;
extern float lim_y;
extern int time_p;
extern int timebase;
extern int reload_time;
extern float default_guided_lifetime;
extern float normal_vector(float x, float y);
extern string fit_size(int,int);
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
extern GLuint red;
extern GLuint meteor;
extern GLuint item;
extern GLuint bomb;
extern int reimustate;
extern float reimu_time;
extern sf::Sound shoot,destroy,gameOver,die,sound,itempick;
extern sf::SoundBuffer shootbuffer,empty;
extern bool play_on;
#endif
