#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "BENSCHILLIBOWL.h"
#define BENSCHILLIBOWL_SIZE 4
#define NUM_CUSTOMERS 6
#define NUM_COOKS 2
#define ORDERS_PER_CUSTOMER 2
#define EXPECTED_NUM_ORDERS NUM_CUSTOMERS * ORDERS_PER_CUSTOMER

BENSCHILLIBOWL *bcb;
void* BENSCHILLIBOWLCustomer(void* tid) 
{
    int customer_id = (int)(long) tid;
  
    for (int i = 0; i < ORDERS_PER_CUSTOMER; i++)
    {
      Order *order = (Order*) malloc(sizeof(Order));
      MenuItem menu_item = PickRandomMenuItem();
      order->customer_id = customer_id;
			order->menu_item = menu_item;
      order->next = NULL;
      int order_number = AddOrder(bcb, order);
      printf("Customer #%d added order #%d\n", customer_id, order_number);
    }
    return NULL;
}


void* BENSCHILLIBOWLCook(void* tid)
{
    int cook_id = (int)(long) tid;
    int orders_fulfilled = 0;
    Order *order;
    order = GetOrder(bcb);
    while(order != NULL)
    {
      free(order); 
      orders_fulfilled += 1;
      order = GetOrder(bcb);
    }
    
    printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled);
    return NULL;
}
int main() 
{
    bcb = OpenRestaurant(BENSCHILLIBOWL_SIZE, EXPECTED_NUM_ORDERS);
    pthread_t customers[NUM_CUSTOMERS];
    int customer_id[NUM_CUSTOMERS];
  
    for(int i = 0; i < NUM_CUSTOMERS; i++)
    {
      customer_id[i] = i+1;
      pthread_create(&(customers[i]), NULL, BENSCHILLIBOWLCustomer, &(customer_id[i]));
    }
    
    pthread_t cooks[NUM_COOKS];
    int cook_id[NUM_COOKS];
    for (int i = 0; i < NUM_COOKS; i++)
    {
      cook_id[i] = i+1;
      pthread_create(&(cooks[i]), NULL, BENSCHILLIBOWLCook, &(cook_id[i]));
    }
    for(int i = 0; i< NUM_CUSTOMERS; i++)
    {
      pthread_join(customers[i], NULL);
    }
    for (int i = 0; i< NUM_COOKS; i++)
    {
      pthread_join(cooks[i], NULL);
    }
    CloseRestaurant(bcb);
    return 0;
}
