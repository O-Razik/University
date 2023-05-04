#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

#include "C:\Users\razik\source\repos\oop_lab8_prog\oop_lab5_prog\class.h"
#include "C:\Users\razik\source\repos\oop_lab8_prog\oop_lab5_prog\class.cpp"
#include "C:\Users\razik\source\repos\oop_lab8_prog\oop_lab5_prog\queue_err_sizeZero.h"
#include "C:\Users\razik\source\repos\oop_lab8_prog\oop_lab5_prog\queue_err_sizeZero.cpp"

class MOCK_CQueue : public CQueue
{
	struct Member;
	Member* first;
	Member* last;

public:
	MOCK_CQueue() {}
	MOCK_CQueue(double first_num) : CQueue(first_num) {}
	MOCK_CQueue(CQueue&& other) : CQueue(other) {}
	MOCK_CQueue(const MOCK_CQueue& other) : CQueue(other) {}
	~MOCK_CQueue() = default;

	MOCK_METHOD(double, getFirst, (), (const));
	MOCK_METHOD(double, getLast, (), (const));

	MOCK_METHOD(unsigned int, QueueSize, (), (noexcept));
	MOCK_METHOD(double, QueueMax, (), ());
	MOCK_METHOD(double, QueueMin, (), ());
	MOCK_METHOD(double, QueueAver, (), ());

	MOCK_METHOD(void, QueueFirstOut, (), (noexcept));
	MOCK_METHOD(void, QueueClear, (), (noexcept));
	MOCK_METHOD(bool, QueueIsEmpty, (), (noexcept));

	MOCK_METHOD1(add, void(double num_memb));
	void operator+(int num_memb) {return add(num_memb);}
	MOCK_METHOD1(min, void(int num_memb));
	void operator-(int num_memb) { return min(num_memb); }
	
	MOCK_METHOD1(multip, void(double scalar));
	void operator*(double scalar) { return multip(scalar); }

	MOCK_METHOD2(inWrapper, istream& (istream& is, CQueue& obj));
	istream& in(istream& is, CQueue& obj) { return is >> obj; }
};
