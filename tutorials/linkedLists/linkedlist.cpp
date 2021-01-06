/* Linked List Tutorial.
 *
 * This program creates a linked list.
 *
 * I did not do it object oriented to be able to show the data structure's operations.
 * See the comments in the code for a detailed explanation. Have fun =)
 *
 * This file is part of the Estefannie Explains It All repo.
 *
 * (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */


#include <iostream>
using namespace std;

struct Node
{
    string nickname;
    Node *next;
};

Node* traverseList(Node* head, int position)
{
    Node* it = head;
    int counter = 0;

    while (it != NULL)
    {
        if (counter == position)
        {
            return it;
        }

        it = it->next;
        counter++;
    }
    return NULL;
}

// this function inserts a new node into the list. It does not sort the
// list, it places the node in the position you specifiy.
// For example while creating a new list:

// insertNode(head, "melissa", 2) // {melissa}
// insertNode(head, "jimmy", 1) // {melissa, jimmy}
// insertNode(head, "joe", 0) // {joe, melissa, jimmy}
//
// the list will look like = {"joe", "melissa", "jimmy"}
// Jimmy is in position 3 instead of 2 because Joe was
// inserted last and moved all nodes.
void insertNode(Node*& head, string nickname, int position)
{
    Node* it = head;
    int counter = 1;

    // if this is the first node you are adding, the head will be NULL.
    // so we create the first node. Also, if the position of the new node is 0,
    // then it is the first node.
    if(head == NULL || position == 0)
    {
        Node *firstNode = new Node;
        firstNode->nickname = nickname;
        firstNode->next = it;
        head = firstNode;
        return;
    }

    //traverse through the list and add the new node
    //into the position you want it to be.
    while (it->next != NULL)
    {
        if(counter == position)
        {
            Node *newNode = new Node;
            newNode->nickname = nickname;
            newNode->next = it->next;
            it->next = newNode;
            return;
        }
        it = it->next;
        counter++;
    }

    // this places the node at the end of the list if it is empty
    //or if the position of your new node is greater than the size of your list
    Node* lastNode = new Node;
    lastNode->nickname = nickname;
    lastNode->next = NULL;
    it->next = lastNode;
}

void deleteNode(Node* node, int position)
{
    Node* tracker = node;
    Node* previous = node;

    int counter = 0;

    //traverse through the list until we find the
    //position of the node we want to delete
    while(tracker->next != NULL)
    {
        if(counter == position)
        {
            //delete destroys the node
            previous->next = tracker->next;
            delete tracker;
            return;
        }

        previous = tracker;
        tracker = tracker->next;

        counter++;
    }
}

void printList(Node* head)
{
    while (head != NULL)
    {
        cout << head->nickname << endl;
        head = head->next;
    }
    cout << endl;
}

void destroyList(Node*& item)
{
    while(item)
    {
        Node *temp = item;
        item = temp->next;
        delete temp;
    }
}

int main()
{
    //Create the head and point it to NULL since it
    //is the only node at the moment.
    Node *head = NULL;

    //Insert new nodes. Pass the head to traverese the
    //list, the id, nickname and the position you want it in.
    insertNode(head, "Honey Bunny", 4);
    insertNode(head, "Spaceman", 2);
    insertNode(head, "Kool Kat", 3);
    insertNode(head, "Peeping Tom", 5);
    insertNode(head, "Silly Putty", 7);
    insertNode(head, "Kiddo", 1);
    insertNode(head, "Beebop", 6);

    //delete node at position 5
    deleteNode(head, 5);

    printList(head);

    //destroy list when you are done to clean up memory
    destroyList(head);

    return 0;
}

