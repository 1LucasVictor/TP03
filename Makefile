SRC:= src
ICL:= include
OBJ:= obj
BIN:= bin

${BIN}/tp03: ${OBJ}/main.o ${OBJ}/AVLTree.o ${OBJ}/Dictionary.o ${OBJ}/Hash_EA.o
	c++ ${OBJ}/*.o -o ${BIN}/tp03

${OBJ}/main.o: ${SRC}/main.cpp
	c++ -c ${SRC}/main.cpp -I ${ICL} -o ${OBJ}/main.o

${OBJ}/AVLTree.o: ${SRC}/AVLTree.cpp
	c++ -c ${SRC}/AVLTree.cpp -I ${ICL} -o ${OBJ}/AVLTree.o

${OBJ}/Dictionary.o: ${SRC}/Dictionary.cpp
	c++ -c ${SRC}/Dictionary.cpp -I ${ICL} -o ${OBJ}/Dictionary.o

${OBJ}/Hash_EA.o: ${SRC}/Hash_EA.cpp
	c++ -c ${SRC}/Hash_EA.cpp -I ${ICL} -o ${OBJ}/Hash_EA.o

clean: 
	rm obj/* bin/*