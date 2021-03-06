// Project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Fengyi Guo


#include "pch.h"
#include "Board.h"
#include "AI.h"
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

void print(Board board)
{
	int board_size = 8;
	// print header
	cout << "   ";
	for (int col = 0; col < board_size; ++col)
		printf(" %d ", col + 1);
	cout << endl;

	// print content
	for (int row = 0; row < board_size; ++row)
	{
		printf(" %c ", 'A' + row);
		for (int col = 0; col < board_size; ++col)
		{
			if (board.is_bit_set(board.getGameBoard(), row * board_size + col))
			{
				if (board.is_bit_set(board.getPlayerBoard(), row * board_size + col))
					cout << " X ";
				else
					cout << " O ";
			}
			else
				cout << " - ";
		}
		cout << endl;
	}
	cout << endl;
}


int convert_to_pos(string input)
{
	if (input.size() != 2) return -1;

	char p1 = input[0];
	char p2 = input[1];

	if (!(p1 >= 'a' && p1 <= 'h')
		&& !(p1 >= 'A' && p1 <= 'H'))
		return -1;
	if (p2 < '1' || p2 > '8')
		return -1;

	int row = (p1 | ' ') - 'a';
	int col = p2 - '0' - 1;

	return row * 8 + col;
}

string convert_to_string(int aiMove) {
	int row = aiMove / 8;
	int col = aiMove % 8 + 1;
	string temp = "";
	temp += 'a' + row;
	temp += col + '0';

	return temp;
}

int playerTurn(Board board) {
	cout << "Player turn: " << endl;
	string playerInput;

	cout << "enter Player move: ";
	cin >> playerInput;

	int position;
	while ((position = convert_to_pos(playerInput)) < 0)
	{
		cout << "please input again: ";
		cin >> playerInput;
	}

	return position;
}

void printDisplay(vector<string> display) {
	cout << "Player Vs. Opp" ;
	int row = 1;
	for (unsigned i = 0; i < display.size(); i++) {
		if (i%2 == 0) {
			cout << endl << row << ". ";
			row++;
		}
		cout << display[i] << " ";	
	}
	cout << endl;
	cout << endl;
}

int main()
{
	int time = 0;
	cout << "The maximum amount of time allowed for generating the next move: ";
	cin >> time;
	cout << endl;

	vector<string> display;

	int first = 0;
	cout << "Who wanna go first? (0 for Player, 1 for Opponent): ";
	cin >> first;
	cout << endl;

	Board board;
	AI ai;
	bool playerWin = false;
	bool oppWin = false;
	//board.playerInsert(6);
	//board.playerInsert(7);
	//board.playerInsert(8);
	//board.playerInsert(9);
	//board.playerInsert(10);
	//board.playerInsert(11);
	//if (ai.checkPlayerWin(board)) {
	//	cout << "1!!!!!" << endl;
	//}
	//else {
	//	cout << "wrong" << endl;
	//}
	
	int emptySpace = 64;
	if (first == 0) {
		do {
			print(board);
			string playerInput;
			cout << "Player turn, enter Player move: ";
			cin >> playerInput;

			int position = convert_to_pos(playerInput);
			while (position < 0)
			{
				cout << "please input again: ";
				cin >> playerInput;
				position = convert_to_pos(playerInput);
			}
			bool canmove = board.playerInsert(position);
			while (canmove == false) {
				cout << "move is taken, reenter Player move: ";
				cin >> playerInput;
				position = convert_to_pos(playerInput);
				while (position < 0)
				{
					cout << "please input again: ";
					cin >> playerInput;
					position = convert_to_pos(playerInput);
				}
				canmove = board.playerInsert(position);
			}
			emptySpace--;
			display.push_back(playerInput);
			printDisplay(display);
			print(board);
			if (ai.checkPlayerWin(board)) {
				cout << "player win!!!!!" << endl;
				break;
			}

			int aiMove = ai.minimaxTest(board, first, time);
			cout << "Opp turn: " << endl;
			board.oppInsert(aiMove);
			display.push_back(convert_to_string(aiMove));
			printDisplay(display);
			emptySpace--;
			if (ai.checkOppWin(board)) {
				cout << "Opp win!!!!!" << endl;
				break;
			}
		} while (emptySpace != 0);
	}
	else if (first == 1) {
		board.oppInsert(27);
		display.push_back(convert_to_string(27));
		printDisplay(display);
		emptySpace--;
		do {
			print(board);
			string playerInput;
			cout << "Player turn, enter Player move: ";
			cin >> playerInput;

			int position = convert_to_pos(playerInput);
			while (position < 0)
			{
				cout << "please input again: ";
				cin >> playerInput;
				position = convert_to_pos(playerInput);
			}
			bool canmove = board.playerInsert(position);
			while (canmove == false) {
				cout << "move is taken, reenter Player move: ";
				cin >> playerInput;
				position = convert_to_pos(playerInput);
				while (position < 0)
				{
					cout << "please input again: ";
					cin >> playerInput;
					position = convert_to_pos(playerInput);
				}
				canmove = board.playerInsert(position);
			}
			emptySpace--;
			display.push_back(playerInput);
			printDisplay(display);
			print(board);
			if (ai.checkPlayerWin(board)) {
				cout << "player win!!!!!" << endl;
				break;
			}

			int aiMove = ai.minimaxTest(board, first, time);
			cout << "Opp turn: " << endl;
			board.oppInsert(aiMove);
			display.push_back(convert_to_string(aiMove));
			printDisplay(display);
			emptySpace--;
			if (ai.checkOppWin(board)) {
				cout << "Opp win!!!!!" << endl;
				break;
			}
		} while (emptySpace != 0);
	}
	else {
		cout << "Wrong input. Restart!!" << endl;
	}

	print(board);
	cout << "Draw Game." << endl;
	
	

}
