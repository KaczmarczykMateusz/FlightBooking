/*
 * File.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "File.hpp"

#include <cassert>
#include <iostream>

File::File(const std::string name) :
fileStream(nullptr)  //TODO: consider init with name and mode
	, name(name)
{  }

std::string File::read(uint32_t size, uint32_t offset) {
	std::string str(size, '\0');
	std::string rc = "";
	openToRead();
	fileStream.seekg(offset);
	fileStream.read(&str[0], str.size());
	if(!fileStream.eof()) {  //TODO: consider this check one line earlier
		rc = str;
	}
	closeFile();
	return rc;
}

void File::write(const std::string & str) {
	openToWrite();
	fileStream << str;
	closeFile();
}

void File::openToWrite() {
	fileStream.open(name, std::fstream::out | std::fstream::app);
}

void File::openToRead() {
	fileStream.open(name, std::fstream::in);
}

void File::closeFile() {
	fileStream.close();
}
