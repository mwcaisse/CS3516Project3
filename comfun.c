#include <stdlib.h>
#include <stdio.h>

#include "comfun.h"

//TRACE value
extern int TRACE;
//clocktime
extern float clocktime;


void initialize_node(int nodeid, int* local_costs, int* neighbors, struct distance_table* distance_table) {
	printf("INITIALIZE_NODE: Initializing Node %d at Time %f \n", nodeid, clocktime);
	
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
	//send the update packet to our neighbors
	update_neighbors(nodeid, neighbors, distance_table);	

}


void update_node(int nodeid, int* neighbors, struct distance_table* distance_table, struct rtpkt* rtpkt) {
	int senderid = rtpkt->sourceid;
	printf("UPDATE_NODE: Node %d received an update message from %d at time %f\n", nodeid, senderid, clocktime);
	
	int cost_to_node = min_cost_to(nodeid, senderid, distance_table);
	
	int orig_min_costs[NUM_NODES];
	get_min_costs(nodeid, distance_table, orig_min_costs);
	
	
	//SHALL WE PARSE THEESE MIN COSTSSSSSS!!!!!!!!!!!!!!
	int changes = 0;
	int i=0;
	for (i =0;i < NUM_NODES; i++) {
		//add the cost to the sending node, before we compare with table value.
		int tmp = rtpkt->mincost[i] + distance_table->costs[senderid][nodeid];
		if (tmp < distance_table->costs[i][senderid]) {
			distance_table->costs[i][senderid] = tmp;
			changes++;
		}
	}
	if (changes) { // only do this if we made any changes above
		printf("UPDATE_NODE: Node %d, changes were made to distance table \n", nodeid);
		int new_min_costs[NUM_NODES];
		get_min_costs(nodeid, distance_table, new_min_costs);
		
		int update = 0;
		
		for (i=0; i < NUM_NODES; i++) {
			if (new_min_costs[i] != orig_min_costs[i]) {
				update = 1;
				break; // we dont need to keep checking
			}
		}
	
		if (update) {
			printf("UPDATE_NODE: Node %d, There is a new minimum path to a node,"
				"sending new miniumum path data to our neighbors \n", nodeid);
			//if we made a change update our neighbors saying we did. hoorah
			update_neighbors(nodeid, neighbors, distance_table);
			//if we made changes lets print out our new distance table
			print_distance_table(nodeid, distance_table);
			printf("Node %d min costs \n", nodeid);
			print_min_costs(nodeid, distance_table);
		}
	}
	
	printf("UPDATE_NODE: Node %d, The distance table at the end of the update, \n", nodeid);
	print_distance_table(nodeid, distance_table);
	printf("UPDATE_NODE: Node %d, The minimum path values at the end of the update, \n", nodeid);
	print_min_costs(nodeid, distance_table);
}

void get_min_costs(int nodeid, struct distance_table* distance_table, int* min_costs) {
	int i;
	
	//find the min costs
	for (i=0; i < NUM_NODES; i++) {
		int min = min_cost_to(nodeid, i, distance_table);
		min_costs[i] = min;
	}
}

void update_neighbors(int nodeid, int* neighbors, struct distance_table* distance_table) {
	struct rtpkt update_packet; // the update packet we will use to send to neighbors
	//add the minimum costs to the update packet
	create_update_packet(nodeid, distance_table, &update_packet);
	
	//send the packet to our neighbors
	int i=0;
	for (i = 0;i < NUM_NODES; i++) {
		if (neighbors[i] == -1) break; // we reached end, exit
		send_to_neighbor(neighbors[i], &update_packet);
	}
	
	
}

void send_to_neighbor(int dest_node, struct rtpkt* update_packet) {
	update_packet->destid = dest_node;
	tolayer2(*update_packet);	
}


void create_update_packet(int nodeid, struct distance_table* distance_table, 
	struct rtpkt*  update_packet) {
	
	update_packet->sourceid = nodeid;
	get_min_costs(nodeid, distance_table, update_packet->mincost);
	
}

int min_cost_to(int nodeid, int dest_node, struct distance_table* distance_table) {
	int min_cost = COST_INF;
	int j=0;
	
	for (j=0; j < NUM_NODES; j++) {
		//minimum cost is the cost in the distance table to that node
		int tmp = distance_table->costs[dest_node][j];
		if (tmp < min_cost) {
			min_cost = tmp;
		}
	}
	
	return min_cost;
}



void print_min_costs_packet(int nodeid, struct rtpkt* update_packet) {
	
	printf("TO\t0\t1\t2\t3\t VIA: %d\n", update_packet->sourceid);
	printf("\t%d\t%d\t%d\t%d\n", update_packet->mincost[0], update_packet->mincost[1],
								 update_packet->mincost[2], update_packet->mincost[3]);
}

void print_min_costs(int nodeid, struct distance_table* distance_table) {
	int min_costs[4];
	get_min_costs(nodeid, distance_table, min_costs);
	
	printf("TO\t0\t1\t2\t3\t\n");
	printf("\t%d\t%d\t%d\t%d\n", min_costs[0], min_costs[1],
								 min_costs[2], min_costs[3]);
	
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
