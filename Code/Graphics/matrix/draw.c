#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, int x, int y, int z) {
  if(points->lastcol == points->cols){
    grow_matrix(points, points->cols * 2);
    points->lastcol = points->lastcol + 1;
  }
  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;
  points->lastcol = points->lastcol + 1;
  points++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       int x0, int y0, int z0, 
	       int x1, int y1, int z1) {
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int col;
  for(col=0; col<points->lastcol; col=col+2)
    draw_line(points->m[0][col], points->m[1][col], points->m[0][col + 1], points->m[1][col + 1], s, c);
}


void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
 
  int x, y, dx, dy, d, A, B;
  x = x0;
  y = y0;
  //swap values if octants 3-6
  if ( x0 > x1 ) {
    x = x1;
    y = y1;
    x1 = x0;
    y1 = y0;
  }

  dx = x1 - x;
  dy = y1 - y;
  A = dy * 2;
  B = -2 * dx;
    
  //positive slope: Octants 1,2
  if ( dy > 0 ) {

    //Octant 1
    if ( dx > dy ) {
      
      d = A + B/2;
      while ( x <= x1 ) {
	plot( s, c, x, y );
	if ( d > 0 ) {
	  y++;
	  d+= B;
	}
	x++;
	d+= A;
      }
    }// end octant 1

    //Octant 2
    else {
      
      d = A/2 + B;
      while ( y <= y1 ) {
	plot( s, c, x, y );
	if ( d < 0 ) {
	  x++;
	  d+=A;
	}
	y++;
	d+= B;
      }
    }//Octant 2
  }//octants: 1, 2
  
  //negative slope: Octants: 7, 8
  else {
    //Octant 8
    if ( dx > (-1 * dy) ) {
      d = A - B/2;
      while ( x <= x1 ) {
	plot(s, c, x, y);
	if ( d < 0 ) {
	  y--;
	  d-=B;
	}
	x++;
	d+= A;
      }
    }//end octant 8
    
    //octant 7
    else {
      d = A/2 - B;
      while( y >= y1 ) {
	plot(s, c, x, y);
	if ( d > 0 ) {
	  x++;
	  d+= A;
	}
	y--;
	d-= B;
      }
    } //end octant 7
  }//end Octants 7,8
}
