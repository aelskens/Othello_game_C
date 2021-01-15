all: Player.o Map.o View1.o Main.cpp
	g++ Player.o Map.o View1.o Main.cpp -o Main
Player.o: Player.cpp
	g++ -c Player.cpp
Map.o: Map.cpp
	g++ -c Map.cpp
View1.o: View1.cpp
	g++ -c View1.cpp
clean:
	rm *.o
