indent:	indent.l indent.y indent.h indentfuncs.c
	bison -d indent.y && \
	flex -oindent.lex.c indent.l && \
	cc -g -o $@ indent.tab.c indent.lex.c indentfuncs.c -lm
