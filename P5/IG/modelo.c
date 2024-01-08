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
#include "lector-jpg.h"

using namespace std;

int modo = GL_FILL;    // Modo de visualizacion inicial (GL_POINT, GL_LINE, GL_FILL)
bool iluminacion = true;   // Visualizacion inicial con iluminacion
bool luces[2] = {true, true};   // Luces inicialmente encendidas
bool sombreado = true;   // Visualizacion inicial con sombreado plano (false) y suave (true)
bool animacion = false;   // Animación inicial desactivada
bool texture = true;   // Textura inicialmente desactivada
int  a_dibujar = 0;     // Objeto a dibujar (0: practica original, 1: superficie, 2: malla)
float gl0 = 5;   // Grado de libertad 1
bool max0 = false;   // Grado de libertad 1 en su valor máximo
float gl1 = 5;   // Grado de libertad 2
bool max1 = false;   // Grado de libertad 2 en su valor máximo
float gl2 = 0.1;   // Grado de libertad 3
bool max2 = false;   // Grado de libertad 3 en su valor máximo
PLY malla;
SuperficieRevolucion superficie;
SuperficieRevolucion cilindro("plys/cilindro.ply", 20);
SuperficieRevolucion objeto1("plys/perfil.ply", 20, true);
SuperficieRevolucion objeto2 = objeto1;
SuperficieRevolucion objeto3 = objeto1;
vector<Nodo*> nodos;
float color_seleccion[4] = {1, 1, 1, 1};

/**************************************************************************************/
/**************************************************************************************/

/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel (int opcion, char * nombre_archivo)
{
  if (opcion == 0){
    cilindro.asignarTextura("jpgs/s_textura_test.jpg");
    cilindro.calcularCoordenadasTextura();
    cilindro.setColor(0.5, 0.5, 0.5, 1);
    cilindro.ColorSeleccion(1, 0);

    objeto1.setAmbiente(0, 0, 1, 1);
    objeto1.setDifusa(1, 1, 1, 1);
    objeto1.setEspecular(1, 1, 1, 1);
    objeto1.setShininess(128);
    objeto1.setColor(0, 0, 1, 1);
    objeto1.ColorSeleccion(2, 0);

    objeto2.setAmbiente(0, 0, 0, 1);
    objeto2.setDifusa(0, 1, 0, 1);
    objeto2.setColor(0, 1, 0, 1);
    objeto2.ColorSeleccion(3, 0);

    objeto3.setEmision(1, 0, 0, 1);
    objeto3.setAmbiente(0, 0, 0, 1);
    objeto3.setDifusa(0, 0, 0, 1);
    objeto3.setColor(1, 0, 0, 1);
    objeto3.ColorSeleccion(4, 0);

    nodos = {&cilindro, &objeto1, &objeto2, &objeto3};
  }
  else if (opcion == 1){
    superficie = SuperficieRevolucion(nombre_archivo, 20);
    nodos = {&superficie};
  } else if (opcion == 2){
    malla = PLY(nombre_archivo);
    nodos = {&malla};
  }

  a_dibujar = opcion;
}

/**************************************************************************************/

void Ejes::draw( )
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

Ejes ejesCoordenadas;

/**************************************************************************************/

