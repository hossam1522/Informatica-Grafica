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

enum TipoTransformacion {ROTACION, TRASLACION};

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
void initModel (int opcion = 0, char * nombre_archivo = NULL);

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

/**
 * Funcion de cambio de animacion
*/
void setAnimacion();

/**
 * Aumenta el grado de libertad número i
*/
void aumentarGradoLibertad(int i);

/**
 * Disminuye el grado de libertad número i
*/
void disminuirGradoLibertad(int i);

/**
 * Aumenta la velocidad del grado de libertad número i (solo si la animación está activada)
*/
void aumentarVelocidadGradoLibertad(int i);

/**
 * Disminuye la velocidad del grado de libertad número i (solo si la animación está activada)
*/
void disminuirVelocidadGradoLibertad(int i);

class Nodo
{
  protected:
    std::vector <Nodo*> hijos;

  public:

  virtual void draw(); // Dibuja el objeto

  void addHijo(Nodo* hijo){hijos.push_back(hijo);}

  std::vector <Nodo*> getHijos(){return hijos;}

};

class Ejes:public Nodo
{
	public:
    float longitud = 30;
	// Dibuja el objeto
	void draw( );
};

class Cubo : public Nodo
{
  protected:
	  float lado, alto, ancho;

  public:

  Cubo(float lado)
  {
    this->lado = lado;
    this->alto = lado;
    this->ancho = lado;
  }

  Cubo(float lado, float alto, float ancho)
  {
    this->lado = lado;
    this->alto = alto;
    this->ancho = ancho;
  }

  void draw();
};

class Piramide:public Nodo
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

class Octaedro:public Nodo
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

class MallaVirtual:public Nodo
{
  protected:
    std::vector <float> vertices;
    std::vector <int> triangulos;
    std::vector <float> normales_vertices;

  public:

  MallaVirtual(){};

  MallaVirtual(std::vector <float> vert, std::vector <int> triang);

  void draw();

  void draw_smooth();

  void draw_flat();

  std::vector<float> calculoNormalVertices();

  std::vector<float> calculoNormalCara(std::vector<float> v1, std::vector<float> v2, std::vector<float> v3);

  std::vector<float> normalizaVector(std::vector<float> v);

  MallaVirtual & operator=(const MallaVirtual & otro);

};

class PLY:public MallaVirtual
{
  public:

  PLY(){};

  PLY(const char * nombre_archivo);

};

class SuperficieRevolucion:public MallaVirtual
{
  protected:
    std::vector <float> vertices_ply;
    int num_instancias;

  public:

  SuperficieRevolucion(){};

  SuperficieRevolucion(std::vector <float> vert, int num_inst);

  SuperficieRevolucion(const char * nombre_archivo, int num_inst);

};

class Transformacion:public Nodo
{
  protected:
    TipoTransformacion tipo;
    std::vector<float> valor;
    bool variable;

  public:
    Transformacion(){};

    Transformacion(TipoTransformacion tipo, std::vector<float> valor, bool variable=false)
    {this->tipo = tipo;this->valor = valor;this->variable = variable;}

    void draw();

    bool esLibre(){return variable;}

    float getValorRotacion(){if(tipo==ROTACION)return valor[0];else return -1;}

    void setValorRotacion(float valor){if(tipo==ROTACION && variable==true)this->valor[0] = valor;}

    std::vector<float> getValorTraslacion(){if(tipo==TRASLACION)return valor;else return {-1};}

    void setValorTraslacion(std::vector<float> valor){if(tipo==TRASLACION && variable==true)this->valor = valor;}
};
