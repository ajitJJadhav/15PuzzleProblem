#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct PuzzleState
{
	char puzzle[40];
	int depth;
	int heuristicValue;	
};




int**  loadDataFromStringToMatrix(struct PuzzleState x)
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
				matrix[i][j] = atoi(strtok(x.puzzle, ","));
			}
			else
			{
				matrix[i][j] = atoi(strtok(NULL,","));
			}
		}
	}
	return matrix;
}


/*
Heuristic 1 is the number of misplaced tiles in the current configuration
of the puzzle.
For goal state Heuristic 1 value should be 0.
*/
int heuristic_1(struct PuzzleState x)
{
	int **matrix;
	int count = 0;
	
	matrix = loadDataFromStringToMatrix(x);
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(matrix[i][j] != 4*i + j) 
			{
				count += 1 ;
			}
		}
	}
	return count;
}




/*
Heuristic 2 is the sum of number of moves each tile is away from it's goal position.
Calculate Manhattan distance from goal position
For goal state Heuristic 2 value should be 0.
*/
int heuristic_2(struct PuzzleState x)
{
	int sum = 0, a;
	int **matrix;

	matrix =loadDataFromStringToMatrix(x);
	for(int i =0; i < 4; i++)
	{
		for(int j= 0; j < 4; j++)
		{
			a = matrix[i][j];
			if( a != 4*i +j)
			{
				sum += fabs(a/4 - i) + fabs(a%4 -j); // a/4 represents current row and a%4 represents current column
			}
		}
	}

	return sum;
}




void displayMatrix(int **matrix)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			printf("%d ", matrix[i][j] );
		}
		printf("\n");
	}
}






int main()
{
	struct PuzzleState x;
	strcpy(x.puzzle,"0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15");
	return 0;
}