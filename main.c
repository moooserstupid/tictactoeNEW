#include "include/raylib.h"
#include "include/raymath.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define SCREENWIDTH 640
#define SCREENHEIGHT 480

#define N 3
typedef struct BlockStruct
{
	Vector2 size;
	Vector2 position;
	char mark;
	bool filled;
} blockstruct;
typedef struct MoveStruct
{
	char player;
	int x;
	int y;
} movestruct;

void rotate90CW(blockstruct a[N][N])
{
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


bool DidYouWin(blockstruct board[N][N], movestruct move)
{
	bool Win = true;
	int i = 0, j = 0;
	//Diagonal test
	i = 0;
	Win = true;
	//Horizontal Check
	while(i < N && Win)
	{
		if(board[i][move.y].mark != move.player) Win = false;
		++i;
	}
	if(Win) return Win;
	Win = true;
	j = 0;
	//Vertical Check
	while(j < N && Win)
	{
		if(board[move.x][j].mark != move.player) Win = false;
		++j;
	}
	if(Win) return Win;
	
	if(move.x == move.y)
	{
		while(i < N && Win)
		{
			if(board[i][j].mark != move.player) Win = false;
			++i; ++j;
		}
		if(Win) return Win;
	}
	if(move.x + move.y == N -1)
	{
		Win = true;
		i = 0; j = N - 1;
		while(j >= 0 && Win)
		{
			if(board[i][j].mark != move.player) Win = false;
			++i; --j;
		}
		if(Win) return Win;
	}
	
	return Win;
}
void DrawX(Vector2 origin, float radius, float thickness, Color xcolor)
{
	//Very shitty implementation
	Vector2 start = (Vector2){origin.x - radius, origin.y - radius};
	Vector2 dimensions = (Vector2){origin.x + radius, origin.y + radius};
	DrawRectangleV(start, dimensions, xcolor);
	//DrawLineEx(start, Vector2Add(start, dimensions), thickness, xcolor);
	//DrawLineEx((Vector2){start.x + dimensions.x, start.y}, (Vector2){start.x, dimensions.y}, thickness, xcolor);
}

int genRandoms(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int main()
{
	//Game variable declaration and initialization
	int countX, countY;
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "tictactoe!");
	blockstruct blockarray[N][N];
	Vector2 blocksize = {100, 100};
	int moveCount = 0;
	for(countX = 0; countX < N; ++countX)
	{
		for(countY = 0; countY < N; ++countY)
		{
			blockarray[countX][countY].mark = ' ';					//empty
			blockarray[countX][countY].size = blocksize;
			blockarray[countX][countY].position = (Vector2){((SCREENWIDTH - blocksize.x * N) / 2) + (countX * blocksize.x), 
			((SCREENHEIGHT - blocksize.y * N) / 2) + (countY * blocksize.y)};
			blockarray[countX][countY].filled = false;
		}
	}
	char CurrentPlayer;
	
	if(genRandoms(0, 1)) CurrentPlayer = 'X';
	else CurrentPlayer = 'O';
	bool IsGameWon = false;
	movestruct move;
	SetTargetFPS(60);
	while(!WindowShouldClose())
	{
		Vector2 CurrentMousePosition = GetMousePosition();
		for(countX = 0; countX < N; ++countX)
		{
			for(countY = 0; countY < N; ++countY)
			{
				Rectangle blockbounds = (Rectangle){blockarray[countX][countY].position.x, blockarray[countX][countY].position.y, 
				blockarray[countX][countY].size.x, blockarray[countX][countY].size.y};
				if(CheckCollisionPointRec(CurrentMousePosition, blockbounds) && blockarray[countX][countY].mark == ' ')
				{
					blockarray[countX][countY].filled = true;
					if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
					{
						move.player = CurrentPlayer;
						if(CurrentPlayer == 'X')
						{
							blockarray[countX][countY].mark = 'X';
							CurrentPlayer = 'O';
						}else{
							blockarray[countX][countY].mark = 'O';
							CurrentPlayer = 'X';
						}
						++moveCount;
						move.x = countX; move.y = countY;
						IsGameWon = DidYouWin(blockarray, move);
					}
					
				} else{
					blockarray[countX][countY].filled = false;
				}
			}
		}
		
		const char * CurrentPlayerText = TextFormat("Current Player: %c", CurrentPlayer);
		const char * VictoryText = TextFormat("Player %c Won!", move.player);
		const char * DrawStateText = TextFormat("Draw.");
		BeginDrawing();
		ClearBackground(RAYWHITE);
		if(!IsGameWon) DrawText(CurrentPlayerText, 50, SCREENHEIGHT - 50, 30, RED);
		else if(moveCount == N * N) DrawText(DrawStateText, 50, SCREENHEIGHT - 50, 30, GRAY);
		else DrawText(VictoryText, 50, SCREENHEIGHT - 50, 30, GREEN);
		
		for(countX = 0; countX < N; ++countX)
		{
			for(countY = 0; countY < N; ++countY)
			{
				Vector2 blockcenter = (Vector2){blockarray[countX][countY].position.x + blockarray[countX][countY].size.x / 2,
				blockarray[countX][countY].position.y + blockarray[countX][countY].size.y / 2};
				if(blockarray[countX][countY].mark == 'O') DrawCircleLines(blockcenter.x, blockcenter.y, blocksize.x / 4, RED);
				
				if(blockarray[countX][countY].mark == 'X') DrawCircleV(blockcenter, blocksize.x / 4, RED);
				
				if(blockarray[countX][countY].filled) DrawRectangleV(blockarray[countX][countY].position, blockarray[countX][countY].size, YELLOW);
				else DrawRectangleLines(blockarray[countX][countY].position.x, 
				blockarray[countX][countY].position.y, 
				blockarray[countX][countY].size.x, 
				blockarray[countX][countY].size.y, BLACK);
			}
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
