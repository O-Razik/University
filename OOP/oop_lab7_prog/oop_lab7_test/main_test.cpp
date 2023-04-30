#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "class_test.h"

TEST( MockCCommonParcel, FirstMockTest)
{
	MockCCommonParcel parcel;
	EXPECT_CALL(parcel, PrintName);
	parcel.PrintName();

	EXPECT_CALL(parcel, PrintAddess).Times(1);
	parcel.PrintAddess();

	EXPECT_CALL(parcel, PrintTarrif).Times(2);
	parcel.PrintTarrif();
	parcel.PrintTarrif();

	EXPECT_CALL(parcel, PrintPriority).Times(0);

	EXPECT_CALL(parcel, PrintPrice).Times(1);
	EXPECT_NO_THROW(parcel.PrintPrice());

}

TEST(MockCCommonParcel, SecondMockTest)
{
	MockCCommonParcel parcel(Address::Region, Priority::NonPriority, Tariff::MiddleWeight, 25.75);
	EXPECT_CALL(parcel, GetPrice).Times(2);
	parcel.GetPrice();
	EXPECT_NO_THROW(parcel.GetPrice());
	EXPECT_CALL(parcel, GetPrice).WillOnce(testing::Return(25.75));
	parcel.GetPrice();

	EXPECT_CALL(parcel, GetTransferValue).WillOnce(testing::Return(1.0));
	EXPECT_FLOAT_EQ(parcel.GetTransferValue(100.0), (1.0));

	MockCCommonParcel parcel2(Address::Ukraine, Priority::NonPriority, Tariff::MiddleWeight, 25.75);
	EXPECT_CALL(parcel2, GetTransferValue).WillOnce(testing::Return(1.5));
	EXPECT_FLOAT_EQ(parcel2.GetTransferValue(100.0), (1.5));

	MockCCommonParcel parcel3(Address::Abroad, Priority::NonPriority, Tariff::MiddleWeight, 25.75);
	EXPECT_CALL(parcel3, GetTransferValue).WillOnce(testing::Return(0.9));
	EXPECT_FLOAT_EQ(parcel3.GetTransferValue(100.0), (0.9));

}


int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}