void Cubo::draw()
{
  if (textura){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
  }

  float color[4]={0.5,0.5,0.5,1};
  float nocolor[4]={0,0,0,1};
  glColor3f(0.5, 0.5, 0.5);
  glMaterialfv (GL_FRONT, GL_AMBIENT, nocolor);
  glMaterialfv (GL_FRONT, GL_DIFFUSE, nocolor);
  glMaterialfv (GL_FRONT, GL_SPECULAR, nocolor);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  glBegin(GL_QUADS);
    // left
    glNormal3f(1.0f, 0.0f, 0.0f);
    if (textura) glTexCoord2f( 0.75, 0.25);
    glVertex3f(lado, 0, 0);
    if (textura) glTexCoord2f( 0.5, 0.25);
    glVertex3f(lado, alto, 0);
    if (textura) glTexCoord2f( 0.5, 0.5);
    glVertex3f(lado, alto, ancho);
    if (textura) glTexCoord2f( 0.75, 0.5);
    glVertex3f(lado,0, ancho);

    // right
    glNormal3f(-1.0f, 0.0f, 0.0f);
    if (textura) glTexCoord2f( 0.75, 1.00);
    glVertex3f(0, 0, 0);
    if (textura) glTexCoord2f( 0.75, 0.75);
    glVertex3f(0, 0, ancho);
    if (textura) glTexCoord2f( 0.5, 0.75);
    glVertex3f(0, alto, ancho);
    if (textura) glTexCoord2f( 0.5, 1.0);
    glVertex3f(0, alto, 0);

    // front
    glNormal3f(0.0f, 0.0f, 1.0f);
    if (textura) glTexCoord2f( 0.5, 0.75);
    glVertex3f(lado, alto, ancho);
    if (textura) glTexCoord2f( 0.5, 0.5);
    glVertex3f(0, alto, ancho);
    if (textura) glTexCoord2f( 0.75, 0.5);
    glVertex3f(0, 0, ancho);
    if (textura) glTexCoord2f( 0.75, 0.75);
    glVertex3f(lado, 0, ancho);

    // bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    if (textura) glTexCoord2f( 0.75, 0.75);
    glVertex3f(lado, 0, ancho);
    if (textura) glTexCoord2f( 0.75, 0.5);
    glVertex3f(0, 0, ancho);
    if (textura) glTexCoord2f( 1, 0.5);
    glVertex3f(0, 0, 0);
    if (textura) glTexCoord2f( 1, 0.75);
    glVertex3f(lado, 0, 0);

    // back
    glNormal3f(0.0f, 0.0f, -1.0f);
    if (textura) glTexCoord2f( 0.25, 0.5);
    glVertex3f(0, alto, 0);
    if (textura) glTexCoord2f( 0.25, 0.75);
    glVertex3f(lado, alto, 0);
    if (textura) glTexCoord2f( 0, 0.75);
    glVertex3f(lado, 0, 0);
    if (textura) glTexCoord2f( 0, 0.5);
    glVertex3f(0, 0, 0);

    // top
    glNormal3f(0.0f, 1.0f, 0.0f);
    if (textura) glTexCoord2f( 0.25, 0.75);
    glVertex3f(lado, alto, 0);
    if (textura) glTexCoord2f( 0.25, 0.5);
    glVertex3f(0, alto, 0);
    if (textura) glTexCoord2f( 0.5, 0.5);
    glVertex3f(0, alto, ancho);
    if (textura) glTexCoord2f( 0.5, 0.75);
    glVertex3f(lado, alto, ancho);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}

/**************************************************************************************/

void Piramide::draw(){

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

/**************************************************************************************/

void Octaedro::draw(){

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

/**************************************************************************************/

MallaVirtual::MallaVirtual(vector <float> vert, vector <int> triang)
{
  this->vertices = vertices;
  this->triangulos = triangulos;

  normales_vertices = calculoNormalVertices();
}

PLY::PLY(const char * nombre_archivo)
{
  ply::read(nombre_archivo, vertices, triangulos);

  normales_vertices = calculoNormalVertices();
}

void MallaVirtual::draw(){
  if (cambio_color)
      glColor3ub(color_seleccionado[0], color_seleccionado[1], color_seleccionado[2]);

  if (!seleccionado){
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  }
  else{
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_seleccion);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_seleccion);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color_seleccion);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color_seleccion);
  }

  if (!cambio_material)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

  if (!sombreado)
    draw_flat();
  else
    draw_smooth();

}

