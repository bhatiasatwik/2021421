#ifndef BigInteger_H_INCLUDED
#define BigInteger_H_INCLUDED

typedef struct node 
{
    int data;
    struct node * next;
}Node;
typedef struct BigInteger
{
    struct node * head;
}bi;
struct BigInteger initialize(char *);
void display(struct BigInteger );
bi add(bi  , bi );
bi sub(bi ,bi) ;
bi div1(bi , bi );
bi mod(bi , bi );
bi mul(bi ,bi);

#endif