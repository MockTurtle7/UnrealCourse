#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Empty,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool AllAreBulls() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;

	void Reset();
	FString GenerateWord();
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	bool IsIsogram(FString Guess) const;
	bool IsLowercase(FString Guess) const;
	
	int32 CurrentTry = 1;
	int32 MaxTries = 5;
	FString HiddenWord = "";
	bool bAllAreBulls = false;

};