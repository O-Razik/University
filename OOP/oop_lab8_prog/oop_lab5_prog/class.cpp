#include "class.h"

struct CQueue::Member {
	double* number;
	Member* next;
};

double CQueue::getFirst() const {
	return *(first)->number;
}
double CQueue::getLast() const {
	return *(last)->number;
}

CQueue::CQueue() : first(nullptr), last(nullptr) {}

CQueue::CQueue(double _first_num) {
	if (isnan(_first_num))
	{
		throw std::exception("Error: Number cannot be a NAN");
	}
	try
	{
		first = new Member;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Error: Memory allocation error: " << err.what() << '\n';
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw err;
	}

	last = first;
	try {
		first->number = new double;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Error: Memory allocation error: " << err.what() << '\n';
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw err;
	}
	
	*(first->number) = _first_num;
	first->next = nullptr;
}

CQueue::CQueue(const CQueue& other){
	try
	{
		first = new Member;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Error: Memory allocation error: " << err.what() << '\n';
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw err;
	}

	try
	{
		last = new Member;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Error: Memory allocation error: " << err.what() << '\n';
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw err;
	}

	memcpy(first, other.first, sizeof(Member));
	
	Member *ptemp = first, * pcopied = other.first;
	ptemp->next = first->next;
	try
	{
		first->next = new Member;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Error: Memory allocation error: " << err.what() << '\n';
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw err;
	}

	while(ptemp->next != NULL) {

		try
		{
			ptemp->next = new Member;
		}
		catch (const std::bad_alloc& err)
		{
			std::cout << "Error: Memory allocation error: " << err.what() << '\n';
			std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
			throw err;
		}

		memcpy(ptemp->next, pcopied->next, sizeof(Member));
		ptemp = ptemp->next;
		pcopied = pcopied->next;
	}
	memcpy(last, other.last, sizeof(Member));
}
CQueue::CQueue(CQueue&& other){
	try
	{
		first = new Member;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Error: Memory allocation error: " << err.what() << '\n';
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw err;
	}

	try
	{
		last = new Member;
	}
	catch (const std::bad_alloc& err)
	{
		std::cout << "Error: Memory allocation error: " << err.what() << '\n';
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw err;
	}

	swap(other.first, first);
	swap(other.last, last);
	other.first = nullptr;
	other.last = nullptr;
}

CQueue& CQueue::operator=(const CQueue& other) {
	if (this != &other) {
		QueueClear();
		first = new Member;
		last = new Member;
		memcpy(first, other.first, sizeof(Member));
		memcpy(last, other.last, sizeof(Member));
	}
	return *this;
}
CQueue& CQueue::operator=(CQueue&& other){
	if (this != &other) {
		QueueClear();

		try
		{
			first = new Member;
		}
		catch (const std::bad_alloc& err)
		{
			std::cout << "Error: Memory allocation error: " << err.what() << '\n';
			std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
			throw err;
		}

		try
		{
			last = new Member;
		}
		catch (const std::bad_alloc& err)
		{
			std::cout << "Error: Memory allocation error: " << err.what() << '\n';
			std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
			throw;
		}

		swap(other.first, first);
		swap(other.last, last);
		other.first = nullptr;
		other.last = nullptr;
	}
	return *this;
}

CQueue::~CQueue() {
	QueueClear();
}

unsigned int CQueue::QueueSize() noexcept {
	int size = 0;
	for (Member* member = first; member != nullptr; member = member->next) {
		size++;
	}
	return size;
}

double CQueue::QueueMax() {
	try
	{
		if (QueueSize() <= 0)
		{
			throw queue_err_sizeZero();
		}
	}
	catch (queue_err_sizeZero& err)
	{
		std::cout << err.what();
		throw err;
	}
	double max = *(first->number);
	for (Member* member = first->next; member != nullptr; member = member->next) {
		if (max < *(member->number)) {
			max = *(member->number);
		}
	}
	return max;
}

double CQueue::QueueMin() {
	try
	{
		if (QueueSize() <= 0)
		{
			throw queue_err_sizeZero();
		}
	}
	catch (queue_err_sizeZero& err)
	{
		std::cout << err.what();
		throw err;
	}
	double min = *(first->number);
	for (Member* member = first->next; member != nullptr; member = member->next) {
		if (min > *(member->number)) {
			min = *(member->number);
		}
	}
	return min;
}

double CQueue::QueueAver() {
	try
	{
		if (QueueSize() <= 0)
		{
			throw queue_err_sizeZero();
		}
	}
	catch (queue_err_sizeZero& err)
	{
		std::cout << err.what();
		throw err;
	}
	double sum = 0.0;
	for (Member* member = first; member != nullptr; member = member->next) {
		sum += *(member->number);
	}
	return sum / QueueSize();
}

void CQueue::QueueFirstOut() noexcept {
	Member* pTemp = first, * pTempNext = pTemp->next;
	delete pTemp;
	first = pTempNext;
	if(!first) last = first;
}
void CQueue::QueueClear() noexcept {
	while (first)
	{
		QueueFirstOut();
	}
}

bool CQueue::QueueIsEmpty() noexcept {
	return first == nullptr;
}

void CQueue::operator+(double num) {
	Member* new_member;
	try
	{
		new_member = new Member;
	}
	catch (const std::bad_alloc& err)
	{
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw std::bad_alloc();
	}

	try
	{
		new_member->number = new double;
	}
	catch (const std::bad_alloc& err)
	{
		std::cerr << "Error: Memory allocation error: " << err.what() << '\n';
		throw std::bad_alloc();
	}

	*(new_member->number) = num;
	new_member->next = nullptr;

	if (!first) first = new_member;
	else if (first) last->next = new_member;

	last = new_member;
}

void CQueue::operator-(int num_memb) {
	for (int i = 0; i < num_memb; i++) {
		if (first) QueueFirstOut();
	}
}

void CQueue::operator*(double scalar) {
	if (isnan(scalar))
	{
		throw std::exception("Error: Number cannot be a NAN");
	}
	Member* pTemp = first;
	while (pTemp) {
		*(pTemp->number) = *(pTemp->number) * scalar;
		pTemp = pTemp->next;
	}
}

istream& operator>>(istream& is, CQueue& obj) {
	double num;
	int size_befor = obj.QueueSize(), size_after = size_befor;
	try {
		while (is >> num) {
			obj + num;
			size_after = obj.QueueSize();
		}
		if (size_befor == size_after) throw std::exception("Error: Failed to read input from stream.");
	}
	catch (...) {
		throw std::exception("Error: Failed to read input from stream.");
	}
	return is;
}
ostream& operator<<(ostream& os, CQueue& obj) {
	CQueue::Member* pTemp = obj.first;
	if (obj.QueueIsEmpty())
	{
		throw std::exception("Error: Queue is empty.");
	}
	while (pTemp) {
	
		os << *(pTemp->number) << " ";		
		pTemp = pTemp->next;
	}
	return os;
}