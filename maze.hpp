// class definitions for maze navigation assingment
// Mikhail Nesterenko
// 10/28/2022

#include <cstdlib>
#include <ctime>


#ifndef MAZE_HPP_
#define MAZE_HPP_

// room coordinates
class Room {
public:

    Room();
    Room(int num, char letter) { x_ = num; y_ = letter; } // I added this constructor
    void pick();
    const Room pickAdjacent();
    const Room nextMove() const;
    void print() const;  
    void makeStartRoom() { x_ = 1; y_ = 'a'; }
    void makeCheeseRoom() { x_ = mazeSize_, y_ = 'a' + mazeSize_ - 1; };
    friend bool matchRoom(const Room&, const Room&);

private:
   
    bool goodDirection(const char) const;
    const Room createAdjacent(const char) const;

    static const int mazeSize_ = 4; // maze is mazeSize * mazeSize
    int x_;  // 1 through mazeSize
    char y_; // 'a' through mazeSize
};

// internal wall or next move
class RoomPair {
public:
    RoomPair() {} // void constructor implicitly invokes void constructors on member variables
    RoomPair(const Room& one, const Room& two) :one_(one), two_(two) {} // makes a roomPair out of two rooms
    void pick(); //selects a random wall, uses Room::pickAdjacent()
    void print() const; // prints the locations of the adjacent rooms
    friend bool matchPair(const RoomPair&, const RoomPair&);

private:
    Room one_;
    Room two_;
};

class Maze {
public:
    Maze();
    void print() const;
    void build();
    void start() { currentRoom_.makeStartRoom(); }
    bool move(const Room&);
    const Room getCurrentRoom() { return currentRoom_; }

private:
    
    int checkMaze(const RoomPair&) const;

    Room currentRoom_; // current mouse Location

    static const int numWalls_ = 8;  // number of internal walls
    RoomPair maze_[numWalls_]; // number of internal walls
};





#endif // MAZE_HPP_
