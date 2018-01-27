#include<stdio.h>
#include <string.h>
#include <math.h>
#include<limits.h>
#include<stdlib.h>


struct PuzzleState
{
	char puzzle[40];
	int depth;
	int heuristicValue;
  struct PuzzleState* parent;
};


struct PuzzleState* heap[1000000];
int heapSize;

/*Initialize Heap*/

void Init() {
    heapSize = 0;
    heap[0] = (struct PuzzleState*)malloc(sizeof(struct PuzzleState));
    heap[0]->heuristicValue = heap[0]->depth = 0;
}

/*Insert an element into the heap */

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

void printNode(struct PuzzleState *temp)
{
  printf("\n%d\n%s\n ", temp->heuristicValue, temp->puzzle);
}

void heapify(int position)
{
	int now = position;
	struct PuzzleState *element;
	element = heap[position];

  while ( heap[now / 2]->heuristicValue + heap[now / 2]->depth > element->heuristicValue + element->depth ) {

      heap[now] = heap[now / 2];

      now /= 2;

  }

  heap[now] = element;
}

void Insert(struct PuzzleState *element) {
  heapSize++;

  heap[heapSize] = element; /*Insert in the last place*/
  /*Adjust its position*/

  int now = heapSize;

  while ( heap[now / 2]->heuristicValue + heap[now / 2]->depth > element->heuristicValue + element->depth ) {

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

        if (child != heapSize && heap[child + 1]->heuristicValue + heap[child + 1]->depth < heap[child]->heuristicValue + heap[child]->depth) {

            child++;

        }

        /* To check if the last element fits ot not it suffices to check if the last element

         is less than the minimum element among both the children*/

        if (lastElement->heuristicValue + lastElement->depth > heap[child]->heuristicValue + heap[child]->depth ) {

            heap[now] = heap[child];

        } else /* It fits there */

        {

            break;

        }

    }

    heap[now] = lastElement;

    return minElement;

}



int main() {

    int number_of_elements;

    printf("Program to demonstrate Heap:\nEnter the number of elements: ");

    scanf("%d", &number_of_elements);

    int iter;
    struct PuzzleState* temp;

    Init();


    for (iter = 0; iter < number_of_elements; iter++) {
        temp = (struct PuzzleState*)malloc(sizeof(struct PuzzleState));

        scanf("%s %d", temp->puzzle, &temp->heuristicValue);
        temp->depth = 0;
        Insert(temp);

    }

		//heap[4]->heuristicValue = 1;
		//heapify(4);

    for (iter = 0; iter < number_of_elements; iter++) {
        temp = DeleteMin();
        printNode(temp);
    }

    printf("\n");

    return 0;

}
