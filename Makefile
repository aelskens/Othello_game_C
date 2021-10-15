all: Player.o Map.o View1.o Main.cpp
	g++ -std=c++11 Player.o Map.o View1.o Main.cpp -o Main
Player.o: Player.cpp
	g++ -std=c++11 -c Player.cpp
Map.o: Map.cpp
	g++ -std=c++11 -c Map.cpp
View1.o: View1.cpp
	g++ -std=c++11 -c View1.cpp
clean:
	rm *.o
