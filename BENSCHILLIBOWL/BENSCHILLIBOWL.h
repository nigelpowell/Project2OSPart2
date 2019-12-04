#ifndef LAB3_BENSCHILLIBOWL_H_
#define LAB3_BENSCHILLIBOWL_H_

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef char* MenuItem;
typedef struct OrderStruct 
{
    MenuItem menu_item;
    int customer_id;
    int order_number;
    struct OrderStruct *next;
} Order;
typedef struct Restaurant 
{
    Order* orders;
    int current_size;
    int max_size;
    int next_order_number;
    int orders_handled;
	int expected_num_orders;
    pthread_mutex_t mutex;
    pthread_cond_t can_add_orders, can_get_orders;
} BENSCHILLIBOWL;

MenuItem PickRandomMenuItem();
BENSCHILLIBOWL* OpenRestaurant(int max_size, int expected_num_orders);
void CloseRestaurant(BENSCHILLIBOWL* mcg);
int AddOrder(BENSCHILLIBOWL* mcg, Order* order);
Order *GetOrder(BENSCHILLIBOWL* mcg);

#endif  
