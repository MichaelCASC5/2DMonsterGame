all: compile execute

compile:
	g++ main.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

execute:
	./prog #2>/dev/null