#define GLUT_DISABLE_ATEXIT_HACK
#include <bits/stdc++.h>
//#include <windows.h> //for windows
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
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


//Funcion que dispara la funcion del thread cada cierto intervalo de milisegundos
void timer_start(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() {
        while (true)
        {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}



bool available_fire = 1;
int timer_fire = 0;
float default_guided_lifetime = 30;
float delay_time;
float time_p;
float timebase;
float closer_distance = 20;

///PROYECTILES: comportamiento de estos
//=======

///FUNCIONES EXTERNAS PARA MOVER OBJETOS
void mover_proyectiles(); //funcion quem ueve todos los proyectiles del jugador
void dibujar_proyectiles();
void dibujar_enemigos();
void enemigos_disparan();
//void mover_enemigos();


///FORWARD DECLARATIONS
class Player
{
public:
    pair<float,float> centro; //x,y
    int radio_hitbox;
    int vidas;
    int score;
    float velocidad;

    Player(float pos_x, float pos_y);
    void mover(int direccion);
    void disparar();
    void dibujar();
};

//>>>>>>> Luis
class Proyectil
{
public:
    pair<float,float> centro; //x,y
    int radio_hitbox;
    bool guided;
    int tipo; //determina el movimiento del proyectil
    float velocidad;
    //float guided_lifetime; ////tiempo guiado opcional
    pair<float,float> direccion;
    Proyectil(float x, float y, int type);
    void mover();
    void dibujar();
//<<<<<<< HEAD

//=======
//>>>>>>> Luis
};

class Enemigo
{
public:
    pair<float,float> centro; //x,y
    int tipo;
    int radio_hitbox;
    int vidas;
    float velocidad;

    Enemigo(float pos_x, float pos_y, int type);
    void mover(int direccion);
    void disparar();
    void dibujar();
};


///VARIABLES GLOBALES
Player *el_jugador;
vector<Proyectil> mis_proyectiles;
vector<Proyectil> proyectiles_enemigos;
vector<Enemigo> enemigos;
float lim_x = 245;
float lim_y = 245;

float calc_distance(pair<float, float> a) {
  return sqrt(pow(a.first, 2) + pow(a.second, 2));
}

float calc_distance(pair<float, float> a, pair<float, float> b) {
  return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

///PROYECTILES: comportamiento de estos
Proyectil::Proyectil(float x, float y, int type)
{
    centro.first = x;
    centro.second = y;
    tipo = type;
    if(tipo==1)
//>>>>>>> Luis
    {
      radio_hitbox = 1; /// puede cambiar
        velocidad = 3;
    }
    else if(tipo==2)
    {
        radio_hitbox = 1;
        velocidad = 3;
    }
    else if(tipo==3)
    {
        radio_hitbox = 1;
        velocidad = 0.5;
        direccion.first = el_jugador->centro.first - x;
        direccion.second = el_jugador->centro.second - y;
        float dist = calc_distance(direccion);
        //cout << temp << endl;
        direccion.first /= dist;
        direccion.second /= dist;
    }
    else if (tipo == 4) {
      radio_hitbox = 1;
      velocidad = 3;
      direccion.first = el_jugador->centro.first - x;
      direccion.second = el_jugador->centro.second - y;
      float dist = calc_distance(direccion);
      //cout << temp << endl;
      direccion.first /= dist;
      direccion.second /= dist;
    }
}

void Proyectil::mover()
{
  //proyectiles del jugador
  if(tipo==1)
  {
      centro.second = centro.second + velocidad;
  }
  //proyectiles de enmigos de tipo 1
  else if(tipo==2)
  {
      centro.second = centro.second - velocidad;
  }
  //proyectiles de enmeigos de tipo 3
  else if(tipo==3)
  {
    centro.first = centro.first + direccion.first / velocidad;
    centro.second = centro.second + direccion.second / velocidad;
      /*
      if(centro.second >= el_jugador->centro.second  & guided_lifetime > 0)
      {
          if(centro.first > el_jugador->centro.first) //si el jugador esta hacia la izquierda
          {
              centro.first = centro.first - velocidad;
          }
          else if(centro.first < el_jugador->centro.first) //si el jugador esta hacia la derecha
          {
              centro.first = centro.first + velocidad;
          }
          guided_lifetime-=default_guided_lifetime / 20;
      }
      */
  }
  else if (tipo == 4) {
    if (guided == 1) {
      pair<float, float> new_direction, pos;
      pos.first = x;
      pos.second = y;
      direccion.first -= el_jugador->centro.first;
      direccion.second -= el_jugador->centro.second;
      float dist = calc_distance(direccion);
      //cout << temp << endl;
      direccion.first /= dist;
      direccion.second /= dist;
      if (closer_distance > dist) {
        guided = 0;
      }
    }
    centro.first = centro.first + direccion.first / velocidad;
    centro.second = centro.second + direccion.second / velocidad;
  }
}

void Proyectil::dibujar()
{
  float x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  if(tipo==1)
  {
      glColor3f(1.0f,1.0f,1.0f);
  }
  else if(tipo==2)
  {
      glColor3f(0.0f,1.0f,1.0f);
  }
  else if(tipo==3)
  {
      glColor3f(0.0f,0.0f,1.0f);
  }
  glVertex2f(x+radio_hitbox, y-radio_hitbox);
  glVertex2f(x+radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y-radio_hitbox);
  glEnd();
}


///PLAYER: Clase que controla al jugador
//Constructor del jugador
Player::Player(float x, float y)
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
    float new_pos = 0;
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
  mis_proyectiles.push_back(Proyectil(centro.first,centro.second,1));
}

void Player::dibujar()
{
  float x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  glColor3f(1.0f,0.0f,0.0f);
  glVertex2f(x+radio_hitbox, y-radio_hitbox);
  glVertex2f(x+radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y+radio_hitbox);
  glVertex2f(x-radio_hitbox, y-radio_hitbox);
  glEnd();
}



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
        velocidad = 2;
        vidas = 1;
    }
    else if(tipo==3)
    {
        radio_hitbox = 5;
        velocidad = 5;
        vidas = 2;
    }

}
//El enemigo dispara un proyectil
void Enemigo::disparar()
{
    proyectiles_enemigos.push_back(Proyectil(centro.first,centro.second,tipo));
}