void MallaVirtual::draw_smooth(){

  if (textura){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
  }

  for (int i=0; i<triangulos.size(); i+=3){
    glBegin(GL_TRIANGLES);
      glNormal3f(normales_vertices[3*triangulos[i]], normales_vertices[3*triangulos[i]+1], normales_vertices[3*triangulos[i]+2]);
      if (textura) glTexCoord2f( coordenadas_textura[2*triangulos[i]], coordenadas_textura[2*triangulos[i]+1]);
      glVertex3f(vertices[3*triangulos[i]], vertices[3*triangulos[i]+1], vertices[3*triangulos[i]+2]);
      glNormal3f(normales_vertices[3*triangulos[i+1]], normales_vertices[3*triangulos[i+1]+1], normales_vertices[3*triangulos[i+1]+2]);
      if (textura) glTexCoord2f( coordenadas_textura[2*triangulos[i+1]], coordenadas_textura[2*triangulos[i+1]+1]);
      glVertex3f(vertices[3*triangulos[i+1]], vertices[3*triangulos[i+1]+1], vertices[3*triangulos[i+1]+2]);
      glNormal3f(normales_vertices[3*triangulos[i+2]], normales_vertices[3*triangulos[i+2]+1], normales_vertices[3*triangulos[i+2]+2]);
      if (textura) glTexCoord2f( coordenadas_textura[2*triangulos[i+2]], coordenadas_textura[2*triangulos[i+2]+1]);
      glVertex3f(vertices[3*triangulos[i+2]], vertices[3*triangulos[i+2]+1], vertices[3*triangulos[i+2]+2]);
    glEnd();
  }

  glDisable(GL_TEXTURE_2D);
}

void MallaVirtual::draw_flat(){

  if (textura){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
  }

  for (int i=0; i<triangulos.size(); i+=3){

    // Calculamos la normal del triángulo a partir de las normales de sus vértices
    vector<float> normal(3, 0);

    normal[0] = normales_vertices[3*triangulos[i]]+
                normales_vertices[3*triangulos[i+1]]+
                normales_vertices[3*triangulos[i+2]];

    normal[1] = normales_vertices[3*triangulos[i]+1]+
                normales_vertices[3*triangulos[i+1]+1]+
                normales_vertices[3*triangulos[i+2]+1];

    normal[2] = normales_vertices[3*triangulos[i]+2]+
                normales_vertices[3*triangulos[i+1]+2]+
                normales_vertices[3*triangulos[i+2]+2];

    normal = normalizaVector(normal);

    glBegin(GL_TRIANGLES);
      glNormal3f(normal[0], normal[1], normal[2]);
      if (textura) glTexCoord2f( coordenadas_textura[2*triangulos[i]], coordenadas_textura[2*triangulos[i]+1]);
      glVertex3f(vertices[3*triangulos[i]], vertices[3*triangulos[i]+1], vertices[3*triangulos[i]+2]);
      if (textura) glTexCoord2f( coordenadas_textura[2*triangulos[i+1]], coordenadas_textura[2*triangulos[i+1]+1]);
      glVertex3f(vertices[3*triangulos[i+1]], vertices[3*triangulos[i+1]+1], vertices[3*triangulos[i+1]+2]);
      if (textura) glTexCoord2f( coordenadas_textura[2*triangulos[i+2]], coordenadas_textura[2*triangulos[i+2]+1]);
      glVertex3f(vertices[3*triangulos[i+2]], vertices[3*triangulos[i+2]+1], vertices[3*triangulos[i+2]+2]);
    glEnd();
  }

  glDisable(GL_TEXTURE_2D);
}

vector<float> MallaVirtual::calculoNormalCara(vector<float> v1, vector<float> v2, vector<float> v3){

  vector<float> normal;

  float v1x = v1[0];
  float v1y = v1[1];
  float v1z = v1[2];

  float v2x = v2[0];
  float v2y = v2[1];
  float v2z = v2[2];

  float v3x = v3[0];
  float v3y = v3[1];
  float v3z = v3[2];

  float a1 = v2x - v1x;
  float a2 = v2y - v1y;
  float a3 = v2z - v1z;

  float b1 = v3x - v1x;
  float b2 = v3y - v1y;
  float b3 = v3z - v1z;

  normal.push_back(a2*b3 - a3*b2);
  normal.push_back(a3*b1 - a1*b3);
  normal.push_back(a1*b2 - a2*b1);

  return normal;

}

