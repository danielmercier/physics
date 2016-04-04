EXEC=physics

SRCDIR=src
OBJDIR=obj

SRCWDIR=collisionengine.cpp object.cpp plan.cpp cube.cpp \
				planshape.cpp cubeshape.cpp \
				cuberenderer.cpp planrenderer.cpp renderer.cpp \
				constraint.cpp converter.cpp distanceconstraint.cpp \
				physicsengine.cpp engine.cpp main.cpp

OBJWDIR=$(SRCWDIR:.cpp=.o)

OBJ=$(addprefix $(OBJDIR)/, $(OBJWDIR))
SRC=$(addprefix $(SRCDIR)/, $(SRCWDIR))

$(EXEC): $(OBJ)
	g++ -std=c++11 -lGL -lGLU -lglut -larmadillo -o $(EXEC) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -std=c++11 -o $@ -c $<

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXEC)
