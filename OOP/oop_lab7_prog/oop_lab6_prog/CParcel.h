#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "enum.h"

class CParcel {

private:
	int a;
protected:
	std::unique_ptr<Address> DeliveryAddress;
	std::unique_ptr<double> distance;
	std::unique_ptr <Priority> ParcelPriority;
	std::unique_ptr <Tariff> ParcelTariff;

	std::unique_ptr<double> price;
	std::unique_ptr <Currency> ParcelCurrency;

public:
	
	virtual ~CParcel() = default;

	virtual void PrintName() const = 0;
	virtual void PrintAddess() const;
	virtual void PrintPriority() const;
	virtual void PrintTariff() const;
	virtual void PrintPrice() const;
	virtual void SetDistance();
	virtual void SetPriority();
	virtual void SetAddress();
	virtual void SetPrice(double trans_value);
	virtual void SetTariff();

	virtual double GetDistance();
	virtual double GetPrice();
	virtual double GetTransferValue(double dDistance) const = 0;

	virtual bool CanBeDelivered() const;

	virtual void fInfo();

	friend void AllCoast(std::vector<std::unique_ptr<CParcel>>& ParselArray);

};