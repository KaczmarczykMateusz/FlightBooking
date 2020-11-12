/*
 * Passenger.h
 *
 *  Created on: 12 lis 2020
 *      Author: Mateusz Kaczmarczyk
 */

#ifndef APPLICATION_FLIGHTMANAGEMENT_PASSENGER_H_
#define APPLICATION_FLIGHTMANAGEMENT_PASSENGER_H_

#include <string>

class Passenger {
public:
	Passenger(std::string firstName, std::string surname, uint32_t id);
	Passenger(std::string str);

	std::string getFirstName() const;
	std::string getSurname() const;
	uint32_t getId() const;
	bool getCheckedIn() const;

private:
	std::string firstName;
	std::string surname;
	uint32_t id;
	bool checkedIn;
};

#endif /* APPLICATION_FLIGHTMANAGEMENT_PASSENGER_H_ */
