#ifndef TYPES_H
#define TYPES_H
#include <GL/gl.h>
#include <stdio.h>


enum cellTypes {CELL = 0, GENCELL, GENVISITED, RENDERED, WALL, WAY, CURRENT, LAST, SEEKED, EXIT};
enum actions   {NOTHING = 0, GENERATE, SOLVE, STOP, OUTPUT};

typedef int*  mazeString;
typedef int** mazeMatrix;

typedef struct Cell{
    unsigned int x;
    unsigned int y;
} cell;

typedef struct CellString{
    cell* cells;
    unsigned int size;
} cellString;

typedef struct Stack{
    cell c;
    struct Stack *next;
} stack;

typedef struct MazeData{
    unsigned int width;
    unsigned int height;
    unsigned int unvisitedNum;
    mazeMatrix   maze;
    stack*       s;
    unsigned int stackSize;
    cell         startPoint;
    cell         exitPoint;
    cell         cellNext;
    int error;
} data;

typedef struct Vertex{
    GLfloat x,y;
} vertex;

typedef struct VertexColor{
    GLubyte r,g,b;
} vertexColor;

typedef struct RenderData{
    unsigned int width;
    unsigned int height;
    //opengl data
    GLfloat x;
    GLfloat y;
    GLfloat pSize;
    vertex *vertices;
    vertexColor *verticesColor;
    int vertices_count;
} renderData;

#endif // TYPES_H

