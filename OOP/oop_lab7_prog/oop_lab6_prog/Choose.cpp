#include <iostream>
#include "choose.h"

void Choose(const char mode, int amount, std::vector<std::unique_ptr<CParcel>>& ParselArray, int index) {
	if (mode == 'c' || mode == 'f' || mode == 'b')
	{
		std::cout << "\nChoose your parcel. Press" << std::endl
			<< " 1)Ordinary parcel" << std::endl
			<< " 2)Parcel with declared value" << std::endl
			<< " 3)Electronic transfer" << std::endl << std::endl;
		int input = 0;
		while (input <= 0 || input > 3)
		{
			ParselArray[index] = std::make_unique<CCommonParcel>();
			std::cin >> input;
			if (input == 1) {
				ParselArray[index] = std::make_unique<CCommonParcel>();
				CCommonParcel* parcel = dynamic_cast<CCommonParcel*>(ParselArray[index].get());



				while (!(*parcel).CanBeDelivered())
				{
					parcel->SetAddress();
					parcel->SetPriority();
					parcel->SetTariff();
					parcel->SetDistance();
					parcel->SetPrice(parcel->GetTransferValue(parcel->GetDistance()));
				}

				if(mode == 'c' || mode == 'b')
				{
					parcel->PrintName();
					parcel->PrintAddess();
					parcel->PrintPriority();
					parcel->PrintTariff();
					parcel->PrintPrice();
				} if (mode == 'f' || mode == 'b') {
					parcel->fInfo();

					std::cout << "\nParcel information was written to the file successfully\n";
				}
			}
			else if (input == 2) {
				ParselArray[index] = std::make_unique<CDeclaredValueParcel>();
				CDeclaredValueParcel* parcel = dynamic_cast<CDeclaredValueParcel*>(ParselArray[index].get());

				while (!parcel->CanBeDelivered())
				{
					parcel->SetValue();
					parcel->SetAddress();
					parcel->SetPriority();
					parcel->SetTariff();
					parcel->SetDistance();
					parcel->SetPrice(parcel->GetTransferValue(parcel->GetDistance()));
				}

				if (mode == 'c' || mode == 'b')
				{
					parcel->PrintName();
					parcel->PrintAddess();
					parcel->PrintPriority();
					parcel->PrintTariff();
					parcel->PrintValue();
					parcel->PrintPrice();
				} if (mode == 'f' || mode == 'b') {
					parcel->fInfo();

					std::cout << "\nParcel information was written to the file successfully\n";
				}
			}
			else if (input == 3) {
				ParselArray[index] = std::make_unique<CDigitalTransfer>();
				CDigitalTransfer* parcel = dynamic_cast<CDigitalTransfer*>(ParselArray[index].get());

				while (!parcel->CanBeDelivered())
				{
					parcel->SetFeatrsDelivParcel();
				}

				if (mode == 'c' || mode == 'b')
				{
					parcel->PrintName();
					parcel->FeatrsDelivParcel();

				} if (mode == 'f' || mode == 'b') {
					parcel->fFeatrsDelivParcel();
					std::cout << "\nParcel information was written to the file successfully\n";

				}
			}
			else {
				std::cout << "Incorrect input. Try again" << std::endl;
			}
		}
	}
	else std::cout << "Incorrect mode" << std::endl;

}