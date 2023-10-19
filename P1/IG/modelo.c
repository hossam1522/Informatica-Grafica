/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Hossam El Amraoui Leghzali

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


int modo = GL_FILL;    // Modo de visualizacion inicial (GL_POINT, GL_LINE, GL_FILL)
bool iluminacion = false;   // Visualizacion inicial con iluminacion

/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel ()
{

}



class Ejes:public Objeto3D 
{ 
public: 
    float longitud = 30;
// Dibuja el objeto
void draw( )
{
  glDisable (GL_LIGHTING);
  glBegin (GL_LINES);
  {
    glColor3f (0, 1, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, longitud, 0);

    glColor3f (1, 0, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (longitud, 0, 0);

    glColor3f (0, 0, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, longitud);
  }
  glEnd ();
  glEnable (GL_LIGHTING);

}
} ; 

Ejes ejesCoordenadas;

class Cubo:public Objeto3D 
{
  protected:
    float lado;

  public:

  Cubo(float lado)
  {
    this->lado = lado;
  }

  void draw()
  {
    glBegin(GL_QUADS);
      // right
      glNormal3f(1.0f, 0.0f, 0.0f);
      glVertex3f(lado, 0, 0);
      glVertex3f(lado, lado, 0);
      glVertex3f(lado, lado, lado);
      glVertex3f(lado,0, lado);
  
      // left
      glNormal3f(-1.0f, 0.0f, 0.0f);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, lado);
      glVertex3f(0, lado, lado);
      glVertex3f(0, lado, 0);

    glEnd();

    glBegin(GL_QUAD_STRIP);

      // front
      glNormal3f(0.0f, 0.0f, 1.0f);
      glVertex3f(lado, lado, lado);
      glVertex3f(0, lado, lado);
      glVertex3f(lado, 0, lado);
      glVertex3f(0, 0, lado);

      // bottom
      glNormal3f(0.0f, -1.0f, 0.0f);
      glVertex3f(lado, 0, 0);
      glVertex3f(0, 0, 0);
      
      // back
      glNormal3f(0.0f, 0.0f, -1.0f);
      glVertex3f(lado, lado, 0);
      glVertex3f(0, lado, 0);
      
      // top
      glNormal3f(0.0f, 1.0f, 0.0f);
      glVertex3f(lado, lado, lado);
      glVertex3f(0, lado, lado);

    glEnd();


    // Defensa
    glBegin(GL_TRIANGLE_FAN);
      // front
      glVertex3f(lado/2, -lado, lado/2);
      glVertex3f(lado, 0, lado);
      glVertex3f(0, 0, lado);

      // left
      glVertex3f(0, 0, 0);

      // back
      glVertex3f(lado, 0, 0);

      // right
      glVertex3f(lado, 0, lado);

    glEnd();

    
  }
  
};

Cubo cubo(2);

class Piramide:public Objeto3D
{
  protected:
    float alto, lado;

  public:

  Piramide(float alto, float lado)
  {
    this->alto = alto;
    this->lado = lado;
  }

  void draw(){

    float factor_normalizacion = lado*sqrt(lado*lado/4+alto*alto);

    glBegin(GL_QUADS);
      // bottom
      glNormal3f(0.0f, -1.0f, 0.0f);
      glVertex3f(0, 0, 0);
      glVertex3f(lado, 0, 0);
      glVertex3f(lado, 0, lado);
      glVertex3f(0, 0, lado);
    
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
      // front
      glNormal3f(0, (lado*lado)/2/factor_normalizacion, alto*lado/factor_normalizacion);
      glVertex3f(lado/2, alto, lado/2);
      glVertex3f(0, 0, lado);
      glVertex3f(lado, 0, lado);

      // right
      glNormal3f(alto*lado/factor_normalizacion, (lado*lado)/2/factor_normalizacion, 0);
      glVertex3f(lado, 0, 0);

      // back
      glNormal3f(0, (lado*lado)/2/factor_normalizacion, -alto*lado/factor_normalizacion);
      glVertex3f(0, 0, 0);

      // left
      glNormal3f(-alto*lado/factor_normalizacion, (lado*lado)/2/factor_normalizacion, 0);
      glVertex3f(0, 0, lado);

    glEnd();

  }
    
};

