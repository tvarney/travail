
EXEC := travail

SRC := ./src
INC := ./inc
BIN := ./build

RAPIDJSON_INC := ./modules/rapidjson/include

INCLUDES := -I${INC} -I${RAPIDJSON_INC}

# Get compiler; One of:
#   env CXX
#   env CPP
#   g++
ifndef CXX
  CXX := g++
endif

CXXFLAGS := --std=c++11 -Wall --pedantic ${INCLUDES}
OPT_DBG := -O0 -g
OPT_REL := -O2 -DNDEBUG

LDFLAGS := 
LIBS := -lncurses

REL_OBJS := $(patsubst ${SRC}/%.cpp, ${BIN}/%.o, $(wildcard ${SRC}/*.cpp))
DBG_OBJS := $(patsubst %.o, %.debug.o, ${REL_OBJS})

.PHONEY: all clean release debug

all: release debug

clean:
	rm -f ${BIN}/*

release: CXXFLAGS := ${OPT_REL} ${CXXFLAGS}
release: ${BIN}/${EXEC}

debug: CXXFLAGS := ${OPT_DBG} ${CXXFLAGS}
debug: ${BIN}/${EXEC}.debug

${BIN}/.present:
	mkdir -p ${BIN}
	touch ${BIN}/.present

${BIN}/${EXEC}: ${BIN}/.present ${REL_OBJS}
	${CXX} ${LDFLAGS} -o $@ ${REL_OBJS} ${LIBS}

${BIN}/${EXEC}.debug: ${BIN}/.present ${DBG_OBJS}
	${CXX} ${LDFLAGS} -o $@ ${DBG_OBJS} ${LIBS}

${BIN}/%.o: ${SRC}/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^

${BIN}/%.debug.o: ${SRC}/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $^
