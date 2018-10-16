//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <string>
#include "O3d.h"
#include "O3ds.h"
#include "Cubo.h"
#include "Tetraedro.h"
#include "Peon.h"
#include "ORev.h"
#include "Cono.h"
#include "Vaso.h"
#include "VasoInvertido.h"
#include "Tubo.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "modelosPLY.h"
#include "file_ply_stl.h"
#include "ReguladorWatt.h"
#include "Tablero.h"
#include "Luz.h"
#include "Textura.h"
#include "Material.h"


// tamaño de los ejes
const int AXIS_SIZE=5000;


// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;


// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;


// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;



//CONTROLADOR DEL OBJETO VISUALIZADO
int objeto= 9999;
string fichero;
string ruta;
float velocidadGiro = 0.0;
float anguloGeneral = 0.0;
bool parar = true;
bool sombreadoSmooth = true;
float l0x = 0;
float l0y = 0;
float l0z = 0;
float l1x = 0;
float l1y = 0;
float l1z = 0;
//FLAGS PARA LOS MODOS DE PINTADO
bool ajedrez = false;
bool lineas = false;
bool puntos = false;
bool solido = false;
bool normales = false;
bool normalesV = false;
bool ficheroCargado = false;
bool material1 = false;
bool material2 = false;
bool material3 = false;
bool textura = false;
bool luces = false;
bool moverVista = true;
bool moverl0 = false;
bool moverl1 = false;
// VARIABLES QUE VOY A PINTAR
Cubo miCubo;
Tetraedro miTetraedro;
Cono miCono;
Cilindro miCilindro;
Vaso miVaso;
VasoInvertido miVasoI;
Tubo miTubo;
Peon miPeon;
Esfera miEsfera;
Esfera nuevaEs(10,50);
ORev miRotado;
modelosPLY miPLY;
ReguladorWatt reguladorWatt;
Tablero miTablero(8);
Luz l0(0);//funciona
Luz l2(1);
material miMaterial;
Textura miTextura;



