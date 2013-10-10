#ifndef COMFUN_H
#define COMFUN_H

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
	int costs[4][4];
};


/** Initializes the given node
	@param nodeid The ID of the node that is being initialized
	@param local_costs An integer array of the cost of connecting to the nodes neighbors
	@param distance_table Pointer to the nodes distance table
*/

void initialize_node(int nodeid, int* local_costs, struct distance_table* distance_table);

/** Updates the nodes distance table, and neighbors when an update packet is received
	@param nodeid The ID of the node that ie being updated
	@param distance_table Pointer to the distance table struct of the node
	@param rtpkt The update packet that the node received
*/

void update_node(int nodeid, struct distance_table* distance_table, struct rtpkt* rtpkt);

/** Sends the given packet to the calling nodes neighbors
	@param nodeid the ID of the sending node
	@param rtpkt The packet to send to the nodes neighbors
*/

void send_to_neighbors(int src_node, int dest_node, struct rtpkt* rtpkt);

/** Creates an update packet to send to neighbors for the specified node
	@param src_node THe node id of the source node
	@param dest_node The node id of the desitnation node
	@param distance_table A pointer to the nodes distance_table
	@param Pointer to the pre-allocated update packet
*/

void create_update_packet(int nodeid, struct distance_table* distance_table, 
	struct rtpkt*  update_packet);


/** Printso ut the given deistance table
	@param nodeid THe ID of the node whose distance table is being printed
	@param dist_tbl Pointer to the distance table to print out
*/

void print_distance_table(int nodeid, struct distance_table* dist_tbl);



#endif