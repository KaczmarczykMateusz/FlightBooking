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
	Passenger(std::string firstName, std::string surname, uint64_t personalId);
	Passenger(std::string str);

	std::string getFirstName() const;
	std::string getSurname() const;
	uint64_t getPersonalId() const;
	bool getCheckedIn() const;
	void setCheckedIn(bool checkIn);

private:
	std::string firstName;
	std::string surname;
	uint64_t personalId;
	bool checkedIn;
};

#endif /* APPLICATION_FLIGHTMANAGEMENT_PASSENGER_H_ */
