#include<stdio.h>

int main()
{
	int MEM[20];
	MEM[1] = 0x01;
        MEM[2] = 0x02;
	MEM[3] = 0x03;
	MEM[4] = 0x02;
	MEM[5] = 0x01;
	MEM[6] = 0x01;
	for(int i=0;i<20;i++)
	{
		switch(MEM[i])
		{	
			case 0x01:
				printf("SET ");
				printf("%x ",*(MEM+i+1));
				printf("%x ",*(MEM+i+2));
				i=i+2;
				printf("\n");
				break;
			case 0x02:
				printf("GET ");
				printf("%x ",*(MEM+i+1));
				i=i+1;
				printf("\n");
		}
	}	

}
