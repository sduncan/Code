#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main() {

  screen s;
  struct matrix *edges;
  struct matrix *transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  color c;
  c.red = 250;
  c.blue = 250;
  c.green = 0;
  
  parse_file( "script_c", transform, edges, s, c );

  free_matrix( transform );
  free_matrix( edges );
}  
