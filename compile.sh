g++ -g --std=c++11 -L/usr/include/json -ljsoncpp -L/usr/include/SFML/ -I/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -I./include main.cpp src/**.cpp src/*/*.cpp -o bin/program.out
