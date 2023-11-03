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

using namespace std;

int modo = GL_FILL;    // Modo de visualizacion inicial (GL_POINT, GL_LINE, GL_FILL)
bool iluminacion = false;   // Visualizacion inicial con iluminacion
bool sombreado = false;   // Visualizacion inicial con sombreado plano (false) y suave (true)
int parameter = 0;

/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel ()
{

}

/**************************************************************************************/

void setParameter(int p)
{
  parameter = p;
}

void leeArchivos(char * nombre_archivo)
{
  if (parameter == 0){
    MallaVirtual malla1("plys/beethoven.ply");
    malla1.draw();
  }

  if (parameter == 3){
    MallaVirtual malla2("plys/big_dodge.ply");
    /* MallaVirtual malla1("001-benchmark/bishop.ply");
    MallaVirtual malla2("001-benchmark/helmet.ply"); */
    malla2.draw();
  }

  if (parameter == 1){
    //SuperficieRevolucion superficie("plys/perfil.ply", 9);
    SuperficieRevolucion superficie("000-benchmark/perfil-3.ply", 9);
    superficie.draw();
  }

  if (parameter == 2){ 
    float radio = 2;
    vector<float> plano;
    for (int i=0; i<18; i++){
      double alpha = 2*M_PI*i/(18-1);
      plano.push_back(radio*cos(alpha));
      plano.push_back(0);
      plano.push_back(radio*sin(alpha));
    }
    BarridoLineal cilindro(plano, vector<float>()={1,1,0}, 6, 5);
    cilindro.draw();
  }

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

}

Cubo cubo(2);

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

Piramide piramide(4, 2);

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

Octaedro octaedro (4,2);

/**************************************************************************************/

MallaVirtual::MallaVirtual(vector <float> vert, vector <int> triang)
{
  this->vertices = vertices;
  this->triangulos = triangulos;

  normales_vertices = calculoNormalVertices();
}

MallaVirtual::MallaVirtual(const char * nombre_archivo)
{
  ply::read(nombre_archivo, vertices, triangulos);

  normales_vertices = calculoNormalVertices();
}

void MallaVirtual::draw(){

  /* for (int i=0; i<triangulos.size(); i+=3){
    glBegin(GL_TRIANGLES);
      glVertex3f(vertices[3*triangulos[i]], vertices[3*triangulos[i]+1], vertices[3*triangulos[i]+2]);
      glVertex3f(vertices[3*triangulos[i+1]], vertices[3*triangulos[i+1]+1], vertices[3*triangulos[i+1]+2]);
      glVertex3f(vertices[3*triangulos[i+2]], vertices[3*triangulos[i+2]+1], vertices[3*triangulos[i+2]+2]);
    glEnd();
  } */

  if (!sombreado)
    draw_flat();
  else
    draw_smooth();

}

void MallaVirtual::draw_smooth(){

  for (int i=0; i<triangulos.size(); i+=3){
    glBegin(GL_TRIANGLES);
      glNormal3f(normales_vertices[3*triangulos[i]], normales_vertices[3*triangulos[i]+1], normales_vertices[3*triangulos[i]+2]);
      glVertex3f(vertices[3*triangulos[i]], vertices[3*triangulos[i]+1], vertices[3*triangulos[i]+2]);
      glNormal3f(normales_vertices[3*triangulos[i+1]], normales_vertices[3*triangulos[i+1]+1], normales_vertices[3*triangulos[i+1]+2]);
      glVertex3f(vertices[3*triangulos[i+1]], vertices[3*triangulos[i+1]+1], vertices[3*triangulos[i+1]+2]);
      glNormal3f(normales_vertices[3*triangulos[i+2]], normales_vertices[3*triangulos[i+2]+1], normales_vertices[3*triangulos[i+2]+2]);
      glVertex3f(vertices[3*triangulos[i+2]], vertices[3*triangulos[i+2]+1], vertices[3*triangulos[i+2]+2]);
    glEnd();
  }

}

void MallaVirtual::draw_flat(){

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
      glVertex3f(vertices[3*triangulos[i]], vertices[3*triangulos[i]+1], vertices[3*triangulos[i]+2]);
      glVertex3f(vertices[3*triangulos[i+1]], vertices[3*triangulos[i+1]+1], vertices[3*triangulos[i+1]+2]);
      glVertex3f(vertices[3*triangulos[i+2]], vertices[3*triangulos[i+2]+1], vertices[3*triangulos[i+2]+2]);
    glEnd();
  }

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

  //return normalizaVector(normal);
  return normal;

}

