LIB_FILES=$(wildcard lib/*.so)
SRC_FILES:=$(wildcard *.cpp)
HEAD_FILES:=$(wildcard include/*.h)
OBJ_FILES:=$(SRC_FILES:%.cpp=bin/%.o)
FLAGS=-ldl -lcurl -Wl,-rpath=./lib -w
main:${OBJ_FILES} 
	g++ -w -o main ${OBJ_FILES} ${LIB_FILES} $(FLAGS)
bin/%.o : %.cpp
	g++ -c $(FLAGS) $< -o $@
run:
	./main
rrun:
	sudo ./main
clean:
	rm -f *.o main *.con bin/*.o
debug:${SRC_FILES} 
	g++ -DDEBUG -W  -o main ${OBJ_FILES} ${LIB_FILES} $(FLAGS)
count:
	wc -l $(SRC_FILES) $(HEAD_FILES)
remake:clean main
