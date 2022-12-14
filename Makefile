SRC:= src
ICL:= include
OBJ:= obj
BIN:= bin

${BIN}/tp03: ${OBJ}/main.o ${OBJ}/AVLTree.o ${OBJ}/Hash_EA.o
	c++ ${OBJ}/*.o -o ${BIN}/tp03

${OBJ}/main.o: ${SRC}/main.cpp 
	c++ -c ${SRC}/main.cpp -I ${ICL} -o ${OBJ}/main.o

${OBJ}/AVLTree.o: ${SRC}/AVLTree.cpp ${ICL}/AVLTree.hpp
	c++ -c ${SRC}/AVLTree.cpp -I ${ICL} -o ${OBJ}/AVLTree.o

${OBJ}/Hash_EA.o: ${SRC}/Hash_EA.cpp ${ICL}/Hash_EA.hpp
	c++ -c ${SRC}/Hash_EA.cpp -I ${ICL} -o ${OBJ}/Hash_EA.o

clean: 
	rm obj/* bin/*