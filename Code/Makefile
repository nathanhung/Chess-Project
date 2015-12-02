CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = chessText
OBJECTS = main.o tile.o CPU.o controller.o views/textdisplay.o views/view.o pieces/bishop.o pieces/chesspiece.o pieces/king.o pieces/knight.o pieces/pawn.o pieces/queen.o pieces/rook.o game.o player.o human.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
