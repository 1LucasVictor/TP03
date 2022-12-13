SRC:= src
ICL:= include
OBJ:= obj
BIN:= bin

${BIN}/tp03: ${OBJ}/main.o ${OBJ}/AVLTree.o ${OBJ}/Dictionary.o
	c++ ${OBJ}/*.o -o ${BIN}/tp03

${OBJ}/main.o: ${SRC}/main.cpp
	c++ -c ${SRC}/main.cpp -I ${ICL} -o ${OBJ}/main.o

${OBJ}/AVLTree.o: ${SRC}/AVLTree.cpp
	c++ -c ${SRC}/AVLTree.cpp -I ${ICL} -o ${OBJ}/AVLTree.o

${OBJ}/Dictionary.o: ${SRC}/Dictionary.cpp
	c++ -c ${SRC}/Dictionary.cpp -I ${ICL} -o ${OBJ}/Dictionary.o

clean: 
	rm obj/* bin/*