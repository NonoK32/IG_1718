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
#include "Camara.h"
#include <values.h>


// tamaño de los ejes
const int AXIS_SIZE=5000;

//maximo numero de nombres
const int MAXNAMES = 10;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;


// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;


// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=600,UI_window_height=600;

typedef struct{
	int nnms;
	int nms[MAXNAMES];
	float zmin;
	float zmax;
}OBJ;




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
int ratxo,ratyo;
int idCamara = 0;
bool estadoBotonDerecho = false;
bool estadoBotonIzquierdo = false;
int tipoCamara = 0;
int seleccion = -2;
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
bool Orto = false;
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
Esfera nuevaEs2(5,25);
ORev miRotado;
modelosPLY miPLY;
ReguladorWatt reguladorWatt;
Tablero miTablero(8);
Luz l0(0);//funciona
Luz l2(1);
material miMaterial;
Textura miTextura;
vector<Camara> listaCamaras;
bool explorar = false;
Tetraedro tt2;
Cubo c2;
Esfera e2;
Peon p2;
modelosPLY Ply2("modelosPLY/beethoven.ply");
modelosPLY Ply3("modelosPLY/beethoven.ply");
vector<modelosPLY> beth;
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
const GLfloat ratio = GLfloat(UI_window_height) / GLfloat(UI_window_width);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
if(!Orto)
	glFrustum(-Window_width,Window_width,-Window_height * ratio,Window_height * ratio,Front_plane,Back_plane);
/*
	glOrtho(left,right,bottom,top,near,far);
	glFrustum(mismos parametros)

*/
else
	glOrtho(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);


}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
listaCamaras[idCamara].setObserver();
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

				for(int i=0; i< beth.size(); i++){
					if(seleccion == i){
						if(puntos)
						beth[i].drawPoints(0.2,0.2,0.2);
						if(lineas)
						beth[i].drawLines(0.2,0.2,0.2);
						if(solido)
						beth[i].drawFill(ajedrez,0.2,0.2,0.2);
					}
					else
					{
						if(puntos)
						beth[i].drawPoints();
						if(lineas)
						beth[i].drawLines();
						if(solido)
						beth[i].drawFill(ajedrez);
				}
				}
			/*
				if(seleccion == 1)
					e2.drawFill(ajedrez,0.2,0.2,0.2);
				else
					e2.drawFill(ajedrez);

				if(seleccion == 2)
					tt2.drawFill(ajedrez,0.2,0.2,0.2);
				else
					tt2.drawFill(ajedrez);

				if(seleccion == 3){

					Ply2.drawFill(ajedrez,0.2,0.2,0.2);

				}else{

					Ply2.drawFill(ajedrez);

				}

				if(seleccion == 4)
					p2.drawFill(ajedrez,0.2,0.2,0.2);
				else
					p2.drawFill(ajedrez);

				if(seleccion == 5){

				Ply3.drawFill(ajedrez,0.2,0.2,0.2);

			}else{

				Ply3.drawFill(ajedrez);

			}

		*/
/*
				tt2.drawFill(ajedrez,0.2,0.2,0.2);

				c2.drawFill(ajedrez);

				p2.drawFill(ajedrez);
*/
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
UI_window_width = Ancho1;
UI_window_height = Alto1;
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
//////////////////////////MOVIMIENTO DE LA CAMARA///////////////////////////////
if (toupper(Tecla1)=='W'){ listaCamaras[idCamara].AumentarPosZ();	}
if (toupper(Tecla1)=='S'){ listaCamaras[idCamara].DisminuirPosZ();	}
if (toupper(Tecla1)=='A'){ listaCamaras[idCamara].AumentarPosX();	}
if (toupper(Tecla1)=='D'){ listaCamaras[idCamara].DisminuirPosX();	}
////////////////////////////////////////////////////////////////////////////////
////////////////////////MODOS DE PINTADO////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////


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
 if(toupper(Tecla1)=='Z'){
	 sombreadoSmooth = !(sombreadoSmooth);
	 if(!sombreadoSmooth)
		 glShadeModel(GL_SMOOTH);
	 else
		 glShadeModel(GL_FLAT);
 }


 if(toupper(Tecla1)=='X'){
	Orto = !(Orto);
	change_projection();
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
	anguloGeneral += velocidadGiro*0.05;

	glutPostRedisplay();
	}
}




