#include "test_main.hh"

TEST(single_linked_list, create_node) {
	CSingleLinkedList *single_linked_list = new CSingleLinkedList();

	int data_element = 5;
	Node *head = NULL;
	Node *new_node = NULL;
	NodeData data;
	data.data = data_element;

	new_node = single_linked_list->create_SLL_node(&data);

	EXPECT_EQ(data_element, new_node->data_element.data);

	single_linked_list->destroy_SLL_node(new_node);
}

TEST(single_linked_list, append_node) {
	CSingleLinkedList *single_linked_list = new CSingleLinkedList();

	Node *head = NULL;
	Node *new_node_01 = NULL;
	Node *new_node_02 = NULL;

	int data_element_01 = 5;
	int data_element_02 = 7;
	NodeData data_01;
	NodeData data_02;
	data_01.data = data_element_01;
	data_02.data = data_element_02;

	/* create nodes */
	new_node_01 = single_linked_list->create_SLL_node(&data_01);
	new_node_02 = single_linked_list->create_SLL_node(&data_02);

	single_linked_list->append_SLL_node(&head, new_node_01);
	single_linked_list->append_SLL_node(&head, new_node_02);

	EXPECT_EQ(data_element_01, head->data_element.data);
	EXPECT_EQ(data_element_02, head->next_node->data_element.data);

	single_linked_list->destroy_SLL_node(new_node_01);
	single_linked_list->destroy_SLL_node(new_node_02);
}

int main(int argc, char **argv) {
	std::cout << "Hanbit algorithm" << std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
