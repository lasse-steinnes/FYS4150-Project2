
all: compile execute

compile:
	c++ -o main.out $(wildcard *.cpp) -larmadillo

execute:
	./main.out

plot:
	python3 plot.py
