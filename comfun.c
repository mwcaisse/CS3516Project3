#include <stdlib.h>
#include <stdio.h>

#include "comfun.h"

//TRACE value
extern int TRACE;


void initialize_node(int nodeid, int* local_costs, struct distance_table* distance_table) {
	int i;
	int j;
	
	//add the costs of the direct neighbors
	for (j=0;j < NUM_NODES; j ++) {
		//cost from THIS node to J
		distance_table->costs[nodeid][j] = local_costs[j];
	}
	
	//the costs via another node are unkown, set to infinite
	for (i=0; i < NUM_NODES; i++) {
		if (i == nodeid) continue; //we already added the local costs.
		for (j=0;j < NUM_NODES; j++) {
			distance_table->costs[i][j] = COST_INF;
		}
	}

}


void update_node(int nodeid, struct distance_table* distance_table, struct rtpkt* rtpkt) {

}


void send_to_neighbors(int src_node, int dest_node, struct rtpkt* rtpkt) {

}


void create_update_packet(int nodeid, struct distance_table* distance_table, 
	struct rtpkt*  update_packet) {
	
}

void print_distance_table(int nodeid, struct distance_table* dist_tbl) {
	printf("Node %d Distance table \n", nodeid);
	printf("\t VIA \n");
	printf("\t\t0\t1\t2\t3\n");
	printf("0\t%d\t%d\t%d\t%d\n", dist_tbl->costs[0][0],dist_tbl->costs[0][1],
		dist_tbl->costs[0][2],dist_tbl->costs[0][3]);
	printf("1\t%d\t%d\t%d\t%d\n", dist_tbl->costs[1][0],dist_tbl->costs[1][1],
		dist_tbl->costs[1][2],dist_tbl->costs[1][3]);
	printf("2\t%d\t%d\t%d\t%d\n", dist_tbl->costs[2][0],dist_tbl->costs[2][1],
		dist_tbl->costs[2][2],dist_tbl->costs[2][3]);
	printf("3\t%d\t%d\t%d\t%d\n", dist_tbl->costs[3][0],dist_tbl->costs[3][1],
		dist_tbl->costs[3][2],dist_tbl->costs[3][3]);
}
