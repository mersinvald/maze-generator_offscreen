#ifndef COMMON_H
#define COMMON_H
#include <generator.h>
#include <SDL2/SDL.h>
#include <types.h>
#include <stack.h>
#include <libpng16/png.h>

extern data initGeneratorData(int width, int height, cell startPoint);
extern data initSeekerData(data d,cell startPoint, cell exitPoint);
extern renderData initRenderData(data d, int windowW, int windowH);

//generator and seeker common functions
extern mazeMatrix setMode      (cell c,
                         mazeMatrix maze,
                         int type);

extern cellString getNeighbours(unsigned int width,
                         unsigned int height,
                         mazeMatrix maze,
                         cell       c,
                         int distance);

extern unsigned int        randomRange
                        (unsigned int low,
                         unsigned int high);

//save to png
extern int save_png_libpng(const char *filename, uint8_t *pixels, int w, int h);

#endif // COMMON_H

