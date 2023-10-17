#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024

typedef struct {
	char word[42];
	unsigned count;
} WORD_T;

WORD_T *words = NULL;
size_t total_words = 0;

void print_and_free(WORD_T*, size_t, char*);
int comparator(const void *a, const void *b) {
	return strcmp(a, b);
}

int main(int argc, char **argv) {
	if (argc != 2) return -1;

	char *infile = argv[1];
	// TODO: open the file O_RDONLY
	int fd = open(infile, O_RDONLY);
	if (fd == -1) return -2;

			
	//Checking the ability to read from the file	
	int success=1; 
	while (success!= 0)
	{       //Memory allocation
		char *buffer = malloc(BUFSIZE);
		//Reading the file
		success=read(fd, buffer, BUFSIZE -1);		
		
		buffer[success] = '\0' ;
		//printf("%s/n", buffer);
		
		char *stringp = buffer;	
		while (stringp != NULL) {

		char *token = strsep(&stringp, " \n");
					        
			if(stringp == NULL){
				int track = strlen(token); // size of last token
				memmove(buffer, token, track);
				break;
			}
			
			else if(strlen(token) > 0){
				WORD_T *position = lfind(token, words, &total_words, sizeof(WORD_T), comparator);
				
				//word is found
				if(position == NULL){
					words = realloc(words, sizeof(WORD_T) * (total_words+1));
					strcpy(words[total_words].word, token);
					words[total_words].count = 1;
					total_words++;
					}
				
				//word is not found 
				else{
				
					position -> count++; 
				
				}
			}
			
		}
		
		stringp = buffer;
		
		
		
		
		}


	print_and_free(words, total_words, infile);
		close (fd);
	// TODO: close the file

	return 0;
}

void print_and_free(WORD_T *words, size_t total_words, char *infile) {
	int sum = 0;
	for (int i = 0; i < total_words; ++i) {
		if (words[i].count > 1)
			printf("%s: %u\n", words[i].word, words[i].count);
		sum += words[i].count;
	}
	printf("\n%d %s\n", sum, infile);

	free(words);
}

