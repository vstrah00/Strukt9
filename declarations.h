#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define LOWER 11
#define UPPER 89

struct Stablo;
typedef struct Stablo* Position;
typedef struct Stablo{
    int num;
    Position left;
    Position right;
}cvor;

struct Queue;
typedef struct Queue* positionQ;
typedef struct Queue{
    int leafNum;
    positionQ next;
}queue;

int Push(positionQ head, int currentNum);
int SortPush(positionQ head, int currentNum);
int PushToEnd(positionQ head, int currentNum);
int Pop(positionQ head);
int insertAfter(positionQ current, positionQ newElement);
int freeList(positionQ head);


Position insert(Position current, Position newEl);
//Position replace(Position current, positionQ head);
int replace(Position current);
Position createElem();
Position createElemWithNum(int newNumber);
Position insertArray(Position root);
Position freeTree(Position root);
int InOrderPrint(Position root);
int writeTreeIntoFile(Position root, positionQ head);
int InOrderStoreInList(Position root, positionQ head);
int ReplaceStoreInList(Position root, positionQ head);

#endif