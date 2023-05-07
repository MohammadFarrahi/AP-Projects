CC_COMPILER=g++
CC_FALGS=-c -g -pedantic
CC_STANDARD=--std=c++11
EXE_NAME=utrip.out
BUILD_DIR=build


CC=${CC_COMPILER} ${CC_STANDARD} ${CC_FALGS} 


all: ${EXE_NAME}

utrip.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/PageShowers.o $(BUILD_DIR)/Handlers.o $(BUILD_DIR)/UTrip.o $(BUILD_DIR)/UsersManager.o $(BUILD_DIR)/HotelArrange.o $(BUILD_DIR)/UserRating.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/DataReader.o $(BUILD_DIR)/ReserveItem.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Tools.o $(BUILD_DIR)/TimePeriod.o $(BUILD_DIR)/Exception.o
	g++ --std=c++11 $(BUILD_DIR)/main.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/PageShowers.o $(BUILD_DIR)/Handlers.o $(BUILD_DIR)/UTrip.o $(BUILD_DIR)/UsersManager.o $(BUILD_DIR)/HotelArrange.o $(BUILD_DIR)/UserRating.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/DataReader.o $(BUILD_DIR)/ReserveItem.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Tools.o $(BUILD_DIR)/TimePeriod.o $(BUILD_DIR)/Exception.o -o ${EXE_NAME}

$(BUILD_DIR)/main.o: project/main.cpp project/PageShowers.hpp project/Handlers.hpp project/UTrip.hpp project/UsersManager.hpp project/HotelArrange.hpp project/User.hpp project/Filter.hpp project/Hotel.hpp project/Room.hpp project/ReserveItem.hpp project/TimePeriod.hpp project/Tools.hpp project/Exception.hpp project/DataReader.hpp project/Const.hpp project/UserRating.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	${CC} project/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Handlers.o: project/Handlers.cpp project/Handlers.hpp project/UTrip.hpp project/UsersManager.hpp project/HotelArrange.hpp project/Filter.hpp project/Hotel.hpp project/TimePeriod.hpp project/Exception.hpp project/DataReader.hpp project/Const.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	${CC} project/Handlers.cpp -o $(BUILD_DIR)/Handlers.o

$(BUILD_DIR)/PageShowers.o: project/PageShowers.cpp project/PageShowers.hpp project/UTrip.hpp project/UsersManager.hpp project/HotelArrange.hpp project/Hotel.hpp project/Exception.hpp project/DataReader.hpp project/Const.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	${CC} project/PageShowers.cpp -o$(BUILD_DIR)/PageShowers.o

$(BUILD_DIR)/UTrip.o: project/UTrip.cpp project/UTrip.hpp project/UsersManager.hpp project/HotelArrange.hpp project/User.hpp project/Filter.hpp project/Hotel.hpp project/Room.hpp project/ReserveItem.hpp project/TimePeriod.hpp project/Tools.hpp project/Exception.hpp project/DataReader.hpp project/Const.hpp project/UserRating.hpp
	${CC} project/UTrip.cpp -o $(BUILD_DIR)/UTrip.o

$(BUILD_DIR)/UsersManager.o: project/UsersManager.cpp project/UsersManager.hpp project/User.hpp project/Filter.hpp project/Hotel.hpp project/Room.hpp project/ReserveItem.hpp project/TimePeriod.hpp project/Tools.hpp project/Exception.hpp project/Const.hpp project/UserRating.hpp
	${CC} project/UsersManager.cpp -o $(BUILD_DIR)/UsersManager.o

$(BUILD_DIR)/User.o: project/User.cpp project/User.hpp project/Tools.hpp project/UsersManager.hpp project/Filter.hpp project/Hotel.hpp project/Room.hpp project/ReserveItem.hpp project/TimePeriod.hpp project/Exception.hpp project/Const.hpp project/UserRating.hpp
	${CC} project/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Filter.o: project/Filter.cpp project/Filter.hpp project/Hotel.hpp project/ReserveItem.hpp project/TimePeriod.hpp project/Exception.hpp project/Const.hpp
	${CC} project/Filter.cpp -o $(BUILD_DIR)/Filter.o

$(BUILD_DIR)/UserRating.o: project/UserRating.cpp project/UserRating.hpp project/Const.hpp project/UsersManager.hpp project/Tools.hpp project/Exception.hpp project/Hotel.hpp
	${CC} project/UserRating.cpp -o $(BUILD_DIR)/UserRating.o

$(BUILD_DIR)/DataReader.o: project/DataReader.cpp project/DataReader.hpp project/Hotel.hpp project/Const.hpp
	${CC} project/DataReader.cpp -o $(BUILD_DIR)/DataReader.o

$(BUILD_DIR)/HotelArrange.o: project/HotelArrange.cpp project/HotelArrange.hpp project/Exception.hpp project/Hotel.hpp project/Const.hpp project/UsersManager.hpp project/User.hpp project/UserRating.hpp
	${CC} project/HotelArrange.cpp -o $(BUILD_DIR)/HotelArrange.o

$(BUILD_DIR)/Hotel.o: project/Hotel.cpp project/Hotel.hpp project/Room.hpp project/ReserveItem.hpp project/TimePeriod.hpp project/Exception.hpp project/Const.hpp
	${CC} project/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/ReserveItem.o: project/ReserveItem.cpp project/ReserveItem.hpp project/TimePeriod.hpp project/Exception.hpp project/Hotel.hpp project/Const.hpp
	${CC} project/ReserveItem.cpp -o $(BUILD_DIR)/ReserveItem.o

$(BUILD_DIR)/Room.o: project/Room.cpp project/Room.hpp project/TimePeriod.hpp project/Exception.hpp project/Hotel.hpp project/Const.hpp
	${CC} project/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/Tools.o: project/Tools.cpp project/Tools.hpp project/Exception.hpp project/Const.hpp
	${CC} project/Tools.cpp -o $(BUILD_DIR)/Tools.o

$(BUILD_DIR)/TimePeriod.o: project/TimePeriod.cpp project/TimePeriod.hpp project/Exception.hpp
	${CC} project/TimePeriod.cpp -o $(BUILD_DIR)/TimePeriod.o

$(BUILD_DIR)/Exception.o: project/Exception.cpp project/Exception.hpp
	${CC} project/Exception.cpp -o $(BUILD_DIR)/Exception.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	${CC} utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	${CC} utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	${CC} utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	${CC} server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	${CC} server/route.cpp -o $(BUILD_DIR)/route.o


clean:
	rm $(BUILD_DIR)/*.o
	rm *.out
