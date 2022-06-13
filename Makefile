CC=gcc
CCFLAGS = -std=c99 -Wall -Werror
MODULES = pgmCheckingValue.o pgmErrors.o pgmRead.o pgmWrite.o
MAINS = gtopoEcho.o gtopoComp.o gtopoReduce.o gtopoTile.o gtopoAssemble.o gtopoPrintLand.o gtopoAssembleReduce.o
TARGETS = gtopoEcho gtopoComp gtopoReduce gtopoTile gtopoAssemble gtopoPrintLand gtopoAssembleReduce

.c.o:
	$(CC) $(CCFLAGS) -c -o $@ $<

all: ${TARGETS} ${MAINS}

gtopoEcho:	gtopoEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o gtopoEcho gtopoEcho.o ${MODULES}

gtopoComp: gtopoComp.o ${MODULES}
	${CC} ${CCFLAGS} -o gtopoComp gtopoComp.c ${MODULES}

gtopoReduce: gtopoReduce.o ${MODULES}
	${CC} ${CCFLAGS} -o gtopoReduce gtopoReduce.c ${MODULES}

gtopoTile: gtopoTile.o ${MODULES}
	${CC} ${CCFLAGS} -o gtopoTile gtopoTile.c ${MODULES}

gtopoAssemble: gtopoAssemble.o ${MODULES}
		${CC} ${CCFLAGS} -o gtopoAssemble gtopoAssemble.c ${MODULES}

gtopoPrintLand: gtopoPrintLand.o ${MODULES}
		${CC} ${CCFLAGS} -o gtopoPrintLand gtopoPrintLand.c ${MODULES}

gtopoAssembleReduce: gtopoAssembleReduce.o ${MODULES}
		${CC} ${CCFLAGS} -o gtopoAssembleReduce gtopoAssembleReduce.c ${MODULES}


clean:
	rm ${TARGETS} *.o
