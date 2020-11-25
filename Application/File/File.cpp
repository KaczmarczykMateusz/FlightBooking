/*
 * File.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#include "File.hpp"

#include <cassert>
#include <iostream>

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

std::string File::readOff(uint32_t size, uint32_t relativeOffset) {
	std::string rc = "";
	if(fileStream.is_open()) {
		fileStream.seekg(relativeOffset, std::fstream::seekdir::_S_cur);
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
	} else {
		assert(0);
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

bool File::eraseRecord(std::string & toRemove, uint32_t recordLength) {
	bool rc = false;
	do {
		std::ofstream newFileStream("tmp.dat", std::fstream::trunc | std::fstream::binary);
		if(!newFileStream.is_open()) {
			break;
		}

		openToRead();
		uint32_t recordOffset = recordLength + 1;
		//XXX: For cross platform compatibility ('\n' vs 'r''n')
		StringUtilities::rtrimNewLine(toRemove);
		fileStream.seekg(0);
		std::string str(recordOffset, ' ');
		fileStream.read(&str[0], recordOffset);
		while(!fileStream.fail()) {
			StringUtilities::rtrimNewLine(str);
			if(str.compare(toRemove)) {
				newFileStream << str << '\n';
			}
			fileStream.read(&str[0], recordOffset);
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
	fileStream.open(name, std::fstream::in | std::fstream::binary);
	return fileStream.is_open();
}

void File::close() {
	fileStream.close();
}
