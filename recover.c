#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

typedef uint8_t BYTE;

//required functions
void itoa(int, char*);
void reverse(char*);
#define NUMMAX 50
#define NUMDIGMAX 3

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
    
    int i,j,temp;
    
    //int dummy_num=0;
    char dummy[11]={'0','1','2','3','4','5','6','7','8','9','\0'};
    int dum_arr[3];
    char name[50][10];
    
    for(i=0;i<NUMMAX;i++){
        temp=i;
        for(j=0;j<NUMDIGMAX;j++){
            dum_arr[j]=temp%10;
            temp=temp/10;
        }
        for(j=0;j<3;j++){
            name[i][j]=dummy[dum_arr[2-j]];
        }
        name[i][3]='\0';
    }
    
    for (i=0;i<50;i++){
        outptr[i]=fopen(strcat(name[i],".jpg"), "w");
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