objects = create_children list_children

all: create_children list_children

create_children: create_children.c
	gcc -o create_children create_children.c

list_children: list_children.c
	gcc -o list_children list_children.c

clean:
	rm $(objects)
