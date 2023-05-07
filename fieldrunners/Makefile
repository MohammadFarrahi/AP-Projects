CC_COMPILER=g++
CC_FALGS=-c -g
CC_STANDARD=--std=c++11
EXE_NAME=FieldRunners.out


CC=${CC_COMPILER} ${CC_STANDARD} ${CC_FALGS} 
OUT=-o ${EXE_NAME}
SDL_FLAGS=-l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: ${EXE_NAME}
	

FieldRunners.out: main.o Game.o User.o Field.o Tower.o Shot.o Enemy.o Shape.o Movement.o rsdl.o
	g++ --std=c++11 main.o Game.o User.o Field.o Tower.o Shot.o Enemy.o Shape.o Movement.o rsdl.o ${SDL_FLAGS} ${OUT}

main.o: main.cpp Game.hpp User.hpp Field.hpp Tower.hpp Shot.hpp Enemy.hpp Shape.hpp Movement.hpp ./src/rsdl.hpp
	${CC} main.cpp

Game.o: Game.cpp Game.hpp User.hpp Field.hpp Tower.hpp Shot.hpp Enemy.hpp Shape.hpp Movement.hpp ./src/rsdl.hpp
	${CC} Game.cpp

User.o: User.cpp User.hpp ./src/rsdl.hpp
	${CC} User.cpp

Field.o: Field.cpp Field.hpp Tower.hpp Shot.hpp Enemy.hpp Shape.hpp Movement.hpp ./src/rsdl.hpp
	${CC} Field.cpp

Tower.o: Tower.cpp Tower.hpp Shot.hpp Enemy.hpp Movement.hpp Shape.hpp ./src/rsdl.hpp
	${CC} Tower.cpp

Shot.o: Shot.cpp Shot.hpp Enemy.hpp Movement.hpp Shape.hpp ./src/rsdl.hpp
	${CC} Shot.cpp

Enemy.o: Enemy.cpp Enemy.hpp Movement.hpp Shape.hpp ./src/rsdl.hpp
	${CC} Enemy.cpp

Shape.o: Shape.cpp Shape.hpp Movement.hpp ./src/rsdl.hpp
	${CC} Shape.cpp

Movement.o: Movement.cpp Movement.hpp ./src/rsdl.hpp
	${CC} Movement.cpp

rsdl.o: ./src/rsdl.hpp ./src/rsdl.cpp
	${CC}  src/rsdl.cpp


clean:
	rm *.o
	rm *.out