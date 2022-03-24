
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define BOARDW 5
typedef struct BlockStruct
{
	int mark;
} blockstruct;

void rotate90CW(blockstruct a[BOARDW][BOARDW])
{
	int N = BOARDW;
	int i, j;
	for(i = 0; i < N / 2; ++i)
	{
		for(j = i; j < N - i - 1; ++j)
		{
			char temp = a[i][j].mark;
			a[i][j].mark = a[N - 1 - j][i].mark;
			a[N - 1 - j][i].mark = a[N - 1 - i][N - 1 - j].mark;
			a[N - 1 - i][N - 1 - j].mark = a[j][N - 1 - i].mark;
			a[j][N - 1 - i].mark = temp;
		}
	}
}



int genRandoms(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
void print2DArray(blockstruct a[BOARDW][BOARDW])
{
	int i, j;
	for(i = 0; i < BOARDW; ++i)
	{
		for(j = 0; j < BOARDW; ++j) printf("%d ", a[i][j].mark);
		printf("\n");
	}
}

int main()
{
	blockstruct board[BOARDW][BOARDW];
	int i, j;
	for(i = 0; i < BOARDW; ++i)
	{
		for(j = 0; j < BOARDW; ++j) board[i][j].mark = genRandoms(0, 20);
	}
	print2DArray(board);
	for(i = 0; i < 4; ++i)
	{
		printf("\nRotation Number: %d \n", i + 1);
		rotate90CW(board);
		print2DArray(board);
	}
	
	return 0;
}
