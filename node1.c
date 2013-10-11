#include <stdio.h>

#include "comfun.h"


extern int TRACE;
extern int YES;
extern int NO;

//cost of connections to neighbors.
int local_costs1[4] = {1,0,1,COST_INF};
int neighbors1[3] = {0,2,-1};

struct distance_table dt1;


/* students to write the following two routines, and maybe some others */


rtinit1() 
{
	initialize_node(1, local_costs1, neighbors1, &dt1);
}


rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
	update_node(1, neighbors1, &dt1, rcvdpkt);
}


printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



linkhandler1(linkid, newcost)   
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


