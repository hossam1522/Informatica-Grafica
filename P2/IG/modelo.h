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

=======================================================

	 modelo.h
*/

#include <vector>

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

/**
	Funcion de cambio de modo
**/
void setModo (int M);

/**
	Funcion de cambio de iluminacion
**/
void setIluminacion ();

/**
  Funcion de cambio del modo de sombreado
**/
void setSombreado ();



class Objeto3D
{
public:

virtual void draw( ) = 0; // Dibuja el objeto
} ;

class Ejes:public Objeto3D
{
	public:
    float longitud = 30;
	// Dibuja el objeto
	void draw( );
};

class Cubo : public Objeto3D
{
  protected:
	  float lado;

  public:

  Cubo(float lado)
  {
    this->lado = lado;
  }

  void draw();
};

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

  void draw();
};

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

  void draw();
};

class MallaVirtual:public Objeto3D
{
  protected:
    std::vector <float> vertices;
    std::vector <int> triangulos;
    std::vector <float> normales_vertices;

  public:

  MallaVirtual(){};

  MallaVirtual(std::vector <float> vertices, std::vector <int> triangulos);

  MallaVirtual(const char * nombre_archivo);

  void draw();

  void draw_smooth();

  void draw_flat();

  std::vector<float> calculoNormalVertices();

  std::vector<float> calculoNormalCara(std::vector<float> v1, std::vector<float> v2, std::vector<float> v3);

  std::vector<float> normalizaVector(std::vector<float> v);

};

class SuperficieRevolucion:public MallaVirtual
{
  protected:
    std::vector <float> vertices_ply;
    int num_instancias;

  public:

  SuperficieRevolucion(){};

  SuperficieRevolucion(std::vector <float> vertices_ply, int num_instancias);

  SuperficieRevolucion(const char * nombre_archivo, int num_instancias);

};

class BarridoLineal:public MallaVirtual
{
  protected:
    std::vector <float> vertices_plano;
    int num_instancias;
    int altura;

  public:

  BarridoLineal(){};

  BarridoLineal(std::vector <float> vertices_plano, int num_instancias, int altura);

};
