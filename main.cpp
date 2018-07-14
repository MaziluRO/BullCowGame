#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


//to make syntax unreal friendly
using FText = std::string;
using int32 = int;


void PrintIntro();
int32 ChooseDifficulty();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame;//declared a name for the class
int32 Level;

int main()
{
	
	
	bool bPlayAgain = false;
	bool ValidLevel = false;
	do
	{
		
		PrintIntro();
		Level = ChooseDifficulty();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
		
		
	} 
	while (bPlayAgain);
	 
	return 0;
}



void PrintIntro() //Prints intro and asks to select level of difficulty
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun game!\n";
	return;
	
}


//plays a game until completion
void PlayGame()
{
	BCGame.Reset();
	BCGame.GenerateHiddenWord(Level);
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "\n\nCan you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n"; 
	std::cout << "You have a maximum of " << MaxTries <<" tries to win. Good luck!" << std::endl;
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText WordGuess = "";
		WordGuess = GetValidGuess();
		

		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(WordGuess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;

		
	}
	
	
return;
	
	
}
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won!\n";

	}
	else
	{
		std::cout << "Sorry! You lost! The correct answer was: " << BCGame.CorrectAnswer();
		std::cout <<"\nBetter luck next time.\n";
	}

}


FText GetValidGuess()
{
	
	EGuessStatus Status = EGuessStatus::invalid_status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry:" << CurrentTry << " of "<< BCGame.GetMaxTries() << std::endl;
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);
		
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with all letters lowercase. \n\n ";
			break;
		case EGuessStatus::not_isogram:
			std::cout << "Please enter a word without repeating letters. \n\n ";
		default:
			break;
		}
		
	} while (Status != EGuessStatus::ok);
	return Guess;
}

//asks to play again
bool AskToPlayAgain()
{
	std::cout << "\n Do you want to play again?(y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;
	

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

int32 ChooseDifficulty()
{
	int32 DifficultyLevel;
	std::cout << " Choose your difficulty! \n";
	std::cout << "   EASY    \n";
	std::cout << "  MEDIUM   \n";
	std::cout << "   HARD     \n";
	do
	{
		std::cout << " Enter a valid difficulty: ";
		std::cin >> DifficultyLevel;

	} while (DifficultyLevel != 1 && DifficultyLevel != 2 && DifficultyLevel != 3);

	return DifficultyLevel;
}
