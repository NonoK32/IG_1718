#include "Tablero.h"
#include <algorithm>
Tablero::Tablero(){

}
////////////////////////////////////////////////////////////////////////////////
Tablero::Tablero(int m){

  int vsize;
  /*float fila,columna;
  fila = columna = 0.0;

  for(int i = 0; i < m ; i++){

    for(int j = 0; j < m; j++){
      vertices.push_back(_vertex3f(fila,columna,0.0));
      //Entre 0 y 1
      coordenadasTextura.push_back(_vertex2f(i/tam * tamCasilla, j/tam *tamCasilla));
      columna +=tamCasilla;
    }
    fila += tamCasilla;
  }
*/

int x,y,z;
float posX,posY;
posX = 0.0;
posY = 0.0;
for(x = 0; x < m; x++){

  vertices.push_back(_vertex3f(x,0,0));
//  coordenadasTextura.push_back(_vertex2f(posX,posY));
//  posX += 0.125;


}
//posX=0.0;
//posY=0.125;
for(z = 1; z < m; z++){
  vertices.push_back(_vertex3f(0,0,z));
//  posX = 0.0;
  for(x = 1; x< m ; x++){
    vertices.push_back(_vertex3f(x,0,z));
//    coordenadasTextura.push_back(_vertex2f(posX,posY));
    vsize = vertices.size()-1;
    cout << "X es: " << x << " Y es: " << y << " Z es: " << z << endl;

    caras.push_back(_vertex3i(vsize - 1, vsize - 1 - m, vsize - m));
    caras.push_back(_vertex3i(vsize, vsize - 1, vsize - m));
  //  posX += 0.125;
  }
  //posY += 0.125;

}
////////////////////////////////////////////////////////////////////////////////

//Entero
for(int i = 0; i < m; i++){
  for(int j = 0; j < m; j++){
    coordenadasTextura.push_back(_vertex2f(posX,posY));
    cout << "PosX es: " << posX << " PosY es: " << posY << endl;
    posY += 1.0/(m-1);
  }
  posY=0;
  posX += 1.0/(m-1);
}

////////////////////////////////////////////////////////////////////////////////
//2:1
/*
for(int i = 0; i < m; i++){
  for(int j = 0; j < m; j++){
    coordenadasTextura.push_back(_vertex2f(posX,posY));
    cout << "PosX es: " << posX << " PosY es: " << posY << endl;
    posY += 1.0/(m*2);
  }
  posY=0;
  posX += 1.0/(m*2);
}

*/
////////////////////////////////////////////////////////////////////////////////
// 1:2
/*
for(int i = 0; i < m/2; i++){
  for(int j = 0; j < m/2; j++){
    coordenadasTextura.push_back(_vertex2f(posX,posY));
    cout << "PosX es: " << posX << " PosY es: " << posY << endl;
    posY += 1.0/(m/2);
  }
  posY=0;
  posX += 1.0/(m/2);
}
pequeño = true;
cout << "Tam vertices: " << vertices.size() << " Tam tex: " << coordenadasTextura.size() << " m: " << m << endl;
*/

//reverse(vertices.begin(),vertices.end());
CalcularNormalesCaras();
CalcularNormalesVertices();
NormalizarVector();
NormalizarVertices();

}
////////////////////////////////////////////////////////////////////////////////
