#ifndef _CAMARA
#define _CAMARA


#include <GL/gl.h>
#include <GL/glut.h>
#include "vertex.h"

using namespace std;

class Camara{

  private:

    _vertex3f Centro;
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;
    GLfloat PosEjeX;
    GLfloat PosEjeY;
    GLfloat PosEjeZ;



  public:
    Camara();
    Camara(GLfloat posX, GLfloat posY, GLfloat posZ, float x, float y, float z);


    void setObserverAngleX(GLfloat x);
    void setObserverAngleY(GLfloat y);
    void setObserverDistance(GLfloat dist);
    void AumentarAnguloX();
    void AumentarAnguloY();
    void AumentarDistancia();
    void DisminuirAnguloX();
    void DisminuirAnguloY();
    void DisminuirDistancia();

    void AumentarPosX();
    void AumentarPosY();
    void AumentarPosZ();

    void DisminuirPosX();
    void DisminuirPosY();
    void DisminuirPosZ();

    void setObserver();
    void setPos(GLfloat posX, GLfloat posY, GLfloat posZ);

};
#endif
