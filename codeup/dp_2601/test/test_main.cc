#include "gtest/gtest.h"
#include "fibonacci.hh"

TEST(fibonacci, fibonacci) {
	EXPECT_EQ(0, fibonacci(0));
	EXPECT_EQ(1, fibonacci(1));
	EXPECT_EQ(1, fibonacci(2));
	EXPECT_EQ(13, fibonacci(7));
}

int main(int argc, char **argv) {
	std::cout << "DP 2601" << std::endl;

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
