#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

typedef uint8_t BYTE;

//required functions
void itoa(int, char*);
void reverse(char*);

int main(int argc, char* argv[]){
    
    if(argc!=2){
        fprintf(stderr,"Usage: ./recover infile\n");
        return 1;
    }
    
    char* infile=argv[1];
    
    FILE* inptr=fopen(infile, "r");
    if(inptr==NULL){
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }
    
    BYTE b[512];
    
    //50 output files
    FILE* outptr[50];
    
    int i;
    
    for (i=0;i<50;i++){
        char str[10];
        itoa(i+1,str);
        outptr[i]=fopen(strcat(str,".jpeg"), "w");
    }
    
    i=-1;
    
    while(fread(b,1,512,inptr)){
        
        if((b[0]==0xff)&&(b[1]==0xd8)&&(b[2]==0xff)&&(b[3]>0xdf)&&(b[3]<0xf0)){
            i++;
        }
        
        if(i>=0) fwrite(&b,1,512,outptr[i]);
    }
    
    for(i=0;i<50;i++){
        fclose(outptr[i]);
    }
    
    return 0;
}

void itoa(int n, char s[]){
    int i, sign;
 
    if ((sign = n) < 0)  /* record sign */
    n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
    s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
    s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]){
    int i, j;
    char c;
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}