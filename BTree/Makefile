TARGET=Tree

$(TARGET) : Main.o Menu.o
	g++ -g Main.o Menu.o -o $(TARGET) && rm *.o

Main.o : Main.cpp
	g++ -g -c Main.cpp -o Main.o

Menu.o : Menu.cpp
	g++ -g -c Menu.cpp -o Menu.o

clean:
	rm -rf *.o $(TARGET)
