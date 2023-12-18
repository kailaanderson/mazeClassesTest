// Demonstrates Maze lab using classes
// Definitions
// Kaila Anderson
// October 31, 2022

#include <iostream>
#include "maze.hpp"

using std::cin; using std::cout; using std::endl;

// Room class definitions

Room::Room() : x_(-1), y_('*') {} //void constructor definition

void Room::pick() {

	int xcoord = rand() % mazeSize_ + 1;
	char ycoord = rand() % mazeSize_ + 1;

	switch (ycoord) {
	case 1:
		ycoord = 'a';
		break;
	case 2:
		ycoord = 'b';
		break;
	case 3:
		ycoord = 'c';
		break;
	case 4:
		ycoord = 'd';
		break;
	}
	x_ = xcoord;
	y_ = ycoord; 

}

bool Room::goodDirection(char direction) const {

	bool good = false;
	switch (direction) {
	case 'u':
		if (x_ > 1) {
			good = true;
		}
		break;
	case 'd':
		if (x_ < mazeSize_) {
			good = true;
		}
		break;
	case 'l':
		if (y_ > 'a') {
			good = true;
		}
		break;
	case 'r':
		if (y_ < 'd') {
			good = true;
		}
		break;
	}
	return good;
}

const Room Room::createAdjacent(const char direction) const {
	
	int number = x_; 
	char letter = y_; 

	switch (direction) {
	case 'u':
		number -= 1;
		break;
	case 'd':
		number += 1;
		break;
	case 'l':
		letter -= 1;
		break;
	case 'r':
		letter += 1;
		break;
	}
	Room adj(number, letter);

	return adj;

}

const Room Room::pickAdjacent() {
	bool chosenAdj = false;
	Room adjacent;

	while (chosenAdj == false) {
		
		char direction = rand() % 4 + 1; 
		switch (direction) {
		case 1:
			direction = 'u';
			break;
		case 2:
			direction = 'd';
			break;
		case 3:
			direction = 'l';
			break;
		case 4:
			direction = 'r';
			break;
		}

		
		if (goodDirection(direction)) {
			adjacent = createAdjacent(direction);
			chosenAdj = true;
		}
		else continue; 
	}
	return adjacent; 
}

const Room Room::nextMove() const {
	
	int number = x_;
	char letter = y_;
	Room nextMove(number, letter); 

	bool validMove = false; 

	while (validMove == false) {
		cout << "Which direction would you like to go?: " << endl
			<< "u (up), d (down), r (right), l (left), q (quit)." << endl;
		char direction;
		cin >> direction;
		if (direction == 'q') {
			return nextMove; 
		}

		if (goodDirection(direction)) {
			nextMove = createAdjacent(direction);
			validMove = true;
		}
		else {
			cout << "The direction you choose took you out of the maze. Please select a new direction" << endl;
		}
	}
	return nextMove; 
}

void Room::print() const {
	cout << y_ << x_; 
}

bool matchRoom(const Room& first, const Room& second) {
	bool match = false; 

	if (first.x_ == second.x_ &&
		first.y_ == second.y_) {
		match = true; 
	}
	return match; 
}

// class RoomPair definitions

void RoomPair::pick() {
	int randomX = rand() % 4 + 1;
	char randomY = rand() % 4 + 1; 
	
	switch (randomY) {
	case 1:
		randomY = 'a';
		break; 
	case 2: 
		randomY = 'b';
		break; 
	case 3: 
		randomY = 'c';
		break; 
	case 4:
		randomY = 'd';
		break;
	}
	
	one_ = { randomX, randomY };  
	two_ = one_.pickAdjacent();   
	
}

void RoomPair::print() const {
	Room one = one_; 
	one_.print();
	cout << "|"; 
	Room two = two_; 
	two_.print(); 
	cout << endl;
}

bool matchPair(const RoomPair& one, const RoomPair& two) {
	RoomPair first = one;
	RoomPair second = two;
	
	if (matchRoom(first.one_, second.one_) || matchRoom(first.one_, second.two_)) {
		if (matchRoom(first.two_, second.one_) || matchRoom(first.two_, second.two_)) {
			return true;
		}
	}
	else return false;
}

// class Maze definitions

Maze::Maze() {
	for (int i = 0; i < numWalls_; ++i) {
		maze_[i] = { { -1, '*' }, { -1, '*' } };
	}

}

void Maze::print() const {
	
	for (int i = 0; i < numWalls_; ++i) {
		maze_[i].print(); 
	}
	
}

void Maze::build() {
	int wallsBuilt = 0; 
	RoomPair Pair;

	while (wallsBuilt < numWalls_) {
		for (int i = 0; i < numWalls_; ++i) {
			Pair.pick(); 

			if (checkMaze(Pair) == -1) {
				maze_[i] = Pair;
				++wallsBuilt;
			}
			else
				--i; 
		}
	}
}

bool Maze::move(const Room& newMove) {
	RoomPair Pair = { currentRoom_, newMove }; 

	if (checkMaze(Pair) == -1) {
		currentRoom_ = newMove; 
		return true;
	}
	else {
		return false; 
	}
}

int Maze::checkMaze(const RoomPair& check) const {
	
	for (int i = 0; i < numWalls_; ++i) {
		if (matchPair(maze_[i], check)) {
			return i;
		}
		else {
			if (i == numWalls_ - 1) { return -1; }
			continue; 
		}
	}

}

