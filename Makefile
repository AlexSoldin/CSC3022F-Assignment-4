clusterer: clusterer.o
	g++ -o clusterer clusterer.cpp --std=c++11

clusterer.o: clusterer.cpp
	g++ -o clusterer.o clusterer.cpp --std=c++11

clean: 
	@rm -f *.o *.run clusterer

#	./clusterer <dataset> [-o output] [-k n] [-bin b]
run: clusterer
#	./clusterer Gradient_Numbers_PPMS -o output -k 10 -bin 1
#	./clusterer Gradient_Numbers_PPMS -k 10 -bin 1
	./clusterer Gradient_Numbers_PPMS -k 10 -bin 1 -colour
