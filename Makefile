all: compile link run

compile:
	g++ -I"C:\SFML-2.6.2\include" -I"C:\SFML-2.6.2\include" -c animated.cpp -o animated.o

link: 
	g++ -I"C:\SFML-2.6.2\include" .\animated.o -o animated.exe -L"C:\SFML-2.6.2\lib" -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main 

run:
	./animated.exe