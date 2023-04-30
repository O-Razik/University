#include "CDeclaredValueParcel.h"

CDeclaredValueParcel::CDeclaredValueParcel() : value(0.0) {}
CDeclaredValueParcel::CDeclaredValueParcel(double value) : value(value) {}
CDeclaredValueParcel::CDeclaredValueParcel(double value, Address DeliveryAddress) :
	value(value), CCommonParcel(DeliveryAddress) {}
CDeclaredValueParcel::CDeclaredValueParcel(double value, Address DeliveryAddress, Priority ParcelPriority) :
	value(value), CCommonParcel(DeliveryAddress, ParcelPriority) {}
CDeclaredValueParcel::CDeclaredValueParcel(double value, Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff) :
	value(value), CCommonParcel(DeliveryAddress, ParcelPriority, ParcelTariff) {}
CDeclaredValueParcel::CDeclaredValueParcel(double value, Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff, double price) :
	value(value), CCommonParcel(DeliveryAddress, ParcelPriority, ParcelTariff, price) {}

void CDeclaredValueParcel::PrintName() const {
	std::cout << " class: CDeclaredValueParcel \n";
}

void CDeclaredValueParcel::PrintValue() const {
	std::cout << " value: " << value << ' ';
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

double CDeclaredValueParcel::GetTransferValue(double dDistance) const
{
	double trans_value = 0.0;
	switch (*DeliveryAddress) {
	case Address::Region:
		trans_value = dDistance * 0.1 + value * 0.011;
		break;
	case Address::Ukraine:
		trans_value = dDistance * 0.15 + value * 0.012;
		break;
	case Address::Abroad:
		trans_value = dDistance * 0.09 + value * 0.008;
		break;
	default:;
	}
	return trans_value;
}

void CDeclaredValueParcel::SetValue() {
	std::cout << "\nEnter the value: " << std::endl << std::endl;
	std::cin >> this->value;
}
void CDeclaredValueParcel::SetPrice(double trans_value) {
	if ((*DeliveryAddress == Address::unKnown) || (*ParcelTariff == Tariff::None)) {
		*(this->price) = 0.0;
	}
	else {
		*(this->price) = 0.0;
		double coef = 1;
		switch (*DeliveryAddress)
		{

		case Address::Region:

			*ParcelCurrency = Currency::UAH;
			if (*ParcelPriority == Priority::has_priority) coef = 1.25;

			switch (*ParcelTariff)
			{
			case Tariff::LightWeight:
				*(this->price) += coef * 18.0;
				break;
			case Tariff::MiddleWeight:
				*(this->price) += coef * 36.0;
				break;
			case Tariff::HeavyWeight:
				*(this->price) += coef * 48.0;
				break;
			}

			*(this->price) += value * 0.1;
			*(this->price) += trans_value*0.0075;

			break;
		case Address::Ukraine:
			*ParcelCurrency = Currency::UAH;
			if (*ParcelPriority == Priority::has_priority) coef = 1.25;

			switch (*ParcelTariff)
			{
			case Tariff::LightWeight:
				*(this->price) += coef * 18.0;
				break;
			case Tariff::MiddleWeight:
				*(this->price) += coef * 36.0;
				break;
			case Tariff::HeavyWeight:
				*(this->price) += coef * 48.0;
				break;
			}
			*(this->price) += trans_value * 0.01;
			*(this->price) += value * 0.1;

			break;
		case Address::Abroad:
			*ParcelCurrency = Currency::USD;
			if (*ParcelPriority == Priority::has_priority) coef = 1.3;

			switch (*ParcelTariff)
			{
			case Tariff::LightWeight:
				*(this->price) += coef * 3.0;
				break;
			case Tariff::MiddleWeight:
				*(this->price) += coef * 11.0;
				break;
			case Tariff::HeavyWeight:
				*(this->price) += coef * 17.0;
				break;
			}

			*(this->price) += value * 0.15;
			*(this->price) += trans_value * 0.001;

			break;
		}
	}
}

void CDeclaredValueParcel::fInfo ()
{
	std::ofstream os;
	os.open("parcals.txt", std::ios::app);
	os << std::endl << "---------------------------------------------------" << std::endl;
	os << " class: CDeclaredValueParcel " << std::endl;
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
	os << " tariff:";
	switch (*ParcelTariff)
	{
	case Tariff::LightWeight:
		os << " LightWeight(0-250g)" << std::endl;
		break;
	case Tariff::MiddleWeight:
		os << " MiddleWeight(250-1000g)" << std::endl;
		break;
	case Tariff::HeavyWeight:
		os << " HeavyWeight(1000-2000g)" << std::endl;
		break;
	default:
		break;
	}
	os << " value: " << value << ' ' ;
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