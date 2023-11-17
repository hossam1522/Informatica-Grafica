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
bool animacion = false;   // Animación inicial desactivada
int  a_dibujar = 0;     // Objeto a dibujar (0: practica original, 1: superficie, 2: malla)
float gl0 = 5;   // Grado de libertad 1
bool max0 = false;   // Grado de libertad 1 en su valor máximo
float gl1 = 5;   // Grado de libertad 2
bool max1 = false;   // Grado de libertad 2 en su valor máximo
float gl2 = 0.1;   // Grado de libertad 3
bool max2 = false;   // Grado de libertad 3 en su valor máximo
PLY malla;
SuperficieRevolucion superficie;

/**************************************************************************************/
/**
 * @brief Telescopio
 *
 */
SuperficieRevolucion A("plys/A.ply", 20);
SuperficieRevolucion B("plys/B.ply", 20);
SuperficieRevolucion C("plys/C.ply", 20);
SuperficieRevolucion D_("plys/D.ply", 20);
SuperficieRevolucion SoporteCabeza("plys/SoporteCabeza.ply", 20);
SuperficieRevolucion P("plys/Pata.ply", 20);

Nodo *Telescopio = new Nodo();
Nodo *Cabeza = new Nodo();
Nodo *Patas = new Nodo();
Nodo *Pata = new Nodo();
Nodo *Cuerpo = new Nodo();
Nodo *Mira = new Nodo();

Transformacion T1(TRASLACION, vector<float>()={0, 3, 0});
Transformacion T2(TRASLACION, vector<float>()={0, -6, 0});
Transformacion T3(TRASLACION, vector<float>()={0, 0, 0});
Transformacion T4(TRASLACION, vector<float>()={0, 0, 0});
Transformacion T5(TRASLACION, vector<float>()={-4.5, 0, 0});
Transformacion T6(TRASLACION, vector<float>()={-3, -1, 0});
Transformacion T7(TRASLACION, vector<float>()={0, -6, 0});
Transformacion T8(TRASLACION, vector<float>()={0, 14, 0});
Transformacion T9(TRASLACION, vector<float>()={0, 2, 0});
Transformacion Ta(TRASLACION, vector<float>()={0, 0, 0}, true);
Transformacion R1(ROTACION, vector<float>()={120, 0, 1, 0});
Transformacion R2(ROTACION, vector<float>()={120, 0, 1, 0});
Transformacion R3(ROTACION, vector<float>()={-37, 0, 0, 1});
Transformacion R4(ROTACION, vector<float>()={-60, 0, 0, 1});
Transformacion R5(ROTACION, vector<float>()={90, 0, 0, 1});
Transformacion R6(ROTACION, vector<float>()={90, 0, 0, 1});
Transformacion Ra(ROTACION, vector<float>()={0, 0, 1, 0}, true);
Transformacion Rb(ROTACION, vector<float>()={0, 0, 0, 1}, true);

