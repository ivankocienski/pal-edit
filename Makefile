

EXE=paleditor
GPP=g++
OBJ=main.o application.o color-grid.o font.o mode-base.o video.o surface.o
CFLAGS=-Wall -g
LIBS=-lglfw -lGL -lGLU -lpng

all: $(OBJ)
	$(GPP) $(OBJ) -o $(EXE) $(CFLAGS) $(LIBS)

.cc.o:
	$(GPP) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXE)
