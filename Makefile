# Makefile for InkV.7.3: compiles inkv7 executable and dependances.

# Call without target to make the executable
#      with clean to remove intermediate files.
#      with deepclean to remove all generated files.
#      with test to run the program with gdb as a test wrapper.

### Variables & Setup

# Leave empty to compile for release, otherwise system compiles for debugging.
USE_DEBUG=

# Name of binary executable.
EXE=proto-town

# The base name of every code file used to create the binary.
FILENAMES=main utils loop-clock event-queue event-pass control-map \
	map image-lib tile \
	mob mob-collect part-ai player-ai \
	physics-1 physics-2 physics-3 physics-mob contact accel-request \
        input-event input-handler

# C++ Compiler
CXX=g++
# Flags for compilation
CXXFLAGS=-Wall --std=c++11
# Additional libraries for the linking step.
CXXLIBS=-lsfml-graphics -lsfml-window -lsfml-system
# Additional flags for debug builds.
DEBUG=-ggdb -DDEBUG=true

# Internal Directories
TMPDIR=.tmp
CODEDIR=code
# Calculated File Names
CPPFILES=${FILENAMES:%=${CODEDIR}/%.cpp}
OBJFILES=${FILENAMES:%=${TMPDIR}/%.o}
DEPFILES=${OBJFILES:%.o=%.d}

# If USE_DEBUG add the DUBUG flags.
CXXFLAGS+=${if ${USE_DEBUG},${DEBUG},}

.PHONY : all clean test

### Recipes and Rules

all : ${EXE}

# Rule for the binary
${EXE} : ${OBJFILES}
	${CXX} ${CXXFLAGS} ${CXXLIBS} $^ -o $@

# Rule for object files
${OBJFILES} : ${TMPDIR}/%.o : ${CODEDIR}/%.cpp | ${TMPDIR}
	${CXX} ${CXXFLAGS} -MMD -c $< -o $@

# Rule for the temperary directory
${TMPDIR} :
	mkdir $@

# Phony rule for cleaning intermediate files
clean :
	-rm ${OBJFILES}
	-rm ${DEPFILES}
	-rmdir ${TMPDIR}

# Phony rule for cleaning generated files
deepclean : clean
	-rm ${EXE}

# Phony rule for running the test wrapper
test : ${EXE}
	gdb ./${EXE}

### Include Depends Files

-include ${DEPFILES}
