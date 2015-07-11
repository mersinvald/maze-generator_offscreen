#include <stdio.h>
#include <stdlib.h>
#include <generator.h>
#include <seeker.h>
#include <renderer.h>
#include <types.h>
#include <common.h>
#include <string.h>
#include <sys/time.h>


void printWithTime(const char* message, struct timeval startup){
    struct timeval current;
    gettimeofday(&current, NULL);

    int cSec = current.tv_sec - startup.tv_sec;

    printf("[%i]\t\t%s", cSec, message);
    fflush(stdout);
}

void help(int argc, char** argv){
    printf("Usage: %s [width] [height] [picture_width] [picture_height] [draw each N] [folder path]\n", argv[0]);
}

void output(int sizeX, int sizeY, char* filename){
    uint8_t *data; //промежуточный между GL-контекстом и libpng указатель, будет хранить пиксельные данные.
    data = malloc(sizeX * sizeY * 4 * sizeof(uint8_t));

    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, sizeX , sizeY,  GL_RGBA, GL_UNSIGNED_BYTE, data);

    save_png_libpng(filename, data, sizeX, sizeY);

    free(data);
}




int main(int argc, char **argv)
{

    if(argc < 7) {help(argc, argv); return 0;}
    int width      = atoi(argv[1]);
    int height     = atoi(argv[2]);
    int sizeX      = atoi(argv[3]);
    int sizeY      = atoi(argv[4]);
    int drawEach   = atoi(argv[5]);
    char* path     = argv[6];

    cell startPoint;
    cell exitPoint;

    startPoint.x = 1;
    startPoint.y = 1;
    exitPoint.x = (width % 2 == 0) ? width - 3 : width - 2;
    exitPoint.y = (height % 2 == 0) ? height - 3 : height - 2;

    data d;
    renderData rd;

    char* defaultGenFileName = malloc(sizeof(path) + sizeof("/maze_") + 4);
    strcpy(defaultGenFileName, path);
    strcat(defaultGenFileName, "/maze_");

    char* defaultSolveFileName = malloc(sizeof(path) + sizeof("/maze_solved_") + 4);
    strcpy(defaultSolveFileName, path);
    strcat(defaultSolveFileName, "/maze_solved_");

    struct timeval startup;
    gettimeofday(&startup, NULL);
    printWithTime("Initialization\n", startup);

    srand((unsigned)clock()); //инициализируем seed от тактов процессора
    OSMesaContext context = OSMesaCreateContext(OSMESA_RGBA, NULL); //создаем offscreen openGL контекст

    void *buffer = malloc(sizeX*sizeY*4*sizeof(GLfloat)); //буффер рендеринга. По 4 вершины на каждую клетку лабиринта.
    OSMesaMakeCurrent(context, buffer, GL_UNSIGNED_BYTE, sizeX, sizeY);

    //OpenGL 4.1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glOrtho(-sizeX/2,sizeX/2,sizeY/2,-sizeY/2,0,1);
    glClearColor( 1, 1, 1, 0 );

    //инициализация данных рендерера и генератора
    d = initGeneratorData(width, height, startPoint);
    rd = initRenderData(d, sizeX, sizeY);

    //скармливаем openGL указатели на массивы вершин и цветов.
    glVertexPointer(2, GL_FLOAT, sizeof(vertex), rd.vertices);
    glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(vertexColor), rd.verticesColor);

    printWithTime("Done\n\n", startup);
    printWithTime("Generating maze\n", startup);
    //Генерация
    unsigned int frameCount = 0;
    unsigned int savedCount = 0;
    char cBuffer[30];
    char* currentFileName;
    do{
        d = generateStep(d);
        frameCount++;
        if((drawEach > 0) ? (frameCount % drawEach == 0) : 0 || d.unvisitedNum <= 0){ //рисуем каждый drawEach кадр или последний.
            if(d.unvisitedNum <= 0){
                wipe(&d.s, &d.stackSize); //очищаем стек, если генерация уже окончена. Workaround для генерации больших лабиринтов.
            }
            printWithTime("Rendering frame ", startup); printf("%u\n", frameCount);
            setMode(d.startPoint, d.maze, CURRENT);
            renderMatrix(d.maze, rd, GENERATE);
            setMode(d.startPoint, d.maze, GENVISITED);
            printWithTime("Saving frame ", startup); printf("%u\n", frameCount);

            sprintf(cBuffer, "%i", ++savedCount);
            currentFileName = malloc(sizeof(defaultGenFileName) + sizeof(cBuffer));
            strcpy(currentFileName, defaultGenFileName);
            strcat(currentFileName, cBuffer);

            output(sizeX, sizeY, currentFileName);
            free(currentFileName);
        }
    }
    while(d.unvisitedNum > 0);
    printWithTime("Maze generated\n\n", startup);

    printWithTime("Solving\n", startup);
    //Решение
    frameCount = 0;
    savedCount = 0;
    int solved = 0;
    d = initSeekerData(d, startPoint, exitPoint);
    do{
        d = seekStep(d);
        frameCount++;
        if(d.startPoint.x == exitPoint.x && d.startPoint.y == exitPoint.y){
            solved = 1;
            wipe(&d.s, &d.stackSize);
        }
        if((drawEach > 0) ? (frameCount % drawEach == 0) : 0 || solved){ //рисуем каждый drawEach кадр или последний.
            printWithTime("Rendering frame ", startup); printf("%i\n", frameCount);
            setMode(d.startPoint, d.maze, CURRENT);
            renderMatrix(d.maze, rd, SOLVE);
            setMode(d.startPoint, d.maze, WAY);
            printWithTime("Saving frame ", startup); printf("%i\n", frameCount);

            sprintf(cBuffer, "%i", ++savedCount);
            currentFileName = malloc(sizeof(defaultSolveFileName) + sizeof(cBuffer));
            strcpy(currentFileName, defaultSolveFileName);
            strcat(currentFileName, cBuffer);

            output(sizeX, sizeY, currentFileName);
            free(currentFileName);
        }
    }
    while(!solved);

    printWithTime("Maze solved\n", startup);
    return 0;
}
