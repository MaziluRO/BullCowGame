#pragma once
#include "FBullCowGame.h"
#include <map>
#include <iostream>
#include <string>
#include <cstdlib>
#define TMap std::map

using int32 = int;

//this is the constructor
FBullCowGame::FBullCowGame()
{
	Reset();
}


int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {5,7},{6,10} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	
}


int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}


int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (char Letter : Guess)
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

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}



void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (char letter : Guess)
	{
		if (!islower(letter))
		{
			return false;
		}
		
	}
	return true;
	

}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::not_isogram;
	}
		
	else if (!IsLowercase(Guess))
	{
		
		return EGuessStatus::Not_Lowercase;
	
		
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::ok;
	}
	
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	
	MyCurrentTry++;
	
	FBullCowCount BullCowCount;
	
	
	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++) 
	{
		for (int32 j = 0; j < WordLength; j++) 
		{
			if (Guess[i] == MyHiddenWord[j]) 
			{
				if (i == j) 
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
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}



	return BullCowCount;
}



void FBullCowGame::GenerateHiddenWord(int32 level) 
{
	TMap<int32, FString> WordList{ {1,"dog"},{2,"cat"},{3,"pig"},{4,"plane"},{5,"music"},{6,"judge"},{7,"planet"},{8,"jumper"},{9,"zombie"} };
	switch (level)
	{
	case 1:
		MyHiddenWord = WordList[(rand() % 3) + 1];
		break;
	case 2:
		MyHiddenWord = WordList[(rand() % 3) + 4];
		break;
	case 3:
		MyHiddenWord = WordList[(rand() % 3) + 7];
		break;
	default:
		break;

	}
	return;
}

FString FBullCowGame::CorrectAnswer() const
{
	return MyHiddenWord;
}


