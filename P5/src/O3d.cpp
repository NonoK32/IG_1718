#include "O3d.h"

O3d::O3d(){}

/***************************************************************************/


void O3d::drawLines(){

  int Vertice1,Vertice2,Vertice3;

 glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//Interpreto los triangulos como lineas

 glBegin(GL_TRIANGLES);

         glColor3f(0, 0, 1);

         for (int i= 0; i < caras.size(); i++){

          Vertice1 = caras[i]._0;
          glVertex3f(vertices[Vertice1].x, vertices[Vertice1].y, vertices[Vertice1].z);
          Vertice2 = caras[i]._1;
          glVertex3f(vertices[Vertice2].x, vertices[Vertice2].y, vertices[Vertice2].z);
          Vertice3 = caras[i]._2;
          glVertex3f(vertices[Vertice3].x, vertices[Vertice3].y, vertices[Vertice3].z);

         }

  glEnd();

}

void O3d::drawLines(float r, float g, float b){
  int Vertice1,Vertice2,Vertice3;

 glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//Interpreto los triangulos como lineas

 glBegin(GL_TRIANGLES);

         glColor3f(r, g, b);

         for (int i= 0; i < caras.size(); i++){

          Vertice1 = caras[i]._0;
          glVertex3f(vertices[Vertice1].x, vertices[Vertice1].y, vertices[Vertice1].z);
          Vertice2 = caras[i]._1;
          glVertex3f(vertices[Vertice2].x, vertices[Vertice2].y, vertices[Vertice2].z);
          Vertice3 = caras[i]._2;
          glVertex3f(vertices[Vertice3].x, vertices[Vertice3].y, vertices[Vertice3].z);

         }

  glEnd();

}
/***************************************************************************/

void O3d::drawFill(bool ajedrez){

  glPointSize(2);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //Ahora cambio la interpretacion a relleno

 int Vertice1,Vertice2,Vertice3;

  //gl_Enable(GL_NORMALIZE);
  glBegin(GL_TRIANGLES);

        for (int i= 0; i < caras.size(); i++){
         // Cambio de color para el ajedrez
         if(ajedrez && i %2 == 0){
             glColor3f(1, 0, 0);
           }
         else{
             glColor3f(0, 1, 0);
           }

         Vertice1 = caras[i]._0;
         glNormal3f(normalesVertices[Vertice1].x,normalesVertices[Vertice1].y,normalesVertices[Vertice1].z);
         if(coordenadasTextura.size() > 0)
          glTexCoord2f(coordenadasTextura[Vertice1].x,coordenadasTextura[Vertice1].y);
         glVertex3f(vertices[Vertice1].x, vertices[Vertice1].y, vertices[Vertice1].z);

         Vertice2 = caras[i]._1;
         glNormal3f(normalesVertices[Vertice2].x,normalesVertices[Vertice2].y,normalesVertices[Vertice2].z);
         if(coordenadasTextura.size() > 0)
          glTexCoord2f(coordenadasTextura[Vertice2].x,coordenadasTextura[Vertice2].y);
         glVertex3f(vertices[Vertice2].x, vertices[Vertice2].y, vertices[Vertice2].z);

         Vertice3 = caras[i]._2;
         glNormal3f(normalesVertices[Vertice3].x,normalesVertices[Vertice3].y,normalesVertices[Vertice3].z);
         if(coordenadasTextura.size() > 0)
          glTexCoord2f(coordenadasTextura[Vertice3].x,coordenadasTextura[Vertice3].y);
         glVertex3f(vertices[Vertice3].x, vertices[Vertice3].y, vertices[Vertice3].z);

        }

    glEnd();
}



void O3d::drawFill(bool ajedrez, float r, float g, float b){

  glPointSize(2);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //Ahora cambio la interpretacion a relleno

 int Vertice1,Vertice2,Vertice3;

  //gl_Enable(GL_NORMALIZE);
  glBegin(GL_TRIANGLES);

        for (int i= 0; i < caras.size(); i++){
         // Cambio de color para el ajedrez
         if(ajedrez && i %2 == 0){
             glColor3f(1, 0, 0);
           }
         else{
             glColor3f(r, g, b);
           }

         Vertice1 = caras[i]._0;
         glNormal3f(normalesVertices[Vertice1].x,normalesVertices[Vertice1].y,normalesVertices[Vertice1].z);
         if(coordenadasTextura.size() > 0)
          glTexCoord2f(coordenadasTextura[Vertice1].x,coordenadasTextura[Vertice1].y);
         glVertex3f(vertices[Vertice1].x, vertices[Vertice1].y, vertices[Vertice1].z);

         Vertice2 = caras[i]._1;
         glNormal3f(normalesVertices[Vertice2].x,normalesVertices[Vertice2].y,normalesVertices[Vertice2].z);
         if(coordenadasTextura.size() > 0)
          glTexCoord2f(coordenadasTextura[Vertice2].x,coordenadasTextura[Vertice2].y);
         glVertex3f(vertices[Vertice2].x, vertices[Vertice2].y, vertices[Vertice2].z);

         Vertice3 = caras[i]._2;
         glNormal3f(normalesVertices[Vertice3].x,normalesVertices[Vertice3].y,normalesVertices[Vertice3].z);
         if(coordenadasTextura.size() > 0)
          glTexCoord2f(coordenadasTextura[Vertice3].x,coordenadasTextura[Vertice3].y);
         glVertex3f(vertices[Vertice3].x, vertices[Vertice3].y, vertices[Vertice3].z);

        }

    glEnd();
}
/***************************************************************************/

