CXX=g++
FLAGS=-g -c
LIB=-L/opt/local/lib -L/usr/local/lib
INC=-I/opt/local/include -I/usr/local/include
LINK=-lglfw -lglew -framework OpenGL

PREAM=$(CXX) $(FLAGS) $(LIB) $(INC) $(LINK)
TINY=include/tinyobjloader/tiny_obj_loader.cc

all: top

_model.o: _model.cpp
	$(PREAM) $(TINY) _model.cpp

_object.o: _model.o _object.cpp
	$(PREAM) $(TINY) _object.cpp

_model_loader.o: _model.o _object.o _model_loader.cpp
	$(PREAM) $(TINY) _model_loader.cpp

top: _model_loader.o _model.o _object.o
	$(CXX) -g $(TINY) _model_loader.o _model.o _object.o -o modeltest

clean:
	rm -rf *.o modeltest *.dSYM
