/*
 * FileInterface.hpp
 *
 *  Created on: 29 Oct 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FILEINTERFACE_HPP_
#define APPLICATION_FILEINTERFACE_HPP_

#include "../FlightManagement/Flight.hpp"
#include "../UserInterface.hpp"
#include "../Common/Common.hpp"

#include <fstream>
#include <string>
#include <vector>

class FileInterface {
public:
	FileInterface(const std::string Name);

	virtual ~FileInterface() = default;

	virtual bool GetRecord(std::string &dst, uint16_t recordNumber) = 0;

protected:
	//TODO: make private and inmplement getters
	std::fstream File;  //TODO: implement separate streams for input and output

	void openToWrite() {
		File.open(Name, std::fstream::out | std::fstream::app);
	}
	void openToRead() {
		File.open(Name, std::fstream::in);
	}
	void closeFile() {
		File.close();
	}

private:
	std::string Name;
};


#endif /* APPLICATION_FILEINTERFACE_HPP_ */
