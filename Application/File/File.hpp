/*
 * File.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 *
 *  Description: Base class for handling record files
 */

#ifndef APPLICATION_FILE_HPP_
#define APPLICATION_FILE_HPP_

#include "../FlightManagement/Flight.hpp"
#include "../UserInterface.hpp"
#include "../Common/Common.hpp"

#include <fstream>
#include <string>
#include <vector>

class File {
public:
	File();
	File(const std::string name);

	virtual ~File() = default;

	virtual bool getRecord(std::string &dst, uint16_t recordNumber) = 0;
	void close();

protected:
	bool openToRead();
	std::string read(uint32_t size, uint32_t offset);
	//In order to use ensure to open file before and close after
	std::string readOff(uint32_t size, uint32_t skipBefore);

	bool write(const std::string & str);
	bool write(const std::string & str, uint32_t offset);  //TODO: Remove method
	bool erase(uint32_t offset, uint32_t length); //TODO: Provide method for erasing further than max stream size
	void setName(const std::string & str);

private:
	std::fstream fileStream;
	std::string name;

	bool openToWrite();
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
