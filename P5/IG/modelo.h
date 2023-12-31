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
  Funcion de encendido y apagado de la luz número i
**/
void setLuz(int i);

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

std::vector<float> normalizaVector(std::vector<float> v);


class Nodo
{
  protected:
    std::vector <Nodo*> hijos;
    GLuint texId=0;
    unsigned char * texImagen;
    unsigned int texAncho, texAlto;
    bool textura = false;

  public:

  virtual void draw(); // Dibuja el objeto

  void addHijo(Nodo* hijo){hijos.push_back(hijo);}

  std::vector <Nodo*> getHijos(){return hijos;}

  void asignarTextura (const char * nombre_archivo);

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
    std::vector <float> coordenadas_textura;
    float color [4] = {0.5, 0.5, 0.5, 1.0}; // Por defecto gris
    float ambiente[4] = {0.2, 0.2, 0.2, 1.0};
    float difusa[4] = {0.8, 0.8, 0.8, 1.0};
    float especular[4] = {0.0, 0.0, 0.0, 1.0};
    float emision[4] = {0.0, 0.0, 0.0, 1.0};
    float shininess[1] = {0.0};
    bool cambio_material = false;

  public:

  MallaVirtual(){};

  MallaVirtual(std::vector <float> vert, std::vector <int> triang);

  void draw();

  void draw_smooth();

  void draw_flat();

  std::vector<float> calculoNormalVertices();

  std::vector<float> calculoNormalCara(std::vector<float> v1, std::vector<float> v2, std::vector<float> v3);
  MallaVirtual & operator=(const MallaVirtual & otro);

  void setColor(float r, float g, float b, float a){color[0] = r;color[1] = g;color[2] = b;color[3] = a;}

  void setAmbiente(float r, float g, float b, float a){
    ambiente[0] = r;ambiente[1] = g;ambiente[2] = b;ambiente[3] = a;cambio_material = true;}

  void setDifusa(float r, float g, float b, float a){
    difusa[0] = r;difusa[1] = g;difusa[2] = b;difusa[3] = a;cambio_material = true;}

  void setEspecular(float r, float g, float b, float a){
    especular[0] = r;especular[1] = g;especular[2] = b;especular[3] = a;cambio_material = true;}

  void setEmision(float r, float g, float b, float a){
    emision[0] = r;emision[1] = g;emision[2] = b;emision[3] = a;cambio_material = true;}

  void setShininess(float s){shininess[0] = s;cambio_material = true;}

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

  SuperficieRevolucion(std::vector <float> vert, int num_inst, bool tapa = false);

  SuperficieRevolucion(const char * nombre_archivo, int num_inst, bool tapa = false);

  void calcularCoordenadasTextura(float xi=0, float xf=1, float yi=0, float yf=1);

  void draw();

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
