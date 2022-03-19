#include <gtest/gtest.h>

#include "api/telloc_config.h"

TEST(ConfigurationApi, CreateAndDelete)
{
	TellocConfigPtr uutPtr = CreateTellocConfigInstance();

	EXPECT_NE(uutPtr, nullptr);

	DestroyTellocConfigInstance(&uutPtr);

	EXPECT_EQ(uutPtr, nullptr);
}

TEST(ConfigurationApi, GetDefaults)
{
	TellocConfigPtr uutPtr = CreateTellocConfigInstance();
	ASSERT_NE(uutPtr, nullptr);

	const char* getStr = GetIpAddress(uutPtr);
	unsigned int getPort = GetPort(uutPtr);

	EXPECT_EQ(strcmp(getStr, "192.168.10.1"), 0);
	EXPECT_EQ(getPort, 8889);

	DestroyTellocConfigInstance(&uutPtr);
	ASSERT_EQ(uutPtr, nullptr);
}

TEST(ConfigurationApi, SetAndGet_IpAddress)
{
	TellocConfigPtr uutPtr = CreateTellocConfigInstance();
	ASSERT_NE(uutPtr, nullptr);

	SetIpAddress(uutPtr, "localhost");
	const char* getStr = GetIpAddress(uutPtr);

	EXPECT_EQ(strcmp(getStr, "localhost"), 0);

	DestroyTellocConfigInstance(&uutPtr);
	ASSERT_EQ(uutPtr, nullptr);
}

TEST(ConfigurationApi, SetAndGet_Port)
{
	TellocConfigPtr uutPtr = CreateTellocConfigInstance();
	ASSERT_NE(uutPtr, nullptr);

	SetPort(uutPtr, 1234);
	unsigned int getPort = GetPort(uutPtr);

	EXPECT_EQ(getPort, 1234);

	DestroyTellocConfigInstance(&uutPtr);
	ASSERT_EQ(uutPtr, nullptr);
}
