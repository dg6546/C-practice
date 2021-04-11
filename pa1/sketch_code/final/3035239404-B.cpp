#include "ListNode.h"
#include <iostream>
#include <string>
#include <sstream>

ListNode * SolveB(int n){
    /* your code starts here */
    //construct a list accrording to input
    int inp;
    ListNode *head = new ListNode(-1);
    ListNode *last = new ListNode(-1);
	for(int i = 0; i < n; i++){
		cin >> inp;
		ListNode *temp = new ListNode(inp);
		if(i == 0){
			head = temp;
			last = temp;
		}else{
			last->next = temp;
			last = temp;
		}
	}
    //rearrange the list
	if (head == NULL){
		return NULL;
	}

	ListNode *odd = head;
	ListNode *even = head->next;
	ListNode *evenFirstNode = even;

	while(true){
		if(!odd || !even || !(even->next)){
			odd->next = evenFirstNode;
			break;
		}
		odd->next = even->next;
		odd = even->next;
		if(odd->next == NULL){
			even->next = NULL;
			odd->next = evenFirstNode;
			break;
		}
		even->next = odd->next;
		even = odd->next;
	}
	return head;
}