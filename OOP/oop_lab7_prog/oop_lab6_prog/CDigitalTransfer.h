#pragma once
#pragma once

#ifndef CPARCEL_H
#include "CParcel.h"
#endif
#ifndef ENUM_H
#include "enum.h"
#endif

class CDigitalTransfer : public CParcel
{
private:

	double value;

protected:

	void SetTariff() override;

public:

	CDigitalTransfer();
	CDigitalTransfer(double value);
	CDigitalTransfer(Address DeliveryAddress);
	CDigitalTransfer(Address DeliveryAddress, double value);
	~CDigitalTransfer();

	void SetAddress() override;
	void SetPrice(double trans_value) override;
	void SetValue();
	double GetTransferValue(double dDistance) const override;

	void FeatrsDelivParcel() const;
	void SetFeatrsDelivParcel();


	void fFeatrsDelivParcel() const;

	void PrintName() const override;
	void PrintValue() const;
	void PrintTariff() const override;

	

	bool CanBeDelivered() const override;
};

//--------------------------------------------------------------