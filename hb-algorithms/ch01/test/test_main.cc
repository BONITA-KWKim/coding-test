#include "test_main.hh"

TEST(linked_list, single_linked_list) {
	EXPECT_EQ(0, 0);
}

int main(int argc, char **argv) {
	std::cout << "Hanbit algorithm" << std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
