#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* loadDataFromMatrixToString(int **matrix)
{
	char* str = (char*)malloc(40*sizeof(char));
	char buffer[5];
	strcpy(str,"\0");
	for(int i =0 ; i < 4; i++)
	{
		for(int j =0 ;j < 4; j++)
		{
			sprintf(buffer,"%d",matrix[i][j]);//itoa(matrix[i][j],buffer,10);
			strcat(str,buffer);
			strcat(str,",");
		}
	}

	printf("%s\n",str );
	return str;

}

int**  loadDataFromStringToMatrix(char puzzle[])
{


	int **matrix = (int**)malloc(4 * sizeof(int*));
	for(int k = 0; k < 4 ;k++)
	{
		matrix[k] = (int*)malloc(4 * sizeof(int));
	}



	for(int i = 0; i < 4; i++)
	{
		for(int j =0 ;j < 4; j++)
		{
			if(i == j && i == 0)
			{
				matrix[i][j] = atoi(strtok(puzzle, ","));
			}
			else
			{
				matrix[i][j] = atoi(strtok(NULL,","));
			}
		}
	}
	return matrix;
}




int main()
{
	char lol[] = "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15";
	int **m;
	/*char *str;
  int **matrix = (int**)malloc(4 * sizeof(int*));
  for(int k = 0; k < 4 ;k++)
  {
    matrix[k] = (int*)malloc(4 * sizeof(int));
  }
  int count = 0;

  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      matrix[i][j] = count++;
    }
  }

  str = loadDataFromMatrixToString(matrix);*/
	m = loadDataFromStringToMatrix(lol);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("%d ",m[i][j]);//matrix[i][j] = count++;
		}
		printf("\n");
	}

}
