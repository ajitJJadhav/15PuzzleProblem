#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
#include <iostream>
using namespace std;
*/

#define up 0
#define down 1
#define left 2
#define right 3


struct PuzzleState
{
	char puzzle[40];
	int depth;
	int heuristicValue;
	int f;
	struct PuzzleState* parent;
	struct PuzzleState* next;
};


struct PuzzleState *ClosedList = NULL;

void addToCloseList(struct PuzzleState *temp)
{
	struct PuzzleState *x =  (struct PuzzleState *)malloc(sizeof(struct PuzzleState)) ;
	strcpy(x->puzzle, temp->puzzle);
	x->next = ClosedList ;
	x->depth = temp->depth;
	x->f = temp->f;
	x->heuristicValue = temp->heuristicValue ;
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


struct PuzzleState* heap[1000000];
int heapSize;

/*Initialize Heap*/

void Init() {
    heapSize = 0;
    heap[0] = (struct PuzzleState*)malloc(sizeof(struct PuzzleState));
    heap[0]->heuristicValue = heap[0]->depth = heap[0]->f = 0;
}


struct PuzzleState* createNode(char puzzle[],int heuristicValue,int depth)
{
  struct PuzzleState* temp;
  temp = (struct PuzzleState*)malloc(sizeof(struct PuzzleState));


  strcpy(temp->puzzle,puzzle);
  temp->heuristicValue = heuristicValue;
  temp->depth = depth;
  temp->parent = NULL;
  return temp;
}


/* moves[] is the array that contains the boolean values
for possible moves that the blank can take.
0- up 1 - down 2 - left 3 - right */
void checkPossibleMoves(int moves[], int position)
{
	int row,column;

	for(int i = 0 ; i < 4 ; i++)
	{
		moves[i] = 1;
	}

	row = position / 4;
	column = position % 4;

	if(row == 0)
	{
		moves[up] = 0;
	}
	if(row == 3)
	{
		moves[down] = 0;
	}
	if(column == 0)
	{
		moves[left] = 0;
	}
	if(column == 3)
	{
		moves[right] = 0;
	}
}


int positionOfBlank(int **A)
{
	int i,j;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			if(A[i][j] == 0)
				return 4*i+j;
	}
}

void printNode(struct PuzzleState *temp)
{
  printf("\n%d\n%s\n ", temp->heuristicValue, temp->puzzle);
}


void heapify(int position)
{
	int now = position;
	struct PuzzleState *element;
	element = heap[position];

  while ( heap[now / 2]->f  > element->f ) {

      heap[now] = heap[now / 2];

      now /= 2;

  }

  heap[now] = element;
}

/*Insert an element into the heap */
void Insert(struct PuzzleState *element) {
  heapSize++;

  heap[heapSize] = element; /*Insert in the last place*/

	/*Adjust its position*/
  int now = heapSize;

  while ( heap[now / 2]->f > element->f ) {

      heap[now] = heap[now / 2];

      now /= 2;

  }

  heap[now] = element;

}

struct PuzzleState* DeleteMin() {

    /* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased.

     Now heap[1] has to be filled. We put the last element in its place and see if it fits.

     If it does not fit, take minimum element among both its children and replaces parent with it.

     Again See if the last element fits in that place.*/

    int child, now;
    struct PuzzleState *minElement,*lastElement;

    minElement = heap[1];

    lastElement = heap[heapSize--];

    /* now refers to the index at which we are now */

    for (now = 1; now * 2 <= heapSize; now = child) {

        /* child is the index of the element which is minimum among both the children */

        /* Indexes of children are i*2 and i*2 + 1*/

        child = now * 2;

        /*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one

         child */

        if (child != heapSize && heap[child + 1]->f < heap[child]->f) {

            child++;

        }

        /* To check if the last element fits ot not it suffices to check if the last element

         is less than the minimum element among both the children*/

        if (lastElement->f > heap[child]->f ) {

            heap[now] = heap[child];

        } else /* It fits there */

        {
            break;
        }

    }

    heap[now] = lastElement;

    return minElement;

}

char* loadDataFromMatrixToString(int **matrix)
{
	char* str = (char*)malloc(40*sizeof(char));
	char buffer[5];
	strcpy(str,"\0");
	for(int i =0 ; i < 4; i++)
	{
		for(int j =0 ;j < 4; j++)
		{
			sprintf(buffer,"%d",matrix[i][j]); //itoa(matrix[i][j],buffer,10);
			strcat(str,buffer);
			strcat(str,",");
		}
	}

	// printf("%s\n",str );
	return str;

}

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
			if(matrix[i][j] != 4*i + j + 1  && matrix[i][j] != 0)
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
			if( a != 4*i +j + 1  && a != 0)
			{
				sum += fabs((a-1)/4 - i) + fabs((a-1)%4 -j); // a/4 represents current row and a%4 represents current column
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
			if(matrix[i][j] != 0)
			{
				printf("%d ", matrix[i][j] );

				//fromatting the output properly
				if(matrix[i][j] < 10)
					printf(" ");
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}
	//printf("\n\n");
}