Piramide piramide(4, 2);


class Octaedro:public Objeto3D
{
  protected:
    float alto, lado;

  public:

  Octaedro(float alto, float lado)
  {
    this->alto = alto;
    this->lado = lado;
  }

  void draw(){

    float factor_normalizacion = lado*sqrt(lado*lado/4+alto*alto);

    // Parte de arriba
    glBegin(GL_TRIANGLE_FAN);
      // front
      glNormal3f(0, (lado*lado)/2/factor_normalizacion, alto*lado/factor_normalizacion);
      glVertex3f(lado/2, alto, lado/2);
      glVertex3f(0, 0, lado);
      glVertex3f(lado, 0, lado);

      // right
      glNormal3f(alto*lado/factor_normalizacion, (lado*lado)/2/factor_normalizacion, 0);
      glVertex3f(lado, 0, 0);

      // back
      glNormal3f(0, (lado*lado)/2/factor_normalizacion, -alto*lado/factor_normalizacion);
      glVertex3f(0, 0, 0);

      // left
      glNormal3f(-alto*lado/factor_normalizacion, (lado*lado)/2/factor_normalizacion, 0);
      glVertex3f(0, 0, lado);

    glEnd();

    // Parte de abajo
    glBegin(GL_TRIANGLE_FAN);
      // front
      glNormal3f(0, -(lado*lado)/2/factor_normalizacion, alto*lado/factor_normalizacion);
      glVertex3f(lado/2, -alto, lado/2);
      glVertex3f(lado, 0, lado);
      glVertex3f(0, 0, lado);

      // left
      glNormal3f(-alto*lado/factor_normalizacion, -(lado*lado)/2/factor_normalizacion, 0);
      glVertex3f(0, 0, 0);

      // back
      glNormal3f(0, -(lado*lado)/2/factor_normalizacion, -alto*lado/factor_normalizacion);
      glVertex3f(lado, 0, 0);

      // right
      glNormal3f(alto*lado/factor_normalizacion, -(lado*lado)/2/factor_normalizacion, 0);
      glVertex3f(lado, 0, lado);

    glEnd();

  }
    
};

Octaedro octaedro (4,2);


/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz
  //static GLfloat  pos[4] = { -13.0, -6.0, 0.0, 0.0 };	// Posicion de la fuente de luz


  float  color[4] = { 0.8, 0.0, 1, 1 };
  float color2[4] = { 0.0, 1.0, 1, 1 };
  float color3[4] = { 1.0, 0.0, 0, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  //glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  glClearColor (1.0, 1.0, 1.0, 1.0);	// Fija el color de fondo a blanco

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  glShadeModel(GL_FLAT);
  glPointSize(5);

  setModo (modo);           // Establece el modo de dibujo inicial

  if (!iluminacion)         // Establece el tipo de iluminación inicial
    glDisable(GL_LIGHTING);
  else
    glEnable(GL_LIGHTING);

  glColor3f(0.8, 0.0, 1);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)   

  cubo.draw();
  glColor3f(0.0, 1.0, 1);
  glMaterialfv ( GL_FRONT , GL_AMBIENT_AND_DIFFUSE , color2 ) ;      
  glTranslatef(2.5, 0, 0);
  piramide.draw(); 

  glColor3f(1.0, 0.0, 0);
  glMaterialfv ( GL_FRONT , GL_AMBIENT_AND_DIFFUSE , color3 ) ;      
  glTranslatef(2.5, 0, 0);
  octaedro.draw();

  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}

void setModo (int M)
{
  modo = M;
  glPolygonMode (GL_FRONT_AND_BACK, modo);
}

void setIluminacion ()
{
  iluminacion = !iluminacion;
}