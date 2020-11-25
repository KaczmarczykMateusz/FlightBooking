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
	/*
	 * Provides interface for reading at offset relative to last read
	 * In order to use ensure to open file before and close after
	 */
	std::string readOff(uint32_t size, uint32_t relativeOffset);

	bool write(const std::string & str);
	bool eraseRecord(std::string & toRemove, uint32_t recordLength);
	void setName(const std::string & str);

private:
	std::fstream fileStream;
	std::string name;

	bool openToWrite();
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
