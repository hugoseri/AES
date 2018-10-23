matrix44.o: matrix44.cpp matrix44.h
		g++ -c matrix44.cpp -lm

messageMatrix.o: messageMatrix.cpp messageMatrix.h
		g++ -c messageMatrix.cpp -lm

keyMatrix.o: keyMatrix.cpp keyMatrix.h
		g++ -c keyMatrix.cpp -lm

main.o: main.cpp keyMatrix.h messageMatrix.o
		g++ -c main.cpp -lm

aes: main.o	matrix44.o messageMatrix.o keyMatrix.o
		g++ main.o	matrix44.o messageMatrix.o keyMatrix.o -o aes
