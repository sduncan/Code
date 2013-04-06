#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         l: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 i: set the transform matrix to the identity matrix - 
	 s: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 t: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 x: create an x-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 y: create an y-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 z: create an z-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 a: apply the current transformation matrix to the 
	    edge matrix
	 v: draw the lines of the edge matrix to the screen
	    display the screen
	 g: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 q: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)

jdyrlandweaver
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * pm,
                  screen s, color c) {

  FILE * fp = fopen(filename, "r");

  char * lines = (char *)malloc(1);
  float x0, y0, z0, x1, y1, z1;
  float x, y, z;
  float theta;
	
  while(fscanf(fp, "%c", lines)) {
    printf("lines gets: %c \n", *lines); 
    switch (*lines){
    case 'l':
      {
	fscanf(fp, "%f %f %f %f %f %f", &x0, &y0, &z0, &x1, &y1, &z1);
	add_edge(pm, x0, y0, z0, x1, y1, z1);
	break;
      }
    case 'i':
      {
	ident(transform);
	break;
      }
    case 's':
      {
	fscanf(fp, "%f %f %f", &x, &y, &z);
	struct matrix * scale = make_scale(x, y, z);
	matrix_mult(scale, transform);
	free(scale);
	break;
      }
    case 't':
      {
	fscanf(fp, "%f %f %f", &x, &y, &z);
	struct matrix * trans = make_translate(x, y, z);
	matrix_mult(trans, transform);
	free(trans);
	break;
      }
    case 'x':
      {
	fscanf(fp, "%f", &theta);
	struct matrix * transx = make_rotX(theta);
	matrix_mult(transx, transform);
	free(transx);
	break;
      }
    case 'y':
      {
	fscanf(fp, "%f", &theta);
	struct matrix * transy = make_rotY(theta);
	matrix_mult(transy, transform);
	free(transy);
	break;
      }
    case 'z':
      {
	fscanf(fp, "%f", &theta);
	struct matrix * transz = make_rotZ(theta);
	matrix_mult(transz, transform);
	free(transz);
	break;
      }
    case 'a':
      {
	matrix_mult(transform, pm);
	break;
      }
    case 'v':
      {
	clear_screen(s);
	draw_lines(pm, s, c);
	display(s);
	break;
      }
    case 'g':
      {
	char * file = (char *)malloc(256);
	fscanf(fp, "%s", file);
	clear_screen(s);
	draw_lines(pm, s, c);
	save_extension(s, file);
	free(file);
	break;
      }
    case 'q':
      {
	exit(0);
      }
    default:
      {
	exit(1);
      }
    }
    fscanf(fp, "%c", lines);
  }
  
  fclose(fp);
  free(lines);
  
}

  
