#pragma once
#include <iostream>
#include <exception>
#include <string>

class queue_err_sizeZero : std::exception
{
public:
    queue_err_sizeZero() = default;
    char const* what() const override;
};

