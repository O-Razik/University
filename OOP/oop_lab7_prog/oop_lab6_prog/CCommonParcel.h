#pragma once

#ifndef CPARCEL_H
#include "CParcel.h"
#endif
#ifndef ENUM_H
#include "enum.h"
#endif


class CCommonParcel : virtual public CParcel {

private:
	int a;

protected:
	int b;

public:

	CCommonParcel();
	CCommonParcel(Address DeliveryAddress);
	CCommonParcel(Address DeliveryAddress, Priority ParcelPriority);
	CCommonParcel(Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff);
	CCommonParcel(Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff, double price);

	~CCommonParcel();

	virtual double GetTransferValue(double dDistance) const override;

	virtual void PrintName() const override;
	virtual void SetPrice(double trans_value) override;

	virtual void fInfo() override;

};