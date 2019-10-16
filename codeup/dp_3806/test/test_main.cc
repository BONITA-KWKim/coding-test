#include "gtest/gtest.h"
#include "zoo.hh"

TEST(zoo, zoo) {
	EXPECT_EQ(0, zoo(0));
}

int main(int argc, char **argv) {
	std::cout << "DP 3806" << std::endl;

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
