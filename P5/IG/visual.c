/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23

	Codigo base para la realización de las practicas de IG

	Estudiante:

	Programa principal
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
modulo visual.c
    Inicialización de ventana X
    Transformación de visualización
    Transformación de proyección

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <vector>
#include "practicasIG.h"


//================================================ VARIABLES

/**

Angulos de rotacion de la camara.

**/

float view_rotx = 0, view_roty = 0;


/**

Distancia de la cámara

**/
std::vector<float> posicion = {5,10,15}; // Posición de la cámara
std::vector<float> vpn; // Dirección hacia la que mira la cámara
float D = 10;

/**

Tamaño de la ventana X

**/


float anchoVentana, altoVentana;

float getAnguloX(){
  return view_rotx;
}

void setAnguloX(float x){
  view_rotx = x;
}

float getAnguloY(){
  return view_roty;
}

void setAnguloY(float y){
  view_roty = y;
}

void setPosicion(float x, float y, float z){
  posicion[0] = x;
  posicion[1] = y;
  posicion[2] = z;
}

std::vector<float> getPosicion(){
  return posicion;
}

std::vector<float> getVPN(){
  return vpn;
}

void calculaVPN (){
  vpn = {sin(view_rotx)*sin(view_roty), -cos(view_rotx), -sin(view_rotx)*cos(view_roty)};

  vpn = normalizaVector(vpn);

}

void resetVisualizacion()
{
  view_rotx = 0;
  view_roty = 0;
  posicion[0] = 5;
  posicion[1] = 10;
  posicion[2] = 15;
  D = 10;
}

void actualizarRotacion (float x, float y)
{
  view_rotx += x;
  view_roty += y;
}


/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y el desplazamiento de la camara D.

La cámara mira al origen de coordenadas a una distancia D desde la posición angular view_rotx,
view_roty;

**/
void transformacionVisualizacion ()
{
  calculaVPN();

  gluLookAt(posicion[0], posicion[1], posicion[2],
            posicion[0]+vpn[0], posicion[1]+vpn[1], posicion[2]+vpn[2],
            0, 1, 0);
}

int pick (int x, int y)
{

  GLint viewport[4];
  unsigned char data[4];

  glGetIntegerv ( GL_VIEWPORT , viewport);
  glDisable ( GL_DITHER );
  setIluminacion(false);
  setTexture(false);

  dibujoEscena ();
  glReadPixels ( x, viewport[3]-y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

  setTexture(true);
  setIluminacion(true);
  glEnable ( GL_DITHER );
  glFlush ( );
  glFinish ();

  int resultado = data[0];

  glutPostRedisplay ();
  return resultado;
}

/**	void fijaProyeccion()

Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

**/

void fijaProyeccion ()
{
  float calto;			// altura de la ventana corregida

  if (anchoVentana > 0)
    calto = altoVentana / anchoVentana;
  else
    calto = 1;

  glFrustum (-1, 1, -calto, calto, 1.5, 1500);

  glMatrixMode (GL_MODELVIEW);
// A partir de este momento las transformaciones son de modelado.
  glLoadIdentity ();

}


/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana (GLsizei ancho, GLsizei alto)
{
  altoVentana = alto;
  anchoVentana = ancho;

  glViewport (0, 0, ancho, alto);	// Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  fijaProyeccion ();		// Cargamos la transformacion de proyeccion

}
