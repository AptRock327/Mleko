#include <shuffle.h> //from local include dir

unsigned int* shuffled(unsigned int size)
{
	//Initialize list of natural numbers
	unsigned int* list = malloc(size * sizeof(unsigned int));
	for(int i = 0; i < size; i++)
	{
		list[i] = i;
	}

	//Shuffle the list
	unsigned int tmp;
	unsigned int swap;
	srand(time(0));
	for(int i = 0; i < size; i++)
	{
		swap = rand() % size;
		tmp = list[i];
		list[i] = list[swap];
		list[swap] = tmp;
	}

	return list;
}