/**************************************************************************************/


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel (int opcion, char * nombre_archivo)
{
  if (opcion == 0){
    Pata->addHijo(&T5);Pata->addHijo(&R3);Pata->addHijo(&P);
    Patas->addHijo(&T2);Patas->addHijo(Pata);Patas->addHijo(&T3);Patas->addHijo(&R1);Patas->addHijo(Pata);
    Patas->addHijo(&T4);Patas->addHijo(&R2);Patas->addHijo(Pata);
    Cuerpo->addHijo(&B);Cuerpo->addHijo(&T7);Cuerpo->addHijo(&C);Cuerpo->addHijo(&Ta);
    Cuerpo->addHijo(&T8);Cuerpo->addHijo(&A);
    Mira->addHijo(&D_);Mira->addHijo(&T9);Mira->addHijo(&R6);Mira->addHijo(&D_);
    Cabeza->addHijo(&R4);Cabeza->addHijo(Cuerpo);Cabeza->addHijo(&T6);Cabeza->addHijo(&R5);Cabeza->addHijo(Mira);
    Telescopio->addHijo(Patas);Telescopio->addHijo(&SoporteCabeza);Telescopio->addHijo(&T1);
    Telescopio->addHijo(&Ra);Telescopio->addHijo(&Rb);Telescopio->addHijo(Cabeza);
  }
  else if (opcion == 1){
    superficie = SuperficieRevolucion(nombre_archivo, 20);
  } else if (opcion == 2){
    malla = PLY(nombre_archivo);
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
  glBegin(GL_QUADS);
    // right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(lado, 0, 0);
    glVertex3f(lado, alto, 0);
    glVertex3f(lado, alto, ancho);
    glVertex3f(lado,0, ancho);

    // left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, ancho);
    glVertex3f(0, alto, ancho);
    glVertex3f(0, alto, 0);

  glEnd();

  glBegin(GL_QUAD_STRIP);

    // front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(lado, alto, ancho);
    glVertex3f(0, alto, ancho);
    glVertex3f(lado, 0, ancho);
    glVertex3f(0, 0, ancho);

    // bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(lado, 0, 0);
    glVertex3f(0, 0, 0);

    // back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(lado, alto, 0);
    glVertex3f(0, alto, 0);

    // top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(lado, alto, ancho);
    glVertex3f(0, alto, ancho);

  glEnd();

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

MallaVirtual& MallaVirtual::operator=(const MallaVirtual &m){
  vertices = m.vertices;
  triangulos = m.triangulos;
  normales_vertices = m.normales_vertices;

  return *this;
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
  float color5[4] = { 0.5, 0.5, 0.5, 1 };

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

  glColor3f(0.5, 0.5, 0.5);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);

  if (a_dibujar == 0)
    Telescopio->draw();
  else if (a_dibujar == 1)
    superficie.draw();
  else if (a_dibujar == 2)
    malla.draw();

  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
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

void setIluminacion ()
{
  iluminacion = !iluminacion;
}

void setSombreado ()
{
  sombreado = !sombreado;
}

void setAnimacion ()
{
  animacion = !animacion;
}

bool getAnimacion ()
{
  return animacion;
}

void aumentarGradoLibertad(int i){
  if (i == 0 && !animacion){

    float v = ((Transformacion*)Telescopio->getHijos()[3])->getValorRotacion();
    ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v +5);
    if (v +5 > 360)
      ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v +5 -360);

  }
  else if (i==0){

    float v = ((Transformacion*)Telescopio->getHijos()[3])->getValorRotacion();
    ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v +gl0);
    if (v +gl0 > 360)
      ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v +gl0 -360);

  }
  else if (i == 1 && !animacion){

    float v = ((Transformacion*)Telescopio->getHijos()[4])->getValorRotacion();
    if (v +5 < 20)
      ((Transformacion*)Telescopio->getHijos()[4])->setValorRotacion (v +5);

  }
  else if (i==1){

    float v = ((Transformacion*)Telescopio->getHijos()[4])->getValorRotacion();
    if (v +gl1 < 20)
      ((Transformacion*)Telescopio->getHijos()[4])->setValorRotacion (v +gl1);
    else
      max1 = true;

  }
  else if (i == 2 && !animacion){
    vector <float> v = ((Transformacion*)Cuerpo->getHijos()[3])->getValorTraslacion();
    if (v[1]+0.1 < 1.7)
      ((Transformacion*)Cuerpo->getHijos()[3])->setValorTraslacion (vector<float>()={v[0], v[1]+0.1, v[2]});

  }
  else if (i==2){
    vector <float> v = ((Transformacion*)Cuerpo->getHijos()[3])->getValorTraslacion();
    ((Transformacion*)Cuerpo->getHijos()[3])->setValorTraslacion (vector<float>()={v[0], v[1]+gl2, v[2]});
    if (v[1]+gl2 < 1.7)
      ((Transformacion*)Cuerpo->getHijos()[3])->setValorTraslacion (vector<float>()={v[0], v[1]+gl2, v[2]});
    else
      max2 = true;
  }
}

void disminuirGradoLibertad(int i){
  if (i == 0 && !animacion){

    float v = ((Transformacion*)Telescopio->getHijos()[3])->getValorRotacion();
    ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v -5);
    if (v -5 < 0)
      ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v -5 +360);

  }
  else if (i==0){

    float v = ((Transformacion*)Telescopio->getHijos()[3])->getValorRotacion();
    ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v -gl0);
    if (v -gl0 < 0)
      ((Transformacion*)Telescopio->getHijos()[3])->setValorRotacion (v -gl0 +360);

  }
  else if (i == 1 && !animacion){

    float v = ((Transformacion*)Telescopio->getHijos()[4])->getValorRotacion();
    if (v -5 > -70)
      ((Transformacion*)Telescopio->getHijos()[4])->setValorRotacion (v -5);

  }
  else if (i==1){

    float v = ((Transformacion*)Telescopio->getHijos()[4])->getValorRotacion();
    if (v -gl1 > -70)
      ((Transformacion*)Telescopio->getHijos()[4])->setValorRotacion (v -gl1);
    else
      max1 = false;

  }
  else if (i == 2 && !animacion){
    vector <float> v = ((Transformacion*)Cuerpo->getHijos()[3])->getValorTraslacion();
    if (v[1]-0.1 > -1.3)
      ((Transformacion*)Cuerpo->getHijos()[3])->setValorTraslacion (vector<float>()={v[0], v[1]-0.1, v[2]});

  }
  else if (i==2){
    vector <float> v = ((Transformacion*)Cuerpo->getHijos()[3])->getValorTraslacion();
    if (v[1]-gl2 > -1.3)
      ((Transformacion*)Cuerpo->getHijos()[3])->setValorTraslacion (vector<float>()={v[0], v[1]-gl2, v[2]});
    else
      max2 = false;
  }
}

void aumentarVelocidadGradoLibertad(int i){
  if (animacion)
    if (i==0)
      gl0+=5;
    else if (i==1)
      gl1+=5;
    else if (i==2)
      gl2+=0.1;
}

void disminuirVelocidadGradoLibertad(int i){
  if (animacion)
    if (i==0)
      gl0-=5;
    else if (i==1)
      gl1-=5;
    else if (i==2)
      gl2-=0.1;
}
