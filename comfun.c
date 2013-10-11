#include <stdlib.h>
#include <stdio.h>

#include "comfun.h"

//TRACE value
extern int TRACE;


void initialize_node(int nodeid, int* local_costs, int* neighbors, struct distance_table* distance_table) {
	int i;
	int j;
	
	
	//initialize the distance table so all costs are infinite
	for (i=0; i < NUM_NODES; i++) {
		for (j=0;j < NUM_NODES; j++) {
			distance_table->costs[i][j] = COST_INF;
		}
	}
	
	//add the costs of our direct neighbors to the table
	for (i=0;i < NUM_NODES; i ++) {
		//cost from THIS node to J
		distance_table->costs[i][nodeid] = local_costs[i];
	}
	
	
	if (TRACE) {
		printf("Node %d initialization done, printing distance table \n", nodeid);
		print_distance_table(nodeid, distance_table);
	}
	
	//send the update packet to our neighbors
	update_neighbors(nodeid, neighbors, distance_table);	

}


void update_node(int nodeid, int* neighbors, struct distance_table* distance_table, struct rtpkt* rtpkt) {
	printf("Node %d received an update packet!! Hoorah! \n", nodeid);
	print_min_costs(nodeid, rtpkt);
}

void update_neighbors(int nodeid, int* neighbors, struct distance_table* distance_table) {
	struct rtpkt update_packet; // the update packet we will use to send to neighbors
	//add the minimum costs to the update packet
	create_update_packet(nodeid, distance_table, &update_packet);
	
	//send the packet to our neighbors
	int i=0;
	for (i = 0;i < NUM_NODES; i++) {
		if (neighbors[i] == -1) break; // we reached end, exit
		send_to_neighbor(nodeid, neighbors[i], &update_packet);
	}
	
	
}

void send_to_neighbor(int src_node, int dest_node, struct rtpkt* update_packet) {
	update_packet->sourceid = src_node;
	update_packet->destid = dest_node;
	tolayer2(*update_packet);	
}


void create_update_packet(int nodeid, struct distance_table* distance_table, 
	struct rtpkt*  update_packet) {
	int i;
	int j;
	
	//put the minimum costs into the update packet
	for (i=0; i < NUM_NODES; i++) {
		int min = COST_INF;
		for (j=0;j<NUM_NODES;j++) {
			if (distance_table->costs[i][j] < min) {
				min = distance_table->costs[i][j];
			}
		}
		update_packet->mincost[i] = min;
	}
	
	//now we will send to neighbors
	
}



void print_min_costs(int nodeid, struct rtpkt* update_packet) {
	
	printf("TO\t0\t1\t2\t3\t VIA: %d\n", update_packet->sourceid);
	printf("\t%d\t%d\t%d\t%d\n", update_packet->mincost[0], update_packet->mincost[1],
								 update_packet->mincost[2], update_packet->mincost[3]);
}

void print_distance_table(int nodeid, struct distance_table* dist_tbl) {
	printf("Node %d Distance table \n", nodeid);
	printf("VIA\tTO\n");
	printf("\t0\t1\t2\t3\n");
	printf("0\t%d\t%d\t%d\t%d\n", dist_tbl->costs[0][0],dist_tbl->costs[1][0],
								  dist_tbl->costs[2][0],dist_tbl->costs[3][0]);
								  
	printf("1\t%d\t%d\t%d\t%d\n", dist_tbl->costs[0][1],dist_tbl->costs[1][1],
								  dist_tbl->costs[2][1],dist_tbl->costs[3][1]);
								  
	printf("2\t%d\t%d\t%d\t%d\n", dist_tbl->costs[0][2],dist_tbl->costs[1][2],
								  dist_tbl->costs[2][2],dist_tbl->costs[3][2]);
								  
	printf("3\t%d\t%d\t%d\t%d\n", dist_tbl->costs[0][3],dist_tbl->costs[1][3],
		  						  dist_tbl->costs[2][3],dist_tbl->costs[3][3]);
}
