#include <stack>
#include <vector>
#include <iostream>

// please implement all your classes in this file

class Cell {
    public:
        bool isVisited () {return this->visited;};      
        void setVisited (bool v) {this->visited = v;};

        bool isRightOpen () {return this->rightOpen;};    
        void openRight() {this->rightOpen = true;};
        bool isBottomOpen () {return this->bottomOpen;};   
        void openBottom() {this->bottomOpen = true;};

        bool isOnPath() {return this->onPath;};
        void setOnPath(bool p) {this->onPath = p;};
    private:
        bool visited = false;
        bool rightOpen = false;
        bool bottomOpen = false;
        bool onPath = false;
};

class Coordinate {
    public:
        Coordinate (int row, int column) {
            this->row = row;
            this->column = column;
        };
        int getRow() {
            return this->row;
        };
        int getColumn() {
            return this->column;
        };

    private:
        int row;
        int column;
};

// your class Maze must implement the public: interface shown here (or it won't compile)
// the private: part of the class is completely up to you
class Maze{
    public:
        Maze(int rows, int columns);

        void generate();
        // generates the maze for the given size (rows and columns) using the recursive backtracker algorithm
        // explained in the video linked to on Canvas

        bool findPath(Coordinate from, Coordinate to);
        // finds a path from the coordinate (0,0) (top left corner) to the coordinate (rows-1,columns-1) (bottom right corner)
        // using the algorithm explained on Canvas

        // the following five functions return basic information about the maze, allowing it to be printed
        // the latter three bool functions only need to work after both the maze has been created and the path has been found
        int getColumns();
        int getRows();
        bool hasConnectionToTheRightNeighbour(int row, int column);
        // returns whether the wall in between (row,column) and (row,column+1) has been removed
        bool hasConnectionToTheBottomNeighbour(int row, int column);
        // returns whether the wall in between (row,column) and (row+1,column) has been removed
        bool isPartOfPath(int row, int column);
        // returns whether (row,column) is on the path from the top-left to the bottom-right corner

    private:
        int rows;
        int columns;
        std::vector<std::vector<Cell>> M;

        // helper for generating maze
        void generate (Coordinate c);
        bool inBounds (Coordinate c);
        std::vector<Coordinate> allNeighbours (Coordinate c);
        std::vector<Coordinate> unvisitedNeighbours (Coordinate c);
        std::vector<Coordinate> reachableNeighbours (Coordinate c);
};


Maze::Maze (int rows, int columns) {
    this->rows = rows;
    this->columns = columns;

    // make maze of appropriate size
    this->M.resize(rows, std::vector<Cell> (columns));
}
int Maze::getColumns() {
    return this->columns;
}
int Maze::getRows() {
    return this->rows;
}

void Maze::generate () {
    generate(Coordinate(0, 0));
}
void Maze::generate (Coordinate c) {
    this->M.at(c.getRow()).at(c.getColumn()).setVisited(true);
    // find all neighbours that are inbound && not visited
    std::vector<Coordinate> validNeighbour = this->unvisitedNeighbours(c);

    while (validNeighbour.size() != 0) {
        Coordinate next = validNeighbour.at(std::rand() % validNeighbour.size());
        /*
        positions:
            0
        3   c   1
            2
        */
        // pos 0
        if (next.getRow() < c.getRow()) {
            this->M.at(next.getRow()).at(next.getColumn()).openBottom();
        }
        // pos 1
        else if (next.getColumn() > c.getColumn()) {
            this->M.at(c.getRow()).at(c.getColumn()).openRight();        
        }
        // pos 2
        else if (next.getRow() > c.getRow()) {
            this->M.at(c.getRow()).at(c.getColumn()).openBottom();        
        }
        // pos 3
        else if (next.getColumn() < c.getColumn()) {
            this->M.at(next.getRow()).at(next.getColumn()).openRight();        
        }
        else {
            std::cerr << "u fucked up brah" << std::endl;
            return;
        }

        generate(next);
        validNeighbour = this->unvisitedNeighbours(c);
    }
    // if list is epmty;
    return;
    

}

std::vector<Coordinate> Maze::allNeighbours (Coordinate c) {
    std::vector<Coordinate> Neighbours;
    std::vector<int> directionRow = {-1, 0, 1, 0};
    std::vector<int> directionColumn = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        Coordinate neighbour = Coordinate(c.getRow() + directionRow.at(i), c.getColumn() + directionColumn.at(i));
        if (this->inBounds(neighbour)) {
            Neighbours.push_back(neighbour);
        }
    }
    return Neighbours;
}

std::vector<Coordinate> Maze::unvisitedNeighbours (Coordinate c) {
    // find all neighbours that are inbound && not visited
    std::vector<Coordinate> n = Maze::allNeighbours(c);
    std::vector<Coordinate> validNeighbour;
    for (int i = 0; i < n.size(); i++) {
        int row = n.at(i).getRow();
        int column = n.at(i).getColumn();
        if (!this->M.at(row).at(column).isVisited()) {
            validNeighbour.push_back(n.at(i));
        }
    }
    return validNeighbour;
}

std::vector<Coordinate> Maze::reachableNeighbours (Coordinate c) {
    std::vector<Coordinate> n = Maze::allNeighbours(c);
    std::vector<Coordinate> reachableNeighbour;
    for (int i = 0; i < n.size(); i++) {
        int rowN = n.at(i).getRow();
        int columnN = n.at(i).getColumn();
        int rowC = c.getRow();
        int columnC = c.getColumn();
        // pos 0
        if (rowN < rowC) {
            if (M.at(rowN).at(columnN).isBottomOpen()) {
                reachableNeighbour.push_back(n.at(i));
            }
        }
        // pos 1
        if (columnC < columnN) {
            if (M.at(rowC).at(columnC).isRightOpen()) {
                reachableNeighbour.push_back(n.at(i));
            }
        }
        // pos 2
        if (rowC < rowN) {
            if (M.at(rowC).at(columnC).isBottomOpen()) {
                reachableNeighbour.push_back(n.at(i));
            }
        }
        // pos 3
        if (columnN < columnC) {
            if (M.at(rowN).at(columnN).isRightOpen()) {
                reachableNeighbour.push_back(n.at(i));
            }
        }
        
    }
    return reachableNeighbour;
}



bool Maze::inBounds (Coordinate c) {
    return (
        0 <= c.getRow() && c.getRow() < this->getRows() &&
        0 <= c.getColumn() && c.getColumn() < this->getColumns()
    );
}



bool Maze::hasConnectionToTheRightNeighbour(int row, int column) {
    return (this->M.at(row).at(column).isRightOpen());
}
bool Maze::hasConnectionToTheBottomNeighbour(int row, int column) {
    return (this->M.at(row).at(column).isBottomOpen());
}

bool Maze::findPath(Coordinate from, Coordinate to) {
    M.at(from.getRow()).at(from.getColumn()).setOnPath(true);
    if (from.getRow() == to.getRow() && from.getColumn() == to.getColumn()) {
        return true;
    }
    std::vector<Coordinate> neighbours = reachableNeighbours(from);
    for (int i = 0; i < neighbours.size(); i++) {
        if (!M.at(neighbours.at(i).getRow()).at(neighbours.at(i).getColumn()).isOnPath()) {
            if (findPath(neighbours.at(i), to)) {
                return true;
            }
        }
    }
    M.at(from.getRow()).at(from.getColumn()).setOnPath(false);
    return false;
}

bool Maze::isPartOfPath(int row, int column) {return this->M.at(row).at(column).isOnPath();}