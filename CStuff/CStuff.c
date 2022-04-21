#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdbool.h>

void drawgrid(char grid[9])
{
	char todraw[13] = "";
	int offset = 0;
	for (int i = 0; i < 9; i++)
	{
		todraw[3] = '\n';
		todraw[7] = '\n';
		todraw[11] = '\n';

		if (i == 3 || i == 6) offset++;
		todraw[i + offset] = grid[i];
	}
	printf(todraw);
	printf("\n");
}
bool IsFinished(char grid[9], bool player)
{
	bool isfinished = true;
	bool istie = true;
	char tocheck;
	if (player)
	{
		tocheck = 'o';
	}
	else
	{
		tocheck = 'x';
	}
	for (int i = 0; i < 9; i++)
	{
		if (grid[i] == '\'') { isfinished = false; istie = false; }
	}
	if (grid[0] == tocheck && grid[1] == tocheck && grid[2] == tocheck) isfinished = true;
	if (grid[3] == tocheck && grid[4] == tocheck && grid[5] == tocheck) isfinished = true;
	if (grid[6] == tocheck && grid[7] == tocheck && grid[8] == tocheck) isfinished = true;
	if (grid[0] == tocheck && grid[4] == tocheck && grid[8] == tocheck) isfinished = true;
	if (grid[2] == tocheck && grid[4] == tocheck && grid[6] == tocheck) isfinished = true;
	if (grid[2] == tocheck && grid[5] == tocheck && grid[8] == tocheck) isfinished = true;
	if (grid[1] == tocheck && grid[4] == tocheck && grid[7] == tocheck) isfinished = true;
	if (grid[0] == tocheck && grid[3] == tocheck && grid[6] == tocheck) isfinished = true;
	if (isfinished == true)
	{
		if (istie) printf("A tie. \n");
		else if (player) printf("Congratulations Circle, you won! \n");
		else printf("Congratulations Cross, you won! \n");
	}
	return isfinished;
}

