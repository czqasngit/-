//
//  main.c
//  LinkedList
//
//  Created by legendry on 2018/10/13.
//  Copyright © 2018 legendry. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


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
    if(list == NULL || node == NULL || index < 0) return;
    if(list->count == 0) {
        //没有头
        list->head = node;
        list->head->next = NULL;
        list->count ++;
    } else if(index >= list->count ) {
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
void Append(struct LinkedList *list, struct Node *node) {
    Insert(list, node, list->count);
}
//O(n)
struct Node *GetNodeAtIndex(struct LinkedList *list, int index) {
    if (list->count == 0 || index > list->count - 1 || index < 0) return NULL;
    int i = 0 ;
    struct Node *curNode = list->head;
    while (curNode != NULL) {
        if (i == index) {
            break;
        }
        curNode = curNode->next;
        i ++;
    }
    return curNode;
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
void DumpNode(struct Node *node) {
    if (node && node->value) {
        printf("Node: %c\n", node->value);
        return;
    }
    printf("Node is NULL \n");
}
//O(n)
//删除
void RemoveNode(struct LinkedList *list, struct Node *node) {
    if (list == NULL || list->count == 0 || node == NULL) return ;
    struct Node *curNode = list->head;
    struct Node *preNode = NULL;
    while (curNode != NULL) {
        if(curNode->value == node->value) {
            struct Node *next = curNode->next;
            if(preNode == NULL) {
                list->head = next;
            } else {
                preNode->next = next;
            }
            break;
        }
        preNode = curNode;
        curNode = curNode->next;
        
    }
}
struct Node *CreateNewNode(int value) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    memset(node, 0, sizeof(struct Node));
    node->value = value;
    return node;
}
//O(n)
//反转链表
struct LinkedList * ReverseLinkedList(struct LinkedList *list) {
    if(!list) return NULL;
    int count = list->count;
    if(count == 0) return list;
    struct Node *next = list->head;
    struct LinkedList *reverseList = (struct LinkedList *)malloc(sizeof(LinkedList));
    memset(reverseList, 0, sizeof(LinkedList));
    while (next) {
        struct Node *n = CreateNewNode(next->value);
        Append(reverseList, n);
        next = next->next;
    }
    return reverseList;
}
//O(n)
//检测链表中环
struct Node *GetCenterNode(struct LinkedList *list, int *index) {
    if (list == NULL || list->count == 0)  {
        *index = -1;
        return NULL;
    }
    struct Node *centerNode = NULL;
    int centeIndex = 0;
    struct Node *fast = list->head;
    struct Node *slow = list->head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        centeIndex ++;
    }
    *index = centeIndex;
    centerNode = slow;
    return centerNode;
}

void testInsert(){
    struct LinkedList list ;
    memset(&list, 0, sizeof(struct LinkedList));
    Insert(&list, CreateNewNode('A'), 0);
    Insert(&list, CreateNewNode('B'), 1);
    Insert(&list, CreateNewNode('C'), 2);
    DumpList(&list);
    Insert(&list, CreateNewNode('D'), 2);
    DumpList(&list);
    Insert(&list, CreateNewNode('E'), 0);
    DumpList(&list);
    Insert(&list, CreateNewNode('F'), 1);
    DumpList(&list);
    Append(&list, CreateNewNode('G'));
    DumpList(&list);
  
    DumpNode(GetNodeAtIndex(&list, -1));
    DumpNode(GetNodeAtIndex(&list, 0));
    DumpNode(GetNodeAtIndex(&list, 1));
    DumpNode(GetNodeAtIndex(&list, 6));
    DumpNode(GetNodeAtIndex(&list, 7));
    DumpNode(GetNodeAtIndex(&list, 4));
}
void testRemove() {
    struct LinkedList list ;
    memset(&list, 0, sizeof(struct LinkedList));
    Insert(&list, CreateNewNode('A'), 0);
    Insert(&list, CreateNewNode('B'), 1);
    Insert(&list, CreateNewNode('C'), 2);
    DumpList(&list);
    Insert(&list, CreateNewNode('D'), 2);
    DumpList(&list);
    Insert(&list, CreateNewNode('E'), 0);
    DumpList(&list);
    Insert(&list, CreateNewNode('F'), 1);
    DumpList(&list);
    Append(&list, CreateNewNode('G'));
    DumpList(&list);
    printf("删除 \n");
    RemoveNode(&list, CreateNewNode('C'));
    DumpList(&list);
    RemoveNode(&list, CreateNewNode('E'));
    DumpList(&list);
    RemoveNode(&list, CreateNewNode('G'));
    DumpList(&list);
}

void testReverse() {
    struct LinkedList list ;
    memset(&list, 0, sizeof(struct LinkedList));
    Insert(&list, CreateNewNode('A'), 0);
    Insert(&list, CreateNewNode('B'), 1);
    Insert(&list, CreateNewNode('C'), 2);
    Insert(&list, CreateNewNode('D'), 2);
    Insert(&list, CreateNewNode('E'), 0);
    Insert(&list, CreateNewNode('F'), 1);
    Append(&list, CreateNewNode('G'));
    DumpList(&list);
    printf("反转 \n");
    struct LinkedList * reverseList = ReverseLinkedList(&list);
    DumpList(reverseList);
    free(reverseList);
}

void testGetCenter() {
    struct LinkedList list ;
    memset(&list, 0, sizeof(struct LinkedList));
    Insert(&list, CreateNewNode('A'), 0);
    Insert(&list, CreateNewNode('B'), 1);
    Insert(&list, CreateNewNode('C'), 2);
    Insert(&list, CreateNewNode('D'), 2);
    Insert(&list, CreateNewNode('E'), 0);
    Insert(&list, CreateNewNode('F'), 1);
    Append(&list, CreateNewNode('G'));
    Append(&list, CreateNewNode('F'));
    Append(&list, CreateNewNode('X'));
    Append(&list, CreateNewNode('M'));
    DumpList(&list);
    int centeIndex = -1;
    struct Node *centerNode = GetCenterNode(&list, &centeIndex);
    printf("中点: %c -- %d \n", centerNode->value, centeIndex);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
//    testInsert();
//    testRemove();
//    testReverse();
    testGetCenter();
    return 0;
}

