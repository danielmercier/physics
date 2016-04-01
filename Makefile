all:
	g++ -std=c++11 -lGL -lGLU -lglut main.cpp

clean:
	rm -f main.o a.out