void O3d::drawParametros(bool puntos, bool lineas, bool relleno, bool ajedrez){

  if(puntos) drawPoints();
  if(lineas) drawLines();
  if(relleno) drawFill(ajedrez);

}
////////////////////////////////////////////////////////////////////////////////
/*
void O3d::drawTextura(){
  for(int i = 0; i<vertices.size(); i++){
  if(coordenadasTextura.size()>0)
    glTexCoord2f(coordenadasTextura[i].x,coordenadasTextura[i].y);
  }
  glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
}
*/
_vertex3f O3d::ProductoVectorial(_vertex3f A, _vertex3f B){
  return /*A.cross_product(B)*/_vertex3f(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x);
}
////////////////////////////////////////////////////////////////////////////////

_vertex3f O3d::ProductoVectorial(_vertex3f vertice1, _vertex3f vertice2, _vertex3f vertice3)
{
  //Hago dos vectores con los tres puntos

  _vertex3f A, B;

  //Calculos para A

  A.x = vertice2.x - vertice1.x;
  A.y = vertice2.y - vertice1.y;
  A.z = vertice2.z - vertice1.z;

  //Calculos para B

  B.x = vertice3.x - vertice1.x;
  B.y = vertice3.y - vertice1.y;
  B.z = vertice3.z - vertice1.z;

  return ProductoVectorial(A, B);
}
////////////////////////////////////////////////////////////////////////////////
void O3d::CalcularNormalesCaras(){
  normalesCaras.clear();
  for(int i = 0; i < caras.size(); i++){
    normalesCaras.push_back(ProductoVectorial(vertices[caras[i]._0],vertices[caras[i]._1],vertices[caras[i]._2]));
  }
}
////////////////////////////////////////////////////////////////////////////////
_vertex3f O3d::CalcularPMedioCara(int indice){
  _vertex3f A(vertices[caras[indice]._0]);
  _vertex3f B(vertices[caras[indice]._1]);
  _vertex3f C(vertices[caras[indice]._2]);
  _vertex3f Resultado;

  Resultado.x = (A.x + B.x + C.x)/3;
  Resultado.y = (A.y + B.y + C.y)/3;
  Resultado.z = (A.z + B.z + C.z)/3;

  return Resultado;

}
////////////////////////////////////////////////////////////////////////////////
void O3d::drawNormales(){

  _vertex3f PuntoMedio;
  glBegin(GL_LINES);
    glColor3f(0,0,0);

    for(int i = 0; i < normalesCaras.size(); i++){

      PuntoMedio = CalcularPMedioCara(i);
      glVertex3f(PuntoMedio.x ,PuntoMedio.y , PuntoMedio.z);
      glVertex3f(normalesCaras[i].x + PuntoMedio.x, normalesCaras[i].y + PuntoMedio.y, normalesCaras[i].z + PuntoMedio.z);


    }

  glEnd();
}
////////////////////////////////////////////////////////////////////////////////

void O3d::NormalizarVector(){

  _vertex3f normal;
  _vertex3f normalizado;
  for(int i = 0; i < normalesCaras.size(); i++){

    //normalesCaras[i].normalize();
    normal = normalesCaras[i];
    normalizado.x = (normal.x)/sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));
    normalizado.y = (normal.y)/sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));
    normalizado.z = (normal.z)/sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));

    normalesCaras[i] = normalizado;

  }

}
////////////////////////////////////////////////////////////////////////////////

void O3d::CalcularNormalesVertices(){

  normalesVertices=vector<_vertex3f> (vertices.size(),_vertex3f(0.0,0.0,0.0));

  int v1,v2,v3;

  for(int i = 0; i < caras.size(); i++){

    v1 = caras[i]._0;
    v2 = caras[i]._1; //A estos les sumo el valor de normal cara
    v3 = caras[i]._2;

    normalesVertices[v1] += normalesCaras[i];
    normalesVertices[v2] += normalesCaras[i];
    normalesVertices[v3] += normalesCaras[i];


  }

}
////////////////////////////////////////////////////////////////////////////////
void O3d::drawNormalesVertices(){

  _vertex3f vertice;
  //Esto es provisional

  glBegin(GL_LINES);

    glColor3f(1,0,1);

    for(int i = 0; i < normalesVertices.size(); i++){

      vertice = vertices[i];
      glVertex3f(vertice.x ,vertice.y , vertice.z);
      glVertex3f(normalesVertices[i].x + vertice.x, normalesVertices[i].y + vertice.y, normalesVertices[i].z + vertice.z);

    }

  glEnd();
}
////////////////////////////////////////////////////////////////////////////////
void O3d::NormalizarVertices(){

  _vertex3f normal;
  _vertex3f normalizado;
  for(int i = 0; i < normalesVertices.size(); i++){
      //normalesVertices[i].normalize();

    normal = normalesVertices[i];
    normalizado.x = (normal.x)/sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));
    normalizado.y = (normal.y)/sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));
    normalizado.z = (normal.z)/sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));

    normalesVertices[i] = normalizado;

  }

}
////////////////////////////////////////////////////////////////////////////////
void O3d::Trasladar(float x, float y, float z){
  for(int i = 0; i < vertices.size(); i++){
    vertices[i].x += x;
    vertices[i].y += y;
    vertices[i].z += z;
  }
}
