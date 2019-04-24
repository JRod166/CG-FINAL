#define GLUT_DISABLE_ATEXIT_HACK
#include <bits/stdc++.h>
// #include <windows.h> //for windows
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();

///extern function for draw and move
//Funcion quemueve todos los proyectiles del jugador
void mover_proyectiles();
void dibujar_proyectiles();


///DECLARACCIONES IMPLICITAS
class Player;
class Proyectil;
//class Item;
//class Enemigo;


///VARIABLES GLOBALES
Player *el_jugador;
vector<Proyectil> mis_proyectiles;
vector<Proyectil> proyectiles_enemigos;
//vector<Item> items;
//vector<Enemigo> enemigos;
int lim_x = 245;
int lim_y = 245;

bool available_fire = 1;
int timer_fire = 0;

///PROYECTILES: comportamiento de estos
class Proyectil
{
public:
    pair<int,int> centro; //x,y
    int radio_hitbox;
    //bool es_enemigo; /// posible comentario
    int tipo; //determina el movimiento del proyectil
    int velocidad;

    Proyectil(int x, int y, int tip, bool es_enem);
    void mover();
    void dibujar();

};

Proyectil::Proyectil(int x, int y, int tip, bool es_enem)
{
    centro.first = x;
    centro.second = y;
    tipo = tip;
    //es_enemigo = es_enem;
    if(tipo = 1)
    {
        radio_hitbox = 1;
        velocidad = 2;
    }
}

void Proyectil::mover()
{

  int new_pos = 0;
  if(tipo==1)
  {
    new_pos =  centro.second + velocidad;
    if( new_pos < lim_y )
    {
      centro.second = new_pos;
    }
  }
}

void Proyectil::dibujar() {
  int x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  glColor3f(1.0f,1.0f,1.0f);
  glVertex2f(x+radio_hitbox, y-radio_hitbox);
  glVertex2f(x+radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y-radio_hitbox);
  glEnd();
}

///PLAYER: Clase que controla al jugador
class Player
{
public:
    pair<int,int> centro; //x,y
    int radio_hitbox;
    int vidas;
    int score;
    int velocidad;

    Player(int pos_x, int pos_y);
    void mover(int direccion);
    void disparar();
    void dibujar();
};

//Constructor del jugador
Player::Player(int x, int y)
{
    centro.first = x;
    centro.second = y;
    radio_hitbox = 3;
    velocidad = 4;
    vidas = 3;
    score = 0;
}

//Funcion de movimiento del personaje del jugador
void Player::mover(int direccion)
{
    int new_pos = 0;
    //Arriba
    if(direccion == 1)
    {
        new_pos =  centro.second + velocidad;
        if( new_pos < lim_y )
        {
            centro.second = new_pos;
        }
    }
    //Abajo
    else if(direccion == 2)
    {
        new_pos =  centro.second - velocidad;
        if( new_pos > -(lim_y) )
        {
            centro.second = new_pos;
        }
    }
    //Izquierda
    else if(direccion == 3)
    {
        new_pos =  centro.first - velocidad;
        if( new_pos > -(lim_x) )
        {
            centro.first = new_pos;
        }
    }
    //Derecha
    else if(direccion == 4)
    {
        new_pos =  centro.first + velocidad;
        if( new_pos < lim_x )
        {
            centro.first = new_pos;
        }
    }
}

//El jugador dispara un proyectil
void Player::disparar()
{
  mis_proyectiles.push_back(Proyectil(centro.first,centro.second,1,false));
}

void Player::dibujar() {
  int x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  glColor3f(1.0f,0.0f,0.0f);
  glVertex2f(x+radio_hitbox, y-radio_hitbox);
  glVertex2f(x+radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y-radio_hitbox);
  glEnd();
}







/////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
  int modifier = glutGetModifiers();
  switch (modifier) {
    case GLUT_ACTIVE_CTRL:
    if (available_fire == 1) {
      el_jugador->disparar();
      available_fire = 0;
      timer_fire = 10;
    }
    break;

  }
  glMatrixMode(GL_PROJECTION);
	switch (key)
	{
	case GLUT_KEY_UP:
	    //movemos al jugador hacia arriba
	    el_jugador->mover(1);
	    glutPostRedisplay();			// et on demande le r�affichage.
		break;

	case GLUT_KEY_DOWN:
	    //movemos al jugador hacia abajo
	    el_jugador->mover(2);
		glutPostRedisplay();			// et on demande le r�affichage.
		break;

	case GLUT_KEY_LEFT:
	    //movemos al jugador hacia la izquierda
	    el_jugador->mover(3);
		glutPostRedisplay();			// et on demande le r�affichage.
		break;

	case GLUT_KEY_RIGHT:
	    //movemos al jugador hacia la derecha
	    el_jugador->mover(4);
		glutPostRedisplay();			// et on demande le r�affichage.
		break;
  }

}



///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{

	}

}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
    glutPostRedisplay(); //redibujar
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 3 : Transformaciones");


	///INICIALIZAR EL JUEGO
	el_jugador = new Player(0,0);


	initGL();
	init_scene();


	glutDisplayFunc(&window_display);

	glutKeyboardFunc(&window_key);
  //glutGetModifiers(&callback_modifier);
  glutSpecialFunc(&callback_special);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);

	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}


///FUNCION QUE DIBUJA LA PANTALLA
GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0f, 20.0f, -20.0f, 20.0f, -20.0f, 20.0f);
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glTranslatef(0.0f, 0.0f, -30.0f);


	//Dibujar al jugador
	int x = el_jugador->centro.first;
	int y = el_jugador->centro.second;
	int radio = el_jugador->radio_hitbox;
	glBegin(GL_QUADS);

  el_jugador -> dibujar();

  //Dibujar_proyectiles
  dibujar_proyectiles();
	glutSwapBuffers();

	glFlush();
}



GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
	glMatrixMode(GL_MODELVIEW);
}

void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;
  case GLUT_ACTIVE_CTRL:
  if (available_fire == 1) {
    el_jugador->disparar();
    available_fire = 0;
    timer_fire = 10;
  }
  break;
  case 26:
  if (available_fire == 1) {
    el_jugador->disparar();
    available_fire = 0;
    timer_fire = 10;
  }
  break;
  case 'z':
  if (available_fire == 1) {
    el_jugador->disparar();
    available_fire = 0;
    timer_fire = 10;
  }
  break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}



//function called on each frame
GLvoid window_idle()
{
  if (available_fire == 0) {
    if (timer_fire == 1) {
      available_fire = 1;
    }
    timer_fire --;
  }
  mover_proyectiles();

	glutPostRedisplay();
}

//Funcion quemueve todos los proyectiles del jugador
void mover_proyectiles()
{
  for (int i = 0; i < mis_proyectiles.size(); ) {
    mis_proyectiles[i].mover();
    if (abs(mis_proyectiles[i].centro.second) >= lim_y - 1) {
      mis_proyectiles.erase(mis_proyectiles.begin() + i);
    }
    else {
      ++i;
    }
  }
}
void dibujar_proyectiles()
{
  for (int i = 0; i < mis_proyectiles.size(); i++) {
    mis_proyectiles[i].dibujar();
  }
}
