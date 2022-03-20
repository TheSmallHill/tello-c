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
	unsigned int getCmdPort = GetCommandPort(uutPtr);
	unsigned int getStatePort = GetStatePort(uutPtr);

	EXPECT_EQ(strcmp(getStr, "192.168.10.1"), 0);
	EXPECT_EQ(getCmdPort, 8889);
	EXPECT_EQ(getStatePort, 8890);

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

TEST(ConfigurationApi, SetAndGet_CommandPort)
{
	TellocConfigPtr uutPtr = CreateTellocConfigInstance();
	ASSERT_NE(uutPtr, nullptr);

	SetCommandPort(uutPtr, 1234);
	unsigned int getPort = GetCommandPort(uutPtr);

	EXPECT_EQ(getPort, 1234);

	DestroyTellocConfigInstance(&uutPtr);
	ASSERT_EQ(uutPtr, nullptr);
}

TEST(ConfigurationApi, SetAndGet_StatePort)
{
	TellocConfigPtr uutPtr = CreateTellocConfigInstance();
	ASSERT_NE(uutPtr, nullptr);

	SetStatePort(uutPtr, 1234);
	unsigned int getPort = GetStatePort(uutPtr);

	EXPECT_EQ(getPort, 1234);

	DestroyTellocConfigInstance(&uutPtr);
	ASSERT_EQ(uutPtr, nullptr);
}
