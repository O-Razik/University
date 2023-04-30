#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "C:/Users/razik/source/repos/oop_lab7_prog/oop_lab6_prog/CParcel.h"
#include "C:/Users/razik/source/repos/oop_lab7_prog/oop_lab6_prog/CCommonParcel.h"
#include "C:/Users/razik/source/repos/oop_lab7_prog/oop_lab6_prog/CParcel.cpp"
#include "C:/Users/razik/source/repos/oop_lab7_prog/oop_lab6_prog/CCommonParcel.cpp"


class MockCCommonParcel : virtual public CParcel, virtual public CCommonParcel
{
	protected:
	std::unique_ptr<Address> DeliveryAddress;
	std::unique_ptr<double> distance;
	std::unique_ptr <Priority> ParcelPriority;
	std::unique_ptr <Tariff> ParcelTariff;

	std::unique_ptr<double> price;
	std::unique_ptr <Currency> ParcelCurrency;

public:

	MockCCommonParcel();
	MockCCommonParcel(Address DeliveryAddress);
	MockCCommonParcel(Address DeliveryAddress, Priority ParcelPriority);
	MockCCommonParcel(Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff);
	MockCCommonParcel(Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff, double price);

	MOCK_METHOD(void, PrintName, (), (const));
	MOCK_METHOD(void, PrintAddess, (), (const));
	MOCK_METHOD(void, PrintPriority, (), (const));
	MOCK_METHOD(void, PrintTarrif, (), (const));
	MOCK_METHOD(void, PrintPrice, (), (const));

	MOCK_METHOD(void, SetAddress, ());
	MOCK_METHOD(void, SetDistance, ());
	MOCK_METHOD(void, SetPriority, ());
	MOCK_METHOD(void, SetTariff, ());
	MOCK_METHOD(void, SetPrice, ());

	MOCK_METHOD(double, GetDistance, ());
	MOCK_METHOD(double, GetPrice, ());
	MOCK_METHOD(double, GetTransferValue, (double), (const));
	MOCK_METHOD0(fInfo, void());

};

MockCCommonParcel::MockCCommonParcel() {}

MockCCommonParcel::MockCCommonParcel(Address DeliveryAddress) :
	CCommonParcel(DeliveryAddress) {}

MockCCommonParcel::MockCCommonParcel(Address DeliveryAddress, Priority ParcelPriority) :
	CCommonParcel(DeliveryAddress, ParcelPriority) {}

MockCCommonParcel::MockCCommonParcel(Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff) :
	CCommonParcel(DeliveryAddress, ParcelPriority, ParcelTariff) {}

MockCCommonParcel::MockCCommonParcel
	(Address DeliveryAddress, Priority ParcelPriority,Tariff ParcelTariff, double price) :
		CCommonParcel(DeliveryAddress, ParcelPriority, ParcelTariff, price) {}