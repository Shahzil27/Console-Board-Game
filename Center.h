//
// Center.h
//
//
#pragma once

#include <iostream>
#include <sstream>
#include <string>


template <typename Data>
std::string center(const Data& value);

template <typename Data>
std::string center(const Data& value, unsigned int width);

#include "Center.inl"
