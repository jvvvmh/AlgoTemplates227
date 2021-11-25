#include <bits/stdc++.h>

using namespace std;

class SinglyLinkedListNode {
    public:
        int data;
        SinglyLinkedListNode *next;
}

SinglyLinkedListNode* removeNodes(SinglyLinkedListNode* listHead, int x) {
    SinglyLinkedListNode * res = listHead;
    while (res && res->data > x){
        res = res->next;
    }
    if (!res){
        return nullptr;
    }
    SinglyLinkedListNode * tmp = res;
    while (tmp->next){
        if (tmp->next->data <= x){
            tmp = tmp->next;
        }
        else{
            tmp->next = (tmp->next)->next;
        }
    }
    return res;
}