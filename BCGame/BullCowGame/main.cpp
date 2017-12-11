/*This is the console executable that makes use of the Bull-Cow class.
This acts as the view in a MVC pattern, and is responsible for all user interactions.
For game logic, see the FBullCowGame class*/

#include <iostream>
#include <string>
#include <map>
#include "FBullCowGame.h"
#define TMap std::map;

// make syntax more Unreal-friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayTheGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
//void ChooseDifficulty();

// instantiate the game and reuse across plays
FBullCowGame BCGame;

int main()
{
	bool bRepeat = false;
	do
	{
		PrintIntro();
		PlayTheGame();
		bRepeat = AskToPlayAgain();
	}
	while (bRepeat);

	return 0; // exit the application

}


void PlayTheGame()
{
	BCGame.Reset();

	int32 Max_Tries = BCGame.GetMaxTries();

	// loop for the number of turns asking for and print out guesses
	// while the game is not won
	// and there are still tries remaining
	while (!BCGame.AllAreBulls() && BCGame.GetCurrentTry() <= Max_Tries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// print the number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;

	}

	PrintGameSummary();
	return;
}


// get the guess from the player, loop continually until the guess is valid for the game
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Empty;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 MaxTries = BCGame.GetMaxTries();
		std::cout << "Try " << CurrentTry << " of " << MaxTries;
		std::cout << " Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without any repeating letters.";
			std::cout << std::endl;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
			std::cout << "-letter word." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word without any uppercase letters.";
			std::cout << std::endl;
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no error.

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play it again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
	
}

// introduce the game
void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "    /                       \\" << std::endl;
	std::cout << "  /X/                       \\X\\" << std::endl;
	std::cout << " |XX\\       _______         /XX|" << std::endl;
	std::cout << " |XXX\\    _/        \\_     /XXX|___________" << std::endl;
	std::cout << "  \\XXXXXX              XXXXXXX/            \\\\\\" << std::endl;
	std::cout << "   \\XXXX    /     \\    XXXXX/                \\\\\\" << std::endl;
	std::cout << "        |   0     0   |                         \\" << std::endl;
	std::cout << "         |           |                           \\" << std::endl;
	std::cout << "          \\         /                            |______//" << std::endl;
	std::cout << "           \\       /                             |" << std::endl;
	std::cout << "            | O_O | \\                            |" << std::endl;
	std::cout << "             \\ _ /   \\          ________         |" << std::endl;
	std::cout << "                      \\________/       \\         /" << std::endl;
	std::cout << " No Bullshit,          \\  | \\  |        \\_______/" << std::endl;
	std::cout << " Please...              \\ |  \\ |         \\ |  \\ |" << std::endl;
	std::cout << "                      __/ |__/ |       __| |__| |" << std::endl;
	std::cout << "                      |___||___|       |___||___|" << std::endl;
	std::cout << std::endl;
	std::cout << "Bull-Cow Game, a fun word game!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << "-letter isogram I am thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}


void PrintGameSummary()
{
	if (BCGame.AllAreBulls())
	{
		std::cout << "Congrats! You have the word!" << std::endl;
	}
	else if ((!BCGame.AllAreBulls()) && (BCGame.GetCurrentTry() >= BCGame.GetMaxTries()))
	{
		std::cout << "You failed. MISERABLY." << std::endl;
	}
	return;
}
/*
void ChooseDifficulty()
{
	FText Difficulty = "";
	std::cout << "Choose the difficulty between 3 and 7: ";
	std::getline(std::cin, Difficulty);
	std::cout << std::endl;
}*/
