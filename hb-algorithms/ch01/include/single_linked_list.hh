#ifndef __SINGLE_LINKED_LIST_HH__
#define __SINGLE_LINKED_LIST_HH__

#include <cstdlib>
#include <cstring>

typedef struct tagNodeData {
	int data;
} NodeData;

typedef struct tagNode {
	NodeData data_element;
	struct tagNode *next_node;
} Node;

class CSingleLinkedList {
public:
	CSingleLinkedList(){};
	~CSingleLinkedList(){};

	Node *create_SLL_node(NodeData *data);
	void destroy_SLL_node(Node *node);
	void append_SLL_node(Node **head, Node *new_node);
	int remove_SLL_node(Node **head, Node *target_node);
	int search_SLL_node(Node **head, Node *target_node);
	int insert_after_SLL_node(Node **head, Node *new_node);
	int insert_before_SLL_node(Node **head, Node *new_node);
	Node *get_SLL_node(Node **head, int position);
	int get_position_SLL_node(Node **head, Node *target_node);
private:
};

#endif //__SINGLE_LINKED_LIST_HH__
