#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"


//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int x = x0;
  int y = y0;
  int A = y1-y0;
  int B = -(x1-x0);
  int m = -(A/B);
  int d = 0;
  if(m <= 1 && m >= 0){
    d = A + (B/2);
    while(x <= x1){
      plot(s, c, x, y);
      if(d > 0){
	y++;
	d += B;
      }
      x++;
      d += A;
    }
  }
  else if(m > 1){
    d = (A/2) + B;
    while(x < x1){
      plot(s, c, x, y);
      if(d < 0){
	y++;
	x++;
	d += A+B;
      }
      else{
	y++;
	d += B;
      }
    }
  }
  else if(m >= -1 && m < 0){
    d = A - (B/2);
    while(x < x1){
      plot(s, c, x, y);
      if(d > 0){
	x++;
	d += A;
      }
      else{
	x++;
	y--;
	d += (A - B);
      }
    }
  }
}
