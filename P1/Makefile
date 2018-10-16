# fichero Makefile
#
# nombre del fichero ejecutable
#

# VARIABLES

BIN = bin
SRC = src
OBJ = obj
LIB = lib
INCLUDE = include

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE)
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE)

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

TARGETS = practica1

all: presentacion clean $(TARGETS)

# regla de ejecucion
#
$(TARGETS):
	$(CC) -o $(BIN)/$@ $(CXXFLAGS) $(SRC)/O3ds.cpp $(SRC)/O3d.cpp $(SRC)/Cubo.cpp $(SRC)/Tetraedro.cpp $(SRC)/practica1.cc $(LDFLAGS)
#
#

.PHONY: presentacion
presentacion:
	@echo "##################################################"
	@echo "#    Antonio Jaimez Jimenez 3ºA (A1)             #"
	@echo "#    Informatica Grafica                         #"
	@echo "#    Curso 2017/2018                             #"
	@echo "#    Practica1                                   #"
	@echo "##################################################"

.PHONY: clean
clean:
	@echo "Limpiando.."
	@rm -f $(BIN)/*\
	$(OBJ)/*\
	./*.tgz
	@echo "Limpieza finalizada"

#
#
.PHONY: redo
redo:
	touch $(SRC)/*.cpp
	make

#
#
.PHONY: superclean
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#

tgz:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*
	tar -zcvf $(TARGETS).tgz *
