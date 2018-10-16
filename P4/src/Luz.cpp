#include "Luz.h"

Luz::Luz(int num){
  if(num == 0)
    luz = GL_LIGHT0;

  if(num == 1)
    luz = GL_LIGHT1;

  if(num == 2)
    luz = GL_LIGHT2;

  if(num == 3)
    luz = GL_LIGHT3;

  if(num == 4)
    luz = GL_LIGHT4;

  if(num == 5)
    luz = GL_LIGHT5;

  if(num == 6)
    luz = GL_LIGHT6;

  if(num == 7)
    luz = GL_LIGHT7;

  SetValoresIniciales();
  encendida=false;
}
////////////////////////////////////////////////////////////////////////////////
void Luz::encender(){
  encendida = true;
  glEnable(luz);
}
////////////////////////////////////////////////////////////////////////////////
void Luz::apagar(){
  encendida = false;
  glDisable(luz);
}
////////////////////////////////////////////////////////////////////////////////
bool Luz::getEstado(){
  return encendida;
}
////////////////////////////////////////////////////////////////////////////////
void Luz::interruptor(){
  if(!encendida)
    encender();
  else
    apagar();
}
////////////////////////////////////////////////////////////////////////////////
void Luz::SetAmbiente(GLfloat x,GLfloat y, GLfloat z, GLfloat w){
  ambiente[0] = x;
  ambiente[1] = y;
  ambiente[2] = z;
  ambiente[3] = w;
  glLightfv(luz,GL_AMBIENT,ambiente);
}
////////////////////////////////////////////////////////////////////////////////
void Luz::SetEspecular(GLfloat x,GLfloat y, GLfloat z, GLfloat w){
  especular[0] = x;
  especular[1] = y;
  especular[2] = z;
  especular[3] = w;
  glLightfv(luz,GL_SPECULAR,especular);
}
////////////////////////////////////////////////////////////////////////////////
void Luz::SetDifuso(GLfloat x,GLfloat y, GLfloat z, GLfloat w){
  difuso[0] = x;
  difuso[1] = y;
  difuso[2] = z;
  difuso[3] = w;
  glLightfv(luz,GL_DIFFUSE,difuso);
}
////////////////////////////////////////////////////////////////////////////////
void Luz::SetPosicion(GLfloat x,GLfloat y, GLfloat z, GLfloat w){
  posicion[0] = x;
  posicion[1] = y;
  posicion[2] = z;
  posicion[3] = w;
  glLightfv(luz,GL_POSITION,posicion);
}
////////////////////////////////////////////////////////////////////////////////
void Luz::SetValoresDireccional(){
  SetAmbiente(0.9,0.9,0.4,1.0);
  SetEspecular(1.0,1.0,1.0,1.0);
  SetDifuso(0.9,0.9,0.4,1.0);
  SetPosicion(10.0,0.0,0.0,0);
}
void Luz::SetValoresIniciales(){
  SetAmbiente(0.0,0.0,0.0,1.0);
  SetEspecular(1.0,1.0,1.0,1.0);
  SetDifuso(0.0,0.0,0.0,1.0);
  SetPosicion(0.0,10.0,0.0,1);

}
////////////////////////////////////////////////////////////////////////////////
void Luz::Posicionar(){
  SetPosicion(posicion[0],posicion[1],posicion[2],posicion[3]);
}
