/*
 * File.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "File.hpp"

#include <cassert>

File::File() :
	  fileStream(nullptr)
	, name("")
{   }

File::File(const std::string name) :
	  fileStream(nullptr)
	, name(name)
{  }

std::string File::read(uint32_t size, uint32_t offset) {
	std::string rc = "";
	openToRead();
	if(fileStream.is_open()) {
		fileStream.seekg(offset);
		if(!fileStream.eof()) {
			std::string str(size, '\0');
			fileStream.read(&str[0], str.size());
			//Failbit may be set when reaching eof or exceeding uint32_t max stream size etc.
			if(!fileStream.fail()) {
				rc = str;
			} else {
				fileStream.clear();
			}
		}
		close();
	}
	return rc;
}

bool File::write(const std::string & str) {
	bool openSuccess = openToWrite();
	if(openSuccess) {
		fileStream << str;
		fileStream.flush();
		close();
	}
	return openSuccess;
}

bool File::write(const std::string & str, uint32_t offset) {
	bool openSuccess = fileStream.is_open();
	if(openSuccess) {
		fileStream.seekp(offset);
		if(!fileStream.eof()) {
			fileStream.write(&str[0], str.size());
		}
		fileStream.flush();
	}
	return openSuccess;
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
		fileStream.seekg(0);
		fileStream.read(&str[0], length);
		while(!fileStream.fail()) {
			if(fileStream.tellg() != (offset + length)) {
				newFileStream << str;
			}
			fileStream.read(&str[0], length);
		}

		newFileStream.close();
		close();

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

void File::close() {
	fileStream.close();
}
