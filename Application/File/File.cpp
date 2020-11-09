/*
 * File.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "File.hpp"

#include <cassert>
#include <iostream>

File::File(const std::string Name) :
FileStream(nullptr)  //TODO: consider init with name and mode
	, Name(Name)
{  }

std::string File::read(uint32_t size, uint32_t offset) {
	std::string str(size, '\0');
	std::string rc = "";
	openToRead();
	FileStream.seekg(offset);
	FileStream.read(&str[0], str.size());
	if(!FileStream.eof()) {  //TODO: consider this check one line earlier
		rc = str;
	}
	closeFile();
	return rc;
}

void File::write(const std::string & str) {
	openToWrite();
	FileStream << str;
	closeFile();
}

void File::openToWrite() {
	FileStream.open(Name, std::fstream::out | std::fstream::app);
}

void File::openToRead() {
	FileStream.open(Name, std::fstream::in);
}

void File::closeFile() {
	FileStream.close();
}
