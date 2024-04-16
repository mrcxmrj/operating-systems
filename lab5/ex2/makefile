OBJECTS = sender catcher
FLAGS = -Wall -g

all: sender catcher

sender: sender.c
	gcc $(FLAGS) -o sender sender.c

catcher: catcher.c
	gcc $(FLAGS) -o catcher catcher.c

clean:
	rm $(OBJECTS)
