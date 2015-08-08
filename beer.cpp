#include "hexxx.h"
#include "draw.h"





void draw_beer(void) {
    Point sP={9,6};
    Point eP;
    //top
    ws2811_led_t glassC=color( 1,1, 200 );
    ws2811_led_t beerC=color( 255,255, 30 );
    draw_hex(sP,3,glassC);
    //fill top
    draw_hex(sP,2,beerC);
    draw_hex(sP,1,beerC);
    draw_hex(sP,0,beerC);


    //bottum
    sP={9,12};
    draw_hex(sP,3,glassC);

    //handle
    sP={13,11};
    draw_hex(sP,3,glassC);
    draw_hex(sP,2,glassC);
    sP={6,6};
    eP={6,13};
    draw_line(sP,eP,glassC);

    //sides
    sP={sP.X+1,sP.Y+2};
    eP={eP.X+1,eP.Y};
    draw_line(sP,eP,beerC);
    sP={sP.X+1,sP.Y+1};
    eP={eP.X+1,eP.Y+1};
    draw_line(sP,eP,beerC);

    sP={9,9};
    eP={9,16};
    draw_line(sP,eP,glassC);

    sP={sP.X+1,sP.Y+1};
    eP={eP.X+1,eP.Y-1};
    draw_line(sP,eP,beerC);
    sP={sP.X+1,sP.Y};
    eP={eP.X+1,eP.Y};
    draw_line(sP,eP,beerC);


    sP={12,8};
    eP={12,16};
    draw_line(sP,eP,glassC);
}


void logic_thread() {
  draw_beer();

  while (1) {
    usleep(200000);
  }
}
