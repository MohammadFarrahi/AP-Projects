CC_COMPILER=g++
CC_FALGS=-c -g
CC_STANDARD=--std=c++11
EXE_NAME=utrip.out

CC=${CC_COMPILER} ${CC_STANDARD} ${CC_FALGS} 
OUT=-o ${EXE_NAME}


all: ${EXE_NAME}

utrip.out: main.o UTrip.o UsersManager.o HotelArrange.o UserRating.o User.o Filter.o Hotel.o DataReader.o ReserveItem.o Room.o Tools.o TimePeriod.o Exception.o
	g++ --std=c++11 main.o UTrip.o UsersManager.o HotelArrange.o UserRating.o User.o Filter.o Hotel.o DataReader.o ReserveItem.o Room.o Tools.o TimePeriod.o Exception.o ${OUT}

main.o: main.cpp UTrip.hpp UsersManager.hpp HotelArrange.hpp User.hpp Filter.hpp Hotel.hpp Room.hpp ReserveItem.hpp TimePeriod.hpp Tools.hpp Exception.hpp DataReader.hpp Const.hpp UserRating.hpp
	${CC} main.cpp

UTrip.o: UTrip.cpp UTrip.hpp UsersManager.hpp HotelArrange.hpp User.hpp Filter.hpp Hotel.hpp Room.hpp ReserveItem.hpp TimePeriod.hpp Tools.hpp Exception.hpp DataReader.hpp Const.hpp UserRating.hpp
	${CC} UTrip.cpp

UsersManager.o: UsersManager.cpp UsersManager.hpp User.hpp Filter.hpp Hotel.hpp Room.hpp ReserveItem.hpp TimePeriod.hpp Tools.hpp Exception.hpp Const.hpp UserRating.hpp
	${CC} UsersManager.cpp

User.o: User.cpp User.hpp Tools.hpp UsersManager.hpp Filter.hpp Hotel.hpp Room.hpp ReserveItem.hpp TimePeriod.hpp Exception.hpp Const.hpp UserRating.hpp
	${CC} User.cpp

Filter.o: Filter.cpp Filter.hpp Hotel.hpp ReserveItem.hpp TimePeriod.hpp Exception.hpp Const.hpp
	${CC} Filter.cpp

UserRating.o: UserRating.cpp UserRating.hpp Const.hpp UsersManager.hpp Tools.hpp Exception.hpp Hotel.hpp
	${CC} UserRating.cpp

DataReader.o: DataReader.cpp DataReader.hpp Hotel.hpp Const.hpp
	${CC} DataReader.cpp

HotelArrange.o: HotelArrange.cpp HotelArrange.hpp Exception.hpp Hotel.hpp Const.hpp UsersManager.hpp User.hpp UserRating.hpp
	${CC} HotelArrange.cpp

Hotel.o: Hotel.cpp Hotel.hpp Room.hpp ReserveItem.hpp TimePeriod.hpp Exception.hpp Const.hpp
	${CC} Hotel.cpp

ReserveItem.o: ReserveItem.cpp ReserveItem.hpp TimePeriod.hpp Exception.hpp Hotel.hpp Const.hpp
	${CC} ReserveItem.cpp

Room.o: Room.cpp Room.hpp TimePeriod.hpp Exception.hpp Hotel.hpp Const.hpp
	${CC} Room.cpp

Tools.o: Tools.cpp Tools.hpp Exception.hpp Const.hpp
	${CC} Tools.cpp

TimePeriod.o: TimePeriod.cpp TimePeriod.hpp Exception.hpp
	${CC} TimePeriod.cpp

Exception.o: Exception.cpp Exception.hpp
	${CC} Exception.cpp

clean:
	rm *.o
	rm *.out
