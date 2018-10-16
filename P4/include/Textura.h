#ifndef _TEXTURA
#define _TEXTURA

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include <string>

#include "CImg.h"
using namespace std;



class Textura{

  private:
    GLuint id;
    GLbyte imagen[512][256][3];
    //GLbyte *pixeles;
    GLuint ancho;
    GLuint alto;

  public:
    Textura();
    void activarTextura();
    void desactivarTextura();
    void cargarImagen();

};

#endif