//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*//
void Dibuja(){
	/*glLoadName(1);
	nuevaEs.drawFill(ajedrez);
	glLoadName(2);
	miCubo.drawFill(ajedrez);*/
	glPushName(0);
		if(puntos)
			beth[0].drawPoints();
		if(lineas)
			beth[0].drawLines();
		if(solido)
			beth[0].drawFill(ajedrez);

	glPopName();

	glPushName(1);

	if(puntos)
		beth[1].drawPoints();
	if(lineas)
		beth[1].drawLines();
	if(solido)
		beth[1].drawFill(ajedrez);
	glPopName();

	glPushName(2);
	if(puntos)
		beth[2].drawPoints();
	if(lineas)
		beth[2].drawLines();
	if(solido)
		beth[2].drawFill(ajedrez);
	glPopName();

	glPushName(3);
	if(puntos)
		beth[3].drawPoints();
	if(lineas)
		beth[3].drawLines();
	if(solido)
		beth[3].drawFill(ajedrez);
	glPopName();

	glPushName(4);
	if(puntos)
		beth[4].drawPoints();
	if(lineas)
		beth[4].drawLines();
	if(solido)
		beth[4].drawFill(ajedrez);
	glPopName();

	glPushName(5);
	if(puntos)
		beth[5].drawPoints();
	if(lineas)
		beth[5].drawLines();
	if(solido)
		beth[5].drawFill(ajedrez);
	glPopName();

	glPushName(6);
	if(puntos)
		beth[6].drawPoints();
	if(lineas)
		beth[6].drawLines();
	if(solido)
		beth[6].drawFill(ajedrez);
	glPopName();

	glPushName(7);
	if(puntos)
		beth[7].drawPoints();
	if(lineas)
		beth[7].drawLines();
	if(solido)
		beth[7].drawFill(ajedrez);
	glPopName();

	glPushName(8);
	if(puntos)
		beth[8].drawPoints();
	if(lineas)
		beth[8].drawLines();
	if(solido)
		beth[8].drawFill(ajedrez);
	glPopName();

	glPushName(9);
	if(puntos)
		beth[9].drawPoints();
	if(lineas)
		beth[9].drawLines();
	if(solido)
		beth[9].drawFill(ajedrez);
	glPopName();

	glPushName(10);
	if(puntos)
		beth[10].drawPoints();
	if(lineas)
		beth[10].drawLines();
	if(solido)
		beth[10].drawFill(ajedrez);
	glPopName();

	glPushName(11);
	if(puntos)
		beth[11].drawPoints();
	if(lineas)
		beth[11].drawLines();
	if(solido)
		beth[11].drawFill(ajedrez);
	glPopName();

	glPushName(12);
	if(puntos)
		beth[12].drawPoints();
	if(lineas)
		beth[12].drawLines();
	if(solido)
		beth[12].drawFill(ajedrez);
	glPopName();

	glPushName(13);
	if(puntos)
		beth[13].drawPoints();
	if(lineas)
		beth[13].drawLines();
	if(solido)
		beth[13].drawFill(ajedrez);
	glPopName();

	glPushName(14);
	if(puntos)
		beth[14].drawPoints();
	if(lineas)
		beth[14].drawLines();
	if(solido)
		beth[14].drawFill(ajedrez);
	glPopName();

	glPushName(15);
	if(puntos)
		beth[15].drawPoints();
	if(lineas)
		beth[15].drawLines();
	if(solido)
		beth[15].drawFill(ajedrez);
	glPopName();
}
////////////////////////////////////////////////////////////////////////////////

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*//
//Funcion que fija la proyeccion
void fijaProyeccion(){
	const GLfloat ratio = GLfloat(UI_window_height) / GLfloat(UI_window_width);
	glFrustum(-Window_width,Window_width,-Window_height * ratio,Window_height * ratio,Front_plane,Back_plane);
}
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*//
// Funcion que permite seleccionar un objeto dibujado y modificar el
// comportamiento de la camara respecto a dicho objeto

