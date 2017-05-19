#include <stdio.h>
/*!
  Lazurite AES keygen
  */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	int i;
	long seeds;
	char key[33];
	unsigned int data;

	// set Signal Trap

	if(argc<2) {
		printf("aes_keygen need key data\n");
		printf("aes_keygen 0-32767\n");
		return 0;
	} else {
		seeds = strtol(argv[1],NULL,0); 
		printf("aes key=%d\n",seeds);
	}
	
	srand(seeds);
	memset(key,0,sizeof(key));
	for (i=0;i<32;i++) {
		data = rand()%16;
		key[i] = (data) < 10 ? ('0'+data) : ('A'+data-10);
	}

	printf("%s\n",key);

	return 0;
}
