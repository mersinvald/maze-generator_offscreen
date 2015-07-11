#include <renderer.h>


void renderMatrix(mazeMatrix maze, renderData rd, int mode){
    glClear(GL_COLOR_BUFFER_BIT);

    if(mode == GENERATE)   drawGenerateMatrix(maze, rd);
    else                   drawSolveMatrix(maze, rd);

    glDrawArrays(GL_QUADS,0, rd.vertices_count);
    //memset(cArray, 255, sizeof(vertexColor)*rd.width*rd.height*4); //очистка массива цветов точек
}

void drawGenerateMatrix(mazeMatrix maze, renderData rd){
    unsigned long long int i, j, c, col = 0;
    for(i = 0; i < rd.height; i++){
        for(j = 0; j < rd.width; j++){
            if(maze[i][j] != WALL && maze[i][j] != GENCELL){
                for(c = 0; c<4; c++){
                    switch (maze[i][j]){
                        case CURRENT: rd.verticesColor[col].r = 0;
                                      rd.verticesColor[col].g = 255;
                                      rd.verticesColor[col].b = 0;
                                      break;
                        case GENVISITED:
                                      rd.verticesColor[col].r = 255;//randomRange(0, 255);//= 0;
                                      rd.verticesColor[col].g = 255;//randomRange(0, 255);//= 0;
                                      rd.verticesColor[col].b = 255;//randomRange(0, 255);//= 0;
                                      break;
                    }
                    col++;
                }
            }
            else col+=4;
        }
    }
}


void drawSolveMatrix(mazeMatrix maze, renderData rd){
    unsigned long long int i, j, c, col = 0;
    for(i = 0; i < rd.height; i++){
        for(j = 0; j < rd.width; j++){
            if(maze[i][j] != WALL && maze[i][j] != GENCELL && maze[i][j] != GENVISITED){
                for(c = 0; c<4; c++){
                    switch (maze[i][j]){
                        case WAY:
                                      rd.verticesColor[col].r = 255;
                                      rd.verticesColor[col].g = 0;
                                      rd.verticesColor[col].b = 0;
                                      break;
                        case SEEKED:  rd.verticesColor[col].r = 30;  //= 255;
                                      rd.verticesColor[col].g = 90;  //= 255;
                                      rd.verticesColor[col].b = 255; //= 255;
                                      break;
                        case CURRENT:
                                      rd.verticesColor[col].r = 0;
                                      rd.verticesColor[col].g = 255;
                                      rd.verticesColor[col].b = 0;
                                      //rd.verticesColor[col].r = 10;
                                      //rd.verticesColor[col].g = 255;
                                      //rd.verticesColor[col].b = 70;
                                      break;
                        case EXIT:    rd.verticesColor[col].r = 0;
                                      rd.verticesColor[col].g = 255;
                                      rd.verticesColor[col].b = 0;
                        default: break;
                    }
                    col++;
                }
            }
            else col+=4;
        }
    }
}
