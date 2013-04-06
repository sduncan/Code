#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

int main() {

  screen s;
  color c;

  c.red = 0;
  c.green = 255;
  c.blue = 255;

  int i, j;

  for( i=0; i<XRES; i++) 
    for ( j=0; j<YRES; j++) {

      c.red = random() % (MAX_COLOR + 1);
      c.green = random() % (MAX_COLOR + 1);
      c.blue = random() % (MAX_COLOR + 1);

      plot( s, c, i, j);
    }

  struct matrix * points = new_matrix(4, 4);
  add_point(points, 50, 250, 0);
  add_point(points, 70, 250, 0);
  add_edge(points, 30, 100, 0, 300, 400, 0);
  draw_lines(points, s, c);
  print_matrix(points);
  printf("\n");
  //  scalar_mult(2.0, points);
  //  printf("\n");
  ident(points);
  printf("\n");
  //display( s );    
  save_ppm(s,  "picture" );
  save_extension(s, "picture.jpg");
  
}  
