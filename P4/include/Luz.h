#ifndef _LUZ
#define _LUZ

#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

class Luz{

  private:

    GLenum luz;
    bool encendida;

    GLfloat ambiente[4];
    GLfloat especular[4];
    GLfloat difuso[4];
    GLfloat posicion[4];

  public:

    Luz(int num);
    void encender();
    void apagar();
    void interruptor();
    bool getEstado();
    void SetAmbiente(GLfloat x,GLfloat y, GLfloat z, GLfloat w);
    void SetEspecular(GLfloat x,GLfloat y, GLfloat z, GLfloat w);
    void SetDifuso(GLfloat x,GLfloat y, GLfloat z, GLfloat w);
    void SetPosicion(GLfloat x,GLfloat y, GLfloat z, GLfloat w);
    void SetValoresIniciales();
    void SetValoresDireccional();
    void Posicionar();



};



#endif
