FLAGS = -Werror

main.exe: main.o database.o
	g++ -o ./main.exe ./*.o

main.o : main.cpp database.cpp database.h
	g++ -Werror -std=c++11 -c ./*.cpp

clean:
	rm *.o
	rm main