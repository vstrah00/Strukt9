#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "declarations.h"

int main(){
    Position root=NULL;
    Position extra=NULL;
    queue headOfQ={.leafNum=0, .next=NULL};
    positionQ head=&headOfQ;
    int check=0, checkScan;
    int comNum=0;
    int randomNum=0;
    srand(time(NULL));

    while(1){
        printf("\n1. Insert"
                "\n2. Insert random"
                "\n3. Inorder print to screen"
                "\n4. Replace"
                "\n5. Wipe memory"
                "\n6. Write Tree Into File"
                "\n7. Exit");
        if(root==NULL){
        printf("\n8. Insert hardcoded array(2, 5, 7, 8, 11, 1, 4, 2, 3, 7)");
        }
        printf("\nInput command number:\t");
        checkScan=scanf(" %d", &comNum);
        printf("----------------------------------\n");
        if(checkScan!=1){
            printf("Input ERROR!\n");
            root=freeTree(root);
            return 0;
        }
        switch(comNum){
            case 1: 
                extra=createElem();
                if(extra==NULL){
                    root=freeTree(root);
                    return -1;
                }
                root=insert(root, extra);
                break;
            case 2:
                randomNum = (rand() % (UPPER - LOWER + 1)) + LOWER;
                extra=createElemWithNum(randomNum);
                if(extra==NULL){
                    root=freeTree(root);
                    return -1;
                }
                root=insert(root, extra);
                break;
            case 3:
                InOrderPrint(root);
                break;
            case 4:
                if(root==NULL){
                    printf("\nThe tree is empty!");
                }
                else
                    root=replace(root, head);
                break;
            case 5:
                root=freeTree(root);
                break;
            case 6:
                check=writeTreeIntoFile(root, head);
                if(check<0){
                    printf("Writing to file error!\n");
                }
                else{
                    root=freeTree(root);
                    printf("Tree succesfully stored! Memory wiped.\n");
                }
                break;
            case 7:
                root=freeTree(root);
                return 0;
                break;
            case 8:
                if(root==NULL){
                    root=insertArray(root);
                    if(root==NULL){
                        return -1;
                    }
                }
                else
                    printf("Wrong command input!\n");
                break;
            default:
                printf("Wrong command input!\n");
                break;
        }
    }

    return 0;
}
