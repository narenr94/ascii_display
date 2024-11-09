rm ./*.o
g++ -Wall -c ../src/*.cpp ./cube_rotate.cpp -I ../include/ -g -lncurses
g++ -Wall ./*.o -o ./cube_example -g -lncurses