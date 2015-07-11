#include <generator.h>

data generateStep(data d){
    unsigned int randNum;
    cellString cellStringUnvisited;
    cellString cellStringNeighbours = getNeighbours(d.width, d.height, d.maze, d.startPoint, 2);
    if(cellStringNeighbours.size != 0){ //если у клетки есть непосещенные соседи
        randNum  = randomRange(0, cellStringNeighbours.size-1);
        d.cellNext = cellStringNeighbours.cells[randNum]; //выбираем случайного соседа
        push(d.startPoint, &d.s, &d.stackSize); //заносим текущую точку в стек
        d.maze = removeWall(d.startPoint, d.cellNext, d.maze); //убираем стену между текущей и сосендней точками
        d.unvisitedNum--;
        d.startPoint = d.cellNext; //делаем соседнюю точку текущей и отмечаем ее посещенной
        d.maze        = setMode(d.startPoint, d.maze, GENVISITED);
        free(cellStringNeighbours.cells);
    }
    else if(d.stackSize){ //если нет соседей, возвращаемся на предыдущую точку
        d.startPoint = pop(&d.s, &d.stackSize);
    }
    else{ //если нет соседей и точек в стеке, но не все точки посещены, выбираем случайную из непосещенных
        cellStringUnvisited = getUnvisitedCells(d.width, d.height, d.maze);
        randNum             = randomRange(0, cellStringUnvisited.size-1);
        d.startPoint      = cellStringUnvisited.cells[randNum];
        free(cellStringUnvisited.cells);
    }
    return d;
}

mazeMatrix init(unsigned int width, unsigned int height){ //used
    unsigned int i, j;
    mazeMatrix maze;

    maze  = malloc(height * sizeof(int*));

    for(i = 0; i < height; i++){ //инициализируем матрицу и заполняем стенами
        maze[i] = malloc(width  * sizeof(int));
        for(j = 0; j < width; j++){
            maze[i][j] = WALL;
        }
    }

    for(i = 1; i < height-1; i+=2){ //инициализируем клетки.
        for(j = 1; j < width-1; j+=2){
            maze[i][j] = GENCELL;
        }
    }
    return maze;
}

mazeMatrix finalize(unsigned int width, unsigned int height, mazeMatrix maze){
    unsigned int i, j;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if(maze[i][j] != WALL)
                maze[i][j] = CELL;
        }
    }

    return maze;
}

cellString getUnvisitedCells(unsigned int width, unsigned int height, mazeMatrix maze){
    cellString cells;
    unsigned long long i, j, size = 0;

    cells.cells = malloc(width*height*sizeof(cell));

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if((maze[i][j] != WALL) && (maze[i][j] != GENVISITED)){
                cells.cells[size].x = j;
                cells.cells[size].y = i;
                size++;
            }
        }
    }
    cells.size = size;
    return cells;
}

mazeMatrix removeWall(cell first, cell second, mazeMatrix maze){ //used
    short int xDiff = second.x - first.x;
    short int yDiff = second.y - first.y;
    short int addX, addY;
    cell target;

    addX = (xDiff != 0) ? (xDiff / abs(xDiff)) : 0;
    addY = (yDiff != 0) ? (yDiff / abs(yDiff)) : 0;

    target.x = first.x + addX; //координаты стенки
    target.y = first.y + addY;

    maze[target.y][target.x] = GENVISITED;
    return maze;
}

unsigned int unvisitedCount(unsigned int width, unsigned int height, mazeMatrix maze){ //used
    unsigned int count = 0, i, j;
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            if(maze[i][j] != WALL && maze[i][j] != GENVISITED) count++;
    return count;
}
