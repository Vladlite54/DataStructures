TARGET=Tree

$(TARGET) : Main.o Menu.o Test.o
	g++ -g Main.o Menu.o Test.o -o $(TARGET) && rm *.o

Main.o : Main.cpp
	g++ -g -c Main.cpp -o Main.o

Menu.o : Menu.cpp
	g++ -g -c Menu.cpp -o Menu.o

Test.o : Test.cpp
	g++ -g -c Test.cpp -o Test.o

clean:
	rm -rf *.o $(TARGET)
