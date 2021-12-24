#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "declarations.h"
//#define LOWER 11
//#define UPPER 89


int writeTreeIntoFile(Position root, positionQ head){
    char fileName[30]={0};
    FILE* fp=NULL;
    positionQ temp=NULL;

    if(root==NULL){
        return -1;
    }

    printf("\nInput file name:\t");
    scanf(" %s", fileName);

    fp=fopen(fileName, "w");
    if(fp==NULL){
        return -2;
    }

    fprintf(fp, "Normal: ");
    InOrderStoreInList(root, head);
    temp=head->next;
    while(temp!=NULL){
        fprintf(fp, "%d ", temp->leafNum);
        temp=temp->next;
    }
    freeList(head);


    fprintf(fp, "\nAfter Replace:");
    root=replace(root, head);
    ReplaceStoreInList(root, head);
    temp=head->next;
    while(temp!=NULL){
        fprintf(fp, "%d ", temp->leafNum);
        temp=temp->next;
    }
    freeList(head);

    fclose(fp);
    return 0;
}

int ReplaceStoreInList(Position root, positionQ head){
    if(root!=NULL){
        if(root->right){
            ReplaceStoreInList(root->right, head);
        }

        SortPush(head, root->num);

        if(root->left){
            ReplaceStoreInList(root->left, head);
        }
    }


    return 0;
}

int InOrderStoreInList(Position root, positionQ head){
    if(root!=NULL){
        if(root->left!=NULL){
            InOrderStoreInList(root->left, head);
        }

        Push(head, root->num);     

        if(root->right!=NULL){
            InOrderStoreInList(root->right, head);
        }
    }

    return 0;
}

Position insertArray(Position root){
    int array[]={2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int i=0;
    Position newElement=NULL;
    for(i=0; i<(sizeof(array)/sizeof(int)); i++){
        newElement=createElemWithNum(array[i]);
        if(newElement==NULL){
            printf("\nUnable to allocate memory!");
            return NULL;
        }
        root=insert(root, newElement);
    }
    return root;
}

Position insert(Position current, Position newEl){
    if(current==NULL){
        current = newEl;
    }
    else if(current->num > newEl->num){
        current->right=insert(current->right, newEl);
    }
    else
        current->left=insert(current->left, newEl);

    return current;
}


Position createElem(){
    Position newEl=NULL;
    int numb=0, check=0;

    printf("Input new element number:\t");
    check=scanf(" %d", &numb);
    if(check!=1){
        printf("Input ERROR!\n");
        return NULL;
    }

    newEl=(Position)malloc(sizeof(cvor));
    if(newEl==NULL){
        printf("Cannot allocate memory!\n");
        return NULL;
    }

    newEl->num=numb;
    newEl->left=NULL;
    newEl->right=NULL;

    return newEl;
}

//mogao sam koristiti jednu funkciju umijesto dvije jako slicne
Position createElemWithNum(int newNumber){
    Position newEl=NULL;

    newEl=(Position)malloc(sizeof(cvor));
    if(newEl==NULL){
        printf("Cannot allocate memory!");
        return NULL;
    }

    newEl->num=newNumber;
    newEl->left=NULL;
    newEl->right=NULL;

    return newEl;
}


Position replace(Position current, positionQ head){
    if(current->left && current->right){
        Push(head, current->left->num);
        current->left=replace(current->left, head);
        Push(head, current->right->num);
        current->right=replace(current->right, head);
        current->num = Pop(head) + Pop(head) + current->right->num + current->left->num;
    }
    else if(current->left){
        Push(head, current->left->num);
        current->left=replace(current->left, head);
        Push(head, 0);
        current->num=Pop(head)+Pop(head)+current->left->num;
    }
    else if(current->right){
        Push(head, 0);
        Push(head, current->right->num);
        current->right=replace(current->right, head);
        current->num=Pop(head)+Pop(head)+current->right->num;
    }
    else{
        Push(head, 0);
        Push(head, 0);
        current->num=Pop(head)+Pop(head);
    }

    return current;
}


int Push(positionQ head, int currentNum){
    positionQ newEl=NULL;

    newEl=(positionQ)malloc(sizeof(queue));
    if(newEl==NULL){
        return -1;
    }

    newEl->next=head->next;
    head->next=newEl;

    newEl->leafNum=currentNum;

    return 0;
}

int SortPush(positionQ head, int currentNum){
    positionQ newEl=NULL;
    positionQ prev=head;
    positionQ post=head->next;

    newEl=(positionQ)malloc(sizeof(queue));
    if(newEl==NULL){
        return -1;
    }

    newEl->leafNum=currentNum;

    while(prev){
        if(prev->next==NULL){
            insertAfter(prev, newEl);
            return 0;
        }
        else if(post->next==NULL){
            if(post->leafNum > currentNum)
                insertAfter(prev, newEl);
            else
                insertAfter(post, newEl);
            return 0;
        }
        else{
            if(prev->leafNum < currentNum  &&  post->leafNum > currentNum){
                insertAfter(prev, newEl);
                return 0;
            }
            else if( prev->leafNum == currentNum  ||  post->leafNum == currentNum){
                insertAfter(prev, newEl);
                return 0;
            }

            prev=prev->next;
            post=post->next;
        }
        
    }
}

int insertAfter(positionQ current, positionQ newElement){
    newElement->next=current->next;
    current->next=newElement;

    return 0;
}

int Pop(positionQ head){
    positionQ temp=NULL;
    int popNum=0;
    if(head->next!=NULL){
        temp=head->next;
        head->next=temp->next;
        popNum=temp->leafNum;
        free(temp);
    }
    return popNum;
}

int freeList(positionQ head){
    positionQ temp=NULL;
    while(head->next){
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }
    return 0;
}

Position freeTree(Position root){
    if(root!=NULL){
        if(root->left!=NULL){
            root->left=freeTree(root->left);
        }
        if(root->right!=NULL){
            root->right=freeTree(root->right);
        }
    }
    free(root);
    return NULL;
}

int InOrderPrint(Position root){
    if(root!=NULL){
        if(root->right!=NULL){
            InOrderPrint(root->right);
        }

        printf(" %d", root->num);

        if(root->left!=NULL){
            InOrderPrint(root->left);
        }
    }
    else{
        printf("The tree is empty!");
    }
    return 0;
}

