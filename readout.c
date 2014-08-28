#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>



/*


   Settings
   ./read 0

   Reads out whole data package

   ./read 1

   Read out the temperatue only

   ./read [0/1] SECS
   SECS stands for the seconds waited in the loop


   /.read [0/1] SECS file.cvs
   Write temperatures into cvs file in 123,3123 format 
The values will be in the secomd column.

   ./read [0/1] SECS file.cvs NUMBEr

NUMBER says how many data you want to collect - leave it out and there will be an infinite loop which can onle be borken by SIGKILL (strg+c) atm, which leads to the bug that no data will be written into the cvs file

< */



int main(int argc, char* argv[])
{

	FILE* file;
FILE* file_2;



	char path[1024];
	char* file_input[4096];
	int i = 0;
	int wait_time;
	int check;
	time_t now;

	if(argc < 3)
	{
		printf("Please specify the unique folder of the sensor you will find it in /sys/bus/w1/devices/   . You onle need to give that one cryptic number\n");
		printf("also enter a 0 if you only want to see the temperature, if you want to see the full data package enter 1 \n"); 
		exit(1);
	}

	int all = atoi(argv[2]);

	printf("The folder you are looking in is %s\n", argv[1]);
	sprintf(path,"/sys/bus/w1/devices/%s/w1_slave", argv[1]);

	file = fopen(path,"r");
	if(file == NULL)
	{
		printf("Could not find file - please check if the file really exists! \n");
		exit(1);
	}
	else
	{	
		printf("File opening was sucessfull \n");
	}

	for(;i < 76; i++)
	{
		fscanf(file,"%c", &file_input[i]);
	}




	if(all == 1)
	{
		for(i=0; i < 76; i++)
		{	
			printf("%c", file_input[i]);
		}
	}
	else
	{
		for(i=69; i < 76; i++)
		{
			printf("%c", file_input[i]);
		}

	}

	if(argv[3] != NULL)
	{
		wait_time = atoi(argv[3]);
	}
	else
	{
		wait_time = 1;
		printf("Default time is one second \n");
	}

	if(argv[4] != NULL)
	{
		file_2 = fopen(argv[4], "w");
		if(file_2 == NULL)
		{
			printf("could not open %s", argv[4]);
			exit(1);
		}
		check = 1;
	}

	int x = 0;
	int y = 0;
	if(argv[5] != NULL)
	{
		y = atoi(argv[5]);
	}
	//Looping
	while(x <= y)
	{
		sleep(wait_time);
		now = time(0);
		printf("\n\n%s \n", ctime(&now));

		for(i=0;i < 76; i++)
		{
			fscanf(file,"%c", &file_input[i]);
		}


		if(all == 1)
		{

			fprintf(file_2,"%s;", ctime(&now));
			for(i=0; i < 76; i++)
			{       
				printf("%c", file_input[i]);

				if(check == 1)			
				{
					fprintf(file_2,"%c", file_input[i]);
				}
			}
		}
		else
		{

			fprintf(file_2,"%s;", ctime(&now));

			for(i=69; i < 76; i++)
			{
				printf("%c", file_input[i]);

				if(check == 1)  
				{

					fprintf(file_2,"%c", file_input[i]);

				}


			}

		}
		x++;
	}

	if(argv[4] != NULL)
	{
		fclose(file_2);
	}



	fclose(file);	





}
