#define GLUT_DISABLE_ATEXIT_HACK

#include "Player.h"
#include "Enemigo.h"

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

///LOAD IMAGE FROM FREE FreeImage
GLuint LoadTexture(const char* filename, GLenum image_format, GLint internal_format, GLint level=0, GLint border=0)
{
  //image format
  FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
  //pointer to the image, once loaded
  FIBITMAP *dib(0);
  //pointer to the image data
  BYTE* bits(0);
  //image width and height
  unsigned int width(0), height(0);
  //OpenGL's image ID to map to
  GLuint textureID;

  //check the file signature and deduce its format
  fif = FreeImage_GetFileType(filename, 0);
  //if still unknown, try to guess the file format from the file extension
  if(fif == FIF_UNKNOWN)
  fif = FreeImage_GetFIFFromFilename(filename);
  //if still unkown, return failure
  if(fif == FIF_UNKNOWN)
  return false;

  //check that the plugin has reading capabilities and load the file
  if(FreeImage_FIFSupportsReading(fif))
  dib = FreeImage_Load(fif, filename);
  //if the image failed to load, return failure
  if(!dib)
  return false;

  //retrieve the image data
  bits = FreeImage_GetBits(dib);
  //get the image width and height
  width = FreeImage_GetWidth(dib);
  height = FreeImage_GetHeight(dib);
  //if this somehow one of these failed (they shouldn't), return failure
  if((bits == 0) || (width == 0) || (height == 0))
  return false;

  //generate an OpenGL texture ID for this texture
  glGenTextures(1, &textureID);


  glBindTexture(GL_TEXTURE_2D, textureID);
  //store the texture data for OpenGL use
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, bits);


  /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



  //glGenerateMipmap(GL_TEXTURE_2D);
  FreeImage_Unload(dib);

  //return success
  return textureID;
}

//Funcion que recibe un vector de 2 dimensiones y retorna su normal



///FUNCIONES EXTERNAS PARA MOVER OBJETOS
void mover_proyectiles(); //funcion quem ueve todos los proyectiles del jugador
void dibujar_proyectiles();
void dibujar_enemigos();
void enemigos_disparan();
//void mover_enemigos();


///FORWARD DECLARATIONS






///VARIABLES GLOBALES
Player *el_jugador;
vector<Proyectil> mis_proyectiles;
vector<Proyectil> proyectiles_enemigos;
vector<Enemigo> enemigos;







///CUANDO SE PRESIONA UNA TECLA DE MOVIMIENTO
GLvoid callback_special(int key, int x, int y)
{
  glMatrixMode(GL_PROJECTION);
  if( key == GLUT_KEY_UP)
  {
      //movemos al jugador hacia arriba
      up_pressed = true;
      glutPostRedisplay();			// et on demande le r�affichage.
  }
  if( key == GLUT_KEY_DOWN )
  {
      //movemos al jugador hacia abajo
      down_pressed = true;
      glutPostRedisplay();
  }
  if( key == GLUT_KEY_LEFT )
  {
      //movemos al jugador hacia la izquierda

      left_pressed = true;

      glutPostRedisplay();
  }
  if( key == GLUT_KEY_RIGHT )
  {
      //movemos al jugador hacia la derecha
	    right_pressed = true;

		glutPostRedisplay();
  }
}

///CUANDO SE DEJA DE PRESIONAR UNA TECLA DE MOVIMIENTO
GLvoid callback_specialUp(int key, int x, int y)
{
  glMatrixMode(GL_PROJECTION);
  if( key == GLUT_KEY_UP)
  {
      //se detiene el movimiento hacia arriba
      up_pressed = false;
      glutPostRedisplay();
  }
  if( key == GLUT_KEY_DOWN )
  {
      //se detiene el movimiento hacia abajo
      down_pressed = false;
      glutPostRedisplay();
  }
  if( key == GLUT_KEY_LEFT )
  {
      //se detiene el movimiento hacia la izquierda
      left_pressed =false;
      glutPostRedisplay();
  }
  if( key == GLUT_KEY_RIGHT )
  {
      //se detiene el movimiento hacia la derecha
      right_pressed = false;
      glutPostRedisplay();
  }
}

///CUANDO SE PRESIONA UNA TECLA DE DISPARO
GLvoid window_key(unsigned char key, int x, int y)
{
    if( key == 'z')
    {
        fire_pressed = true;
    }
}