bool ParseLocation(char toparse[3], int* location)
{
	if ((toparse[0] != 'a' && toparse[0] != 'b' && toparse[0] != 'c' && toparse[0] != 'A' && toparse[0] != 'B' && toparse[0] != 'C') || (toparse[1] != '1' && toparse[1] != '2' && toparse[1] != '3'))
	{
		return false;
	}
	int templocation = 0;
	switch (toparse[0])
	{
	case 'a':
	{
		templocation = (templocation + 0);
		break;
	}
	case 'A':
	{
		templocation = (templocation + 0);
		break;
	}
	case 'b':
	{
		templocation = (templocation + 3);
		break;
	}
	case 'B':
	{
		templocation = (templocation + 3);
		break;
	}
	case 'c':
	{
		templocation = (templocation + 6);
		break;
	}
	case 'C':
	{
		templocation = (templocation + 6);
		break;
	}
	}
	switch (toparse[1])
	{
	case '1':
	{
		templocation = (templocation + 0);
		break;
	}
	case '2':
	{
		templocation = (templocation + 1);
		break;
	}
	case '3':
	{
		templocation = (templocation + 2);
		break;
	}
	}
	*location = *&templocation;
	return true;

}
bool isvalid(char grid[9], int location)
{
	if (grid[location] == '\'')
	{
		return true;
	}
	else return false;
}
bool MoveIsWin(char grid[9], int one, int two, int three, char tocheck)
{
	int thingstocheck[3];
	int empty;
	int i = 0;
	if (grid[one] == '\'') { empty = one; }
	else { thingstocheck[i] = one; i++; }
	if (grid[two] == '\'') { empty = two; }
	else { thingstocheck[i] = two; i++; }
	if (grid[three] == '\'') { empty = three; }
	else { thingstocheck[i] = three; i++; }
	if (i < 2) return false;
	else
	{
		if (grid[thingstocheck[0]] == tocheck && grid[thingstocheck[1]] == tocheck) return true;
		else printf("Fatal error");
	}
}
void DoEnemyMove(char grid[9], bool player)
{
	int move;
	// "AI" stuff
	//check if AI can win
	bool canwin = false;
	char tocheck = player ? 'o' : 'x';

	/*if (grid[0] == '\'' && grid[1] == tocheck && grid[2] == tocheck) { canwin = true; move = 0; }
	else if (grid[0] == tocheck && grid[1] == '\'' && grid[2] == tocheck) { canwin = true; move = 1; }
	else if (grid[0] == tocheck && grid[1] == tocheck && grid[2] == '\'') { canwin = true; move = 2; }

	else if (grid[3] == '\'' && grid[4] == tocheck && grid[5] == tocheck) { canwin = true; move = 3; }
	else if (grid[3] == tocheck && grid[4] == '\'' && grid[5] == tocheck) { canwin = true; move = 4; }
	else if (grid[3] == tocheck && grid[4] == tocheck && grid[5] == '\'') { canwin = true; move = 5; }

	else if (grid[6] == '\'' && grid[7] == tocheck && grid[8] == tocheck) { canwin = true; move = 6; }
	else if (grid[6] == tocheck && grid[7] == '\'' && grid[8] == tocheck) { canwin = true; move = 7; }
	else if (grid[6] == tocheck && grid[7] == tocheck && grid[8] == '\'') { canwin = true; move = 8; }

	else if (grid[0] == '\'' && grid[4] == tocheck && grid[8] == tocheck) { canwin = true; move = 0; }
	else if (grid[0] == tocheck && grid[4] == '\'' && grid[8] == tocheck) { canwin = true; move = 4; }
	else if (grid[0] == tocheck && grid[4] == tocheck && grid[8] == '\'') { canwin = true; move = 8; }

	else if (grid[2] == '\'' && grid[4] == tocheck && grid[6] == tocheck) { canwin = true; move = 2; }
	else if (grid[2] == tocheck && grid[4] == '\'' && grid[6] == tocheck) { canwin = true; move = 4; }
	else if (grid[2] == tocheck && grid[4] == tocheck && grid[6] == '\'') { canwin = true; move = 6; }

	else if (grid[2] == '\'' && grid[5] == tocheck && grid[8] == tocheck) { canwin = true; move = 2; }
	else if (grid[2] == tocheck && grid[5] == '\'' == tocheck && grid[8]) { canwin = true; move = 5; }
	else if (grid[2] == tocheck && grid[5] == tocheck && grid[8] == '\'') { canwin = true; move = 8; }

	else if (grid[1] == '\'' == tocheck && grid[4] == tocheck && grid[7]) { canwin = true; move = 1; }
	else if (grid[1] == tocheck && grid[4] == '\'' && grid[7] == tocheck) { canwin = true; move = 4; }
	else if (grid[1] == tocheck && grid[4] == tocheck && grid[7] == '\'') { canwin = true; move = 7; }

	else if (grid[0] == '\'' && grid[3] == tocheck && grid[6] == tocheck) { canwin = true; move = 0; }
	else if (grid[0] == tocheck && grid[3] == '\'' && grid[6] == tocheck) { canwin = true; move = 3; }
	else if (grid[0] == tocheck && grid[3] == tocheck && grid[6] == '\'') { canwin = true; move = 6; }*/
	if (MoveIsWin(grid,0,1,2,tocheck)) { canwin = true; move = 0; }

	if (canwin) { grid[move] = player ? 'o' : 'x'; return; }
	//Will enemy win logic goes second
	bool enemycanwin = false;
	tocheck = player ? 'x' : 'o';
	if (grid[0] == '\'' && grid[1] == tocheck && grid[2] == tocheck) { enemycanwin = true; move = 0; }
	else if (grid[0] == tocheck && grid[1] == '\'' && grid[2] == tocheck) { enemycanwin = true; move = 1; }
	else if (grid[0] == tocheck && grid[1] == tocheck && grid[2] == '\'') { enemycanwin = true; move = 2; }

	else if (grid[3] == '\'' && grid[4] == tocheck && grid[5] == tocheck) { enemycanwin = true; move = 3; }
	else if (grid[3] == tocheck && grid[4] == '\'' && grid[5] == tocheck) { enemycanwin = true; move = 4; }
	else if (grid[3] == tocheck && grid[4] == tocheck && grid[5] == '\'') { enemycanwin = true; move = 5; }

	else if (grid[6] == '\'' && grid[7] == tocheck && grid[8] == tocheck) { enemycanwin = true; move = 6; }
	else if (grid[6] == tocheck && grid[7] == '\'' && grid[8] == tocheck) { enemycanwin = true; move = 7; }
	else if (grid[6] == tocheck && grid[7] == tocheck && grid[8] == '\'') { enemycanwin = true; move = 8; }

	else if (grid[0] == '\'' && grid[4] == tocheck && grid[8] == tocheck) { enemycanwin = true; move = 0; }
	else if (grid[0] == tocheck && grid[4] == '\'' && grid[8] == tocheck) { enemycanwin = true; move = 4; }
	else if (grid[0] == tocheck && grid[4] == tocheck && grid[8] == '\'') { enemycanwin = true; move = 8; }

	else if (grid[2] == '\'' && grid[4] == tocheck && grid[6] == tocheck) { enemycanwin = true; move = 2; }
	else if (grid[2] == tocheck && grid[4] == '\'' && grid[6] == tocheck) { enemycanwin = true; move = 4; }
	else if (grid[2] == tocheck && grid[4] == tocheck && grid[6] == '\'') { enemycanwin = true; move = 6; }

	else if (grid[2] == '\'' && grid[5] == tocheck && grid[8] == tocheck) { enemycanwin = true; move = 2; }
	else if (grid[2] == tocheck && grid[5] == '\'' == tocheck && grid[8]) { enemycanwin = true; move = 5; }
	else if (grid[2] == tocheck && grid[5] == tocheck && grid[8] == '\'') { enemycanwin = true; move = 8; }

	else if (grid[1] == '\'' == tocheck && grid[4] == tocheck && grid[7]) { enemycanwin = true; move = 1; }
	else if (grid[1] == tocheck && grid[4] == '\'' && grid[7] == tocheck) { enemycanwin = true; move = 4; }
	else if (grid[1] == tocheck && grid[4] == tocheck && grid[7] == '\'') { enemycanwin = true; move = 7; }

	else if (grid[0] == '\'' && grid[3] == tocheck && grid[6] == tocheck) { enemycanwin = true; move = 0; }
	else if (grid[0] == tocheck && grid[3] == '\'' && grid[6] == tocheck) { enemycanwin = true; move = 3; }
	else if (grid[0] == tocheck && grid[3] == tocheck && grid[6] == '\'') { enemycanwin = true; move = 6; }
	if (enemycanwin) { grid[move] = player ? 'o' : 'x'; return; }
	//Then check corners
	if (grid[0] == '\'') move = 0;
	else if (grid[2] == '\'') move = 2;
	else if (grid[6] == '\'') move = 6;
	else if (grid[8] == '\'') move = 8;
	//Then centre/sides
	else if (grid[1] == '\'') move = 1;
	else if (grid[3] == '\'') move = 3;
	else if (grid[5] == '\'') move = 5;
	else if (grid[4] == '\'') move = 4;
	else if (grid[7] == '\'') move = 7;
	//Execute move
	grid[move] = player ? 'o' : 'x';
	return;
}

