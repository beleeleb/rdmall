#ifndef __TREE_IP_H__
#define __TREE_IP_H__

typedef struct ip_node ip_node_t;
typedef char* ip_t;

/*********************************************
 *	Creates address                          *
 *	Parameters: N/A.                         *
 *	Returns: Pointer to new address_tree.    *
 ********************************************/
ip_node_t* ip_tree_create(void);

/***************************************
 *	Destroys a given address.          *
 *	Parameters:                        *
 *	 	root : pointer to ip_tree root.* 
 *  Returns: N/A                       *
 **************************************/
void ip_tree_destroy(ip_node_t** root); 

/***********************************************************
*	issues an available ip address via the address creator.*
*	Parameters:                                            *
*	 	root : pointer to ip_tree root.                    *
*	Returns: next available ip addres 	     	           *
***********************************************************/
ip_t get_next_ip(ip_node_t* root);

/************************************************
 *	checks if requested ip address is available.* 
 *      Yes: Returns requested ip.              *
 *           No: Returns nearest ip.            *
 *	Parameters:                                 *
 * 	root : pointer to ip_tree root.             *
 *	 	ip_p: wanted ip address.                *
 *	Returns: given ip addres or NULL 	        *
 ***********************************************/
ip_t get_ip_requested(ip_node_t* root ,ip_t ip);

/***************************************
 *	relese a given ip address.         *
 *	Parameters:                        *
 *  	root : pointer to ip_tree root.*
 *	 	ip_t: ip to release.           *
 *	Returns: success/failure.    	   *
 **************************************/
int release_ip(ip_node_t* root ,ip_t ip);

#endif 	/* __TREE_IP_H__	*/
