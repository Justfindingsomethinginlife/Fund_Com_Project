#include<stdio.h>
#include<stdlib.h>

int main()
{	
    int b[3];
    FILE *fp;
    fp = fopen("test.bin","rb");
    fseek(fp,0,SEEK_SET);
    for(int i=0;i<20;i++)
    {
	fread(b,1,1,fp);
	printf("%x ",*b);
	switch(*b)
		{	
			case 0x01:
				printf("SET ");
				fread(b,1,1,fp);
				printf("%x ",*b);
				fread(b,1,1,fp);
				printf("%x ",*b);
				printf("\n");
				break;
			case 0x02:
				printf("GET ");
				fread(b,1,1,fp);
				printf("%x ",*b);
				printf("\n");
				break;
		}	
    }
    
    fclose(fp);
} 
