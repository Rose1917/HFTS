LIB_FILES=$(wildcard lib/*.so)
SRC_FILES=$(wildcard *.cpp)
main:${SRC_FILES} 
	g++ -w -o main ${SRC_FILES} ${LIB_FILES} 
run:
	sudo ./main
clean:
	rm -f *.o main *.con
debug:${SRC_FILES} 
	g++ -DDEBUG -W  -o main ${SRC_FILES} ${LIB_FILES}
remake:clean main