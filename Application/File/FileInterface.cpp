/*
 * FileInterface.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "FileInterface.hpp"

#include <cassert>
#include <iostream>

FileInterface::FileInterface(const std::string Name) :
	File(nullptr)  //TODO: consider init with name and mode
	, Name(Name)
{  }
