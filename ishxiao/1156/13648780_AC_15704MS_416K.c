// 1156

#include <stdio.h>
#include <stdlib.h>

// Maximum width of data
#define DW 700
// Maximum width of plain to find
#define PW 100
// Maximum criteria
#define MC 10

int pl[DW];
int np;
int npc[MC+1];
int cl[DW][MC+1];

int w, h, c;

long ma=1;
int x1=1, y1=1, x2=1, y2=1;

int main()
{
  int np, hd, hdc;
  int wc, hc, wc2;
  register int cc;
  int r, hm;
  long ca;



  scanf("%d %d %d", &w, &h, &c);

// Process the first line
  y1 = y2 = h;
  for(wc=0; wc < w; wc++) {
    scanf( "%d", &pl[wc]);
    for(cc=0; cc <= c; cc++) {
      cl[wc][cc] = 1;
      for(wc2=wc; 0 <= wc2 && wc - wc2 < PW; wc2--) {
        hdc = pl[wc2]-pl[wc]+cc;
        if(0 <= hdc && hdc <= c) {
          if(ma < (ca = (long) (wc - wc2 + 1))) {
            ma = ca;
            x1 = wc2+1;
            x2 = wc+1;
          }
        }
        else
          break;
      }
    }
  }

// Process the remaining lines
  for(hc=h-1; 0 < hc; hc--) {
    for(wc=0; wc < w; wc++) {
      scanf( "%d", &np);
      hd = pl[wc]-np;
      for(cc=0; cc <= c && hd+cc < 0; cc++)
        npc[cc] = 1;
      for(; cc <= c && (r = hd+cc) <= c; cc++)
        npc[cc] = cl[wc][r]+1;
      for(; cc <= c; cc++)
        npc[cc] = 1;
      pl[wc] = np;
      for(cc = 0; cc <= c; cc++)
        cl[wc][cc] = npc[cc];
      for(cc=0; cc <= c; cc++) {
        hm = cl[wc][cc];
        for(wc2=wc; 0 <= wc2 && wc - wc2 < PW; wc2--) {
          hdc = pl[wc2]-pl[wc]+cc;
          if(0 <= hdc && hdc <= c) {
            if(cl[wc2][hdc] < hm)
              hm = cl[wc2][hdc];
            if(ma < (ca = (long) hm * (long) (wc - wc2 + 1))) {
              ma = ca;
              x1 = wc2+1;
              y1 = hc;
              x2 = wc+1;
              y2 = hc+hm-1;
            }
          }
          else
            break;
        }
      }
    }
  }
  printf("%d",(x2-x1+1)*(y2-y1+1));

  return 0;
}


