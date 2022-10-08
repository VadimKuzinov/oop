#include <gtest/gtest.h>
#include "../Curve/Curve.h"

#include <cmath>

const long double pi = 3.14159265358979323846L;
const long double eps = 1e-6;

TEST(DistanceToCurve, AlphaIsPiAndNoLoop) {
	Curve cv(2, 5);
	auto small = cv.GetRSmall(pi);
	auto big = cv.GetRBig(pi);
	EXPECT_EQ(small, 3);
	EXPECT_EQ(big, 7);
}

TEST(DistanceToCurve, AlphaIsPiAndLoop) {
	Curve cv(5, 2);
	auto small = cv.GetRSmall(pi);
	auto big = cv.GetRBig(pi);
	EXPECT_EQ(small, 3);
	EXPECT_EQ(big, 7);
}

TEST(DistanceToCurve, AlphaIsGeneralAndLoop) {
	Curve cv(5, 2);
	long double angle = atan(3.0L / 8);
	auto small = cv.GetRSmall(angle);
	auto big = cv.GetRBig(angle);
	EXPECT_NEAR(small, 2.8639988689975L, eps);
	EXPECT_NEAR(big, 7.136000936322L, eps);
}

TEST(YFromX, CoordXIsZero) {
	Curve cv(5, 2);
	auto y = cv.GetY(0);
	EXPECT_EQ(y, 0);
}

TEST(YFromX, CoordXIsGeneral) {
	Curve cv(5, 2);
	auto y = cv.GetY(-1.7312);
	EXPECT_NEAR(y, 32.1558127422525, eps);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


