#include "VasoInvertido.h"

VasoInvertido::VasoInvertido(){

  vector<_vertex3f> perfil;
  perfil.push_back(_vertex3f(0.0,5.0,0.0));
  perfil.push_back(_vertex3f(2.5,5.0,0.0));
  perfil.push_back(_vertex3f(5.0, -5.0 ,0.0));

  Rotar(perfil,20);

}
