#include "CParcel.h"

void CParcel::PrintTariff() const {
	std::cout << " tariff:";
	switch (*ParcelTariff)
	{
	case Tariff::None:
		std::cout << " None" << std::endl;
		break;
	case Tariff::LightWeight:
		std::cout << " LightWeight(0-250g)" << std::endl;
		break;
	case Tariff::MiddleWeight:
		std::cout << " MiddleWeight(250-1000g)" << std::endl;
		break;
	case Tariff::HeavyWeight:
		std::cout << " HeavyWeight(1000-2000g)" << std::endl;
		break;
	default:
		break;
	}
}
void CParcel::PrintPriority() const{
	std::cout << " priority:";
	switch (*ParcelPriority)
	{
	case Priority::NonPriority:
		std::cout << " nonpriority" << std::endl;
		break;
	case Priority::has_priority:
		std::cout << " priority" << std::endl;
		break;
	default:
		break;
	}
}
void CParcel::PrintAddess() const {
	std::cout << " Address:";
	switch (*DeliveryAddress)
	{
	case Address::unKnown:
		std::cout << " none" << std::endl;
		
		break;
	case Address::Region:
		std::cout << " region" << std::endl;
		break;
	case Address::Ukraine:
		std::cout << " Ukraine" << std::endl;
		break;
	case Address::Abroad:
		std::cout << " abroad" << std::endl;
		break;
	default:
		break;
	}
}
void CParcel::PrintPrice()  const {
	std::cout << " price: " << *price << ' ';
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

void CParcel::SetDistance()
{
	std::cout << "Enter the distance: ";
	std::cin >> *(this->distance);
	std::cout << std::endl;
}

void CParcel::SetPriority() {
	std::cout << "Prioritize your parcel? If yes, press 1" << std::endl;
	int input;
	std::cin >> input;
	if (input == 1) {
		*ParcelPriority = Priority::has_priority;
	}
}
void CParcel::SetAddress() {
	std::cout << "\nChoose your delivery address region?" << std::endl << " Press 1 for your region" << std::endl
		<< " Press 2 for all of Ukraine" << std::endl << " Press 3 for abroad" << std::endl << std::endl;;
	int input;
	std::cin >> input;
	switch (input)
	{
	case 1:
		*DeliveryAddress = Address::Region;
		*ParcelCurrency = Currency::UAH;
		break;
	case 2:
		*DeliveryAddress = Address::Ukraine;
		*ParcelCurrency = Currency::UAH;
		break;
	case 3:
		*DeliveryAddress = Address::Abroad;
		*ParcelCurrency = Currency::USD;
		break;

	default:
		break;
	}
	std::cout << std::endl;
}

void CParcel::SetPrice(double trans_value) {
	std::cout << "Enter the price: ";
	std::cin >> *(this->price);
	std::cout << std::endl;
}
void CParcel::SetTariff() {
	int weight_grm;
	std::cout << "\nEnter weight in grams: ";
	while(1)
	{
		std::cin >> weight_grm;
		if (weight_grm < 0 || weight_grm > 2000) {
			std::cout << std::endl << "Weigth is incorrect\n" << std::endl;
			continue;
		}
		else {
			if (weight_grm <= 250.0) {
				*ParcelTariff = Tariff::LightWeight;

			} else if (weight_grm < 1000.0) {
				*ParcelTariff = Tariff::MiddleWeight;

			} else if (weight_grm <= 2000.0) {
				*ParcelTariff = Tariff::HeavyWeight;
			}

			std::cout << "Parcel tariff is";
			switch (*ParcelTariff)
			{
			case Tariff::LightWeight:
				std::cout << " light weight (0-250g)" << std::endl;
				break;
			case Tariff::MiddleWeight:
				std::cout << " middle weight (250-1000g)" << std::endl;
				break;
			case Tariff::HeavyWeight:
				std::cout << " heavy weight (1000-2000g)" << std::endl;
				break;
			default:
				break;
			}
		}
		break;
	}
	std::cout << std::endl;
}

double CParcel::GetDistance()
{
	return *(this->distance);
}

double CParcel::GetPrice()
{
	return *(this->price);
}

bool CParcel::CanBeDelivered()  const {
	bool check;
	if (*price == 0.0) {
		check = 0;
	}
	else {
		check = 1;
	}
	return check;
}

void CParcel::fInfo()
{
	std::ofstream os;
	os.open("parcals.txt", std::ios::app);
	os << std::endl << "---------------------------------------------------" << std::endl;
	os << " class: CParcel " << std::endl;
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
	os << " price: " << *price << ' ';
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
	os << std::endl << "---------------------------------------------------"  << std::endl<< std::endl;

}

void AllCoast(std::vector<std::unique_ptr<CParcel>>& ParselArray)
{
	int currency_type = 0;
	double allcoast = 0;
	do {
		std::cout << "Choose currency:\n 1)UAH\n 2)USD\n" << std::endl;
		std::cin >> currency_type;
		if (currency_type != 1 && currency_type != 2) std::cout << "\nTry again\n" << std::endl;
	} while (currency_type != 1 && currency_type != 2);
	if(currency_type == 1)
	{
		for (int i = 0; i < ParselArray.size(); i++)
		{
			ParselArray[i]->SetPrice(ParselArray[i]->GetTransferValue(ParselArray[i]->GetDistance()));
			if (*(ParselArray[i]->ParcelCurrency) == Currency::USD)
			{
				allcoast += (ParselArray[i]->GetPrice()) * 39;
			}
			else allcoast += (ParselArray[i]->GetPrice());
		}
		std::cout << "All coast is " << allcoast << " UAH" << std::endl;
	}
	if (currency_type == 2)
	{
		for (int i = 0; i < ParselArray.size(); i++)
		{
			ParselArray[i]->SetDistance();
			ParselArray[i]->SetPrice(ParselArray[i]->GetTransferValue(ParselArray[i]->GetDistance()));
			if (*(ParselArray[i]->ParcelCurrency) == Currency::UAH)
			{
				allcoast += (ParselArray[i]->GetPrice()) / 39;
			}
			else allcoast += (ParselArray[i]->GetPrice());
		}
		std::cout << "\nAll coast is" << allcoast << " USD" << std::endl;
	}
}
