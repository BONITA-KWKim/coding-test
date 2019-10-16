#ifndef __SINGLE_LINKED_LIST_HH__
#define __SINGLE_LINKED_LIST_HH__

typedef struct tagNodeData {
	int data;
} NodeData;

typedef struct tagNode {
	NodeData *data;
	tagNode *nextNode;
} Node;

class CSingleLinkedList {
public:
	CSingleLinkedList(){};
	~CSingleLinkedList(){};

	int create_SLL_node(int data);
	void destroy_SLL_node(Node *node);
	int append_SLL_node(Node **head, Node *newNode);
	int remove_SLL_node(Node **head, Node *targetNode);
	int search_SLL_node(Node **head, Node *targetNode);
	int insert_after_SLL_node(Node **head, Node *newNode);
	int insert_before_SLL_node(Node **head, Node *newNode);
	Node *get_SLL_node(Node **head, int position);
	int get_position_SLL_node(Node **head, Node *targetNode);
private:
};

#endif //__SINGLE_LINKED_LIST_HH__
