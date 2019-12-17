CC = g++
CFLAGS = -ansi -pedantic -Wall -std=c++11 -g #-DMAP

MAIN = main
SRCS = Trajet.cpp TrajetSimple.cpp TrajetCompose.cpp main.cpp Catalogue.cpp
OBJS = $(SRCS:.cpp=.o)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.cpp %.h
	$(CC) $(CFLAGS) -c $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c $^

.PHONY : launch

launch :
	./main
