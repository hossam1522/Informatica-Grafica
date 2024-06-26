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
	modulo mouse.c
	Gestion de eventos de raton

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "visual.h"
#include "practicasIG.h"
#include <iostream>

/**	 void clickRaton( int boton, int estado, int x, int y )

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

bool MOVIENDO_CAMARA = false;
float xant = 0, yant = 0;

void clickRaton (int boton, int estado, int x, int y)
{
	if (boton == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN)
		MOVIENDO_CAMARA = true;
	else
		MOVIENDO_CAMARA = false;

	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
		int figura = pick (x, y);
		for (int i = 0; i < getNodos().size(); i++)
			if (figura-1 == i)
				getNodos()[i]->setSeleccionado(true);
			else
				getNodos()[i]->setSeleccionado(false);
	}

}


/**	void RatonMovido( int x, int y )

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido (int x, int y)
{
	if (MOVIENDO_CAMARA)
	{
		actualizarRotacion((y-yant)/100, (x-xant)/100);
		xant = x;
		yant = y;
	}

	glutPostRedisplay();
}
