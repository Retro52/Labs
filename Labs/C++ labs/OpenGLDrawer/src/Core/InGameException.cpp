//
// Created by Anton on 25.08.2022.
//

#include "InGameException.h"

InGameException::InGameException(std::string error) : message(std::move(error)) {}

const char *InGameException::what() const noexcept
{
    return message.c_str();
}
