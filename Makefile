all: CS325_Homework1.cpp
	g++ -g -Wall -o hw1 CS325_Homework1.cpp

clean:
	$(RM) hw1