int pick(int x, int y){
	int vp[4],nobj;
	GLuint buff[512];

	glSelectBuffer(512, buff);	// Indicamos el buffer de los objetos seleccionados
  glRenderMode(GL_SELECT);	// Realizamos la visualización en modo selección
  glInitNames();
  glPushName(-1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glGetIntegerv(GL_VIEWPORT, vp);
  gluPickMatrix(x,vp[3]-y,5,5,vp);

  fijaProyeccion();
  Dibuja();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  fijaProyeccion();

	nobj = glRenderMode(GL_RENDER);

  OBJ obj;
  int i, j, k, omin = -1;
  float zmin = MAXFLOAT;
  int ins;
  k = i = 0;

	while(k < nobj)
 {
	 ins = 0;
	 obj.nnms = buff[i++];
	 obj.zmin = (float)buff[i++]/0xFFFFFFFF;
	 obj.zmax = (float)buff[i++]/0xFFFFFFFF;
	 if(obj.zmin < zmin) ins = 1;
	 for(j = 0; j < obj.nnms; j++)
	 {
		 obj.nms[j] = buff[i++];
		 if(ins && obj.nms[j] >= 0)
			 omin = obj.nms[j];
	 }
	 k++;
 }

 return omin;

}

//******************************************************************************
// Funcion que se encarga de gestionar los eventos que se producen por entradas de raton
// el raton manda a la funcion,
// boton, estado, posx y posy
//

void MiRaton(int boton, int estado, int x, int y){
	switch (boton){

    case GLUT_LEFT_BUTTON:

			if(estado == GLUT_LEFT_BUTTON){
			seleccion = pick(x,y);

			switch (seleccion){

				case -1:
					cout<<"\n No has seleccionado nada";
					idCamara = 0;
				break;

				case 0:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;

				break;

				case 1:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;

				break;

				case 2:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;
				break;


				case 3:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;
				break;


				case 4:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 5:

				if(explorar)
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 6:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 7:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 8:

				if(explorar)
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 9:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 10:
				if(explorar)
					idCamara = seleccion;
				else
					idCamara = 0;
				break;

				case 11:

				if(explorar)
					idCamara = seleccion;
				else
				idCamara = 0;
				break;

				case 12:

				if(explorar )
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 13:

				if(explorar)
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 14:

				if(explorar)
					idCamara = seleccion;
					else
						idCamara = 0;
				break;

				case 15:

				if(explorar)
					idCamara = seleccion;
					else
						idCamara = 0;
				break;
			}
			glutPostRedisplay();
		}
				/*//Hacemos click izquierdo
        if(estado == GLUT_DOWN){
					estadoBotonIzquierdo = true;
          cout<<"Apretando click izquierdo..."<<endl;
					//cout<<"Pos x: "<<x<<endl;
					//cout<<"Pos y: "<<y<<endl;
        }
				//Soltamos click izquierdo
				else{
					estadoBotonIzquierdo = true;
					cout<<"Soltando click izquierdo..."<<endl;
				}*/
    break;

		case GLUT_RIGHT_BUTTON:

				//Hacemos click izquierdo
        if(estado == GLUT_DOWN){
					estadoBotonDerecho = true;
          cout<<"Apretando click derecho..."<<endl;
					ratxo=x;
					ratyo=y;
        }
				//Soltamos click izquierdo
				else{
					estadoBotonDerecho = false;
					cout<<"Soltando click derecho..."<<endl;
				}
    break;

		case GLUT_MIDDLE_BUTTON:

				//Hacemos click izquierdo
        if(estado == GLUT_DOWN){
					cout<<"Apretando la rueda..."<<endl;

        }
				//Soltamos click izquierdo
				else{
					cout<<"Soltando la rueda..."<<endl;

				}
    break;

		case 3:
		 if (estado == GLUT_UP) return;
		 else{
			listaCamaras[idCamara].AumentarDistancia();
			glutPostRedisplay();
		}
		break;

		case 4:
		if (estado == GLUT_UP) return;
	 else{
		listaCamaras[idCamara].DisminuirDistancia();
		glutPostRedisplay();
	}

  }
}


//***************************************************************************
// Funcion que gestiona el moviento de la camara en funcion de si se esta
// pulsando el boton del raton que se encarga de ello

void MoverRaton(int x, int y){
	if(estadoBotonDerecho){
		if(tipoCamara == 0){} //Primera Persona
			listaCamaras[idCamara].setObserverAngleX(y - ratyo);
			listaCamaras[idCamara].setObserverAngleY(x - ratxo);
			ratxo=x;
			ratyo=y;

			glutPostRedisplay();
		}else{
			if(tipoCamara == 1){}
	}
}


//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*//
//                             SELECCION
/*      Por color
				Por Bufer


				-Por Color:Cada objeto tiene un color determinado
				-Por Bufer: Se le pone nombre a cada que queremos seleccionar



				void dibuja_seleccion(){
				glDisable(GL_DITHER);
				glColor3ub(255,0,0);
				objeto1();
				glColor3ub(0,255,0);
				objeto();
				.
				.
				.
				glEnable(GL_DITHER);
			}

			glReadPixed(x,y,width,height,format,type,*pixels)
			en FORMAT usamos GL_RGB
			en TYPE GL_UNSIGNED_BYTE
			en *PIXELS los valores leidos



			void procesaClcik(int x, int y){
			GLint viewport[4];
			GLubyte pixel[3];
			glGetIntegeru(GL_VIEWPORT,viewport);
			glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE, (void)* pixel);
			if(pixel[0]==255
					&&
					pixel[1]==0;
					&&
					pixel[2]==0){
					cout<<"obejto1";
				}
		}

		void ClickRatron(...){
		if estado == exminar
			if( ... = down)
			dibuja_seleccion()
				procesaClcik(x,y);
	}

*/
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

	case GLUT_KEY_F8:
	idCamara = 0;
	break;

	case GLUT_KEY_F9:
	explorar = !(explorar);
	break;

	case GLUT_KEY_F10:
	l0.interruptor();
	break;

	case GLUT_KEY_F11:
	l2.interruptor();
	break;

	case GLUT_KEY_LEFT:
		if(moverVista) listaCamaras[idCamara].DisminuirAnguloY();
		else{
			if(moverl0)l0y--;
			if(moverl1)l1y--;
		}
	break;

	case GLUT_KEY_RIGHT:
		if(moverVista) listaCamaras[idCamara].AumentarAnguloY();
		else{
			if(moverl0)l0y++;
			if(moverl1)l1y++;
		}
	break;

	case GLUT_KEY_UP:
		if(moverVista) listaCamaras[idCamara].DisminuirAnguloX();
		else{
			if(moverl0)l0x--;
			if(moverl1)l1x--;
		}
	break;

	case GLUT_KEY_DOWN:
		if(moverVista) listaCamaras[idCamara].AumentarAnguloX();
		else{
			if(moverl0)l0x++;
			if(moverl1)l1x++;
		}
	break;

	case GLUT_KEY_PAGE_UP:
		if(moverVista) listaCamaras[idCamara].AumentarDistancia();
		else{
			if(moverl0)l0z++;
			if(moverl1)l1z++;
		}
	break;

	case GLUT_KEY_PAGE_DOWN:
		if(moverVista) listaCamaras[idCamara].DisminuirDistancia();
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

listaCamaras.push_back(Camara());

/*listaCamaras.push_back(Camara(5.0,0.0,3.0,5,0,0));//Esfera
listaCamaras.push_back(Camara(-5.0,0.0,3.0,-5,0,0));//Tetraedro
listaCamaras.push_back(Camara(0.0,-13.0,3.0,0,-13,0));//Cubo
listaCamaras.push_back(Camara(0.0,0.0,2,0,0,5));
listaCamaras.push_back(Camara(0.0,0.0,-2,0,0,-5));
*/
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
beth.push_back(Ply2);
int posx,posy,posz;

posx = posy = posz =0;
for(int i = 0; i < 16; i++){

	if(i == 4){
		posx = 0;
		posz += 10;
	}
	if(i == 8){
		posx = 0;
		posz += 10;
	}

	if(i == 12){
		posx=0;
		posz+=10;
	}
	beth[i].Trasladar(posx,posy,posz);
	listaCamaras.push_back(Camara(posx,posy,posz,posx,posy,posz));
	posx +=10;
}


tt2.Trasladar(5,0,0);
e2.Trasladar(-5,0,0);
/*
glPushMatrix();
Ply2.Trasladar(0,13,0);
glScalef(0.2,0.2,0.2);
glPopMatrix();
*/
p2.Trasladar(0,0,-5);
/*
glPushMatrix();
glScalef(0.2,0.2,0.2);
Ply3.Trasladar(0,0,5);
glPopMatrix();
*/
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
// asignacion de la funcion llamada "mi raton " al evento correspondiente
glutMouseFunc(MiRaton);
// asignacion de la funcion llamada "movimientoRAton" al evento correspondiente
glutMotionFunc(MoverRaton);
// asignacion de la funcion llamada "animacion" al evento correspondiente
glutIdleFunc(animacion);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
