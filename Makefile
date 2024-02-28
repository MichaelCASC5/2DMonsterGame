all: compile execute

compile:
	g++ Driver.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system -pthread -lX11

execute:
	./prog #2>/dev/null