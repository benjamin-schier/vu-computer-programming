#include <iostream>

#include "maze.cpp"

void printMaze(Maze& m){
    int numColumns = m.getColumns();
    int numRows = m.getRows();
    std::cout << '+';
    for (int c=0; c<numColumns; c++){
        char connector = '+';
        std::cout << "---" << connector;
    }
    std::cout << std::endl;
    for ( int r=0; r<numRows; r++){
        std::cout << '|';
        for (int c=0; c<numColumns; c++){
            char connector = m.hasConnectionToTheRightNeighbour(r,c) ? ' ' : '|';
            std::string cell = "   ";
            if ( m.isPartOfPath(r,c) ) cell = " . ";
            std::cout << cell << connector;
        }
        std::cout << std::endl;
        std::cout << '+';
        for (int c=0; c<numColumns; c++){
            char connector = '+';
            std::string wall = m.hasConnectionToTheBottomNeighbour(r,c) ? "   " : "---";
            std::cout << wall << connector;
        }
        std::cout << std::endl;
    }
}

class Parameters{
    public:
        Parameters(int argc, char *argv[]){
            try{
                switch (argc){
                    case 4:
                        randomSeed = std::stoi(argv[3]);
                    case 3:
                        rows = std::stoi(argv[1]);
                        columns = std::stoi(argv[2]);
                        if ( rows < 1 || columns < 1 ) throw std::runtime_error(errorMessage);
                        break;
                    case 1:
                        break;
                    default:
                        throw std::runtime_error(errorMessage);
                    
                }
            }catch ( std::invalid_argument &e ){
                throw std::runtime_error(errorMessage);
            }
        }
        int rows = 12;
        int columns = 18;
        int randomSeed = time(NULL);
    private:
        std::string errorMessage = "Invalid parameter list";
};

int main(int argc, char *argv[]){
    try{
        Parameters param(argc, argv);
        std::srand(param.randomSeed);

        Maze maze(param.rows, param.columns);
        maze.generate();

        bool hasValidPath = maze.findPath(Coordinate(0,0), Coordinate(param.rows-1,param.columns-1));
        if ( !hasValidPath ){
            throw std::runtime_error("No valid path found");
        }
        printMaze(maze);
    }catch (std::runtime_error &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}