//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	if(l0.getEstado()){
		glPushMatrix();
		glRotatef(l0x,1,0,0);
		glRotatef(l0y,0,1,0);
		glRotatef(l0z,0,0,1);
		l0.Posicionar();
		glPopMatrix();
	}
	if(l2.getEstado()){
		glPushMatrix();
		glRotatef(l1x,1,0,0);
		glRotatef(l1y,0,1,0);
		glRotatef(l1z,0,0,1);
		l2.Posicionar();
		glPopMatrix();
	}


	switch(objeto){

		case 1:{ //Cubo
			if(puntos)
				miCubo.drawPoints();

			if(lineas)
				miCubo.drawLines();

			if(solido)
				miCubo.drawFill(ajedrez);

			if(normales)
				miCubo.drawNormales();

			if(normalesV)
				miCubo.drawNormalesVertices();


		}break;




		case 2:{//Tetraedro
			if(puntos)
				miTetraedro.drawPoints();

			if(lineas)
				miTetraedro.drawLines();

			if(solido)
				miTetraedro.drawFill(ajedrez);

			if(normales)
				miTetraedro.drawNormales();

			if(normalesV)
				miTetraedro.drawNormalesVertices();

		}break;


		case 3:{//Revolucionado

			if(!ficheroCargado){
			 cout<<"Presione '3' sobre la interfaz Glut para cargar otro fichero"<<endl;
			 cout<<"Nombre del fichero PLY a cargar: "<<endl;

			 ruta = "modelosPLY/";
			 cin >> fichero;
			 ruta += fichero;
			 ficheroCargado = true;
		 }

			modelosPLY miPLY(ruta);
			if(puntos)
				miPLY.drawPoints();

			if(lineas)
				miPLY.drawLines();

			if(solido)
				miPLY.drawFill(ajedrez);

			if(normales)
				miPLY.drawNormales();

			if(normalesV)
				miPLY.drawNormalesVertices();

		}break;


		case 4:{//Revolucionado

			miRotado = miPeon;
			if(puntos)
				miRotado.drawPoints();

			if(lineas)
				miRotado.drawLines();

			if(solido)
				miRotado.drawFill(ajedrez);

			if(normales)
				miRotado.drawNormales();

			if(normalesV)
				miRotado.drawNormalesVertices();

		}break;


		case 5:{
			miRotado = miVaso;
			if(puntos)
				miRotado.drawPoints();

			if(lineas)
				miRotado.drawLines();

			if(solido)
				miRotado.drawFill(ajedrez);

			if(normales)
				miRotado.drawNormales();

			if(normalesV)
				miRotado.drawNormalesVertices();

		}break;


		case 6:{
			miRotado = miVasoI;
			if(puntos)
				miRotado.drawPoints();

			if(lineas)
				miRotado.drawLines();

			if(solido)
				miRotado.drawFill(ajedrez);

			if(normales)
				miRotado.drawNormales();

			if(normalesV)
				miRotado.drawNormalesVertices();

		}break;


		case 7:{
			miRotado = miCilindro;
			if(puntos)
				miRotado.drawPoints();

			if(lineas)
				miRotado.drawLines();

			if(solido)
				miRotado.drawFill(ajedrez);

			if(normales)
				miRotado.drawNormales();

			if(normalesV)
				miRotado.drawNormalesVertices();

		}break;


		case 8:{
			if(puntos)
				miTablero.drawPoints();
				if(lineas)
					miTablero.drawLines();

				if(solido)
					miTablero.drawFill(ajedrez);

				if(normales)
					miTablero.drawNormales();

				if(normalesV)
				  miTablero.drawNormalesVertices();

		}break;



			case 9:{

				miRotado = nuevaEs;
				if(puntos)
					miRotado.drawPoints();
				if(lineas)
					miRotado.drawLines();
				if(solido)
					miRotado.drawFill(ajedrez);

				if(normales)
					miRotado.drawNormales();

				if(normalesV)
					miRotado.drawNormalesVertices();

				}break;

				case 0:{
					cout << "use + para incrementar velocidad"<<endl;
					cout << " - para decrementarla, 'j' para activar desactivar la animacion" <<endl <<endl;
					reguladorWatt.generarRegulador(velocidadGiro,anguloGeneral,puntos,lineas,solido,ajedrez);

					}break;

	}

}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
if (toupper(Tecla1)=='C'){ //ajedrez
	if(ajedrez)
	 	ajedrez=false;
	else
	 	ajedrez = true;
	}
if (toupper(Tecla1)=='L'){
	if(lineas)
		lineas=false;
	else
		lineas=true;
}//Lineas
if (toupper(Tecla1)=='F'){
	if(solido)
		solido=false;
	else
		solido=true;
}//Relleno
if (toupper(Tecla1)=='P'){
	 if(puntos)
	 	puntos=false;
	 else
	 	puntos=true;

 } //Puntos



	if(toupper(Tecla1)== 'T'){
		textura = !(textura);
		if(textura)
		miTextura.activarTextura();
		else
			miTextura.desactivarTextura();
	}

 if (toupper(Tecla1)== 'I') {
	 luces = !(luces);
	 if(luces)
		glEnable(GL_LIGHTING);
	 else
		glDisable(GL_LIGHTING);
 }
 if(toupper(Tecla1)=='S'){
	 sombreadoSmooth = !(sombreadoSmooth);
	 if(!sombreadoSmooth)
		 glShadeModel(GL_SMOOTH);
	 else
		 glShadeModel(GL_FLAT);
 }

 if(toupper(Tecla1) == 'V') normalesV = !(normalesV);
 if(toupper(Tecla1)== 'N') normales = !(normales);
 if (toupper(Tecla1)=='J') parar=!(parar);
	if(toupper(Tecla1)=='+') { if(velocidadGiro < 62) velocidadGiro++;}
	if(toupper(Tecla1)=='-'){ if(velocidadGiro > -62) velocidadGiro--;}
 if (toupper(Tecla1)=='1') objeto = 1; //Tetraedro
 if (toupper(Tecla1)=='2') objeto = 2; //Cubo
 if (toupper(Tecla1)=='3'){ objeto = 3, ficheroCargado=false;} //PLY

 if (toupper(Tecla1)=='4') objeto = 4; //Peon
 if (toupper(Tecla1)=='5') objeto = 5; //Vaso
 if (toupper(Tecla1)=='6') objeto = 6; //VasoInvertido
 if (toupper(Tecla1)=='7') objeto = 7; //Cilindro
 if (toupper(Tecla1)=='8') objeto = 8; //Tubo
 if (toupper(Tecla1)=='9') objeto = 9; //Cono
 if (toupper(Tecla1)=='0') objeto = 0; //Cono

