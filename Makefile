all: compile execute

compile:
	g++ main.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system -pthread -lX11

execute:
	./prog #2>/dev/null
