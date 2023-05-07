CC_COMPILER=g++
CC_STANDARD=--std=c++11
CC_FLAGS=-c -g

EXE_NAME=1.out

OUT=-o ${EXE_NAME}
CC=${CC_COMPILER} ${CC_STANDARD} ${CC_FLAGS}

all: ${EXE_NAME}

1.out: main.o JsonBuilder.o Container.o Data.o Exception.o
	g++ --std=c++11 main.o JsonBuilder.o Container.o Data.o Exception.o ${OUT}

main.o: main.cpp JsonBuilder.hpp Container.hpp Data.hpp Exception.hpp
	${CC} main.cpp

JsonBuilder.o: JsonBuilder.cpp JsonBuilder.hpp Container.hpp Data.hpp Exception.hpp
	${CC} JsonBuilder.cpp

Container.o: Container.cpp Container.hpp Data.hpp Exception.hpp
	${CC} Container.cpp

Data.o: Data.cpp Data.hpp Exception.hpp
	${CC} Data.cpp

Exception.o: Exception.cpp Exception.hpp
	${CC} Exception.cpp

clean:
	rm *.o
	rm *.out