glutPostRedisplay();
}


void animacion(){
	if(!parar){
	anguloGeneral += velocidadGiro*0.1;

	glutPostRedisplay();
	}
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){


	case GLUT_KEY_F1:
		moverVista = !(moverVista);
		moverl0 = !(moverl0);
		//float valorX,valorY,valorZ;
		/*
		cout << "Introduzca nuevos valores"<<endl;
		cout << "Valor X"<<endl;
		cin >> valorX;
		cout << "Valor Y"<<endl;
		cin >> valorY,
		cout << "Valor Z"<<endl;
		cin >> valorZ;*/

		//l0.SetPosicion(valorX,valorY,valorZ,1);
	break;

	case GLUT_KEY_F2:
		moverVista = !(moverVista);
		moverl1 = !(moverl1);
	break;

	case GLUT_KEY_F5:
	miMaterial.SetAmbiente(0.0,0.05,0.0);
	miMaterial.SetDifuso(0.4,0.5,0.4);
	miMaterial.SetEspecular(0.04,0.7,0.04);
	miMaterial.SetBrillo(0.078125);
	miMaterial.activar();
	break;

	case GLUT_KEY_F6:
	miMaterial.SetAmbiente(0.25,0.20725,0.20725);
	miMaterial.SetDifuso(1,0.829,0.829);
	miMaterial.SetEspecular(0.296648,0.296648,0.296648);
	miMaterial.SetBrillo(0.088);
	miMaterial.activar();
	break;

	case GLUT_KEY_F7:
	miMaterial.SetAmbiente(0.0,0.0,0.0);
	miMaterial.SetDifuso(0.1,0.35,0.1);
	miMaterial.SetEspecular(0.45,0.55,0.45);
	miMaterial.SetBrillo(0.25);
	miMaterial.activar();
	break;
	case GLUT_KEY_F10:
	l0.interruptor();
	break;

	case GLUT_KEY_F11:
	l2.interruptor();
	break;

	case GLUT_KEY_LEFT:
		if(moverVista) Observer_angle_y--;
		else{
			if(moverl0)l0y--;
			if(moverl1)l1y--;
		}
	break;

	case GLUT_KEY_RIGHT:
		if(moverVista) Observer_angle_y++;
		else{
			if(moverl0)l0y++;
			if(moverl1)l1y++;
		}
	break;

	case GLUT_KEY_UP:
		if(moverVista) Observer_angle_x--;
		else{
			if(moverl0)l0x--;
			if(moverl1)l1x--;
		}
	break;

	case GLUT_KEY_DOWN:
		if(moverVista) Observer_angle_x++;
		else{
			if(moverl0)l0x++;
			if(moverl1)l1x++;
		}
	break;

	case GLUT_KEY_PAGE_UP:
		if(moverVista) Observer_distance*=1.2;
		else{
			if(moverl0)l0z++;
			if(moverl1)l1z++;
		}
	break;

	case GLUT_KEY_PAGE_DOWN:
		if(moverVista)Observer_distance/=1.2;
		else{
			if(moverl0)l0z--;
			if(moverl1)l1z--;
		}
		break;
	}
glutPostRedisplay();
}




//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;


// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);

glEnable(GL_NORMALIZE);

l2.SetValoresDireccional();


}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

glutIdleFunc(animacion);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
