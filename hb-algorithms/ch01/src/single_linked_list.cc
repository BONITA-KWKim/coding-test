#include "single_linked_list.hh"

Node *CSingleLinkedList::create_SLL_node(NodeData *data) {
	Node *new_node =NULL;
	new_node = (Node *)malloc(sizeof(Node));
	memcpy(&new_node->data_element, data, sizeof(new_node->data_element));
	new_node->next_node = NULL;

	return new_node;
}

void CSingleLinkedList::destroy_SLL_node(Node *node) {
	free(node);
}

void CSingleLinkedList::append_SLL_node(Node **head, Node *new_node) {
	/* empty SLL */
	if (NULL == *head) {
		*head = new_node;
	} else {
		/* find tail */
		Node *tail = *head;
		while (NULL != tail->next_node) {
			tail = tail->next_node;
		} //while ()

		/* append new node */
		tail->next_node = new_node;
	}
}

int CSingleLinkedList::remove_SLL_node(Node **head, Node *target_node) {
	return 0;
}

int CSingleLinkedList::search_SLL_node(Node **head, Node *target_node) {
	return 0;
}

int CSingleLinkedList::insert_after_SLL_node(Node **head, Node *new_node) {
	return 0;
}

int CSingleLinkedList::insert_before_SLL_node(Node **head, Node *new_node) {
	return 0;
}

Node *CSingleLinkedList::get_SLL_node(Node **head, int position) {
	return NULL;
}

int CSingleLinkedList::get_position_SLL_node(Node **head, Node *target_node){
	return 0;
}