vector<float> MallaVirtual::calculoNormalVertices(){

  vector<float> normales (vertices.size(), 0);

  for (int i=0; i<triangulos.size(); i+=3){
    vector<float> v1;
    v1.push_back(vertices[3*triangulos[i]]);
    v1.push_back(vertices[3*triangulos[i]+1]);
    v1.push_back(vertices[3*triangulos[i]+2]);

    vector<float> v2;
    v2.push_back(vertices[3*triangulos[i+1]]);
    v2.push_back(vertices[3*triangulos[i+1]+1]);
    v2.push_back(vertices[3*triangulos[i+1]+2]);

    vector<float> v3;
    v3.push_back(vertices[3*triangulos[i+2]]);
    v3.push_back(vertices[3*triangulos[i+2]+1]);
    v3.push_back(vertices[3*triangulos[i+2]+2]);

    vector<float> normal = calculoNormalCara(v1, v2, v3);

    normales[3*triangulos[i]] += normal[0];
    normales[3*triangulos[i]+1] += normal[1];
    normales[3*triangulos[i]+2] += normal[2];

    normales[3*triangulos[i+1]] += normal[0];
    normales[3*triangulos[i+1]+1] += normal[1];
    normales[3*triangulos[i+1]+2] += normal[2];

    normales[3*triangulos[i+2]] += normal[0];
    normales[3*triangulos[i+2]+1] += normal[1];
    normales[3*triangulos[i+2]+2] += normal[2];
  }

  return normalizaVector(normales);
}

MallaVirtual& MallaVirtual::operator=(const MallaVirtual &m){
  vertices = m.vertices;
  triangulos = m.triangulos;
  normales_vertices = m.normales_vertices;
  coordenadas_textura = m.coordenadas_textura;
  for (int i=0; i<4; i++){
    ambiente[i] = m.ambiente[i];
    difusa[i] = m.difusa[i];
    especular[i] = m.especular[i];
    color[i] = m.color[i];
  }
  cambio_material = m.cambio_material;

  return *this;
}

/**************************************************************************************/

SuperficieRevolucion::SuperficieRevolucion(vector<float> vert, int num_inst, bool tapa){
  this->vertices_ply = vert;
  this->num_instancias = num_inst;

  if (tapa){
    if (vertices_ply[0] !=0 || vertices_ply[2]!=0){
      float h = vertices_ply[1];

      vertices_ply.insert(vertices_ply.begin(), 0);
      vertices_ply.insert(vertices_ply.begin()+1, h);
      vertices_ply.insert(vertices_ply.begin()+2, 0);
    }

    if (vertices_ply[vertices_ply.size()-3] !=0 || vertices_ply[vertices_ply.size()-1]!=0){
      float h = vertices_ply[vertices_ply.size()-2];

      vertices_ply.push_back(0);
      vertices_ply.push_back(h);
      vertices_ply.push_back(0);
    }
  }

  for (int i=0; i<num_instancias; i++)
    for (int j=0; j<vertices_ply.size(); j+=3){

      if (vertices_ply[j] < 0)
        vertices_ply[j] = -vertices_ply[j];

      double alpha = 2*M_PI*i/(num_instancias-1);

      vertices.push_back(vertices_ply[j]*cos(alpha) + vertices_ply[j+2]*sin(alpha) );

      vertices.push_back(vertices_ply[j+1]);

      vertices.push_back(-vertices_ply[j]*sin(alpha) + vertices_ply[j+2]*cos(alpha) );
    }
}

SuperficieRevolucion::SuperficieRevolucion(const char * nombre_archivo, int num_inst, bool tapa){
  ply::read_vertices(nombre_archivo, vertices_ply);
  this->num_instancias = num_inst;

  if (tapa){
    if (vertices_ply[0] !=0 || vertices_ply[2]!=0){
      float h = vertices_ply[1];

      vertices_ply.insert(vertices_ply.begin(), 0);
      vertices_ply.insert(vertices_ply.begin()+1, h);
      vertices_ply.insert(vertices_ply.begin()+2, 0);
    }

    if (vertices_ply[vertices_ply.size()-3] !=0 || vertices_ply[vertices_ply.size()-1]!=0){
      float h = vertices_ply[vertices_ply.size()-2];

      vertices_ply.push_back(0);
      vertices_ply.push_back(h);
      vertices_ply.push_back(0);
    }
  }

  for (int i=0; i<num_instancias; i++)
    for (int j=0; j<vertices_ply.size(); j+=3){

      if (vertices_ply[j] < 0)
        vertices_ply[j] = -vertices_ply[j];

      double alpha = 2*M_PI*i/(num_instancias-1);

      vertices.push_back(vertices_ply[j]*cos(alpha) + vertices_ply[j+2]*sin(alpha) );

      vertices.push_back(vertices_ply[j+1]);

      vertices.push_back(-vertices_ply[j]*sin(alpha) + vertices_ply[j+2]*cos(alpha) );
    }

}

