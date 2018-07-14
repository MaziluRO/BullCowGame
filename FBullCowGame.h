/* The game logic. It's a simple game logic*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus {
	invalid_status, ok, not_isogram, Not_Lowercase, no_space, Wrong_Length,
};



class FBullCowGame {
public: 
	FBullCowGame(); //constructor
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength()const;
	bool IsGameWon()const;	 
	EGuessStatus CheckGuessValidity(FString)const;
	FBullCowCount SubmitValidGuess(FString);
	void GenerateHiddenWord(int32);
	FString CorrectAnswer()const;

	

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
