# Project: River Raid
# Linux

CPP      = g++
CC       = gcc
OBJ      = main.o RRApp.o Asset.o RRMap.o Bullet.o Enemy.o Fuel.o
LINKOBJ  = main.o RRApp.o Asset.o RRMap.o Bullet.o Enemy.o Fuel.o
LIBS     = -static-libgcc -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -g3
BIN      = river
CXXFLAGS = $(CXXINCS) -std=c++11 -g3 -O3 -Wall
CFLAGS   = $(INCS) -std=c++11 -g3 -O3 -Wall
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
        ${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
        $(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.cpp
        $(CPP) -c main.cpp -o main.o $(CXXFLAGS)

RRApp.o: RRApp.cpp
        $(CPP) -c RRApp.cpp -o RRApp.o $(CXXFLAGS)

Asset.o: Asset.cpp
        $(CPP) -c Asset.cpp -o Asset.o $(CXXFLAGS)

RRMap.o: RRMap.cpp
        $(CPP) -c RRMap.cpp -o RRMap.o $(CXXFLAGS)

Bullet.o: Bullet.cpp
        $(CPP) -c Bullet.cpp -o Bullet.o $(CXXFLAGS)

Enemy.o: Enemy.cpp
        $(CPP) -c Enemy.cpp -o Enemy.o $(CXXFLAGS)

Fuel.o: Fuel.cpp
        $(CPP) -c Fuel.cpp -o Fuel.o $(CXXFLAGS)
