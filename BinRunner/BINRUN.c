#include<stdio.h>
#include<stdlib.h>

int main()
{	
    int b[3];
    FILE *fp;
    fp = fopen("test.bin","rb");
    fseek(fp,0,SEEK_SET);
    for(int i=0;i<10;i++)
    {
	fread(b,1,1,fp);
	printf("%x ",*b);
    }
    
    fclose(fp);
} 
