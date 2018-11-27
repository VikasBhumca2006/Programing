#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<stack>
#include<queue>
#include<list>
#include<stdlib.h>
struct node
{
    int data;
    struct node* next;
};
 

void push(struct node** head_ref, int new_data)
{
    struct node* new_node =
            (struct node*) malloc(sizeof(struct node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);    
    (*head_ref)    = new_node;
}
 
void printList(struct node *head)
{
    struct node *temp = head;
    while(temp != NULL)
    {
        printf("%d  ", temp->data);    
        temp = temp->next;  
    }
}    
node * reverse(node *h)
{
  node *p=h,*q,*r;
  if(p==NULL || p->next==NULL) return p;
  q=p->next;
  p->next=NULL;
  while(q!=NULL)
  {
    r=q->next;
    q->next =p;
    p=q;
    q =r ;
  }
  return p;
} 
int main()
{
    struct node* head = NULL;
     push(&head, 20);
     push(&head, 4);
     push(&head, 15); 
 //    push(&head, 85);      
     printList(head);    
     head = reverse(head);                      
     printf("\n Reversed Linked list \n");
     printList(head);    
     getchar();
}
