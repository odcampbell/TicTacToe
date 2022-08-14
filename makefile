output: main.o common.o playCPU.o ticTacToe.o
	g++ -Wall -Wextra main.o common.o playCPU.o ticTacToe.o -o Play

main.o: main.cpp
	g++ -Wall -Wextra -c main.cpp

common.o: common.cpp common.h
	g++ -Wall -Wextra -c common.cpp

playCPU.o: playCPU.cpp playCPU.h
	g++ -Wall -Wextra -c playCPU.cpp

ticTacToe.o: ticTacToe.cpp ticTacToe.h
	g++ -Wall -Wextra -c ticTacToe.cpp

clean:
	rm *.o Play