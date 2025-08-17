CC = gcc
CFLAGS = -lncurses

# Список исходников
SRCS = main.c signal.c read_dir.c globals.c move_cursor.c draw.c
# Соответствующие объектные файлы
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(OBJS) -lncurses

# Цель для создания только объектных файлов
objs: $(OBJS)

# Правило для компиляции каждого .c в .o
%.o: %.c
	$(CC) -c $< -o $@ -I../include/

clean:
	rm *.o a.out