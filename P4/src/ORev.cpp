#include "ORev.h"
#include <cmath>

ORev::ORev(){}

ORev::ORev(vector<_vertex3f> perfil, int n){

	Rotar(perfil,n);

}

float ORev:: GradosARadianes(float grados){
	return (grados*M_PI)/180.0;
}


void ORev::Rotar(vector<_vertex3f> perfil, int n){

	//Limpio para evitar revoluciones "incorrectas"
	vertices.clear();
	caras.clear();

	float nuevoGrado;
	int i;

int nperfil=perfil.size();

for(int k = 0; k < n; k++){
	nuevoGrado = (360.0/n) * k; //Mas preciso que ir sumando grados
		vertices.push_back(RotarY(perfil[0],GradosARadianes(nuevoGrado)));

	for(int j = 1; j < nperfil; j++)
	{
		i=k*nperfil+j;

		vertices.push_back(RotarY(perfil[j],GradosARadianes(nuevoGrado)));

		_vertex3i cara;

		cara._0 = (i-1);//i;
		cara._1 = (i+nperfil-1)% (n*nperfil);
		cara._2 = i;//(i-1);
		caras.push_back(cara);

		cara._0 = (i+nperfil-1)% (n*nperfil);//i;
		cara._1 = (i+nperfil)% (n*nperfil);
		cara._2 = i;//(i+nperfil-1)% (n*nperfil);
		caras.push_back(cara);

	}

}

}// FIN ROTAR

_vertex3f ORev::RotarY(_vertex3f p, float angulo){
	_vertex3f rotado;
	rotado.x = cos(angulo)*p.x + sin(angulo)*p.z;
	rotado.y = p.y;
	rotado.z = -sin(angulo)*p.x + cos(angulo)*p.z;

	return rotado;
}
