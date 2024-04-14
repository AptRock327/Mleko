//From global include dir
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

//From local include dir
#include <shuffle.h>

#define MAX_MUSIC_FILES 512
#define MAX_FILENAME_LENGTH 128

int main(int argc, char** argv)
{
	//Make sure the argument count is correct
	if(argc < 2)
	{
		printf("Usage: mleko [directory]\n");
		return -1;
	}

	//Initialize and allocate file table
	char** musicFiles = malloc(MAX_MUSIC_FILES * sizeof(char*));
	for(int i = 0; i < MAX_MUSIC_FILES; i++)
	{
		musicFiles[i] = malloc(MAX_FILENAME_LENGTH+1);
	}
	unsigned int fileIndex = 0;

	//Load directory data
	DIR *d;
	struct dirent *dir;
	d = opendir(argv[1]);
	char* extension;
	if(d)
	{
		while(dir = readdir(d))
		{
			extension = strrchr(dir->d_name, '.');
			if(!strcmp(extension, ".wav"))
			{
				strcpy(musicFiles[fileIndex], dir->d_name);
				fileIndex++;
			}
		}
		closedir(d);
	}
	
	//:3
	printf("ENJOY USING MLEKO!\n");

	//Get shuffled list
	unsigned int* shuffledMusic = shuffled(fileIndex);

	//Playback
	char* aplayString = malloc(60+MAX_FILENAME_LENGTH);
	for(int i = 0; i < fileIndex; i++)
	{
		printf("\nNOW PLAYING: %s\n", musicFiles[shuffledMusic[i]]);
		if(i < fileIndex-1) printf("UP NEXT: %s\n", musicFiles[shuffledMusic[i+1]]);
		putchar('\n');
		strcpy(aplayString, "aplay ");
		strcat(aplayString, argv[1]);
		strcat(aplayString, "/");
		strcat(aplayString, musicFiles[shuffledMusic[i]]);
		system(aplayString);
	}

	//Free all the memory
	for(int i = 0; i < MAX_MUSIC_FILES; i++)
	{
		free(musicFiles[i]);
	}
	free(musicFiles);

	free(aplayString);
	return 0;
}