//Dibujar enemigo
void Enemigo::dibujar()
{
  float x = centro.first, y = centro.second;
  glBegin(GL_QUADS);
  if(tipo==2)
  {
      glColor3f(0.0f,1.0f,1.0f);
  }
  else if(tipo==3)
  {
      glColor3f(0.0f,0.0f,1.0f);
  }
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
  glMatrixMode(GL_PROJECTION);
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
	glutCreateWindow("Shooter");


	///INICIALIZAR EL JUEGO
	el_jugador = new Player(0,0);


	//creamos unos enmigos de prueba
	enemigos.push_back(Enemigo(100,100,2));
	enemigos.push_back(Enemigo(0,200,3));
	//los enemigos disparan cada  segundo
	timer_start(enemigos_disparan, 1000);





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
  //////movement
  time_p = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
  delay_time = float(time_p -timebase)/1000.0;// delta time
  timebase = time_p;



	//Dibujar al jugador
	el_jugador -> dibujar();

	//Dibujamos los enemigos en juegos
	dibujar_enemigos();

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
	switch (key)
	{
	case ECHAP:
		exit(1);
		break;
//<<<<<<< HEAD
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
//<<<<<<< HEAD
  if (available_fire == 0) {
    if (timer_fire == 1) {
      available_fire = 1;
    }
    timer_fire --;
  }
  mover_proyectiles();

	glutPostRedisplay();
}

//Funcion que mueve todos los proyectiles del jugador
void mover_proyectiles()
{
    for (int i = 0; i < mis_proyectiles.size();)
    {
        mis_proyectiles[i].mover();
        if( abs(mis_proyectiles[i].centro.second) >= lim_y)
        {
            mis_proyectiles.erase(mis_proyectiles.begin() + i);
        }
        else
        {
            ++i;
        }
    }
  for(int i=0; i<proyectiles_enemigos.size(); )
  {
      proyectiles_enemigos[i].mover();
      if( abs(proyectiles_enemigos[i].centro.second)>=lim_y || abs(proyectiles_enemigos[i].centro.second)>=lim_x )
      {
          proyectiles_enemigos.erase(proyectiles_enemigos.begin()+i);
      }
      else
      {
          ++i;
      }
  }
}

//Dibuja todos los proyectiles en juego
void dibujar_proyectiles()
{
  for (int i = 0; i < mis_proyectiles.size(); i++) {
    mis_proyectiles[i].dibujar();
  }
  for (int i = 0; i < proyectiles_enemigos.size(); i++) {
    proyectiles_enemigos[i].dibujar();
  }
}

//Dibuja todos los enemigos en juego
void dibujar_enemigos()
{
  for(int i=0; i<enemigos.size(); i++)
  {
      enemigos[i].dibujar();
  }
}

//Ordena a todos los enemigos que disparen
void enemigos_disparan()
{
    for(int i=0; i<enemigos.size(); i++)
    {
        enemigos[i].disparar();
    }
}
