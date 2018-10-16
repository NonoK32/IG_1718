#ifndef _MATERIAL
#define _MATERIAL


#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

class material{

  private:

    GLfloat ambiente[3];
    GLfloat especular[3];
    GLfloat difuso[3];
    GLfloat brillo;

  public:

    material();
    void activar();
    void SetAmbiente(GLfloat x, GLfloat y, GLfloat z);
    void SetDifuso(GLfloat x, GLfloat y, GLfloat z);
    void SetEspecular(GLfloat x, GLfloat y, GLfloat z);
    void SetBrillo(GLfloat elBrillo);


};
#endif
