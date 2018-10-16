#include "Material.h"

material::material(){}
////////////////////////////////////////////////////////////////////////////////
void material::activar(){

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
  glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
  glMaterialf(GL_FRONT, GL_SHININESS, brillo * 128);

}
void material::SetAmbiente(GLfloat x, GLfloat y, GLfloat z){
  ambiente[0]=x;
  ambiente[1]=y;
  ambiente[2]=z;

}

void material::SetDifuso(GLfloat x, GLfloat y, GLfloat z){
  difuso[0]=x;
  difuso[1]=y;
  difuso[2]=z;

}

void material::SetEspecular(GLfloat x, GLfloat y, GLfloat z){
  especular[0]=x;
  especular[1]=y;
  especular[2]=z;

}

void material::SetBrillo(GLfloat elBrillo){
  brillo=elBrillo;
}
