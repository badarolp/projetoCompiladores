indent:	indent.l indent.y indent.h indent.c
	bison -d indent.y && \
	flex -oindent.lex.c indent.l && \
	cc -g -o $@ indent.tab.c indent.lex.c indent.c -lm
