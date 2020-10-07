hepsi: program calistir

Kisi.o:
	g++ -I "./include" -c ./src/Kisi.cpp -o ./lib/Kisi.o
Stack.o:
	g++ -I "./include" -c ./src/Stack.cpp -o ./lib/Stack.o
Node.o:
	g++ -I "./include" -c ./src/Node.cpp -o ./lib/Node.o
main.o:
	g++ -I "./include" -c ./src/main.cpp -o ./lib/main.o
program: Kisi.o Stack.o Node.o main.o
	g++ ./lib/Kisi.o ./lib/Stack.o ./lib/Node.o ./lib/main.o -o ./bin/cikti -std=c++0x
calistir:
	./bin/cikti.exe