Сборка проекта:
g++ -std=c++11 -c ascii85.cpp -o ascii85.o
g++ -std=c++11 -c main.cpp -o main.o
g++ -std=c++11 ascii85.o main.o -o ascii85
Сборка тестов:
g++ -std=c++11 -c testAscii85.cpp -o testAscii85.o
g++ -std=c++11 ascii85.o testAscii85.o -lgtest -lgtest_main -lpthread -o test_ascii85
