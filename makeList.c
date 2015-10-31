#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{ //Takes the input argument and creates a .txt file with that name with 100 random integers
	int count, size, num;

	FILE * fp = fopen(argv[1], "w+");
	
	for(count = 0, size = 100; count < size; ++count)
	{
		num = (rand() % 100);
		fprintf(fp, "%d", num);

		if(count != (size-1))
		{
			fputc('\n', fp);
		}
	}

	fclose(fp);
	return(0);
}

