#include "CCommonParcel.h"

CCommonParcel::CCommonParcel() {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(Address::unKnown));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(Priority::NonPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(Tariff::None));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
	this->ParcelCurrency = std::make_unique<Currency>(/*new Currency*/(Currency::None));
}

CCommonParcel::CCommonParcel(Address DeliveryAddress) {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(DeliveryAddress));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(Priority::NonPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(Tariff::None));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
	this->ParcelCurrency = std::make_unique<Currency>(/*new Currency*/(Currency::None));
}

CCommonParcel::CCommonParcel(Address DeliveryAddress, Priority ParcelPriority)  {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(DeliveryAddress));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(ParcelPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(Tariff::None));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->ParcelCurrency = std::make_unique<Currency>(/*new Currency*/(Currency::None)); this->distance = std::make_unique<double>(/*new double*/(0.0));
}

CCommonParcel::CCommonParcel(Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff) {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(DeliveryAddress));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(ParcelPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(ParcelTariff));
	this->price = std::make_unique<double>(/*new double*/(0.0));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
}

CCommonParcel::CCommonParcel(Address DeliveryAddress, Priority ParcelPriority, Tariff ParcelTariff, double price) {
	this->DeliveryAddress = std::make_unique<Address>(/*new Address*/(DeliveryAddress));
	this->ParcelPriority = std::make_unique<Priority>(/*new Priority*/(ParcelPriority));
	this->ParcelTariff = std::make_unique<Tariff>(/*new Tariff*/(ParcelTariff));
	this->price = std::make_unique<double>(/*new double*/(price));
	this->distance = std::make_unique<double>(/*new double*/(0.0));
}

CCommonParcel::~CCommonParcel() {

}

double CCommonParcel::GetTransferValue(double dDistance) const
{
	double trans_value = 0.0;
	switch (*DeliveryAddress) {
	  case Address::Region:
		  trans_value = dDistance * 0.1;
		  break;
	  case Address::Ukraine:
		  trans_value = dDistance * 0.15;
		  break;
	  case Address::Abroad:
		  trans_value = dDistance * 0.09;
		  break;
	  default: ;
	}
	return trans_value;
}


void CCommonParcel::PrintName() const {
	std::cout << " class: CCommonParcel \n";
}


void CCommonParcel::SetPrice(double trans_value) {
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
			*(this->price) += trans_value * 0.01;
			*(this->price) += 20.7;

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

			*(this->price) += 27.0;
			*(this->price) += trans_value * 0.01;

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

			*(this->price) += 2.7;
			*(this->price) += trans_value * 0.001;

			break;
		}
	}
}

void CCommonParcel::fInfo ()
{	
	std::ofstream os;
	os.open("parcals.txt", std::ios::app);
	os << std::endl << "---------------------------------------------------" << std::endl;
	os << " class: CCommonParcel " << std::endl;
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