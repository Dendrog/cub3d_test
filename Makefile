all:
	cc *.c -Lmlx -lmlx -lXext -lX11 -lm -g -fsanitize=address