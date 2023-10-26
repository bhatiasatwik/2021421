#include "BigInteger.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//-----------------------------------------------------------------------------------
void addToHead(struct node ** head, int data)
{
        struct node * curr=(struct node*)malloc(sizeof(struct node));
        curr->data=data;
        curr->next=*head;
        *head=curr;
        return;

}
void addToTail(struct node **head,char k)
{
    struct node * current=(struct node*)malloc(sizeof(struct node));
    current->data=k;
    current->next=NULL;
    if(*head==NULL)
    {
        *head=current;
        return;
    }
    struct node *itr=*head;
    while(itr->next!=NULL)
    {
        itr=itr->next;
    }
    itr->next=current;
}
struct BigInteger  initialize(char *s)
{
    struct BigInteger temp;
    struct node * curr=NULL;
    for(int i=0;s[i]!='\0';i++)
    {
        addToTail(&curr,s[i]-48);
    }
    temp.head=curr;
    return temp;
}
void display(struct BigInteger pass)
{
    struct node * itr=pass.head;
    while(itr!=NULL)
    {
        printf("%d",itr->data);
        itr=itr->next;
    }
    printf("\n");
}
struct node * reverse(struct node * head)
{
    struct node *prev=NULL,* temp=NULL;
    while(head!=NULL)
    {
        temp=head->next;
        head->next=prev;
        prev=head;
        head=temp;
    }
    return prev;
}
struct node *createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node *));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
int length(bi a)
{
    int l=0;
    struct node * itr=a.head;
    while(itr!=NULL)
    {
        l++;
        itr=itr->next;
    }
    return l;
}
//-----------------------------------------------------------------------------------
bi add(bi a , bi b)
{
    if(a.head==NULL)
        return b;
        
    if(b.head==NULL)
        return a;
    struct node* h1=a.head;
    struct node* h2=b.head;
    struct node *res= NULL,*itr = NULL;
    int carry = 0,sum=0,digit=0;
    struct node *l1=reverse(h1);
    struct node *l2=reverse(h2);
    struct node *t1=l1,*t2=l2;
    while(l1!= NULL && l2!= NULL) 
    {
        digit=l1->data+l2->data+carry;
        sum=digit%10;
        carry=digit/10;
        l1=l1->next;
        l2=l2->next;
        if(res==NULL)
        {
            res=createNode(sum);
            itr=res;
        }
        else
        {
            itr->next=createNode(sum);
            itr=itr->next;
        }
    }
    while(l1!=NULL)
    {
        sum=(l1->data+carry)%10;
        itr->next=createNode(sum);
        itr=itr->next;
        carry=(l1->data+carry)/10;
        l1=l1->next;
    }
    while(l2!=NULL)
    {
        sum=(l2->data+carry)%10;
        itr->next=createNode(sum);
        itr=itr->next;
        carry=(l2->data+carry)/10;
        l2=l2->next;
    }
    if(l1==NULL && l2==NULL)
    {
        if(carry!=0)
        {
            itr->next=createNode(carry);
            itr=itr->next;
        }
        itr->next=NULL;
    }
     reverse(t1);
     reverse(t2);
     bi answer;
     answer.head=res;
     answer.head=reverse(answer.head);
    return (answer);
}
//-------------------------------------------------------------------------------------------------------------
bi sub(bi a,bi b)
{
    if(a.head==NULL)
        return b;
        
    if(b.head==NULL)
        return a;
    struct node* h1=a.head;
    struct node* h2=b.head;
    struct node *res= NULL,*itr = NULL;
    int debt=0,diff=0;
    struct node *l1=reverse(h1);
    struct node *l2=reverse(h2);
    struct node *t1=l1,*t2=l2;
    while(l1!= NULL)
    {
        int dig=0;
        if(l2!=NULL)
        {
            dig=l2->data;
        }
        if(l1->data+debt>=dig)
        {
            diff=l1->data-dig+debt;
            debt=0;
        }
        else 
        {
           diff=10+l1->data-dig+debt;
           debt=-1;
        }
       if(res==NULL)
        {
            res=createNode(diff);
            itr=res;
        }
        else
        {
            itr->next=createNode(diff);
            itr=itr->next;
        }
        l1=l1->next;
        if(l2)
            l2=l2->next;
    }
    reverse(t1);
    reverse(t2);
    bi answer;
    answer.head=res;
    answer.head=reverse(answer.head);
     while(answer.head!=NULL&&(answer.head)->data==0)
    {
        struct node *temp=answer.head;
         answer.head=(answer.head)->next;
         free(temp);
    }
     if(answer.head==NULL)
     {
         answer.head=createNode(0);
         return answer;
     }
    return (answer);
}
//------------------------------------------------------------------------------------------------------------
int compare(bi a , bi b)
{
    if(length(a)>length(b))
    {
        return 1;
    }
    if(length(a)<length(b))
    {
        return -1;
    }
    struct node * h1=a.head;
    struct node * h2=b.head;
    while(h1!=NULL)
    {
        if(h1->data>h2->data)
        {
            return 1;
        }
        else if (h1->data<h2->data)
        {
            return -1;
        }
        h1=h1->next;
        h2=h2->next;
    }
    return 0;
}
bi div1(bi a, bi b)
{
    bi ans;
    if(compare(a,b)==0)
    {
        ans.head=createNode(1);
        return ans;
    }
    if(compare(a,b)==-1)
    {
        ans.head=createNode(0);
        return ans;
    }
    if(a.head->data==0&&a.head->next==NULL)
    {
        ans.head=createNode(0);
        return ans;
    }
    if(b.head->data==0&&b.head->next==NULL)
    {
        ans.head=createNode(-1);
        return ans;
    }
    
    bi cntr;
    cntr.head=createNode(0);
    bi adder;
    adder.head=createNode(1);
    bi res=a;
    do{
        res=sub(res,b);
       cntr= add(cntr,adder);
    }while(compare(res,b)!=-1);
    ans.head=cntr.head;
    return ans;
}
bi mod(bi a, bi b)
{
    bi ans;
    if(compare(a,b)==0)
    {
        ans.head=createNode(0);
        return ans;
    }
    if(compare(a,b)==-1)
    {
        return a;
    }
    if(a.head->data==0&&a.head->next==NULL)
    {
        ans.head=createNode(0);
        return ans;
    }
    if(b.head->data==0&&b.head->next==NULL)
    {
        ans.head=createNode(-1);
        return ans;
    }
    
    bi cntr;
    cntr.head=createNode(0);
    bi adder;
    adder.head=createNode(1);
    bi res=a;
    do{
        res=sub(res,b);
       cntr= add(cntr,adder);
    }while(compare(res,b)!=-1);
    ans.head=cntr.head;
    return res;
}
// //-------------------------------------------------------------------------
void insert(Node** head, int val) {
     Node* new = createNode(val);
    if (*head == NULL) {
        *head = new;
         return ;
    }
     Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
}
int rev(struct node** head)
{
    int len=0;
	 Node* prev = NULL,*forward,*curr=*head;
	while (curr!=NULL) {
		len++;
		forward=curr->next;
		curr->next=prev;
		prev=curr;
		curr=forward;
	}
	*head=prev;
	return len;
}
Node* newlist(int size)
{  
	 Node* head = NULL;
	while (size--)
	{
		insert(&head,0);
	}
	return head;
}
 Node* multiply( Node* first, Node* second ,int n,int m,char operation,bi z)
{
    int tmpL=m+n+1;
	 Node* result=newlist(tmpL);
	 Node *ptr2 = second,*resptr1=result,*resptr2,*ptr1;
	while (ptr2!=NULL) {
		int carry = 0;
		resptr2 = resptr1;
		ptr1 = first;
		while (ptr1!=NULL) 
        {
			int mul = ptr1->data * ptr2->data+ carry;
			resptr2->data += mul % 10;
			carry = mul / 10 + resptr2->data / 10;
			resptr2->data = resptr2->data % 10;
			ptr1 = ptr1->next;
			resptr2 = resptr2->next;
		}
		if (carry > 0) {
			resptr2->data += carry;
		}
		resptr1 = resptr1->next;
		ptr2 = ptr2->next;
	}
	  rev(&result);
	 while (!result->data != 0) {
	 	struct node* temp = result;
	 	result = result->next;
	 	free(temp);
	 }
	return result;
}
struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger result;
   if(a.head->data==0&&a.head->next==NULL||b.head->data==0&&b.head->next==NULL)
   {
    result.head=createNode(0);
    return result;
   }
    struct node *second= reverse(b.head);
    struct node * first=reverse(a.head);
    b.head=second;
    a.head=first;
    result.head=multiply(first,second,length(a),length(b),'*',result);
    a.head=reverse(first);
    b.head= reverse(second);
    return result;
}
