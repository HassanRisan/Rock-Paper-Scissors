





#include<iostream>
#include<cstdlib>


using namespace std;


enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };


struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};



int RadomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Conputer" , "No Winner" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWinnerRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Computer;
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;
	}
	return enWinner::Player1;
}

string ChoiceTextName(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Stone" , "Paper" , "Scissors" };
	return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		break;
	case enWinner::Draw:
		system("color 6F");
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 choice : " << ChoiceTextName(RoundInfo.Player1Choice) << "\n";
	cout << "Computer choice: " << ChoiceTextName(RoundInfo.ComputerChoice) << endl;
	cout << "Round winner   :  [" << RoundInfo.WinnerName << "]\n";
	cout << "__________________________________\n" << endl;
	SetWinnerScreenColor(RoundInfo.Winner);
}


enWinner WhoWinnerTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Computer;
	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::Player1;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(int GameRounds, short Player1WinnerTimes,
	short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResult;
	GameResult.GameRounds = GameRounds;
	GameResult.PlayerWinTimes = Player1WinnerTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWinnerTheGame(Player1WinnerTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);
	return GameResult;
}


enGameChoice ReadPlayerChoice()
{
	short Choice = 1;
	bool FaultMessage = false;
	do
	{
		if (FaultMessage)
			cout << "\nPlease enter a number beteen 1 and 3 \n";
		FaultMessage = true;

		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?   ";

		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RadomNumber(1, 3);
}


stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo raoundInfo;
	short player1WinTimes = 0, computerWinTimes = 0, drawTimes = 0;
	for (int gameRound = 1; gameRound <= HowManyRounds; gameRound++)
	{
		cout << "\nRound [" << gameRound << "] begins:\n";
		raoundInfo.RoundNumber = gameRound;
		raoundInfo.Player1Choice = ReadPlayerChoice();
		raoundInfo.ComputerChoice = GetComputerChoice();
		raoundInfo.Winner = WhoWinnerRound(raoundInfo);
		raoundInfo.WinnerName = WinnerName(raoundInfo.Winner);

		//Increase win/Draw counters
		if (raoundInfo.Winner == enWinner::Player1)
			player1WinTimes++;
		else if (raoundInfo.Winner == enWinner::Computer)
			computerWinTimes++;
		else
			drawTimes++;

		PrintRoundResults(raoundInfo);

	}
	return FillGameResults(HowManyRounds, player1WinTimes,
		computerWinTimes, drawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "              +++ G a m e  O v e r +++ \n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}


void ShowFinalGameResults(stGameResults GameResults)
{
	cout << "\n\nPress any key to show game results...\n\n";
	system("pause>0");
	system("color 0F");

	ShowGameOverScreen();
	cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds       :" << GameResults.GameRounds << "\n";
	cout << Tabs(2) << "Player1 won times :" << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer won times: " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times        : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner      : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";
}

short ReadHowManyRounds()
{
	short GameRounds = 1;
	do
	{
		cout << "How Many Rounds 1 to 10 ? \n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds >10);
	return GameRounds;
}


void ResetScreen()
{
	system("cls");
	system("color 0F");
}


void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowFinalGameResults(GameResults);
		cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";

		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

