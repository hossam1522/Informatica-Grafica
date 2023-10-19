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

using namespace std;

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
    vector <float> vertices;
    vector <int> triangulos;
    vector <float> normales_vertices;

  public:

  MallaVirtual(){};

  MallaVirtual(vector <float> vertices, vector <int> triangulos);

  MallaVirtual(const char * nombre_archivo);

  void draw();

  void draw_smooth();

  void draw_flat();

  vector<float> calculoNormalVertices();

  vector<float> calculoNormalCara(vector<float> v1, vector<float> v2, vector<float> v3);

  vector<float> normalizaVector(vector<float> v);

};

class SuperficieRevolucion:public MallaVirtual
{
  protected:
    vector <float> vertices_ply;
    int num_instancias;

  public:

  SuperficieRevolucion(){};

  SuperficieRevolucion(vector <float> vertices_ply, int num_instancias);

  SuperficieRevolucion(const char * nombre_archivo, int num_instancias);
  
};
