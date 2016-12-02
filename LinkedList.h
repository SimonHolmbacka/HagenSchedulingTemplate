#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
#include "metadata.h"
#include "fixdata.h"

using namespace std;

class list
{
public:
    struct node {
        int id;
        string name;
        MetaData metadata;
        FixData fixdata;
        struct node *next;
    } *head, *tail, *ptr;

    list():head(NULL),tail(NULL){
        nr_items = 1;
    }	// constructor
    ~list();			// destructor

    struct list::node* searchName(struct list::node*, string);
    struct list::node* searchId(struct list::node*, int);
    struct list::node* initNode(string, int);
    struct list::node* peekFirst();
    struct list::node* popFirst();

    void reverse();
    void addNode( struct list::node*);
    void addLast( struct list::node*);
    void deleteNode( struct list::node*);
    void deleteList( struct list::node*);
    void displayList( struct list::node*)const;
    void displayNode( struct list::node*)const;

    void incItems();
    void decItems();
    int getNrItems();

private:
    int nr_items;

};
#endif // LINKEDLIST_H
