#include <seeker.h>

data seekStep(data d){
    unsigned int randNum;
    cellString Neighbours = getNeighbours(d.width, d.height, d.maze, d.startPoint, 1);
    if(Neighbours.size){
        d.maze        = setMode(d.startPoint, d.maze, WAY);
        randNum = randomRange(0, Neighbours.size-1);
        d.cellNext = Neighbours.cells[randNum]; //выбираем случайного соседа
        push(d.startPoint, &d.s, &d.stackSize); //заносим текущую точку в стек
        d.startPoint = d.cellNext; //делаем соседнюю точку текущей и отмечаем ее посещенной
        free(Neighbours.cells);
    }
    else if(d.stackSize){
        d.maze = setMode(d.startPoint, d.maze, SEEKED);
        d.startPoint = pop(&d.s, &d.stackSize);;
    }
    else{
        d.error = 1;
    }
    return d;
}
