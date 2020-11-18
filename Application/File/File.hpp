/*
 * File.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FILE_HPP_
#define APPLICATION_FILE_HPP_

#include "../FlightManagement/Flight.hpp"
#include "../UserInterface.hpp"
#include "../Common/Common.hpp"

#include <fstream>
#include <string>
#include <vector>

//XXX: Define only globally
class File {
public:
	File();
	File(const std::string name);

	virtual ~File() = default;

	virtual bool getRecord(std::string &dst, uint16_t recordNumber) = 0;

protected:
	std::string read(uint32_t size, uint32_t offset);  //TODO: Provide method for reading further than max stream size
	bool write(const std::string & str);
	bool write(const std::string & str, uint32_t offset);  //TODO: Provide method for writing further than max stream size
	bool erase(uint32_t offset, uint32_t length);
	void setName(const std::string & str);

private:
	std::fstream fileStream;
	std::string name;

	bool openToWrite();
	bool openToRead();
	void close();
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
