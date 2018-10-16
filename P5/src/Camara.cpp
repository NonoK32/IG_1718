#include "Camara.h"
/*
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);


*/
Camara::Camara(){
  Observer_distance=2*10; //10 es el valor del Front_plane
  Observer_angle_x=0;
  Observer_angle_y=0;
}
Camara::Camara(GLfloat posX, GLfloat posY, GLfloat posZ, float x, float y, float z){
  Observer_distance=2*10; //10 es el valor del Front_plane
  Observer_angle_x=0;
  Observer_angle_y=0;

  PosEjeX = posX;
  PosEjeY = posY;
  PosEjeZ = posZ;

  Centro.x = x;
  Centro.y = y;
  Centro.z = z;
}

void Camara::setObserverAngleX(GLfloat x){
  Observer_angle_x += x;
}

void Camara::setObserverAngleY(GLfloat y){
  Observer_angle_y += y;
}

void Camara::setObserverDistance(GLfloat dist){
  Observer_distance = dist;
}

void Camara::AumentarAnguloX(){
  Observer_angle_x++;
}
void Camara::AumentarAnguloY(){
  Observer_angle_y++;
}
void Camara::AumentarDistancia(){
  Observer_distance*=1.2;
}

void Camara::DisminuirAnguloX(){
  Observer_angle_x--;
}
void Camara::DisminuirAnguloY(){
  Observer_angle_y--;
}
void Camara::DisminuirDistancia(){
  Observer_distance/=1.2;
}

void Camara::AumentarPosX(){
  PosEjeX++;
}
void Camara::AumentarPosY(){
  PosEjeY++;
}

void Camara::DisminuirPosX(){
    PosEjeX--;
}
void Camara::DisminuirPosY(){
    PosEjeY--;
}
void Camara::AumentarPosZ(){
  PosEjeZ++;
}

void Camara::DisminuirPosZ(){
  PosEjeZ--;
}


void Camara::setObserver(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);

  glTranslatef(Centro.x,Centro.y,Centro.z);
////////////////esto es lo de vicente////////////////////
/*
  glTranslatef(PosEjeX,0,0);
  glTranslatef(0,PosEjeY,0);
  glTranslatef(0,0,PosEjeZ);
  glTranslatef(0,0,-Observer_distance );
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);

  glTranslatef(Centro.x,Centro.y,Centro.z);

*/
/////////////////////////////////////////////////////////
}

void Camara::setPos(GLfloat posX, GLfloat posY, GLfloat posZ){
  Observer_distance=2*10; //10 es el valor del Front_plane
  Observer_angle_x=0;
  Observer_angle_y=0;

  PosEjeX = posX;
  PosEjeY = posY;
  PosEjeZ = posZ;


}
