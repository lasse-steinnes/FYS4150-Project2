all: compile execute

compile:
	c++ -o main2.out main2.cpp project2.cpp -larmadillo

execute:
	./main2.out
