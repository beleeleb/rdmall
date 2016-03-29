#include "rec_bin_tree_2.h"
#include "tree_ip.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <arpa/inet.h>

struct ip_node 
{
    int flag;
    struct ip_node* left;
    struct ip_node* right; 
};

static ip_node_t* make_ip_node()
{
	ip_node_t* new_node = NULL;
	new_node = (ip_node_t*)malloc(sizeof(ip_node_t));
    assert(new_node);
    memset(new_node, 0, sizeof(ip_node_t));
	new_node->flag = 0;
    new_node->left = NULL;
    new_node->right = NULL;
	return new_node;
}

ip_node_t* ip_tree_create(void)
{	
	ip_node_t* ip_root = NULL;
	ip_root = make_ip_node();
	return ip_root;
}

static void ip_node_destroy(ip_node_t* node)
{
    assert(node);
    memset(node, 0, sizeof(ip_node_t));
    free(node);
    node = NULL;
}

static void destroy_traverse(ip_node_t* root)
{
    if(root!=NULL)
    {
        destroy_traverse(root->left);
        destroy_traverse(root->right);
        ip_node_destroy(root);
    }
}

void ip_tree_destroy(ip_node_t** root)
{
    destroy_traverse(*root);
    root = NULL;
} 

ip_t get_next_ip(ip_node_t* root)
{
	return get_ip_requested(root , "1.8.2.1");
}

static unsigned int ip_to_int (ip_t ips)
{
	int i = 0;
	ip_t ip = ips;
      	
    unsigned int v = 0;
  
    ip_t start = NULL;

    start = ip;
    for (i = 0; i < 4; i++) {
        char c;
        int n = 0;
        while (1) {
            c = * start;
            start++;
            if (c >= '0' && c <= '9') {
                n *= 10;
                n += c - '0';
            }
          
            else if ((i < 3 && c == '.') || i == 3) {
                break;
            }
            else {
                return 0;
            }
        }
        if (n >= 256) {
            return 0;
        }
        v *= 256;
        v += n;
    }
    return v;
}


static unsigned int* rec_ip2(ip_node_t* root, unsigned int *ip_num, int mask)
{
	unsigned int i = 0x80;
	ip_node_t* node = NULL;
	

	if(mask != 8)
	{
		if(!(*ip_num & (i >> mask)))
		{
			
			if(root->left == NULL)
			{
				node = make_ip_node();
				root->left = node;
			}

			if(root->left->flag == 1)
			{
				*ip_num = *ip_num ^ (i >> mask);
				
				rec_ip2(root, ip_num, mask);	
			}

			else
			{
				rec_ip2(root->left, ip_num, mask + 1);
			}	
		}

		else
		{

			if(root->right == NULL)
			{
				node = make_ip_node();
				root->right = node;
			}

			if(root->right->flag == 1)
			{
				*ip_num = *ip_num ^ (i >> mask);
				
				rec_ip2(root, ip_num, mask);
			}

			else
			{
				rec_ip2(root->right, ip_num, mask + 1);
			}	

		}

		if(root->left != NULL && root->right != NULL && root->left->flag == 1 && root->right->flag == 1)
		{
			root->flag = 1;
		}

	} else root->flag = 1;

	return ip_num;
}

static ip_t return_ip(unsigned int num_ip)
{
  char result[16];

  sprintf(result, "%d.%d.%d.%d",
    (num_ip >> 24) & 0xFF,
    (num_ip >> 16) & 0xFF,
    (num_ip >>  8) & 0xFF,
    (num_ip      ) & 0xFF);

  return result;
}

void recursive_print(ip_node_t* curr, size_t level)
{
    size_t lvl = level;
    
    if (curr->right) 
    {
        recursive_print(curr->right,level+1);
        while (--lvl) printf("    ");
        printf("  /  \n");
    }
    
       lvl = level; 
       while (--lvl) printf("    ");
       printf("%d\n", curr->flag);
       lvl = level; 
       
       if (curr->left) 
       {
           while (--lvl) printf("    ");
        printf("  \\  \n");
           recursive_print(curr->left,level+1);           
       }
}


ip_t get_ip_requested(ip_node_t* root ,ip_t ip)
{
	unsigned int result = 0;
	unsigned int *temp_num = 0;
	
	result = ip_to_int(ip);

	if(result == 0 || result == 0xffffffff)
	return 0;
	
	if(result & 0x80 >> 0)
	{
		root->flag = 1;
	}

	temp_num = rec_ip2(root, &result, 1);
	printf("-----");
	printf("new_ip : %s\n", return_ip(*temp_num));
	return return_ip(0);
}

static int rel_ip(ip_node_t* root, unsigned int ip_num, int mask)
{
	int i = 0;
	if(mask != 8)
	{
		if(!(ip_num & (i >> mask)))
		{
			if(root->left->flag == 1)
			{
				ip_num = ip_num ^ (i >> mask);
				
				rec_ip2(root, ip_num, mask);	
			}

			else
			{
				rec_ip2(root->left, ip_num, mask + 1);
			}	
		}

		else
		{
			if(root->right->flag == 1)
			{
				ip_num = ip_num ^ (i >> mask);
				
				rec_ip2(root, ip_num, mask);
			}

			else
			{
				rec_ip2(root->right, ip_num, mask + 1);
			}	
		}
	}
}


int release_ip(ip_node_t* root ,ip_t ip)
{
	unsigned int ip_num = 0;
	ip_num = ip_to_int(ip);

	if(ip_num == 0 || ip_num == 0xffffffff)
	return 0;

	if(ip_num * 0x80 >> 0)
	{
		root->flag = 0;
	}
	
	rel_ip(root, ip_num, 1);
}




