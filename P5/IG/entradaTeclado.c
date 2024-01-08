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
modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
//#include <vector>
#include <iostream>


/**

Imprime en la consola las instrucciones del programa

**/
void printHelp ()
{

  printf ("\n\n     Prácticas de Informática Gráfica	Curso 2022-2023");
  printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf ("\n");
  printf ("\n Opciones: \n\n");
  printf ("h, H: Imprime informacion de ayuda \n");
  printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf ("+,-: avanza y retrocede la cámara \n\n");
  printf ("Teclas de movimiento de cursor: giran la camara\n\n");
  // Anyade la informacion de las opciones que introduzcas aqui !!
  printf ("w, W: avanza la cámara \n\n");
  printf ("a, A: mueve la cámara hacia la izquierda sin cambiar la dirección de mira \n\n");
  printf ("s, S: retrocede la cámara \n\n");
  printf ("d, D: mueve la cámara hacia la derecha sin cambiar la dirección de mira \n\n");
  printf ("r, R: resetea la visualización \n\n");
  printf ("p, P: muestra únicamente los vértices de la figura \n\n");
  printf ("l, L: muestra únicamente las aristas de la figura \n\n");
  printf ("f, F: rellena la figura con color \n\n");
  printf ("i, I: cambia el modo de iluminación \n\n");
  printf ("o, O: cambia el tipo de sombreado (flat, smooth) \n\n");
  printf ("C: aumenta el primer grado de libertad \n\n");
  printf ("c: disminuye el primer grado de libertad \n\n");
  printf ("V: aumenta el segundo grado de libertad \n\n");
  printf ("v: disminuye el segundo grado de libertad \n\n");
  printf ("B: aumenta el tercer grado de libertad \n\n");
  printf ("b: disminuye el tercer grado de libertad \n\n");
  printf ("A: activa/desactiva la animación \n\n");
  printf ("G: aumenta la velocidad del primer grado de libertad (solo si está la animacion activada) \n\n");
  printf ("g: disminuye la velocidad del primer grado de libertad (solo si está la animacion activada)\n\n");
  printf ("J: aumenta la velocidad del segundo grado de libertad (solo si está la animacion activada)\n\n");
  printf ("j: disminuye la velocidad del segundo grado de libertad (solo si está la animacion activada)\n\n");
  printf ("K: aumenta la velocidad del tercer grado de libertad (solo si está la animacion activada)\n\n");
  printf ("k: disminuye la velocidad del tercer grado de libertad (solo si está la animacion activada)\n\n");
  printf ("1: activa/desactiva la luz 1\n\n");
  printf ("2: activa/desactiva la luz 2\n\n");
  printf ("\n\n");
  printf (" Uso del programa (parámetros disponibles): \n\n");
  printf ("\t--help -> muestra la ayuda \n\n");
  printf ("\tSIN ARGUMENTOS -> muestra el modelo jerárquico escogido para la práctica \n\n");
  printf ("\t--spin ruta/a/archivo.ply -> muestra solamente el objeto de revolución creado por el perfil del archivo indicado por argumento. \n\n");
  printf ("\t--load ruta/a/archivo.ply -> muestra solamente el objeto PLY cargado a partir del archivo indicado como argumento. \n\n");

  printf ("\n Escape: Salir");
  printf ("\n\n\n");
}




/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;
float x_camara = 5, y_camara = 10, z_camara = 15;

