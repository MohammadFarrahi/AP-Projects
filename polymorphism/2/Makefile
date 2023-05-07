CC_COMPILER=g++
CC_STANDARD=--std=c++11
CC_FLAGS=-c -g

CC=${CC_COMPILER} ${CC_STANDARD} ${CC_FLAGS}

EXE_NAME=2.out
OUT=-o ${EXE_NAME}

all: ${EXE_NAME}

2.out: main.o MessengerNetwork.o Bot.o Channel.o Exception.o
	g++ --std=c++11 main.o MessengerNetwork.o Bot.o Channel.o Exception.o ${OUT}

main.o: main.cpp MessengerNetwork.hpp Bot.hpp Channel.hpp Exception.hpp
	${CC} main.cpp

MessengerNetwork.o: MessengerNetwork.cpp MessengerNetwork.hpp Bot.hpp Channel.hpp Exception.hpp
	${CC} MessengerNetwork.cpp

Bot.o: Bot.cpp Bot.hpp Channel.hpp Exception.hpp
	${CC} Bot.cpp

Channel.o: Channel.cpp Channel.hpp
	${CC} Channel.cpp

Exception.o: Exception.cpp Exception.hpp
	${CC} Exception.cpp

clean:
	rm *.o
	rm *.out
