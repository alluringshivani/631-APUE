/*
 * Homework-1 - bbcp.c - bare-bones copy a file
 * Author: Rajat Rajesh Shetty
 * Email: rshett2@stevens.edu
*/

#include <stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<libgen.h>
#include<string.h>
#include<sys/stat.h>

#define BUFFERSIZE 16384


int main(int argc,char* argv[]) {
  FILE *file1,*file2;
  struct stat buf,secondDirectory;
  char buffer[BUFFERSIZE];
  int n,writeDescriptor,filedesc;
  file1=fopen(argv[1],"r");
  file2=fopen(argv[2],"w");
  if (access(argv[1], R_OK) != 0) {
		fprintf(stderr, "%s is not readable (access denied)\n", argv[1]);
		exit(1);
	}
   stat(argv[1],&buf);

    if(argc!=3) {
      fprintf(stderr, "Please specify source-file target-file\n");
      exit(1);
    }

    if (strcmp(argv[1], argv[2]) == 0) {  /* checking if the source file and destination file are the same while copy command is being used*/
		fprintf(stderr, "both files entered are the same\n");
		exit(1);
	  }

    if(S_ISDIR(buf.st_mode)){     /* IS_DIR is a function that checks if the file is a directory or not*/
        printf("Source is a directory\n");
        exit(1);
    }
    if(access((dirname(strdup(argv[2]))), W_OK) != 0) {
		fprintf(stderr, "%s is not writable(access denied)", dirname(strdup(argv[2])));
		exit(1);
	}
	
  stat(argv[2], &buf);
  
    mkdir(dirname(strdup(argv[2])),0777);  /* Reference: https://stackoverflow.com/questions/5425891/how-do-i-check-if-a-directory-exists-is-dir-file-exists-or-both */
    if(S_ISDIR(buf.st_mode)) {
		strcat(argv[2],"/");
		strcat(argv[2],basename(strdup(argv[1])));
	  }
  
  char c;
    while((c=fgetc(file1))!=EOF) { /* copying character by character to the destination file until we reach EOF*/
    fputc(c,file2); 
    }
  fclose(file1);
  fclose(file2);
  return(0);
}
