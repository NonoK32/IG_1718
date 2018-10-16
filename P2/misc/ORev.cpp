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
	//vertices = perfil; //No repetir primeros y ultimos

	float grado = 360.0/n;
	float nuevoGrado = grado;


//Averiguar que vertice es el que tiene mayor altura (1º y ultimo)

_vertex3f MayorY,primerVertice,ultimoVertice;

bool tapaSuperior, tapaInferior,quieroTapa;
int tam = perfil.size();
//Esto es para ver cual seria la parte "superior" y cual la "inferior"

/*
MayorY = perfil[0];
if(MayorY.y < perfil[tam-1].y)
	MayorY = perfil[tam-1];
*/

	/*
	if (primer vertice perfil esta en el eje y)
		lo quitamos del perfil y
		lo guardamos en una variable "PrimerVertice"
	*/

	/*if(perfil[0].x == 0.0 && perfil[0].z == 0.0){
		if(MayorY.y <= perfil[0].y) tapaSuperior = true; //No estoy seguro si tiene sentido asi
		else tapaInferior = true;
		primerVertice = perfil[0]; //Lo guardo y lo saco del perfil para no repetir
		perfil.erase(perfil.begin()); //este punto en las rotaciones

	}
*/
	/*
	else
		primerVertice <- generamos uno nuevo vertice
		sobre el eje y (basandote en el primer vertice del perfil)

	*/
/*
	else{
		tapaSuperior = false; //Si el perfil no genera "tapa superior", creo un
		primerVertice.x = 0.0; //vertice a la misma altura que el punto mas alto por
		primerVertice.y = perfil[0].y;// si quiero que no se quede "hueco"
		primerVertice.z = 0.0;

	}
*/
	/*
		y repetimos lo mismo para el ultimo vertice
	*/

	/*
	if(perfil[tam - 1].x == 0.0 && perfil[tam - 1].z == 0.0){
		if(MayorY.y <= perfil[tam - 1].y) tapaSuperior = true;
		else tapaInferior = true;
		ultimoVertice = perfil[tam - 1];
		perfil.pop_back();

	}
	*/

	/*
	else{
		tapaInferior = false;
		ultimoVertice.x = 0.0;
		ultimoVertice.y = perfil[tam - 1].y;
		ultimoVertice.z = 0.0;

	}
*/


	/*
		revolucionamos de manera normal
	*/
	vertices = perfil;
	int per= perfil.size();

	//Para cada vuelta cojo el primer vertice, lo roto y lo meto
	//Luego hago lo mismo con los demas
	int i =0;
	int ver = 0;

	/* ESTO FUNCIONA
	for(int k = 1; k <= n; k++){

		vertices.push_back(RotarY(perfil[0],GradosARadianes(nuevoGrado)));

		for(int j = 1; j < per; j++){


			i = (k * per) + j;
			vertices.push_back(RotarY(perfil[j],GradosARadianes(nuevoGrado)));

			_vertex3i cara;

			cara._0 = i %(n * per);
			cara._1 = (i - per - 1)%(n * per);
			cara._2 = (i - per)%(n * per);
			cout << "valor de i: " <<  i << endl;
			cout << "valor de per: " <<  per << endl;
			cout << "valor de n: " <<  n << endl << endl;
			cout << "valor de cara 1: " << cara._0  << endl;
			cout << "valor de cara 2: " << cara._1 << endl;
			cout << "valor de cara 3: " << cara._2  << endl;
			cout << endl << endl;


			caras.push_back(cara);

			cara._0 = i% (n * per);
			cara._1 = (i - 1)%(n * per);
			cara._2 = (i - per - 1)%(n * per);
			caras.push_back(cara);

		}

		nuevoGrado += grado;

	}
*/
vertices.clear();

int nperfil=perfil.size();

for(int k = 0; k < n; k++){
	nuevoGrado = (360.0/n) * k; //Mas preciso que ir sumando grados

		vertices.push_back(RotarY(perfil[0],GradosARadianes(nuevoGrado)));

	for(int j = 1; j < nperfil; j++)
	{
		i=k*nperfil+j;
		vertices.push_back(RotarY(perfil[j],GradosARadianes(nuevoGrado)));
		_vertex3i cara;
		cara._0 = i;
		cara._1 = (i+nperfil-1)% (n*nperfil);
		cara._2 = (i-1);
		caras.push_back(cara);
		cara._0 = i;
		cara._1 = (i+nperfil)% (n*nperfil);
		cara._2 = (i+nperfil-1)% (n*nperfil);
		caras.push_back(cara);

	}

}

	/*
		if(vamos a poner tapa de arriba)
			añadimos el primer vertice a los vertices y generamos
			las caras que une al vertice que acabamos de añadir
			con el resto de vertices
	*/

	/*
	if(tapaSuperior || quieroTapa){
		vertices.insert(vertices.begin(),primerVertice);

	}
	*/
	/*
		repetimos el ultimo if con la parte de abajo
	*/

	/*
	if(tapaInferior || quieroTapa){
		vertices.push_back(ultimoVertice);
	}
*/
}// FIN ROTAR



_vertex3f ORev::RotarY(_vertex3f p, float angulo){
	_vertex3f rotado;
	rotado.x = cos(angulo)*p.x + sin(angulo)*p.z;
	rotado.y = p.y;
	rotado.z = -sin(angulo)*p.x + cos(angulo)*p.z;

	return rotado;
}
