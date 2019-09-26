#include "test_main.hh"

int sum(int a, int b) {
	return a + b;
}

TEST(default_test_group, default_test) {
	EXPECT_EQ(2, sum(1,1));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
