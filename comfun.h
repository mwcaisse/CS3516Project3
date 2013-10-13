#ifndef COMFUN_H
#define COMFUN_H

#define NUM_NODES (4)
#define COST_INF (999)

/* a rtpkt is the packet sent from one routing update process to
	 another via the call tolayer3() */
struct rtpkt {
	int sourceid;       /* id of sending router sending this pkt */
	int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
	int mincost[4];    /* min cost to node 0 ... 3 */
};
  
  //distance table struct
struct distance_table {
	int costs[4][4]; // cost will contain full cost to node i
};


/** Initializes the given node
	@param nodeid The ID of the node that is being initialized
	@param local_costs An integer array of the cost of connecting to the nodes neighbors
	@param neighbors An array of the nodes neighbors, terminated by -1
	@param distance_table Pointer to the nodes distance table
*/

void initialize_node(int nodeid, int* local_costs,int* neighbors, struct distance_table* distance_table);

/** Updates the nodes distance table, and neighbors when an update packet is received
	@param nodeid The ID of the node that ie being updated
	@param neighbors An array of the nodes neighbors, terminated by -1
	@param distance_table Pointer to the distance table struct of the node
	@param rtpkt The update packet that the node received
*/

void update_node(int nodeid, int* neighbors, struct distance_table* distance_table, struct rtpkt* rtpkt);

/** Calculates the minimum costs to every node for the given node, and puts them into min_costs
	@param nodeid The ID of the node to calculate the min costs for
	@param distance_table A pointer to the nodes distance table
	@param min_costs A pointer to an array to put the min costs in
*/

void get_min_costs(int nodeid, struct distance_table* distance_table, int* min_costs);

/** Sends the given packet to the specified neighbor
	@param src_node The source node that is sending the packet
	@oaram dest_node The node to send the packet to
	@param rtpkt The packet to send to the nodes neighbors
*/

void send_to_neighbor(int dest_node, struct rtpkt* rtpkt);

/** Sends an updated distance table to all of hte specified nodes neighbors
	@param nodeid THe id of the sending node
	@param neighbors Array containing the nodes neighbors
	@param distance_table Pointer to the distance table for the node
*/

void update_neighbors(int nodeid, int* neighbors, struct distance_table* distance_table);

/** Creates an update packet to send to neighbors for the specified node
	@param src_node THe node id of the source node
	@param dest_node The node id of the desitnation node
	@param distance_table A pointer to the nodes distance_table
	@param Pointer to the pre-allocated update packet
*/

void create_update_packet(int nodeid, struct distance_table* distance_table, 
	struct rtpkt*  update_packet);
	
/** Determines the min cost of nodeid to the destination node
	@param nodeid The node calling this function
	@param dest_node The destination node to find the min path to
	@param distance_table The distance table for the nodeid
*/

int min_cost_to(int nodeid, int dest_node, struct distance_table* distance_table);


/** Prints out the given deistance table
	@param nodeid THe ID of the node whose distance table is being printed
	@param dist_tbl Pointer to the distance table to print out
*/

void print_distance_table(int nodeid, struct distance_table* dist_tbl);

/** Prints out the minimum costs in the given update packet
	@param The id of the node who is calling this funct
	@param update_packet The update packet the node received
*/

void print_min_costs(int nodeid, struct rtpkt* update_packet);



#endif