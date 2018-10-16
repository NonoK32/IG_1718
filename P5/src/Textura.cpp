#include "Textura.h"
#include "CImg.h"

///////////////////////////////////////////////////////////////////////////////
Textura::Textura(){
}
////////////////////////////////////////////////////////////////////////////////
void Textura::activarTextura(){
  //glBindTexture(GL_TEXTURE_2D,id);
  cargarImagen();
  glEnable(GL_DEPTH_TEST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,256,512,
   0, GL_RGB, GL_UNSIGNED_BYTE, &imagen[0][0][0]);


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glEnable(GL_TEXTURE_2D);
  // TRASFIERE LOS DATOS A GPU

}
////////////////////////////////////////////////////////////////////////////////
void Textura::desactivarTextura(){
  glDisable(GL_TEXTURE_2D);
}
////////////////////////////////////////////////////////////////////////////////
void Textura::cargarImagen(){

   cimg_library::CImg<GLubyte> logo;
   logo.load("./logoo.jpg");

   // empaquetamos bien los datos
   for (long y = 0; y < 256/*logo.height()*/; y ++)
      for (long x = 0; x < 512/*logo.width()*/; x ++)
      {
	       imagen[x][y][0] = logo(x, y, 0, 0);
	       imagen[x][y][1] = logo(x, y, 0, 1);
	       imagen[x][y][2] = logo(x, y, 0, 2);
      }
}
