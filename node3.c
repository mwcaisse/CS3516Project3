#include <stdio.h>

#include "comfun.h"

extern int TRACE;
extern int YES;
extern int NO;


struct distance_table dt3;

//cost of connections to neighbors.
int local_costs3[4] = {7,1000,2,0};

/* students to write the following two routines, and maybe some others */

void rtinit3() 
{
	initialize_node(3, local_costs3, &dt3);
}


void rtupdate3(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
	update_node(3, &dt3, rcvdpkt);
}


printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}







