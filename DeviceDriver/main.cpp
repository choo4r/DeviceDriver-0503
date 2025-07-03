#include "gmock/gmock.h"
#include "device_driver.h"
#

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHWSUCESS) {
	// TODO : replace hardware with a Test Double
	MockFlashMemory hardware;
	EXPECT_CALL(hardware, read)
		.WillRepeatedly(Return(0xAA));

	DeviceDriver driver{ &hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0xAA, data);
}

TEST(DeviceDriver, ReadFromHWFAIL) {
	// TODO : replace hardware with a Test Double
	ReadFailException readFailException("ReadFailException");

	MockFlashMemory hardware;
	EXPECT_CALL(hardware, read)
		.WillOnce(Return(-1))
		.WillRepeatedly(Return(0xAA));

	DeviceDriver driver{ &hardware };
	EXPECT_THROW({
	 driver.read(0xFF);
		}, ReadFailException);
}

TEST(DeviceDriver, ReadFromHWMustFiveTimes) {
	// TODO : replace hardware with a Test Double
	MockFlashMemory hardware;
	EXPECT_CALL(hardware, read)
		.Times(5)
		.WillRepeatedly(Return(0xAA));

	DeviceDriver driver{ &hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0xAA, data);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}