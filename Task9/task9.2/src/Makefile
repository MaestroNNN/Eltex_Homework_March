CC = gcc
CFLAGS = -lncurses

# Список исходников
SRCS = task9.2.c signal.c read_dir.c globals.c move_cursor.c
# Соответствующие объектные файлы
OBJS = $(SRCS:.c=.o)

# Цель для создания только объектных файлов
objs: $(OBJS)

# Правило для компиляции каждого .c в .o
%.o: %.c
	$(CC) -c $< -o $@
all:
	$(CC)

clean:
	rm *.o