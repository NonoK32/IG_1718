#ifndef _REGULADORWATT
#define _REGULADORWATT

#include "Cubo.h"
#include "Cilindro.h"
#include "Esfera.h"
#include <cmath>
#include <GL/glut.h>
#include "modelosPLY.h"

class ReguladorWatt{

public:

  ReguladorWatt();
  void generarRegulador(float velocidad, float anguloG, bool Puntos, bool Lineas, bool Relleno, bool Ajedrez);

private:
  modelosPLY miPLY;
  Esfera laEsfera;
  Cubo elCubo;
  Cilindro elCilindro;
  //Para los modos de pintado
  bool Lineas = true;
  bool Puntos = false;
  bool Relleno = false;
  bool Ajedrez = false;

  void Brazo(float angulo, float anguloP);
  void PiezaCentral();
  void TuboGrandeBrazo();
  void EsferaWatt();
  void TuboCentral();
  void Base();
  void PonerBeethoven();
  void BrazoP(float angulo);
  //void CilindroAlargado();
  void CuboAlargado();

  float PasarAGrados(float Grados);

};

#endif
