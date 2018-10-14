//
//  main.c
//  LinkedList
//
//  Created by legendry on 2018/10/13.
//  Copyright © 2018 legendry. All rights reserved.
//

#include <stdio.h>

struct Node {
    //下一个节点
    struct Node *next;
    //节点值
    char value;
}Node;

struct LinkedList {
    struct Node *head;
    int count;
}LinkedList;

//找到单链表的尾巴节点
//O(n)
struct Node *GetTrail(struct LinkedList *list) {
    if(list == NULL || list->count == 0) return NULL;
    struct Node *curNode = list->head;
    while (curNode->next != NULL) {
        curNode = curNode->next;
    }
    return curNode;
}
//O(n)
void Insert(struct LinkedList *list, struct Node *node, int index) {
    if(list == NULL) return;
    if(list->count == 0) {
        //没有头
        list->head = node;
        list->head->next = NULL;
        list->count ++;
    } else if(index >= list->count) {
        //插入到尾巴
        struct Node *trail = GetTrail(list);
        trail->next = node;
        list->count ++;
    } else if(index == 0){
        node->next = list->head;
        list->head = node;
        list->count ++;
    } else {
        struct Node *curNode = list->head;
        int curIndex = 0;
        while (curIndex != index - 1) {
            curNode = curNode->next;
            curIndex ++;
        }
        node->next = curNode->next;
        curNode->next = node;
        list->count ++;
    }
}
//O(n)
void DumpList(struct LinkedList *list) {
    if(list == NULL || list->count == 0) return;
    struct Node *curNode = list->head;
    int curIndex = 0;
    do {
        printf("(%d,%c)->", curIndex, curNode->value);
        curNode = curNode->next;
        curIndex ++;
    }while (curNode != NULL);
    printf("NULL \n");
}

struct Node *CreateNewNode(int value) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    memset(node, 0, sizeof(struct Node));
    node->value = value;
    return node;
}
void testInsert(){
    struct LinkedList list ;
    memset(&list, 0, sizeof(struct LinkedList));
    Insert(&list, CreateNewNode('A'), 0);
    Insert(&list, CreateNewNode('B'), 1);
    Insert(&list, CreateNewNode('C'), 2);
    DumpList(&list);
    Insert(&list, CreateNewNode('D'), 3);
    DumpList(&list);
    Insert(&list, CreateNewNode('E'), 0);
    DumpList(&list);
    Insert(&list, CreateNewNode('F'), 1);
    DumpList(&list);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    testInsert();
    return 0;
}

