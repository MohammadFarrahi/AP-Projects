CC_COMPILER=g++
CC_FALGS=-c -g
CC_STANDARD=--std=c++11
EXE_NAME=Goodreads.out

CC=${CC_COMPILER} ${CC_STANDARD} ${CC_FALGS} 
OUT=-o ${EXE_NAME}


all: ${EXE_NAME}


Goodreads.out: main.o GoodReads.o InputDataProcess.o SupplementData.o User.o Author.o Book.o Review.o Date.o
	g++ --std=c++11 main.o GoodReads.o InputDataProcess.o SupplementData.o User.o Author.o Book.o Review.o Date.o ${OUT}

main.o: main.cpp InputDataProcess.hpp GoodReads.hpp Date.hpp Author.hpp SupplementData.hpp User.hpp Book.hpp Review.hpp
	${CC} main.cpp

GoodReads.o: GoodReads.cpp GoodReads.hpp Date.hpp Author.hpp SupplementData.hpp User.hpp Book.hpp Review.hpp
	${CC} GoodReads.cpp

InputDataProcess.o: InputDataProcess.cpp InputDataProcess.hpp GoodReads.hpp Date.hpp Author.hpp SupplementData.hpp User.hpp Book.hpp Review.hpp
	${CC} InputDataProcess.cpp

SupplementData.o: SupplementData.cpp Date.hpp Author.hpp SupplementData.hpp User.hpp Book.hpp Review.hpp
	${CC} SupplementData.cpp

User.o: User.cpp Author.hpp User.hpp Book.hpp Date.hpp
	${CC} User.cpp

Review.o: Review.cpp User.hpp Review.hpp Date.hpp Author.hpp Book.hpp
	${CC} Review.cpp

Author.o: Author.cpp Book.hpp Author.hpp Date.hpp Review.hpp
	${CC} Author.cpp

Book.o: Book.cpp Book.hpp Author.hpp Date.hpp Review.hpp
	${CC} Book.cpp

Date.o: Date.cpp Date.hpp
	${CC} Date.cpp

clean:
	rm *.o
	rm *.out
