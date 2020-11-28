LIB_FILES=$(wildcard lib/*.so)
SRC_FILES:=$(wildcard *.cpp)
OBJ_FILES:=$(SRC_FILES:%.cpp=bin/%.o)
FLAGS=-ldl  -Wl,-rpath=./lib -w
main:${OBJ_FILES} 
	g++ -w -o main ${OBJ_FILES} ${LIB_FILES} $(FLAGS)
bin/%.o : %.cpp
	g++ -c $(FLAGS) $< -o $@
run:
	./main
clean:
	rm -f *.o main *.con bin/*.o
debug:${SRC_FILES} 
	g++ -DDEBUG -W  -o main ${OBJ_FILES} ${LIB_FILES} $(FLAGS)
remake:clean main