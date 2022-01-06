#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include <cstdlib>
#include <algorithm>    
#include <vector>
using namespace std;

const int ASCII_SYMBOL_OF_0 = 48;
const int ASCII_SYMBOL_OF_a = 97;
const int ASCII_SYMBOL_OF_z = 122;
int wordLength = 0;
int attempts = 5;
vector<string> dictionary;

void loadWords();
void changeAttempts(int attempts);
void clearConsole();
void changeWordLength(const int& length);
bool isValidNumber(const string& str);
int convertToInteger(const string& str);
bool isAlreadyEntered(char character, vector<char> characters);
void printMenu();
bool isWordGuessed(vector<bool> guessedCharacters);
void waitFiveSeconds();
void change();
void printResult(int guessedWords);
void wordIsGuessed(string word);
void wordIsNotGuessed(string word);
string randomWord();

int main()
{
	loadWords();
	string command;
	printMenu();
	int result = 0;
	while (true)
	{
		cin >> command;
		if (command == "start")
		{
			string wordToGuess;
			wordToGuess = randomWord();

			vector<char> charactersEntered;
			vector<bool> guessedCharacters;
			char currentCharacter;
			int currentAttempts = 0;
			for (int i = 0; i < wordToGuess.size(); i++)
			{
				guessedCharacters.push_back(false);
			}
			bool isGuessed = false;
			while (attempts - currentAttempts > 0)
			{
				cout << "<<Attempts left: " << attempts - currentAttempts << " .Guess the word:";
				for (int i = 0; i < wordToGuess.size(); i++)
				{
					if (guessedCharacters[i] == true)
					{
						cout << wordToGuess[i];
					}
					else
					{
						cout << "_ ";
					}
				}
				cout << endl << ">>";
				cin >> currentCharacter;
				if (currentCharacter >= ASCII_SYMBOL_OF_a && currentCharacter <= ASCII_SYMBOL_OF_z)
				{
					if (isAlreadyEntered(currentCharacter, charactersEntered))
					{
						cout << "You already entered this character.Please enter another one" << endl;
					}
					else
					{
						bool wordContainsCurrentCharacter = false;
						for (int i = 0; i < wordToGuess.size(); i++)
						{
							if (wordToGuess[i] == currentCharacter)
							{
								guessedCharacters[i] = true;
								wordContainsCurrentCharacter = true;
							}
						}
						if (wordContainsCurrentCharacter == false)
						{
							currentAttempts++;
						}
						else if (isWordGuessed(guessedCharacters))
						{
							isGuessed = true;
							break;
						}
						charactersEntered.push_back(currentCharacter);
					}
				}
				else
				{
					cout << "You entered invalid character!Please enter a valid one" << endl;
				}
			}
			wordLength = 0;
			if (isGuessed)
			{
				wordIsGuessed(wordToGuess);
				result++;
			}
			else
			{
				wordIsNotGuessed(wordToGuess);
			}
		}
		else if (command == "change")
		{
			change();
		}
		else if (isValidNumber(command))
		{
			int newWordLength = convertToInteger(command);
			if (newWordLength < 4 || newWordLength>11)
			{
				cout << "Word length was not valid.Please enter new command:"<<endl;
			}
			else
			{
				changeWordLength(newWordLength);
			}
		}
		else if (command == "exit")
		{
			break;
		}
		else
		{
			cout << "Your command was not valid.Please enter new one:"<<endl;
		}
	}

	printResult(result);
}

void loadWords()
{
	ifstream file;
	file.open("dictionary.txt", ios::in);
	string currentWord;
	if (file.is_open())
	{
		while (getline(file, currentWord))
		{
			dictionary.push_back(currentWord);
		}
	}
	else
	{
		cout << "A problem occured while opening the file." << endl;
	}
	file.close();
}

void changeAttempts(int newAttempts)
{
	attempts = newAttempts;
	cout << "You successfully changed your attempts to " << attempts << endl;
}

void clearConsole()
{
	system("CLS");
}

void changeWordLength(const int& length)
{
	wordLength = length;
	cout << "You successfully changed the word length to " << length << endl;
}

bool isValidNumber(const string& str)
{
	if (str.size() == 0)
	{
		return false;
	}
	if (str[0] == '0')
	{
		return false;
	}
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] < '0' || str[i]>'9')
		{
			return false;
		}
	}
	return true;
}

int convertToInteger(const string& str)
{
	int result = 0;
	int place = 1;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		result += place * (str[i] - ASCII_SYMBOL_OF_0);
		place *= 10;
	}
	return result;
}

bool isAlreadyEntered(char character, vector<char> characters)
{
	for (int i = 0; i < characters.size(); i++)
	{
		if (characters[i]==character)
		{
			return true;
		}
	}
	return false;
}

void printMenu()
{
	cout << "=====================================" << endl;
	cout << "Select option :" << endl;
	cout << "1) 'start' to start new game" << endl;
	cout << "2) 4-10 to choose word length" << endl;
	cout << "3) 'change' to change the number of attempts" << endl;
	cout << "4) 'exit' to exit the game" << endl;
	cout << "=====================================" << endl;
}

bool isWordGuessed(vector<bool> guessedCharacters)
{
	for (int i = 0; i < guessedCharacters.size(); i++)
	{
		if (guessedCharacters[i]==false)
		{
			return false;
		}
	}
	return true;
}

void waitFiveSeconds()
{
	Sleep(5000);
}

void change()
{
	string attempts;
	
	while (true)
	{
		cout << "New attempts(between 2 and 9):";
	    cin >> attempts;
		if (isValidNumber(attempts))
		{
			int number = convertToInteger(attempts);
			if (number>=2&&number<=9)
			{
				changeAttempts(number);
				break;
			}
		}
	}
}

void printResult(int guessedWords)
{
	cout << "You guessed " << guessedWords << " ";
	cout<<(guessedWords == 1 ? "word" : "words") << endl;
}

void wordIsGuessed(string word)
{
	cout << "<<Congratulations! You guessed the word \'" << word <<"\'" << endl;
	cout << "Returning to menu" << endl;
	waitFiveSeconds();
	clearConsole();
	printMenu();
}

void wordIsNotGuessed(string word)
{
	cout << "<<Sorry! You could not guessed the word \'" << word <<"\'" << endl;
	cout << "Returning to menu" << endl;
	waitFiveSeconds();
	clearConsole();
	printMenu();
}

string randomWord()
{
	if (wordLength != 0)
	{
		vector<string> words;
		for (int i = 0; i < dictionary.size(); i++)
		{
			if (dictionary[i].size() == wordLength)
			{
				words.push_back(dictionary[i]);
			}
		}
		return words[rand() % words.size()];
	}
	else
	{
		return dictionary[rand() % dictionary.size()];
	}
}
