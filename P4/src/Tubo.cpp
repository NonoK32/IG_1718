#include "Tubo.h"
#include <algorithm>
Tubo::Tubo(){
  vector<_vertex3f> perfil;
  perfil.push_back(_vertex3f(2.5,2.5,0.0));
  perfil.push_back(_vertex3f(2.5,-2.5,0.0));
  reverse(perfil.begin(),perfil.end());
  Rotar(perfil,10);

  CalcularNormalesCaras();
	CalcularNormalesVertices();
	NormalizarVector();
	NormalizarVertices();
}
