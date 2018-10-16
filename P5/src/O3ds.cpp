#include "O3ds.h"


O3ds::O3ds(){}

/**************************************************************************/
void O3ds::drawPoints(){

  glPointSize(4);

  glBegin(GL_POINTS);

  glColor3f(0,0,0);
  for (int i=0; i < vertices.size() ;i++){

    glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);

    }
  glEnd();

}
void O3ds::drawPoints(float r, float g, float b){

  glPointSize(4);

  glBegin(GL_POINTS);

  glColor3f(r,g,b);
  for (int i=0; i < vertices.size() ;i++){

    glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);

    }
  glEnd();

}
