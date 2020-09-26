
all: compile execute

compile:
	c++ -Wall -o main.out $(wildcard *.cpp) -larmadillo

execute:
	./main.out

plot1:
	python3 plot_eigenvector.py

plot2:
	python3 plot_transformations.py
