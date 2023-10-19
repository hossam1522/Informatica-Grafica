/*

	Dpto. Lenguajes y Sistemas Inform�ticos
	E.T.S.I. Inform�tica
	Univ. de Granada

    Ejercicio 1.
    compilar con: gcc ej1.c -lglut -lGLU -lGL -o ej1

    Hecho por: Hossam El Amraoui Leghzali
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;

void triangulos ()
{
  float v[72] = {0,1.5,0,0,0,1.5,1.5,0,0,
                0,0,-1.5,0,1.5,0,1.5,0,0,
                0,0,1.5,0,-1.5,0,1.5,0,0,
                0,-1.5,0,0,0,-1.5,1.5,0,0,
                -1.5,0,0,0,0,1.5,0,1.5,0,
                0,0,-1.5,-1.5,0,0,0,1.5,0,
                -1.5,0,0,0,-1.5,0,0,0,1.5,
                0,0,-1.5,0,-1.5,0,-1.5,0,0};

  for (int i=0; i<8; i++)
  {
    glBegin (GL_TRIANGLES);
    glVertex3f (v[i*9], v[i*9+1], v[i*9+2]);
    glVertex3f (v[i*9+3], v[i*9+4], v[i*9+5]);
    glVertex3f (v[i*9+6], v[i*9+7], v[i*9+8]);
    glEnd ();
  }
};

void
Dibuja (void)
{
  GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };
  glPushMatrix ();
  glClearColor (1, 1, 1, 1);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslatef (-0.5, -0.5, -100);
  glLightfv (GL_LIGHT0, GL_POSITION, pos);
  glRotatef (view_rotx, 1.0, 0.0, 0.0);
  glRotatef (view_roty, 0.0, 1.0, 0.0);
  glRotatef (view_rotz, 0.0, 0.0, 1.0);
  triangulos();
  glPopMatrix ();
  glutSwapBuffers ();
}

/* ------------------------------------------------------------------------- */

void
Ventana (GLsizei ancho, GLsizei alto)
{				// Se ejecuta cuando se cambia la ventana, recibe el ancho y alto de la ventana X
  float calto;
  glViewport (0, 0, ancho, alto);	//fija el area de dibujo en la ventana 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  if (ancho > 0)
    calto = 1 * (GLfloat) alto / (GLfloat) ancho;
  else
    calto = 1;
  glFrustum (-1, 1, -calto, calto, 5, 250);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

static void
idle ()
{
  view_roty += 0.15;
  glutPostRedisplay ();
}

int
main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("IG: Ejericio 1");
  glutDisplayFunc (Dibuja);
  glutReshapeFunc (Ventana);
  glutIdleFunc (idle);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_DEPTH_TEST);
  glShadeModel (GL_FLAT);
  glutMainLoop ();
  return 0;
}