vector<float> MallaVirtual::normalizaVector(vector<float> v){

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

/**************************************************************************************/

SuperficieRevolucion::SuperficieRevolucion(vector<float> vert, int num_inst){
  this->vertices_ply = vert;
  this->num_instancias = num_inst;

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

  for (int i=0; i<num_instancias; i++)
    for (int j=0; j<vertices_ply.size(); j+=3){

      if (vertices_ply[j] < 0)
        vertices_ply[j] = -vertices_ply[j];
      else if (vertices_ply[j] > 1.0)
        vertices_ply[j] /= 10;

      double alpha = 2*M_PI*i/(num_instancias-1);

      vertices.push_back(vertices_ply[j]*cos(alpha) + vertices_ply[j+2]*sin(alpha) );

      vertices.push_back(vertices_ply[j+1]);

      vertices.push_back(-vertices_ply[j]*sin(alpha) + vertices_ply[j+2]*cos(alpha) );
    }

  int n = vertices_ply.size()*(num_instancias-1);

  for (int i=0; i<num_instancias-1; i++)
    for (int j=0; j<vertices_ply.size()-3; j+=3){
      int k = i*vertices_ply.size()/3 + j/3;

      triangulos.push_back(k % n);
      triangulos.push_back((k+vertices_ply.size()/3) % n);
      triangulos.push_back((k+vertices_ply.size()/3+1) % n);

      triangulos.push_back(k % n);
      triangulos.push_back((k+vertices_ply.size()/3+1) % n);
      triangulos.push_back((k+1) % n);
    }

  normales_vertices = calculoNormalVertices();
}

SuperficieRevolucion::SuperficieRevolucion(const char * nombre_archivo, int num_inst){
  ply::read_vertices(nombre_archivo, vertices_ply);
  this->num_instancias = num_inst;

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

  for (int i=0; i<num_instancias; i++)
    for (int j=0; j<vertices_ply.size(); j+=3){

      if (vertices_ply[j] < 0)
        vertices_ply[j] = -vertices_ply[j];
      else if (vertices_ply[j] > 1.0)
        vertices_ply[j] /= 10;

      double alpha = 2*M_PI*i/(num_instancias-1);

      vertices.push_back(vertices_ply[j]*cos(alpha) + vertices_ply[j+2]*sin(alpha) );

      vertices.push_back(vertices_ply[j+1]);

      vertices.push_back(-vertices_ply[j]*sin(alpha) + vertices_ply[j+2]*cos(alpha) );
    }

  int n = vertices_ply.size()/3*(num_instancias-1);

  for (int i=0; i<num_instancias-1; i++)
    for (int j=0; j<vertices_ply.size()-3; j+=3){
      int k = i*vertices_ply.size()/3 + j/3;

      triangulos.push_back(k % n);
      triangulos.push_back((k+vertices_ply.size()/3) % n);
      triangulos.push_back((k+vertices_ply.size()/3+1) % n);

      triangulos.push_back(k % n);
      triangulos.push_back((k+vertices_ply.size()/3+1) % n);
      triangulos.push_back((k+1) % n);
    }

  normales_vertices = calculoNormalVertices();
}

/**************************************************************************************/

BarridoLineal::BarridoLineal(std::vector <float> vert, vector<float> direcc, int num_inst, int alt){
  this->vertices_plano = vert;
  this->direccion = normalizaVector(direcc);
  this->num_instancias = num_inst;
  this->altura = alt;

  for (int i=0; i<num_instancias; i++){

    float h = i * altura / (num_instancias-1);

    for (int j=0; j<vertices_plano.size(); j+=3){

      float x = h/direccion[1];

      vertices.push_back(vertices_plano[j]+direccion[0]*x);

      vertices.push_back(vertices_plano[j+1]+h);

      vertices.push_back(vertices_plano[j+2]+direccion[2]*x);

    }
  }

  int n = vertices_plano.size()/3*(num_instancias-1);

  for (int i=0; i<num_instancias-2; i++)
    for (int j=0; j<vertices_plano.size()-3; j+=3){
      int k = i*vertices_plano.size()/3 + j/3;

      triangulos.push_back(k % n);
      triangulos.push_back((k+vertices_plano.size()/3) % n);
      triangulos.push_back((k+vertices_plano.size()/3+1) % n);

      triangulos.push_back(k % n);
      triangulos.push_back((k+vertices_plano.size()/3+1) % n);
      triangulos.push_back((k+1) % n);
    }

  normales_vertices = calculoNormalVertices();
}

/**************************************************************************************/

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz
  //static GLfloat  pos[4] = { -13.0, -6.0, 0.0, 0.0 };	// Posicion de la fuente de luz


  float  color[4] = { 0.8, 0.0, 1, 1 };
  float color2[4] = { 0.0, 1.0, 0, 1 };
  float color3[4] = { 0.8, 0.0, 0, 1 };
  float color4[4] = { 0.0, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  //glClearColor (1.0, 1.0, 1.0, 1.0);	// Fija el color de fondo a blanco

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

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

  /* if (parameter == 0) {
    glColor3f(0, 1, 0);
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    glTranslatef(-12, 0, 0);
    malla1.draw();

  } else if (parameter == 1) {
    glColor3f(0.8, 0.0, 1);
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glTranslatef(7, 0, 0);
    superficie.draw();

  } else if (parameter == 2) {
    glColor3f(0, 0.0, 1);
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
    glTranslatef(3.5, 0, 0);
    cilindro.draw();

  } else if (parameter == 3) {
    glColor3f(0.8, 0.0, 0);
    glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
    glTranslatef(13.5, 0, 0);
    malla2.draw();
  } */

  //leeArchivos();

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

void setSombreado ()
{
  sombreado = !sombreado;
}
