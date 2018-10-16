#include "ReguladorWatt.h"

ReguladorWatt::ReguladorWatt(){
  generarRegulador(0.0,0.0,Puntos,Lineas,Relleno,Ajedrez);
  miPLY = modelosPLY("modelosPLY/beethoven.ply");
}

float ReguladorWatt::PasarAGrados(float grados){
	return grados*(180/M_PI);
}

////////////////////////////////////////////////////////////////////////////////
//Funciones de piezas
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::Brazo(float angulo, float anguloP){
glPushMatrix();
  glRotatef(angulo,0,0,1); //roto todo para dejarlo como quiero

  glTranslatef(-3.25,0,0);

  glPushMatrix();
  //glRotatef(0,0,1);
  glTranslatef(-1,0,0);
  BrazoP(anguloP); //Le pongo el brazo perpendicular
  glPopMatrix();


  glPushMatrix();
  glRotatef(90,0,0,1);
  TuboGrandeBrazo();
  glPopMatrix();

  glPushMatrix();

  glTranslatef(-4.4,0,0); //Pinto la esfera, y la escalo y la muevo,
    PonerBeethoven();
  EsferaWatt();
  glPopMatrix();

glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::PonerBeethoven(){
  glPushMatrix();
    glTranslatef(0,1.8,0);
    glScalef(0.1,0.1,0.1);
    miPLY.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}
void ReguladorWatt::TuboGrandeBrazo(){
  glPushMatrix();
  glScalef(0.5,7,0.5);
    //Pinto el cilindro y lo cuadro para que se quede unido a la esfera
  elCilindro.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////

void ReguladorWatt::EsferaWatt(){
  glPushMatrix();
  glScalef(2.5,2.5,2.5); //Tamaño correcto de la esfera
  laEsfera.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::PiezaCentral(){ //Son los cilindros aplanados que se repiten

  glPushMatrix();
  glScalef(2,1,2); //Tamaño correcto del cilindro
  elCilindro.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::TuboCentral(){ //Este es el de tamaño 5, que esta entre los cilindros aplastados
  glPushMatrix();
  glScalef(0.5,13,0.5);
  elCilindro.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::Base(){//Base donde se apoya todo
  glPushMatrix();
  glScalef(8,1,8);
  elCubo.drawParametros(Puntos,Lineas,Relleno,Ajedrez);;
  glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::BrazoP(float angulo){ //Son los brazos perpendiculares que unen el cilindro central con los brazos
  glPushMatrix();
  glRotatef(angulo,0,0,1);
  glTranslatef(0,-2,0);//O'7 es el ancho del cilindro donde lo estoy enganchando
  glScalef(0.3,4.2,0.3);
  elCilindro.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
/*void ReguladorWatt::CilindroAlargado(){ //Es el cilindro central, esta entre la base y el cilindro aplastado inferior
  glPushMatrix();
  glScalef(0.5,6,0.5);
  elCilindro.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}*/
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::CuboAlargado(){

  glPushMatrix();
  glScalef(0.2,5,0.2);
  elCubo.drawParametros(Puntos,Lineas,Relleno,Ajedrez);
  glPopMatrix();
}

/*void ReguladorWatt::draw(bool P, bool L, bool R, bool A){

  elCubo.drawParametros(P,L,R, A);
  laEsfera.drawParametros(P,L,R,A);
  elCilindro.drawParametros(P,L,R,A);

}*/
////////////////////////////////////////////////////////////////////////////////
void ReguladorWatt::generarRegulador(float velocidad,float anguloG, bool Puntos, bool Lineas, bool Relleno, bool Ajedrez){

  this->Puntos=Puntos;
  this->Lineas=Lineas;
  this->Relleno=Relleno;
  this->Ajedrez=Ajedrez;

  float velocidadActual = velocidad;
  float anguloA = 0.0;
  float anguloB = 0.0;
  float anguloC = 0.0;
  float A = 4.1;
  float B = 6.5;
  float C = 4.2;
  float alturaCentrifuga = 0.0;

  /*
    |c \
    |    \
  B |      \  A 3.5
    |        \
    |a________b\
         C


 A es longitud del TuboCentral
 B es longitud del Brazo
 C es el cilindro que une el brazo con la pieza central

  */

/*if(velocidadActual <= 7){
  anguloC = 51.0357;
  anguloB = 88.5772;
  anguloA = 40.3871;
}*/

if(velocidadActual > 7){
  alturaCentrifuga = alturaCentrifuga + (velocidadActual-7)*0.1;
}
if(velocidadActual < -7){
  alturaCentrifuga = 1.5 + alturaCentrifuga + (velocidadActual - 7)*0.1;
}
B = B - alturaCentrifuga;
anguloA = PasarAGrados(acos((pow(B,2) + pow(C,2) - pow(A,2))/(2*B*C)));
anguloB = 90-PasarAGrados(acos((pow(C,2) + pow(A,2) - pow(B,2))/(2*C*A)));
anguloC = 90-(PasarAGrados(acos((pow(A,2) + pow(B,2) - pow(C,2))/(2*A*B))));

cout<< "Angulo A: "<< anguloA<< endl;
cout<< "Angulo B: "<< anguloB<< endl;
cout<< "Angulo C: "<< anguloC<< endl;

cout <<"valor altura: "<< alturaCentrifuga << endl;
if(velocidadActual == 7){
  cout << "UMBRAL SUPERIOR PARA SUBIR ALCANZADO" << endl;
}
if(velocidadActual == -7){
  cout << "UMBRAL INFERIOR PARA BAJAR ALCANZADO" << endl;
}
cout<<"velocidad: " << velocidadActual <<endl << endl << endl;


  glPushMatrix();
    glTranslatef(0,-6.5,0);
    Base(); //Pongo la base
  glPopMatrix();

  TuboCentral();

  glRotatef(anguloG,0,1,0);


/*
  glPushMatrix();
  glTranslatef(0,abs(alturaCentrifuga),0);
  glTranslatef(0,-3,0);
  glTranslatef(-0.7,0,0);
  CuboAlargado();
  glPopMatrix();
*/


  glPushMatrix();
  glTranslatef(0,(alturaCentrifuga),0);
  //glTranslatef(0,-3,0);
    glPushMatrix();
      glTranslatef(0,-3,0);
      glTranslatef(-0.7,0,0);
      CuboAlargado();
    glPopMatrix();
  PiezaCentral();
  glPopMatrix();



  glTranslatef(0,6.5,0);

  PiezaCentral();

  glPushMatrix();
  Brazo(anguloC,anguloB);
  glPopMatrix();



    glPushMatrix();
    glRotatef(180,0,1,0);
    Brazo(anguloC,anguloB);
    glPopMatrix();



}
