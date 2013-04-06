#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

int main() {

  screen s;
  color c;
 
  
  c.red = MAX_COLOR;
  c.green = MAX_COLOR;
  c.blue = 0;
  
  clear_screen(s);

  int i, j;

  for (i=0; i < YRES; i++)
    for (j=-500; j < XRES; j++ )
      plot(s, c, i, j);
  
  c.green = 0;

  draw_line(0, 0, 400, 350, s, c); //oct 1
  draw_line(0, 0, 400, 450, s, c); //oct 2
  //draw_line(20, 20, 300, 250, s, c); //oct 5
  draw_line(20, 350, 300, 100, s, c); //oct 6
  
  //draw_line(0, 0, 400, 350, s, c);
  //draw_line(0, 0, 400, 350, s, c);
  
  //Note: Display may not work on your system
  //save_ppm and save_extension should be fine
  save_ppm(s, "pic.ppm");
  save_extension(s, "whatevs.png");
  //display(s);
}  
