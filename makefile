LIB_FILES=$(wildcard lib/*.so)
SRC_FILES=$(wildcard *.cpp)
main:${SRC_FILES} 
	g++  -o main ${SRC_FILES} ${LIB_FILES} 
run:
	./main
clean:
	rm -f *.o main *.con
debug:${SRC_FILES} 
	g++ -DDEBUG -o main ${SRC_FILES} ${LIB_FILES}