void letra (unsigned char k, int x, int y)
{
  x_camara = getPosicion()[0];
  y_camara = getPosicion()[1];
  z_camara = getPosicion()[2];

  switch (k)
    {
    case 'h':
    case 'H':
      printHelp ();		// H y h imprimen ayuda
      break;
    case '+':			// acerca la cámara
      x_camara += getVPN()[0];
      y_camara += getVPN()[1];
      z_camara += getVPN()[2];
      break;
    case '-':			// aleja la cámara
      x_camara -= getVPN()[0];
      y_camara -= getVPN()[1];
      z_camara -= getVPN()[2];
      break;
    case 'w':
    case 'W':
      x_camara += getVPN()[0];
      y_camara += getVPN()[1];
      z_camara += getVPN()[2];
      break;
    case 'a':
    case 'A':
      x_camara += getVPN()[2];
      z_camara -= getVPN()[0];
      break;
    case 's':
    case 'S':
      x_camara -= getVPN()[0];
      y_camara -= getVPN()[1];
      z_camara -= getVPN()[2];
      break;
    case 'd':
    case 'D':
      x_camara -= getVPN()[2];
      z_camara += getVPN()[0];
      break;
    case 'r':
    case 'R':
      resetVisualizacion();
      break;
    case 'p':
    case 'P':
      setModo (GL_POINT);	// P y p cambian a modo puntos
      break;
    case 'l':
    case 'L':
      setModo (GL_LINE);	// L y l cambian a modo alambre
      break;
    case 'f':
    case 'F':
      setModo (GL_FILL);	// F y f cambian a modo relleno
      break;
    case 'i':
    case 'I':
      setIluminacion (!getIluminacion());	// I y i cambian a modo iluminacion
      break;
    case 'o':
    case 'O':
      setSombreado ();		// S y s cambian a modo sombreado
      break;
    case 't':
    case 'T':
      setTexture (!getTexture());		// T y t cambian a modo textura
      break;
    case 'C':
      aumentarGradoLibertad(0);
      break;
    case 'c':
      disminuirGradoLibertad(0);
      break;
    case 'V':
      aumentarGradoLibertad(1);
      break;
    case 'v':
      disminuirGradoLibertad(1);
      break;
    case 'B':
      aumentarGradoLibertad(2);
      break;
    case 'b':
      disminuirGradoLibertad(2);
      break;
    case 'M':
      setAnimacion();
      break;
    case 'G':
      aumentarVelocidadGradoLibertad(0);
      break;
    case 'g':
      disminuirVelocidadGradoLibertad(0);
      break;
    case 'J':
      aumentarVelocidadGradoLibertad(1);
      break;
    case 'j':
      disminuirVelocidadGradoLibertad(1);
      break;
    case 'K':
      aumentarVelocidadGradoLibertad(2);
      break;
    case 'k':
      disminuirVelocidadGradoLibertad(2);
      break;
    case '1':
      setLuz(0);
      break;
    case '2':
      setLuz(1);
      break;
    case 27:			// Escape  Terminar
      exit (0);
    default:
      return;
    }
  setPosicion (x_camara, y_camara, z_camara);
  glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}				// de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial (int k, int x, int y)
{

  switch (k)
    {
    case GLUT_KEY_UP:
      rotxCamara = getAnguloX() + 5.0;
      if (rotxCamara > 360)
	rotxCamara = getAnguloX() - 360;
      break;
    case GLUT_KEY_DOWN:
      rotxCamara = getAnguloX() - 5.0;
      if (rotxCamara > 360)
	rotxCamara = getAnguloX() + 360;
      break;
    case GLUT_KEY_LEFT:
      rotyCamara = getAnguloY() + 5.0;
      if (rotyCamara > 360)
	rotyCamara = getAnguloY() - 360;
      break;
    case GLUT_KEY_RIGHT:
      rotyCamara = getAnguloY() - 5.0;
      if (rotyCamara > 360)
	rotyCamara = getAnguloY() + 360;
      break;
    case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
      x_camara += getVPN()[0];
      y_camara += getVPN()[1];
      z_camara += getVPN()[2];
      break;
    case GLUT_KEY_PAGE_UP:	// aleja la cámara
      x_camara -= getVPN()[0];
      y_camara -= getVPN()[1];
      z_camara -= getVPN()[2];
      break;
    default:
      return;
    }
  setAnguloX (rotxCamara); setAnguloY (rotyCamara); setPosicion (x_camara, y_camara, z_camara);
  glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}
