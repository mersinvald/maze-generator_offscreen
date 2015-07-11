#ifndef GENERATOR_H
#define GENERATOR_H
#include <types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <common.h>


extern data generate           (data d);

extern data generateStep       (data d);

extern mazeMatrix init         (unsigned int width,
                         unsigned int height);

extern mazeMatrix finalize     (unsigned int width,
                         unsigned int heiggt,
                         mazeMatrix   maze);

extern mazeMatrix removeWall   (cell first,
                         cell second,
                         mazeMatrix maze);

extern cellString getCells     (unsigned int width,
                         unsigned int height,
                         mazeMatrix maze);

extern cellString getUnvisitedCells
                        (unsigned int width,
                         unsigned int height,
                         mazeMatrix maze);

extern unsigned int        unvisitedCount
                        (unsigned int width,
                         unsigned int height,
                         mazeMatrix maze);

#endif // GENERATOR_H

