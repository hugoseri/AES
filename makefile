matrice44.o: matrice44.cpp matrice44.h
		g++ -c matrice44.cpp -lm

main.o: main.cpp matrice44.h
		g++ -c main.cpp -lm

aes: main.o	matrice44.o
		g++ main.o	matrice44.o -o aes
