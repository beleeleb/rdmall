#include <stdio.h>
#include <arpa/inet.h>
#include "tree_ip.h"

extern void recursive_print(ip_node_t* curr, size_t level);

int main(int argc, char **argv, char **epvm)
{
	ip_node_t* ip_tree = NULL;
	ip_tree = ip_tree_create();


	
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	printf("\nyour new ip is: %s\n", get_ip_requested(ip_tree, "1.0.0.3"));
	
	printf("\nyour new ip is: %s\n", get_next_ip(ip_tree));
	
	recursive_print(ip_tree, 1);

	ip_tree_destroy(&ip_tree);
	return 0;
}


	

