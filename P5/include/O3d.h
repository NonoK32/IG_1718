#ifndef _O3D
#define _O3D

#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <vector>
#include "vertex.h"
#include "O3ds.h"

using namespace std;

class O3d : public O3ds{

  protected:

      vector<_vertex3i> caras;//Este vector almacena 3 posiciones del vector de vertices en cada casilla, para formar triangulos
      vector<_vertex3f> normalesCaras;
      vector<_vertex3f> normalesVertices;
      vector<_vertex2f> coordenadasTextura;

      _vertex3f ProductoVectorial(_vertex3f vertice1, _vertex3f vertice2, _vertex3f vertice3);
      _vertex3f ProductoVectorial(_vertex3f A, _vertex3f B);
      void CalcularNormalesCaras();
      void NormalizarVector();
      void NormalizarVertices();
      void CalcularNormalesVertices();
      _vertex3f CalcularPMedioCara(int indice);
  public:

    O3d();
    void drawLines();
    void drawLines(float r, float g, float b);
    void drawFill(bool ajedrez);
    void drawFill(bool ajedrez, float r, float g, float b);
    void drawParametros(bool puntos, bool lineas, bool relleno, bool ajedrez);
  //  void drawTextura();
    void drawNormales();
    void drawNormalesVertices();
    void Trasladar(float x, float y, float z);
};



#endif
