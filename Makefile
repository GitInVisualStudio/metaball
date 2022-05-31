glad:
	g++ -o ../src/glad.c

install:
	sudo apt install libglfw3 libglfw3-dev libxxf86vm-dev libxi-dev libxinerama-dev freeglut3-dev libglm-dev

compile: glad.o shader.o window.o metaballs.o
	g++ main.cpp -o ./build/main metaballs.o window.o shader.o glad.o -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -pthread
	rm *.o

valgrind: compile
	valgrind ./main

run: compile
	./build/main