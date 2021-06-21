all:
	g++ main.cpp -Isfml/include/ -Lsfml/lib -lsfml-window -lsfml-system -lsfml-graphics
	export LD_LIBRARY_PATH=sfml/lib && ./a.out