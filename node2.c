#include <stdio.h>

#include "comfun.h"

extern int TRACE;
extern int YES;
extern int NO;


struct distance_table dt2;

//cost of connections to neighbors.
int local_costs2[4] = {3,1,0,2};
int neighbors2[4] = {1,0,3,-1};


/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
	initialize_node(2, local_costs2, neighbors2, &dt2);
}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
	update_node(2, neighbors2, &dt2, rcvdpkt);
}


printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}







