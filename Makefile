FLAGS = -Werror

main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

database.o: database.cpp
	g++ ${FLAGS} -c database.cpp

main.exe: main.o
	g++ -o main.exe *.o

clean:
	rm *.o
	rm main