clusterer: clusterer.o
	g++ -o clusterer clusterer.cpp --std=c++11

clusterer.o: clusterer.cpp
	g++ -o clusterer.o clusterer.cpp --std=c++11

clean: 
	@rm -f *.o *.run clusterer

#	./clusterer <dataset> [-o output] [-k n] [-bin b]
run: clusterer
	./clusterer GradientNumbers -o output -k 20 -bin 2
#	./clusterer GradientNumbers -k 20 -bin 2
#	./clusterer GradientNumbers -bin 2