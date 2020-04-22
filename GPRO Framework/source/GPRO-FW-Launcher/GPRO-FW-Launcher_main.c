// GPRO-FW-Launcher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
int launchTicTacToe();
int launchBattleship();

int main()
{
	char choice = 'A';
	while (choice != 'X') {
		printf("T for Tick Tac Toe or B for Battleship and X for Exit: ");
		scanf("%c", &choice);
		switch (choice)
		{
		case 'T':
			launchTicTacToe();
			break;
		case 'B':
			launchBattleship();
			break;
		case 'X':
			break;
		default:
			printf("Invalid Input");
		}
	}
	return 0;
}
