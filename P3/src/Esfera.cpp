#include "Esfera.h"

Esfera::Esfera(){

  vector<_vertex3f> perfil;

  perfil.push_back(_vertex3f(0.5,0.0,0.0));

  perfil = GeneraPerfil(perfil,10);

  Rotar(perfil,10);


}

_vertex3f Esfera::RotarZ(_vertex3f p, float angulo){
	_vertex3f rotado;
	rotado.x = -sin(angulo)*p.x + cos(angulo)*p.y;
	rotado.y = cos(angulo)*p.x + sin(angulo)*p.y;
	rotado.z = p.z;

	return rotado;
}

vector<_vertex3f> Esfera::GeneraPerfil(vector<_vertex3f> perfil, int n){

  vector<_vertex3f> perfilGenerado;

	float nuevoGrado;

int nperfil=perfil.size();

  for(int k = 0; k <= n; k++){

     nuevoGrado = (180.0/n) * k; //Mas preciso que ir sumando grados

		 perfilGenerado.push_back(RotarZ(perfil[0],GradosARadianes(nuevoGrado)));

	    for(int j = 1; j < nperfil; j++){
		      perfilGenerado.push_back(RotarZ(perfil[j],GradosARadianes(nuevoGrado)));
	      }
      }
  return perfilGenerado;
}// FIN
