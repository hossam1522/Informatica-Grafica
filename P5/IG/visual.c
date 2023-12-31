/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23

	Codigo base para la realización de las practicas de IG

	Estudiante: Hossam El Amraoui Leghzali

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
#include "practicasIG.h"
#include <vector>




//================================================ VARIABLES

/**

Angulos de rotacion de la camara.

**/

float view_rotx = 30, view_roty = 45;
float camara_x = 0, camara_y = 5, camara_z = 5; // Posicion de la camara
float pos_x = 0, pos_y = 0; // Lugar hacia donde mira la camara
std::vector<float> direccion = {pos_x - camara_x, pos_y - camara_y, pos_z - camara_z};

/**

Distancia de la cámara

**/

float D = 10;


/**

Tamaño de la ventana X

**/


float anchoVentana, altoVentana;




/** 	void setCamara()

Cambia los parámetros de la cámara en el modulo visual

**/
void setCamara (float ax, float ay, float d)
{
  view_rotx = ax;
  view_roty = ay;

  D = d;
}

void setPuntoDeMira (float x, float y)
{
  pos_x = x;
  pos_y = y;
}

void setPosicion (float x, float y, float z)
{
  camara_x = x;
  camara_y = y;
  camara_z = z;
}

std::vector<float> getDireccion ()
{
  return direccion;
}

void setDireccion (std::vector<float> direcc)
{
  direccion = direcc;
}

void actualizaDireccion ()
{
  direccion = {pos_x - camara_x, pos_y - camara_y, pos_z - camara_z};
}


/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y el desplazamiento de la camara D.

La cámara mira al origen de coordenadas a una distancia D desde la posición angular view_rotx,
view_roty;

**/
void transformacionVisualizacion ()
{

  direccion = normalizaVector(direccion);

  gluLookAt (camara_x, camara_y, camara_z,
             camara_x+direccion[0], camara_y+direccion[1], camara_z+direccion[2],
             0.0, 1.0, 0.0);

  //glTranslatef (0, 0, -D);

  /* glRotatef (view_rotx, 1.0, 0.0, 0.0);
  glRotatef (view_roty, 0.0, 1.0, 0.0); */

  /* setPosicion(pos_x,
               pos_y*cos(view_rotx)-pos_z*sin(view_rotx),
               pos_y*sin(view_rotx)+pos_z*cos(view_rotx));

  setPosicion(pos_x*cos(view_roty)+pos_z*sin(view_roty),
               pos_y,
               -pos_x*sin(view_roty)+pos_z*cos(view_roty)); */

  //setDireccion({pos_x - camara_x, pos_y - camara_y, pos_z - camara_z});

  //glTranslatef(-camara_x,-camara_y,-camara_z);
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
