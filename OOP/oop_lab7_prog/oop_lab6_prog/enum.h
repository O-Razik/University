#pragma once

enum class Tariff
{
	None,
	LightWeight,
	MiddleWeight,
	HeavyWeight
};

enum class Priority
{
	NonPriority, has_priority
};

enum class Address
{
	unKnown, Region, Ukraine, Abroad
};

enum class Currency {
	None, UAH, USD
};