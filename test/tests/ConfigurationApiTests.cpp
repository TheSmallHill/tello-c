#include <gtest/gtest.h>

#include "api/telloc_config.h"

TEST(ConfigurationApi, CreateAndDelete)
{
	TellocConfigPtr uutPtr = CreateTellocConfigInstance();

	EXPECT_NE(uutPtr, nullptr);

	DestroyTellocConfigInstance(&uutPtr);

	EXPECT_EQ(uutPtr, nullptr);
}
