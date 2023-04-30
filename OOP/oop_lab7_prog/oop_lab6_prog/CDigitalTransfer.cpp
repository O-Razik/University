#include "CDigitalTransfer.h"

CDigitalTransfer::CDigitalTransfer() : value(0.0) {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(Address::unKnown));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(Priority::NonPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(Tariff::None));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
	this->ParcelCurrency = std::make_unique<Currency>(/*new Currency*/(Currency::None));
}
CDigitalTransfer::CDigitalTransfer(Address DeliveryAddress) : value(0.0) {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(DeliveryAddress));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(Priority::NonPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(Tariff::None));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
	this->ParcelCurrency = std::make_unique<Currency>(/*new Currency*/(Currency::None));
}
CDigitalTransfer::CDigitalTransfer(double value) : value(value) {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(Address::unKnown));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(Priority::NonPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(Tariff::None));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
	this->ParcelCurrency = std::make_unique<Currency>(/*new Currency*/(Currency::None));
}
CDigitalTransfer::CDigitalTransfer(Address DeliveryAddress, double value) : value(value) {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(DeliveryAddress));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(Priority::NonPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(Tariff::None));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
	this->ParcelCurrency = std::make_unique<Currency>(/*new Currency*/(Currency::None));
}
CDigitalTransfer::~CDigitalTransfer() = default;

void CDigitalTransfer::PrintName() const {
	std::cout << " class: CDigitalTransfer \n";
}

void CDigitalTransfer::SetValue() {
	std::cout << "\nEnter the value: ";
	std::cin >> this->value;
	std::cout << std::endl;
}

void CDigitalTransfer::SetPrice(double trans_value) {
	if (*DeliveryAddress == Address::unKnown) {
		*(this->price) = 0.0;
	}
	else {
		*(this->price) = 0.0;
		double coef = 1;
		switch (*DeliveryAddress)
		{

		case Address::Region:
			*ParcelCurrency = Currency::UAH;
			*(this->price) += value + value * 0.3 + 5.0;
			*(this->price) += trans_value*0.1;
			break;

		case Address::Ukraine:
			*ParcelCurrency = Currency::UAH;
			*(this->price) += value + value * 0.3 + 5.0;
			*(this->price) += trans_value*0.1;
			break;

		case Address::Abroad:
			*ParcelCurrency = Currency::USD;
			*(this->price) += value + value * 0.4;
			*(this->price) += trans_value*0.001;
			break;

		}
	}
}

double CDigitalTransfer::GetTransferValue(double dDistance) const
{
	double trans_value = 0.0;
	switch (*DeliveryAddress) {
	case Address::Region:
		trans_value = dDistance * 0;
		break;
	case Address::Ukraine:
		trans_value = dDistance * 0;
		break;
	case Address::Abroad:
		trans_value = dDistance * 0.1;
		break;
	default:;
	}
	return trans_value;
}

void CDigitalTransfer::FeatrsDelivParcel() const {
	PrintAddess();
	std::cout << std::endl;
	PrintPriority();
	PrintTariff();
	PrintValue();
	PrintPrice();
}

void CDigitalTransfer::SetFeatrsDelivParcel()
{
	SetValue();
	SetAddress();
	SetPriority();
	SetDistance();
	SetPrice(GetTransferValue(*distance));
}

void CDigitalTransfer::PrintValue() const {
	std::cout << " value: " << value  << ' ';
	switch (*ParcelCurrency)
	{
	case Currency::None:
		std::cout << " " << std::endl;
		break;
	case Currency::UAH:
		std::cout << "UAH" << std::endl;
		break;
	case Currency::USD:
		std::cout << "USD" << std::endl;
		break;
	default:
		break;
	}
}

void CDigitalTransfer::PrintTariff()  const {
	std::cout << " tariff: e-transfer" << std::endl;
}

void CDigitalTransfer::SetAddress() {
	std::cout << "Choose your delivery address region?" << std::endl
		<< " Press 1 for all of Ukraine" << std::endl << " Press 2 for abroad" << std::endl;
	int input;
	std::cin >> input;
	switch (input)
	{
	case 1:
		DeliveryAddress = std::make_unique<Address>(Address::Ukraine);
		break;
	case 2:
		DeliveryAddress = std::make_unique<Address>(Address::Abroad);
		break;

	default:
		break;
	}
}

bool CDigitalTransfer::CanBeDelivered()  const {
	bool check;
	if (*price == 0.0) {
		check = false;
	}
	else {
		check = true;
	}
	return check;
}

void CDigitalTransfer::fFeatrsDelivParcel() const {
	
	std::ofstream os;
	os.open("parcals.txt", std::ios::app);
	os << std::endl << "---------------------------------------------------" << std::endl;
	os << " class: CDigitalTransfer \n";
	os << " address:";
	switch (*DeliveryAddress)
	{
	case Address::Region:
		os << " region" << std::endl;
		break;
	case Address::Ukraine:
		os << " Ukraine" << std::endl;
		break;
	case Address::Abroad:
		os << " abroad" << std::endl;
		break;
	default:
		break;
	}
	os << " priority:";
	switch (*ParcelPriority)
	{
	case Priority::NonPriority:
		os << " nonpriority" << std::endl;
		break;
	case Priority::has_priority:
		os << " priority" << std::endl;
		break;
	default:
		break;
	}
	os << " tariff: e-transfer" << std::endl;
	os << " value: " << value << ' '; 
	switch (*ParcelCurrency)
	{
	case Currency::UAH:
		os << "UAH" << std::endl;
		break;
	case Currency::USD:
		os << "USD" << std::endl;
		break;
	default:
		break;
	}
	os << " price: " << price << ' ';
	switch (*ParcelCurrency)
	{
	case Currency::UAH:
		os << "UAH" << std::endl;
		break;
	case Currency::USD:
		os << "USD" << std::endl;
		break;
	default:
		break;
	}
	os << std::endl << "---------------------------------------------------" << std::endl << std::endl;
}

void CDigitalTransfer::SetTariff()
{
	std::cout << "You cannot set a tariff" << std::endl;
}