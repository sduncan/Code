#ifndef DRAW_H
#define DRAW_H

#include "matrix.h"
#include "display.h"

void draw_line(int x0, int y0, int x1, int y1, screen s, color c);
void add_point( struct matrix * points, int x, int y, int z);
void add_edge( struct matrix * points, 
	       int x0, int y0, int z0, 
	       int x1, int y1, int z1);
void draw_lines( struct matrix * points, screen s, color c);

//advanced shapes
void add_circle( struct matrix * points, 
		 double cx, double cy, 
		 double r, double step );
void add_curve( struct matrix *points, 
		double x0, double y0,
		double x1, double y1,
		double x2, double y2,
		double x3, double y3,
		double step, int type );

#endif
