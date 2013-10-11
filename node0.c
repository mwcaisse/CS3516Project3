#include <stdio.h>

#include "comfun.h"


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt0;


//cost of connections to neighbors.
int local_costs0[4] = {0,1,3,7};
int neighbors0[4] = {1,2,3,-1}; // Node 0's neighbors, terminated by -1

/* students to write the following two routines, and maybe some others */

void rtinit0() 
{
	initialize_node(0, local_costs0, neighbors0, &dt0);
}


void rtupdate0(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
	update_node(0, neighbors0, &dt0, rcvdpkt);
}


printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