void SuperficieRevolucion::calcularCoordenadasTextura(float xi, float xf, float yi, float yf){
  if (textura){
    float d[vertices_ply.size()/3];
    d[0]=0;

    for (int i=1; i<vertices_ply.size()/3; i++){
      float x1 = vertices_ply[3*i];
      float y1 = vertices_ply[3*i+1];
      float z1 = vertices_ply[3*i+2];

      float x2 = vertices_ply[3*(i-1)];
      float y2 = vertices_ply[3*(i-1)+1];
      float z2 = vertices_ply[3*(i-1)+2];

      d[i] = d[i-1] + sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
    }

    for (float i=0; i<num_instancias; i++){
      float u = xi+(xf-xi)*i/(num_instancias-1);
      for (unsigned int j=0; j<vertices_ply.size()/3; j++){
        float v = 1.0 - (yi+(yf-yi)*d[j]/d[vertices_ply.size()/3-1]);

        coordenadas_textura.push_back(u);
        coordenadas_textura.push_back(v);
      }
    }
  }
}

void SuperficieRevolucion::draw(){
  vector<int> tmp; // Para guardar los triángulos

  if (!textura){
    int n = vertices_ply.size()/3*(num_instancias-1);

    for (int i=0; i<num_instancias-1; i++)
      for (int j=0; j<vertices_ply.size()-3; j+=3){
        int k = i*vertices_ply.size()/3 + j/3;

        tmp.push_back(k % n);
        tmp.push_back((k+vertices_ply.size()/3) % n);
        tmp.push_back((k+vertices_ply.size()/3+1) % n);

        tmp.push_back(k % n);
        tmp.push_back((k+vertices_ply.size()/3+1) % n);
        tmp.push_back((k+1) % n);
      }
  }
  else {
    int n = vertices_ply.size()/3*(num_instancias-1);

    for (int i=0; i<num_instancias-1; i++)
      for (int j=0; j<vertices_ply.size()-3; j+=3){
        int k = i*vertices_ply.size()/3 + j/3;

        tmp.push_back(k );
        tmp.push_back((k+vertices_ply.size()/3) );
        tmp.push_back((k+vertices_ply.size()/3+1) );

        tmp.push_back(k );
        tmp.push_back((k+vertices_ply.size()/3+1) );
        tmp.push_back((k+1) );
      }
  }

  triangulos = tmp;
  normales_vertices = calculoNormalVertices();

  if (cambio_color)
    glColor3ub(color_seleccionado[0], color_seleccionado[1], color_seleccionado[2]);

  if (!seleccionado){
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difusa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  }
  else{
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_seleccion);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_seleccion);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color_seleccion);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color_seleccion);
  }

  if (!cambio_material)
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

  if (!sombreado)
    draw_flat();
  else
    draw_smooth();
}

/**************************************************************************************/

void Nodo :: draw(){
  glPushMatrix();
    for (int i = 0; i < hijos.size(); i++) {
      hijos[i]->draw();
    }
  glPopMatrix();
}

void Transformacion :: draw(){
  switch (tipo) {
    case ROTACION:
      glRotatef(valor[0], valor[1], valor[2], valor[3]);
      break;
    case TRASLACION:
      glTranslatef(valor[0], valor[1], valor[2]);
      break;
  }
}

/**************************************************************************************/

