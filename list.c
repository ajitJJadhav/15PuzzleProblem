#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct PuzzleState
{
	char puzzle[40];
	int depth;
	int heuristicValue;
	struct PuzzleState* next;	
};


struct PuzzleState *ClosedList = NULL;

void addToCloseList(char puzzle[], int heuristicValue, int depth)
{
	struct PuzzleState *x =  (struct PuzzleState *)malloc(sizeof(struct PuzzleState)) ;
	strcpy(x->puzzle, puzzle);
	x->next = ClosedList ;
	x->depth = depth;
	x->heuristicValue = heuristicValue ;
	ClosedList = x;
}

struct PuzzleState *removefromCloseList(struct PuzzleState *x)
{
	struct PuzzleState *current = ClosedList,*prev = ClosedList;
	struct PuzzleState *temp;
	if( strcmp(x->puzzle,current->puzzle) == 0 )
	{
		ClosedList = ClosedList->next;
		return x;
	}
	current = prev->next ;
	while(current)
	{
		temp = current; //->next;
		if(strcmp(temp->puzzle,x->puzzle) == 0)  //temp == x)
		{
			prev->next = temp->next;
		}
		current = current->next;
		prev = prev->next;
	}
	return x;
}


int checkIfNodeIsInClosedList(struct PuzzleState *x)
{
	struct PuzzleState *current = ClosedList,*temp = NULL;
	int flag = 0; 
	while(current)
	{
		if(strcmp(current->puzzle, x->puzzle) == 0)
		{
			flag = 1;
			if(current->depth > x->depth)
			{
				temp = removefromCloseList(current);
				free(temp);
				return 0;
			}
			else
			{
				return 1;
			}
		}
		current = current->next;
	}
	return flag;
}


void displayCloseList()
{
	struct PuzzleState *current = ClosedList;
	while(current)
	{
		printf("PuzzleState %s\nHeuristic %d\tDepth%d\n",current->puzzle,current->heuristicValue,current->depth );
		current = current->next;
	}
}

int main()
{
	struct PuzzleState *temp = (struct PuzzleState *)malloc(sizeof(struct PuzzleState));//, *testDeletion;
	strcpy(temp->puzzle,"duckoff");
	temp->depth = 1;
	temp->heuristicValue = 0;
	addToCloseList("abcd", 2, 1);
	addToCloseList("abdf", 4, 2);
	addToCloseList("thisiswaste", 7, 3);
	addToCloseList("lolnoob", 5, 6);
	addToCloseList("duckoff", 3, 5);
	displayCloseList();
	//testDeletion = removefromCloseList(temp);
	printf("\n\n\n\n");
	printf("Result is: %d\n", checkIfNodeIsInClosedList(temp));
	displayCloseList();
	return 0;
}