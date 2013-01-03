#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AES_UTILITY.h"

void usage(){
	printf("Incorrect syntax\n\nCorrect usage:\n");
	printf("AES encrypt \"key.file\" \"data.file\" \"output.file\"\n");
	printf("AES decrypt \"key.file\" \"data.file\" \"output.file\"\n");
}

int main(int argc, const char * argv[])
{
	// Validate arguments
	
	if(argc != 5 || (argv[1][0]!='e' && argv[1][0]!='E' && argv[1][0]!='d' && argv[1][0]!='D')){
		usage();
		return -1;
	}
	
	counter c;
	byte temp;
	int fail;
	
	// Read Key
	
	char * keyPath = (char *) argv[2];
	FILE * keyFile = fopen(keyPath, "r");
	if(keyFile == NULL){
		printf("Unable to open key file \"%s\"\n", keyPath);
		return -1;
	}
	
	byte * key = malloc(8);
	size keySize;
	
	fail = 0;
	
	printf("Key:\n");
	for(keySize=0; fail==0; keySize+=1){
		key = realloc(key, 8*keySize+8);
		for(c=0; c < 8; c+=1){
			if(fscanf(keyFile, "%c", &temp)==EOF){ fail=1; break; }
			printf("%02x ", temp);
			key[keySize*8+c] = temp;
		}
		
		if(c==0){ keySize -= 1; c=8; }
		else printf("\n");
	}
	
	printf("\n");
	fclose(keyFile);
	
	// Validate Key length
	if(c!=8){
		keySize -= 1;
		printf("Error: Invalid key length (%u) in \"%s\"\n", 8*keySize+c, keyPath);
		return -1;
	}
	
	// Open Input File
	
	char * dataPath = (char *) argv[3];
	FILE * dataFile = fopen(dataPath, "r");
	
	if(dataFile == NULL){
		printf("Unable to open data file \"%s\"\n", dataPath);
		return -1;
	}
	
	// Open Output File
	
	char * outPath = (char *) argv[4];
	FILE * outFile = fopen(outPath, "w");
	
	if(argv[1][0]=='e' || argv[1][0]=='E'){
		
		// Encrypt
		EncryptStream(dataFile, key, keySize, outFile);
	}
	
	else if(argv[1][0]=='d' || argv[1][0]=='D'){
		
		// Decrypt
		DecryptStream(dataFile, key, keySize, outFile);
	}
	
	fclose(outFile);
	fclose(dataFile);
	
	return 0;
}

// Used for creating test data
//FILE * test = fopen("data.file", "w");
//counter t;
//for(t=0; t<16; t+=1) fprintf(test, "%c", t*16+t);
//for(t=0; t<16; t+=1) fprintf(test, "%c", t*16+t);
//fclose(test);

// Used for creating test key
//FILE * test2 = fopen("key.file", "w");
//counter t2;
//for(t2=0; t2<32; t2+=1) fprintf(test2, "%c", t2);
//fclose(test2);

