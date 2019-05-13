CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -MMD 
OBJECTS=main.o potion.o treasure.o cell.o chamber.o character.o door.o enemy.o floor.o normalCell.o passage.o pc.o spawn.o stair.o wall.o item.o message.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGES} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm *.o *.d cc3k
.PHONY: clean
