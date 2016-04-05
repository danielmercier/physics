#include <stdio.h>
#include <sys/time.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "engine.hpp"

int xnew=0, ynew=0, znew=-100;
int xold=0, yold=0, zold=-100;
int xx1=0, yy1=0, zz1=0;

Engine *engine;

// Etat de la souris
int MouseState=0;

// Ouverture de l'angle de vue
float fov=45.0;

float near_plane=10;
float far_plane=500.0;

int WindowWidth;
int WindowHeight;


void GLInit(void);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void timeTick(void);
double getTime(void);
void display(void);
void reshape(int w, int h);
void MoveToOrigin();
void SetGlobalView(int w, int h);
void Draw3DSGrid();

/* Source de lumière */
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 0.0};   /*  composante diffuse */
GLfloat light_position[] = {0.0,10.0,10.0, 0.0};  /*  position */


/* Definitions des matériaux */
GLfloat mat_specularWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_ambientWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_diffuseWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_shininessWHITE[] ={128.0 * 0.4};

GLfloat mat_specularGRAY[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientGRAY[] ={0.5,0.5,0.5,1.0};
GLfloat mat_diffuseGRAY[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessGRAY[] ={128.0 * 0.6};

GLfloat mat_specularBLUE[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientBLUE[] ={0,0,1,1.0};
GLfloat mat_diffuseBLUE[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessBLUE[] ={128.0 };

GLfloat mat_specularGREEN[] ={0.633, 0.727811, 0.633,1.0};
GLfloat mat_ambientGREEN[] ={0.0215, 0.1745, 0.0215,1.0};
GLfloat mat_diffuseGREEN[] ={0.07568, 0.61424, 0.07568,1.0};
GLfloat mat_shininessGREEN[] ={128.0};

GLfloat mat_specularYELLOW[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientYELLOW[] ={1,1,0,1.0};
GLfloat mat_diffuseYELLOW[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessYELLOW[] ={128.0};

GLfloat mat_specularRED[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientRED[] ={1.0,0.0,0.0,1.0};
GLfloat mat_diffuseRED[] ={0.8,0.50,0.50,1.0};
GLfloat mat_shininessRED[] ={128.0};

/* Fonction de gestion du clavier */
void keyPressed(unsigned char key, int x, int y)
{
  if(key == 'p'){
    engine->run_pause();
  }
}

int call_gl (int argc, char **argv, Engine &e) {
  engine = &e;
  glutInit(&argc, argv);

  /*  Activation des buffers :
     Double buffer
     RGBA color
     Depth buffer */
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

  /* Création de la fenêtre */
  glutInitWindowSize(1024, 768);

  /* Positionnement de la fenêtre */
  glutInitWindowPosition(100, 100);

  /* Ouverture de la fenêtre */
  glutCreateWindow("Projet IG");

  /* Spécification de la fontion de dessin */
  glutDisplayFunc(display);

  /* Spécification de la fontion de redimensionnement */
  glutReshapeFunc(reshape);

  /* Spécification des fontions de gestion de la souris */
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(&keyPressed);

  /* Spécification de la fonction de mise-à-jour */
  glutIdleFunc(timeTick);

  /* Intitialisation des paramètres de l'affichage et de la fenêtre */
  GLInit();

  /* Lancement de la boucle OpenGL */
  glutMainLoop();

return 0;
}

// Intitialisation des paramètres de l'affichage et de la fenêtre
void GLInit(void) {
// Couleur d'effacement du buffer de couleur
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

// paramètrage du Z-buffer
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

// Activation de l'éclairage
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);


// Activation du lissage
  glShadeModel(GL_SMOOTH);

}

/* Encapsulation des fonctions matériaux */
void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{
  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}

void display(void) {
  MoveToOrigin();

  // Effacement du buffer de couleur et de profondeur
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Positionnement du point de vue initial
  SetGlobalView(WindowWidth, WindowHeight);

	SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);

  engine->update();

  // Permutation des buffers et mise-à-jour
  glFlush();
  glutSwapBuffers();
}


void reshape(int w, int h) {
  WindowWidth  = w;
  WindowHeight = h;
}


void Draw3DSGrid() {
  glColor3f(0.0, 0.0,0.0);
  float i;
  for(i = -50; i <= 50; i += 5) {
    glBegin(GL_LINES);
    glVertex3f(-50, 0, i);
    glVertex3f(50, 0, i);
    glVertex3f(i, 0, -50);
    glVertex3f(i, 0, 50);
    glEnd();
  }
}


// Fonction souris : boutons activés
void mouse(int button, int state, int x, int y) {
  if(button==GLUT_LEFT_BUTTON) {
    if(state==GLUT_DOWN) {
      MouseState=1;
      xx1=x;
      yy1=y;
    } else {
      MouseState=0;
      xold=xnew;
      yold=ynew;
    }
  }
  else if (button==GLUT_RIGHT_BUTTON) {
    if (state==GLUT_DOWN) {
      MouseState=2;
      zz1=y;
    } else {
      MouseState=0;
      zold=znew;
    }
  }
  glutPostRedisplay();
}


// Fonction souris : déplacement
void motion(int x, int y) {
  if (MouseState==1) {
    xnew=xold+x-xx1;
    ynew=yold+y-yy1;
    glutPostRedisplay();
  }
  else if (MouseState==2) {
    znew=zold+y-zz1;
    glutPostRedisplay();
  }
}


// Retourne le temps actuel en [sec]
double getTime(void) {
  //struct timeval tv;
  //gettimeofday(&tv, NULL);
  //return (double)tv.tv_sec; + (double)tv.tv_usec/1000000.;
  return glutGet(GLUT_ELAPSED_TIME);
}


// Fonction de mise à jour
void timeTick(void) {

  glutPostRedisplay();
}


void SetGlobalView(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, (double)w/(double)h, near_plane, far_plane);
  glMatrixMode(GL_MODELVIEW);
}


// Positionnement et orientation de la scène par rapport à la caméra
void MoveToOrigin() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f,-30.0f,-50.0f);
  glTranslatef(0.0f,0.0f,znew);
  glRotatef(ynew,1.0,0.0,0.0);
  glRotatef(xnew,0.0,1.0,0.0);
}
