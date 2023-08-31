#include <stdio.h>
#include <stdlib.h>

#include "map.h"

int main(int argc, char **argv)
{
	Map *mymap = malloc(sizeof(Map));
	mymap->ptr = "Hellow World!";
	print_map(mymap);
	free(mymap);
}
