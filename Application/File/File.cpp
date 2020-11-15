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

void File::write(const std::string & str, uint32_t offset) {
	fileStream.open(name, std::fstream::in | std::fstream::out);
	fileStream.seekp(offset);
	if(!fileStream.eof()) {
		fileStream.write(&str[0], str.size());
	}
	closeFile();
}

bool File::erase(uint32_t offset, uint32_t length) {
	bool rc = false;
	do {
		std::ofstream newFileStream("tmp.dat", std::fstream::trunc | std::fstream::binary);
		if(!newFileStream.is_open()) {
			break;
		}

		openToRead();
		std::string str(length, '\0');
		fileStream.read(&str[0], length);
		while(!fileStream.eof()) {
			if(fileStream.tellg() != (offset + length)) {
				newFileStream << str;
			}
			fileStream.read(&str[0], length);
		}

		newFileStream.close();
		fileStream.close();

		if(0 != remove(name.c_str())) {
			break;
		} else {
			if (0 != rename("tmp.dat" , name.c_str())) {
				break;
			}
		}
		rc = true;
	} while(0);

	return rc;
}

void File::setName(const std::string & str) {
	name = str;
}

bool File::openToWrite() {
	fileStream.open(name, std::fstream::out | std::fstream::app | std::fstream::binary);
	return fileStream.is_open();
}

bool File::openToRead() {
	//XXX: Reading in text (not binary) mode causes tellg() to return wrong pos
	fileStream.open(name, std::fstream::in | std::fstream::binary);
	return fileStream.is_open();
}

void File::closeFile() {
	fileStream.close();
}