int checkDuplicate(struct PuzzleState *temp)
{
	int i,flag=0;

	for(i=1;i<=heapSize;i++)
	{
		if(heap[i]->heuristicValue == temp->heuristicValue)
		{
			if(strcmp(heap[i]->puzzle,temp->puzzle) == 0)
			{
				if(temp->depth < heap[i]->depth)
				{
					heap[i]->depth = temp->depth;
					heap[i]->f = temp->f;
					heapify(i);
				}

				flag = 1;
			}
		}
	}

	return flag;
}

char* getPuzzle(int **matrix,int i,int position)
{
	int x1,y1,x2,y2;
	int temp;
	char *x;

	x1 = position/4;
	y1 = position%4;

	x2 = x1;
	y2 = y1;

	if(i == 0)
		x2 = x1-1;
	else if(i == 1)
		x2 = x1+1;
	else if(i == 2)
		y2 = y1-1;
	else
		y2 = y1+1;

	temp = matrix[x1][y1];
	matrix[x1][y1] = matrix[x2][y2];
	matrix[x2][y2] = temp;

	x = loadDataFromMatrixToString(matrix);

	temp = matrix[x1][y1];
	matrix[x1][y1] = matrix[x2][y2];
	matrix[x2][y2] = temp;

	return x;
}

void printPath(struct PuzzleState *temp)
{
	int **matrix;

	while(temp->parent != NULL)
	{
		matrix = loadDataFromStringToMatrix(*temp);
		printf("%d,%d,%d\n",temp->heuristicValue,temp->depth,temp->f);
		displayMatrix(matrix);
		printf("\n\n");
		temp = temp->parent;
	}

}
int isSolvable(struct PuzzleState *x)
{
	int **m, position,*arr,k=0,count= 0;



	arr = (int*)malloc(sizeof(int)*16);
	m = loadDataFromStringToMatrix(*x);
	position = positionOfBlank(m);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4 ; j++)
		{
			arr[k++] = m[i][j];
		}
	}

	for (int i = 0; i < 15; i++)
    {
        for (int j = i + 1; j < 16; j++)
        {
            if (arr[j] && arr[i] && arr[i] > arr[j])
                count++;
        }
    }


   if((count % 2 != 0) &&  (4 - (position/4)) % 2 == 0 )
   {
   		return 1;
   }

   else if((count % 2 == 0) && (4 - (position/4)) % 2 != 0)
   {
   		return 1;
   }

   else
   {
   		return 0;
   }
}




void findMin()
{
	int min = heap[1]->f;
	for(int i=1;i<heapSize;i++)
	{
		if(heap[i]->heuristicValue < min)
			min = heap[i]->f;
	}

	printf("Min : %d\n",min );
}

int main()
{
	struct PuzzleState x,*temp,*node,*leftChildNode,*rightChildNode,*upChildNode,*downChildNode;
	int moves[4] = {0};
	char *puzzle,*teststr;
	int **matrix;
	int position,i,heuristicValue,depth,flag=0;


	strcpy(x.puzzle,"6,2,8,4,12,14,1,10,13,15,3,9,11,0,5,7");

	x.depth = 0;
	x.heuristicValue = heuristic_2(x);
	x.f = x.depth*0.3 + x.heuristicValue;
	x.parent = NULL;


	if(isSolvable(&x)) // check if the puzzle is solvable
	{
		Init();

		Insert(&x);
		while(heapSize>0)
		{
			temp = DeleteMin();
			matrix = loadDataFromStringToMatrix(*temp);

			//check goal PuzzleState
			if(temp->heuristicValue == 0)
				break;


			position = positionOfBlank(matrix);
			checkPossibleMoves(moves,position);
			//evaluating all possible moves
			for(i=0;i<4;i++)
			{
				if(moves[i] == 1)
				{
					puzzle = getPuzzle(matrix,i,position);
					node = createNode(puzzle,-1,temp->depth + 1);
					node->heuristicValue = heuristic_2(*node);
					node->f = node->heuristicValue + node->depth*0.3;
					node->parent = temp;
					if(checkDuplicate(node) == 0)
					{
						if( checkIfNodeIsInClosedList(node) == 0 )//check if node in closed list ---> if there in closed list and depth less than that of closed list then delete from closedlist and add to open list or else leave as it is
						{
								Insert(node);
						}

						else
						{
							//do nothing if it is there in closed and depth is greater than closed list node
						}
					}
				}
			}

			addToCloseList(temp);

		}

		if(temp->heuristicValue == 0)
		{

			printPath(temp);
			printf("%d\n",temp->depth);
		}

		else
			printf("No solution exists.\n");

	}
	else
	{
		printf("Puzzle cannot be solved from the current state.\n");
	}
	return 0;
}