///CUANDO SE DEJA DE PRESIONA LA TECLA DE DISPARO
GLvoid window_keyUp(unsigned char key, int x, int y)
{
    if( key == 'z')
    {
        fire_pressed = false;
    }
    if(key==ECHAP)
    {
      exit(1);
    }
}

GLvoid callback_mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{

	}
}

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

  ///cargar texturas
  reimu=LoadTexture("reimusprite.png",GL_BGRA_EXT, GL_RGBA);
  fairy=LoadTexture("fairy.png",GL_BGRA_EXT,GL_RGBA);
  bullet=LoadTexture("bullets.png",GL_BGRA_EXT,GL_RGBA);
  bg=LoadTexture("space.png",GL_BGR,GL_RGB);


	///INICIALIZAR EL JUEGO
	el_jugador = new Player(0,0);


	//creamos unos enmigos de prueba
	enemigos.push_back(Enemigo(0,100,2));
	enemigos.push_back(Enemigo(-100,200,3));
	enemigos.push_back(Enemigo(100,100,4));
	//los enemigos disparan cada  segundo
	timer_start(enemigos_disparan, 1000);





	initGL();
	init_scene();


	glutDisplayFunc(&window_display);

	glutKeyboardFunc(&window_key);
	glutKeyboardUpFunc(&window_keyUp);

    glutSpecialFunc(&callback_special);
    glutSpecialUpFunc(&callback_specialUp);
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
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
  glEnable(GL_BLEND);//utilizar transparencia

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
	//Calculamos la velocidad de los frames
	time_p = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
	delay_time = float(time_p -timebase)/1000.0;// delta time
	timebase = time_p;

  glPushMatrix();
  glDisable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D,bg);
  glBegin(GL_QUADS);
  glTexCoord2f(1,0);
  glVertex3f(350,-350,2); //bottom-right
  glTexCoord2f(1,1);
  glVertex3f(350,350,2); //top-right
  glTexCoord2f(0,1);
  glVertex3f(-350,350,2); //top-left
  glTexCoord2f(0,0);
  glVertex3f(-350,-350,2); //bottom-left
  glEnd();
  glPopMatrix();

	//Dibujar al jugador
	el_jugador->mover();
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



//Function called on each frame
GLvoid window_idle()
{
    if(left_pressed)
    {reimustate=2;
    reimu_time=5;}
    if(right_pressed)
    {reimustate=3;
    reimu_time=5;}
    if(reimu_time>0)
    {
      reimu_time--;
    }
    else
    {
      reimustate=0;
    }
    for(int i=0;i<enemigosstate.size();i++)
    {
      if(enemigosstate[i].second>0)
      {
        enemigosstate[i].second--;
      }
      else
      {
        enemigosstate[i].first=0;
      }
    }
    //Para disparar, se requiere una recarga de 10 ciclos
    if( fire_pressed == true)
    {
        if(reload_time == 0)
        {
            mis_proyectiles.push_back(el_jugador->disparar());
            reimustate=1;
            reimu_time=5;
            reload_time = 100;
        }
        else
        {
            reload_time--;
        }
    }
    mover_proyectiles();
    glutPostRedisplay();
}

//Funcion que mueve todos los proyectiles del jugador
void mover_proyectiles()
{
    for (int i = 0; i < mis_proyectiles.size();)
    {
        mis_proyectiles[i].mover(el_jugador->centro.first,el_jugador->centro.second);
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
      proyectiles_enemigos[i].mover(el_jugador->centro.first,el_jugador->centro.second);
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
      enemigos[i].dibujar(enemigosstate[i].first);
  }
}

//Ordena a todos los enemigos que disparen
void enemigos_disparan()
{
  enemigosstate.resize(enemigos.size());
    for(int i=0; i<enemigos.size(); i++)
    {
        proyectiles_enemigos.push_back(enemigos[i].disparar());
        enemigosstate[i].first=1;
        enemigosstate[i].second=5;
        if(proyectiles_enemigos[proyectiles_enemigos.size()-1].tipo>2)
        {
          float x=proyectiles_enemigos[proyectiles_enemigos.size()-1].centro.first;
          float y=proyectiles_enemigos[proyectiles_enemigos.size()-1].centro.second;
          proyectiles_enemigos[proyectiles_enemigos.size()-1].direccion.first = el_jugador->centro.first - x;
          proyectiles_enemigos[proyectiles_enemigos.size()-1].direccion.second = el_jugador->centro.second - y;
        }
    }
}
