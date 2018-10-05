/*stack.c*/

/*This program has a buffer overflow vulnerability.*/

/*Our task is to exploit this vulnerability*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int bof(char *str)
{
  char buffer[12];
  /*print the starting address of buffer*/
  printf("the starting address of buffer is %p\n", buffer);
 
  /*The following statement has a buffer overflow problem*/
   strcpy(buffer, str);
  
 /*Print the frame pointer address*/
 printf("Frame Pointer Address is: %p\n", __builtin_frame_address(0));   
 /*you use this address to find return address*/
 return 1;
}

int main(int argc, char **argv)
{
 char str[517];
 FILE *badfile;
 badfile = fopen("badfile", "r");
 fread(str, sizeof(char), 517, badfile);
 bof(str);
 //printf(" the address of stack pointer is: 0x%x\n", __asm__("movl %esp,%eax"));
 printf("Returned Properly\n");
 return 1;
}
