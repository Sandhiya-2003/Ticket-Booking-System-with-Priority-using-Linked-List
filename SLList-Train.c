/*Name : Sandhiya.S
  Reg No. : 2021503552*/

/*PROBLEM STATEMENT : Serving of prioritised ticket booking queue using linked list

Priorities entering into the queue are
				~ Tatkal irrespective of the date and no of passengers 
						*End of last tatkal booking passenger*
				~ Bulk booking more than 10 passengers irrespective of the date
                        *End of queue*
				~ Normal booking less than 10 passengers earlier date first after - last tatkal person
				
NOTE : Unlike queue implementation last in is not followed. 
    Insertion into the booking queue will be based on the above business logic like 
	entry in front of queue , end of queue or middle of queue
*/

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int pno,dd,mm,yyyy,nop,tatkal;
    struct node *next;
};

struct node *front = NULL, *rear = NULL;


void insertEnd(int pno, int dd, int mm, int yyyy, int nop,int tatkal)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->pno = pno;
    newNode->dd = dd;
    newNode->mm = mm;
    newNode->yyyy = yyyy;
    newNode->nop = nop;
    newNode->tatkal = tatkal;
    newNode->next = NULL;
    if(front == NULL && rear == NULL)
        front = rear = newNode;
    else
    {
        printf("%d\n",rear->dd);
        rear->next = newNode;
        rear = newNode;
    }
}

void insertTatkal(int pno, int dd, int mm, int yyyy, int nop,int tatkal)
{
    struct node *newNode = malloc(sizeof(struct node));
    struct node *temp = front;
    struct node *beforeNode;
    newNode->pno = pno;
    newNode->dd = dd;
    newNode->mm = mm;
    newNode->yyyy = yyyy;
    newNode->nop = nop;
    newNode->tatkal = tatkal;
    newNode->next = NULL;
    if(front == NULL && rear == NULL)
        front = rear = newNode;
    else
    {
		temp = front;
		beforeNode = temp;
		while(temp)
		{
			if(temp->tatkal==0) break;
			beforeNode=temp;
			temp = temp->next;
		}
		if(temp == front)
		{
			newNode->next = beforeNode;
			front = newNode;
			return;
		}
        newNode->next = beforeNode->next;
        beforeNode->next = newNode;
        
    }
}

void insertBefore(int pno,int dd,int mm, int yyyy,int nop,int tatkal)
{
    struct node *newNode = malloc(sizeof(struct node));
    struct node *temp = front;
    struct node *beforeNode;
   	long int qdate,bdate;


    if(front == NULL && rear == NULL)
        {
        	front = rear = newNode;
			newNode->pno = pno;
		    newNode->dd = dd;
		    newNode->mm = mm;
		    newNode->yyyy = yyyy;
		    newNode->nop = nop;
		    newNode->tatkal = tatkal;
        	newNode->next = NULL;
        	return;
		}
    while(temp)
    {
    	qdate = temp->yyyy*10000+temp->mm*100+temp->dd;
    	bdate = yyyy*10000+mm*100+dd;
        if(qdate > bdate && temp->tatkal == 0)
        {
			newNode->pno = pno;
		    newNode->dd = dd;
		    newNode->mm = mm;
		    newNode->yyyy = yyyy;
		    newNode->nop = nop;
		    newNode->tatkal = tatkal;
    		newNode->next = beforeNode->next;
    		printf("Before Node %d\n",beforeNode->dd);
    		beforeNode->next = newNode;
    		return;
		}
		beforeNode = temp;
        temp = temp->next;
    }
    temp = beforeNode;
    temp->next = newNode;
	newNode->pno = pno;
    newNode->dd = dd;
    newNode->mm = mm;
    newNode->yyyy = yyyy;
    newNode->nop = nop;
    newNode->tatkal = tatkal;
   	newNode->next = NULL;
}


int removeFirst()
{
    struct node *temp;
    int pno,spno;

    if(front != NULL)
    {
        temp = front;
        pno = temp->pno;
        front = front->next;
        if(front == NULL)
            rear = NULL;
       free(temp);
       return pno;
    }
}

void displayQueue()
{
    struct node *temp = front;
	printf("\nBooking Queue is : \n");
    while(temp)
    {
        printf("%d - %d/%d/%d - %d Persons - Tatkal - ",temp->pno,temp->dd,temp->mm,temp->yyyy,temp->nop);
        if(temp->tatkal == 1) 
          printf("Yes\n");
        else
          printf("No\n");
        temp = temp->next;
    }
    printf("*\nEnd of Queue*\n");
}

int main()
{
	int pno=1,spno,dd,mm,yyyy,nop,tatkal,choice;
	while (1)
	{
		printf("\nChoice : \n");
		printf("1 -> Queue Add\n");
		printf("     Priority :\n");
		printf("     Tatkal at Front\n");
		printf("     Earlier Date First\n");
		printf("     Bulk Booking > 10 Passengers Last in Queue\n");
		printf("2 -> Serve Queue at First Node\n");
		printf("3 -> Display Queue\n");
		printf("4 -> Exit Program\n");
		printf("\nEnter a choice : ");
	    scanf("%d",&choice);
	    switch(choice)
	    {
            case 1:
                {
                	printf("Enter Tatkal(1) or Not (0) : ");
                	scanf("%d",&tatkal);
                	printf("Enter Date of Journey dd mm yyyy : ");
                	scanf("%d %d %d",&dd,&mm,&yyyy);
                	printf("Enter No. of Passengers : ");
                	scanf("%d",&nop);
                	
                	if (nop > 10 && tatkal == 0)
                	{
	                	insertEnd(pno,dd,mm,yyyy,nop,tatkal);
	                	pno = pno + 1;
	                }
                	
                	if (tatkal == 1)
                	{
	                	insertTatkal(pno,dd,mm,yyyy,nop,tatkal);
	                	pno = pno + 1;
	                }

                	if (nop <= 10 && tatkal == 0)
                	{
	                	insertBefore(pno,dd,mm,yyyy,nop,tatkal);
	                	pno = pno + 1;
	                }
                    break;
                }
            case 2:
                {
    				spno = removeFirst();
    				if(spno!= -1) printf("\nPassenger Served PNO = %d\n",spno);
	                break;
                }
            case 3:
				{
	   				displayQueue();
	                break;
				}
            case 4:
				{
	   				return;
	                break;
				}
	
	        }
	
		}
 
    return 0;
}
