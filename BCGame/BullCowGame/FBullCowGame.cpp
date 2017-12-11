#pragma once

#include <iostream>
#include <map>
#include "FBullCowGame.h"

#define TMap std::map

using FString = std::string;
using int32 = int;

const FString HIDDEN_WORD = "blacksmith";
const int32 WORD_LENGTH = HIDDEN_WORD.length();

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return WORD_LENGTH; }
bool FBullCowGame::AllAreBulls() const { return bAllAreBulls; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 7}, {5, 9}, {6, 15}, {7, 19}, {8, 25}, {9, 30}, {10, 30} };
	return WordLengthToMaxTries[HIDDEN_WORD.length()];
	

}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letter words as isogram
	if (Guess.length() <= 1) { return true; }

	// set up the map with the characters in Guess
	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess) // for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

// Produce the error codes regarding the word guess
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	const int32 GuessLength = Guess.length();

	// if the guess is not an isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess is not in lowercase
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is not matching the hidden word length
	else if (GuessLength != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	// all in check
	else
	{
		return EGuessStatus::OK;
	}
	
}


void FBullCowGame::Reset()
{
	CurrentTry = 1;
	HiddenWord = HIDDEN_WORD;
	bAllAreBulls = false;

	return;
}


FString FBullCowGame::GenerateWord()
{
	return HiddenWord;
}

// receives a valid guess, increment turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the turn number
	CurrentTry++;
	
	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	for (int32 HWChar = 0; HWChar < WORD_LENGTH; HWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WORD_LENGTH; GChar++)
		{
			if (HiddenWord[HWChar] == Guess[GChar])
			{
				if (HWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	/*When there are enough bulls, meaning that the guess is correct,
	call a win function*/
	if (BullCowCount.Bulls == WORD_LENGTH)
	{
		bAllAreBulls = true;
	}
	else
	{
		bAllAreBulls = false;
	}
	

	return BullCowCount;
}


