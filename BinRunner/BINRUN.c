#include<stdio.h>
#include<stdlib.h>

int main()
{	
    int b[20];
    FILE *fp;
    fp = fopen("test.bin","rb");
    fseek(fp,0,SEEK_SET);
    //for(int i=0;i<2;i++)
    	//printf("%d",fread(b,1,1,fp));
        fread(b,1,1,fp);
	fread(b+1,1,1,fp);
	//fread(b,1,1,fp);			
	printf("%x ",*(b+1));
    
    fclose(fp);
} 
