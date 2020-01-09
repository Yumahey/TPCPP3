
OBJ=Trajet.o TrajetSimple.o TrajetCompose.o Catalogue.o main.o
EXEC=TP3
FLAGS=-g -o0 -ansi -pedantic -Wall -std=c++11
DEFINES=

.PHONY : clear

clear :
	rm $(OBJ) $(EXEC)

run : $(EXEC)
	./TP3

%.o : %.cpp %.h
	g++ -c $(DEFINES) $<
	
$(EXEC) : $(OBJ)
	g++ $(FLAGS) $(DEFINES) -o $(EXEC) $(OBJ)

build_MAP: DEFINES = -DMAP

build_MAP : $(EXEC)
	