void Nodo::asignarTextura(const char * nombre_archivo){
  texImagen = LeerArchivoJPEG(nombre_archivo, texAncho, texAlto);
  textura = true;
  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texAncho,texAlto,0,GL_RGB,GL_UNSIGNED_BYTE,texImagen);
}

/**************************************************************************************/

void Nodo::ColorSeleccion ( int i , int componente )
{
  cambio_color = true;
  unsigned char r = ( i & 0xFF ) ;
  unsigned char g = ( componente & 0xFF ) ;
  color_seleccionado[0] = r;
  color_seleccionado[1] = g;
  color_seleccionado[2] = 0;
}

/**************************************************************************************/

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void){
  dibujoEscena();
  glutSwapBuffers();
}

void dibujoEscena (void)
{
  static GLfloat  pos1[4] = { 0, 0.0, 5.0, 0.0 };	// Posicion de la fuente de luz
  static GLfloat  pos2[4] = { -13.0, 0.0, -10.0, 0.0 };	// Posicion de la fuente de luz

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  //glClearColor (1.0, 1.0, 1.0, 1.0);	// Fija el color de fondo a blanco

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos1);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  glPointSize(5);

  setModo (modo);           // Establece el modo de dibujo inicial

  if (!iluminacion)         // Establece el tipo de iluminación inicial
    glDisable(GL_LIGHTING);
  else
    glEnable(GL_LIGHTING);

  if (!sombreado)
    glShadeModel(GL_FLAT);
  else
    glShadeModel(GL_SMOOTH);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)

  if (a_dibujar == 0){
    glScalef(4, 4, 4);
    cilindro.draw();
    glTranslatef(3,0,0);
    objeto1.draw();
    glTranslatef(3,0,0);
    objeto2.draw();
    glTranslatef(3,0,0);
    objeto3.draw();
  }
  else if (a_dibujar == 1){
    superficie.ColorSeleccion(1, 0);
    superficie.draw();
  }
  else if (a_dibujar == 2){
    malla.ColorSeleccion(1, 0);
    malla.draw();
  }

  glPopMatrix ();		// Desapila la transformacion geometrica


  //glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{
  if (animacion){
    aumentarGradoLibertad(0);
    if (max1)
      disminuirGradoLibertad(1);
    else
      aumentarGradoLibertad(1);
    if (max2)
      disminuirGradoLibertad(2);
    else
      aumentarGradoLibertad(2);
  }

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}

void setModo (int M)
{
  modo = M;
  glPolygonMode (GL_FRONT_AND_BACK, modo);
}

void setIluminacion (bool i)
{
  iluminacion = i;
}

bool getIluminacion ()
{
  return iluminacion;
}

void setLuz(int i){
  luces[i] = !luces[i];
}

void setSombreado ()
{
  sombreado = !sombreado;
}

void setAnimacion ()
{
  animacion = !animacion;
}

void setTexture(bool t){
  texture = t;

  if (!texture){
    cilindro.setTextura(false);
  }
  else {
    cilindro.setTextura(true);
  }
}

bool getTexture(){
  return texture;
}

void aumentarGradoLibertad(int i){
}

void disminuirGradoLibertad(int i){
}

void aumentarVelocidadGradoLibertad(int i){
  if (animacion)
    if (i==0)
      gl0+=5;
    else if (i==1 && gl1<90)
      gl1+=5;
    else if (i==2 && gl2<1)
      gl2+=0.1;
}

void disminuirVelocidadGradoLibertad(int i){
  if (animacion)
    if (i==0)
      gl0-=5;
    else if (i==1 && gl1>0)
      gl1-=5;
    else if (i==2 && gl2>0.1)
      gl2-=0.1;
}

vector<float> normalizaVector(vector<float> v){

  for (int i=0; i<v.size(); i+=3){
    float modulo = sqrt(v[i]*v[i] + v[i+1]*v[i+1] + v[i+2]*v[i+2]);
    if (modulo > 0){
      v[i] = v[i]/modulo;
      v[i+1] = v[i+1]/modulo;
      v[i+2] = v[i+2]/modulo;
    }
  }

  return v;

}

vector<Nodo*> getNodos(){
  return nodos;
}

