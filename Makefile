# Makefile Partially Taken from CSCI 4229/5229 from University of Colorado Boulder
# Credit goes to Williem (Vlakkies) Schreuder for creating a base to start with this.
all: game

# These are for if you are using GLUT.
#GLB=glut2
#OSXGLNK=GLUT
#LNXGLNK=-lglut
#MGWGLNK=-lglut32cu
#OSXINCLUDE=
# These are for if you are using SDL.
# Hopefully everything here works on Linux and Windows?
GLB=sdlopengl2
OSXGLNK=SDL2 -framework SDL2_image -framework SDL2_ttf
LNXGLNK=-lSDL2 -lSDL2image -lSDL2ttf
MGWGLNK=-lSDL2 -lSLD2image -lSDL2ttf
#OSXINCLUDE=-I /Library/Frameworks/SDL2.framework/Headers
OSXINCLUDE=-F /Library/Frameworks

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=$(MGWGLNK) -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations $(OSXINCLUDE)
LIBS=-framework $(OSXGLNK) -framework OpenGL $(OSXINCLUDE)
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=$(LNXGLNK) -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f game *.o *.a
endif

# Compile rules
.c.o:
	gcc -o $@ -c $(CFLG) $<
.cpp.o:
	g++ -std=c++11 -o $@ -c $(CFLG) $<

glutils/glutil.a:glutils/glConstants.o glutils/$(GLB)/glControls.o glutils/$(GLB)/glTextureGen.o\
		glutils/$(GLB)/glDraw.o glutils/$(GLB)/glShaders.o glutils/$(GLB)/glUtil.o
	ar -rcs $@ $^

utils/util.a:utils/fontBook.o utils/texBook.o utils/gameState.o
	ar -rcs $@ $^

gameFiles/instances.a:gameFiles/arc.o gameFiles/instance.o gameFiles/solid.o gameFiles/player.o\
		main/shaderBox.o gameFiles/shaderboxes/longShaderbox.o gameFiles/textBox.o\
		gameFiles/gsObjects/rain.o gameFiles/gsObjects/grate.o\
		gameFiles/gsObjects/area-jungle/honeyPlatform.o gameFiles/gsObjects/area-jungle/pointLight.o\
		gameFiles/gsObjects/state-objects/button.o gameFiles/gsObjects/state-objects/keyLock.o\
		gameFiles/playerObjects/lighter.o gameFiles/playerObjects/flashlight.o
	ar -rcs $@ $^

gameFiles/levels.a:gameFiles/levels/level.o gameFiles/levels/levelExample.o\
		gameFiles/levels/testLevels/testRain.o gameFiles/levels/testLevels/testJungleObjects.o
	ar -rcs $@ $^

gameFiles/instancesext.a:gameFiles/instancelev.o gameFiles/gsObjects/enclosedLevel.o\
		gameFiles/gsObjects/fakeSolid.o
	ar -rcs $@ $^

# If a level includes instancesExt.h, it belongs here.
gameFiles/levelsext.a:gameFiles/levels/levels.o gameFiles/levels/testLevels/testHorizontalEnclosed.o\
		gameFiles/levels/testLevels/testFalseBlocks.o
	ar -rcs $@ $^

gameFiles/game.a:gameFiles/gameLogic.o 
	ar -rcs $@ $^

game:main/game.o gameFiles/game.a gameFiles/levelsext.a gameFiles/instancesext.a gameFiles/levels.a\
		gameFiles/instances.a utils/util.a glutils/glutil.a
	g++ -std=c++11 -O3 -o $@ $^ $(LIBS)

clean:
	rm -f game *.o *.a
	cd main && rm -f *.o *.a
	cd glutils && rm -f *.o *.a
	cd utils && rm -f *.o *.a
	cd glutils/$(GLB) && rm -f *.o *.a
	cd gameFiles && rm -f *.o *.a
	cd gameFiles/playerObjects && rm -f *.o *.a
	cd gameFiles/gsObjects && rm -f *.o *.a
	cd gameFiles/gsObjects/area-jungle && rm -f *.o *.a
	cd gameFiles/gsObjects/state-objects && rm -f *.o *.a
	cd gameFiles/levels && rm -f *.o *.a
	cd gameFiles/levels/testLevels && rm -f *.o *.a
	cd gameFiles/shaderboxes && rm -f *.o *.a