int main()
{
	char str[2];
	int location = -1;
	char tempgrid[9] = { '\'','\'' ,'\'' ,'\'' ,'\'' ,'\'' ,'\'' ,'\'' ,'\'' };
	bool aienabled;
	bool aifaction;
	printf("Play against AI? (y/n)");
label2:
	gets(str);
	if (str[0] == 'y' || str[0] == 'Y')
	{
		aienabled = true;
	label3:
		printf("Should the AI go first? (y/n)");
		gets(str);
		if (str[0] == 'y' || str[0] == 'Y')
		{
			aifaction = false;
		}
		else if (str[0] == 'n' || str[0] == 'N')
		{
			aifaction = true;
		}
		else
		{
			printf("Failed to parse your response, try again please (y/n)");
			goto label3;
		}
	}
	else if (str[0] == 'n' || str[0] == 'N')
	{
		aienabled = false;
	}
	else
	{
		printf("Failed to parse your response, try again please (y/n)");
		goto label2;
	}
restartLabel: {};
	bool isfinished = false;
	bool whoseturn = false;
	drawgrid(tempgrid);
	while (isfinished == false)
	{
		if (aifaction == whoseturn)
		{
			DoEnemyMove(tempgrid, aifaction);
			drawgrid(tempgrid);
		}
		else
		{

			printf("%s Where do you wish to place your token? (a-c, 1-3)? \n", whoseturn ? "Circle," : "Cross,");
			gets(str);
		label:
			if (ParseLocation(str, &location) == false) // has already placed a thing on said location or invalid location
			{

				printf("Invalid location, please try again, %s", whoseturn ? "Circle\n" : "Cross\n");
				gets(str);
				goto label;
			}
			else if (isvalid(tempgrid, location))
			{
				tempgrid[location] = whoseturn ? 'o' : 'x';
			}
			else
			{
				location = -1;
				str[0] = 'x';
				str[1] = 'x';
				goto label;
			}
			drawgrid(tempgrid);
		}

		isfinished = IsFinished(tempgrid, whoseturn);
		whoseturn = !whoseturn;
	}
	printf("play again (y/n)");
	label4:
	gets(str);
	if (str[0] == 'y' || str[0] == 'Y')
	{
		goto restartLabel;
	}
	else if (str[0] == 'n' || str[0] == 'N');
	else
	{
		printf("Failed to parse your response, try again please (y/n)");
		goto label4;
	}
}
