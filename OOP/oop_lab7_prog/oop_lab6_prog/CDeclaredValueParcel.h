#pragma once

#include <iostream>
#include <fstream>
#include "CCommonParcel.h"
#include "enum.h"

class CDeclaredValueParcel : virtual public CParcel , public CCommonParcel
{
private:

	double value;

protected:

public:

	CDeclaredValueParcel();
	CDeclaredValueParcel(double value);
	CDeclaredValueParcel(double value, Address DeliveryAddress);
	CDeclaredValueParcel(double value, Address DeliveryAddress, Priority ParcelPriority);
	CDeclaredValueParcel(double value, Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff);
	CDeclaredValueParcel(double value, Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff, double price);

	void PrintName() const  override;
	void PrintValue() const;

	double GetTransferValue(double dDistance) const override;
	void SetPrice(double trans_value) override;
	void SetValue();

	void fInfo() override;

};