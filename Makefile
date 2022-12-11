SRC:= src
ICL:= include
OBJ:= obj
BIN:= bin

${BIN}/tp: ${OBJ}/main.o ${OBJ}/AVLTree.o
	c++ ${OBJ}/*.o -o ${BIN}/tp03

${OBJ}/main.o: ${SRC}/main.cpp
	c++ -c ${SRC}/main.cpp -I ${ICL} -o ${OBJ}/main.o


${OBJ}/AVLTree.o: ${SRC}/AVLTree.cpp
	c++ -c ${SRC}/AVLTree.cpp -I ${ICL} -o ${OBJ}/AVLTree.o
