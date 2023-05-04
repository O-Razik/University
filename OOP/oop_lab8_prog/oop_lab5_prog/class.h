#pragma once
#include <iostream>
#include "queue_err_sizeZero.h"
using namespace std;

class CQueue {
private:

	struct Member;
	Member* first;
	Member* last;

public:

	double getFirst() const;
	double getLast() const;

	CQueue();
	CQueue(double _first_num);

	CQueue(const CQueue& other);
	CQueue(CQueue&& other);
	CQueue& operator=(const CQueue& other);
	CQueue& operator=(CQueue&& other);

	~CQueue() noexcept;

	unsigned int QueueSize() noexcept;

	double QueueMax();
	double QueueMin();
	double QueueAver();

	void QueueFirstOut() noexcept;
	void QueueClear() noexcept;
	bool QueueIsEmpty() noexcept;
	void operator+(double num);

	void operator-(int num_memb);

	void operator*(double scalar);

	friend istream& operator>>(istream& is, CQueue& obj);
	friend ostream& operator<<(ostream& os, CQueue& obj);
};