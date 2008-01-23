
BIN = uhcc_sort
SRCS = main.c

${BIN}: ${SRCS}
	gcc -o $@ ${SRCS}

clean:
	rm -f ${BIN}
