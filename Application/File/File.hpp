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

class File {
public:
	File(const std::string Name);

	virtual ~File() = default;

	virtual bool GetRecord(std::string &dst, uint16_t recordNumber) = 0;

protected:
	std::string read(uint32_t size, uint32_t offset);
	void write(const std::string & str);

private:
	std::fstream FileStream;  //TODO: implement separate streams for input and output
	std::string Name;

	void openToWrite();
	void openToRead();
	void closeFile();
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
