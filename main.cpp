/*
 * Initial Idea of the project:
 *     Construct Flight management system letting user to add new(admin lvl),
 *     book, check flights, see their schedule and search for flies  (also with interchanges).
 *     Records will be stored in .dat files distinctive to passanger class and flight schedule class.
 *     It will be possible to display schedule for specific airport on specific date.
 *
 *     There will be module of project or separate project to generate random records in order
 *     to test algorithms efficiency etc.
 *
 *     @Notes: Program builds with Gcc compiler with c++ dialect selected to C++14 (-std=c++14)
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>
#include <limits>
#include <vector>

//using std::__cxx11::string; //TODO: check wheteher to enablein windows
using std::string;
using std::cout;
using std::cin;
using std::endl;

const uint32_t NAME_LENGTH = 30 + 1;
const uint32_t NUMBER_OFFSET = 0;
const uint32_t NUMBER_LENGTH = 5 + 1;
const uint32_t COMPANY_NAME_OFFSET = NUMBER_OFFSET + NUMBER_LENGTH;
const uint32_t COMPANY_NAME_LENGTH = 20 + 1;
const uint32_t DEPARTURE_AIRPORT_OFFSET = COMPANY_NAME_OFFSET + COMPANY_NAME_LENGTH;
const uint32_t DEPARTURE_AIRPORT_LENGTH = 20 + 1;
const uint32_t ARRIVAL_AIRPORT_OFFSET = DEPARTURE_AIRPORT_OFFSET + DEPARTURE_AIRPORT_LENGTH;
const uint32_t ARRIVAL_AIRPORT_LENGTH = 20 + 1;
const uint8_t  DEPARTURE_DATE_OFFSET = ARRIVAL_AIRPORT_OFFSET + ARRIVAL_AIRPORT_LENGTH;
const uint32_t DEPARTURE_DATE_LENGTH = 6;
const uint8_t  DEPARTURE_TIME_OFFSET = DEPARTURE_DATE_OFFSET + DEPARTURE_DATE_LENGTH;
const uint32_t DEPARTURE_TIME_LENGTH = 4;
const uint32_t NEW_LINE_OFFSET = DEPARTURE_TIME_OFFSET + DEPARTURE_TIME_LENGTH;
const uint32_t NEW_LINE_LENGTH = 1;

const uint32_t RECORD_OFFSET = NEW_LINE_OFFSET + NEW_LINE_LENGTH;
const uint32_t RECORD_LENGTH = RECORD_OFFSET;


const string departureCityReq = "Insert departure airport name:\n\n";
const string arrivalCityReq = "Insert arrival airport name:\n\n";
const string newLineStr = "\n\n\n\n\n\n\n\n\n";
const char SEPARATOR = ' ';


struct Time {
	uint8_t Hour;
	uint8_t Minute;
	Time() :
	Hour(0),
	Minute(0)
	{}
};

struct Date {
	uint16_t Year;
	uint8_t Month;
	uint8_t Day;
	Date() :
		Year(0),
		Month(0),
		Day(0)
	{}
};

struct DateTime {
	Time time;
	Date date;
};


class Flight {
	uint16_t Number;
	char Company[COMPANY_NAME_LENGTH];
	DateTime Departure;

public:
	Flight() :
		Number(0),
		Company("\0")
		{}
	void DisplayDetails(uint16_t flightNo) { //TODO: decide whether to use this function
		cout << "Flight No.:\t\tCompany name:\t\tDeparture date:\t\tDeparture time:" << endl;
		cout << (int)Number << "\t\t\t" << Company << "\t\t" <<  (int)Departure.date.Day << "/"
				<< (int)Departure.date.Month << "/" <<  (int)Departure.date.Year << "\t\t\t"
				<< (int)Departure.time.Hour << ":" <<  (int)Departure.time.Minute << endl; //TODO: leading 0
	}

	void SetNumber(uint16_t numb) {
		Number = numb;
	}

	void SetCompanyName(const char * name) {
		strcpy(Company, name);
	}

	void SetDeparture(DateTime depart) {
		Departure = depart;
	}
};

//Mode of searching
typedef enum SearchBy{
	COMPANY,
	DEPARTURE_AIRPORT,
	ARRIVAL_AIRPORT,
	DEPARTURE_DATE
};
#include <stdarg.h>  // For va_start, etc.

#include <algorithm> //For base() etc

class StringUtilities {
public:

	//Trim from end
	static inline void rtrim(std::string &s) {
	    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
	        return !std::isspace(ch);
	    }).base(), s.end());
	}
};

class UserInterface: public StringUtilities {
public:
	/* Input:
	 * fmt Formated buffer where the resulting string is stored.
	 * arg ... (additional arguments)
	 * Depending on the format string, the function may
	 * expect a sequence of additional arguments, each
	 * containing a value to be used to replace a format
	 * specifier in the format string (or a pointer to a storage location, for n).
	 * There should be at least as many of these arguments as the
	 * number of values specified in the format specifiers.
	 * Additional arguments are ignored by the function
	 */
	void Display(const std::string fmt, ...) {
		va_list ap;
		std::string str;
		int32_t size = fmt.length() * 2 + 20;
		while(1) {
			str.resize(size);
			va_start(ap, fmt);
			int32_t n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
			va_end(ap);
			if(-1 < n && n < size) { //Success
				str.resize(n);
				break;
			} else if(n == size) { //Add space for Null terminations sign
				size += 1;
			} else if(-1 < n) {	//Reserve more space
				size += n * 2;
			} else {
				assert(0); //XXXwe should never rnd up here
				throw std::runtime_error("Error in string processing");
			}
		}
		cout << str;
	}

	string GetDate() {
		string input(DEPARTURE_DATE_LENGTH + 2, '\0');
		const string date[4] = {"DAY", "MONTH", "YEAR", "SEPARATOR"};
		const uint16_t minDate[3] = {1, 1, 2019};
		const uint16_t maxDate[3] = {31, 12, 2050};
		const string delimeter(1, '/');

		string rc;
		do {
			rc = "";
			cout << "Enter date (dd/mm/yyyy) :" << endl;
			std::getline(cin, input);

			size_t pos = 0;
			for(uint8_t i = 0; i < 3; i++) {
				pos = input.find(delimeter);

				try {
					if(		(std::string::npos == pos)
							&& (2 != i)  ) {
						i = 3;
						throw std::invalid_argument("User; wrong separator");
					}
					string tmp(2, '\0');
					tmp = input.substr(0, pos);
					input.erase(0, pos + delimeter.length());
					if(	(minDate[i] > std::stoul(tmp))
							|| (maxDate[i] < std::stoul(tmp)) ) {
						throw std::invalid_argument("User; out of range");
					} else {
						if(tmp.length() > ((DEPARTURE_DATE_LENGTH)/3)) {
							tmp.erase(0, ((DEPARTURE_DATE_LENGTH)/3));
						}
						rc.append(tmp);
					}
				} catch(std::invalid_argument & arg) {
					cout << "\n\n\n\n\n\n\n\nException caught by: " << arg.what()  << ".\n" << "You entered WRONG "  << date[i] << "!\n\n";
					break;
				} catch(std::out_of_range & arg) {
					cout << "\n\n\n\n\n\n\n\nException caught by: " << arg.what()  << ".\n" << "You entered WRONG "  << date[i] << "!\n\n";
					break;
				}
			}
		} while(6 != rc.size());
		if(6 != rc.size()) {
			throw "Wrong data size caused by program bug (not user)";
		}
		return rc;
	}

	//Ask user to enter detail and save this detail into dst string
	void RegisterRecord(string & dst, string output, uint32_t offset, uint32_t length) {
		while(1) {
			//output.insert(0, newLineStr);
			Display("%s%s", newLineStr.c_str(), output.c_str());
			string input(length, '\0');
			getline(cin, input);
			if(length < strlen(input.c_str())) {
				Display("Please enter name not longer than %d", (uint32_t)length-1 );
				continue;
			} else {
				//We need to insert separator because getline adds null termination sign
				input.insert(input.length(), length-input.length(), SEPARATOR);
				try {
					dst.replace(offset, strlen(input.c_str()), input);
				}
				catch(...) {
					Display("dst.size: %d\toffset: %d\tlength: %d", dst.size(), offset, length);
					assert(0);// TODO: consider some action
				}
				break;
			}
		}
	}
};

class FileInterface {
	UserInterface UI;
	std::fstream flights;


	void openToWrite() {
		flights.open("flights.dat", std::fstream::out | std::fstream::app);
	}
	void openToRead() {
		flights.open("flights.dat", std::fstream::in | std::fstream::app);
	}
	void closeFile() {
		flights.close();
	}

public:

	// Return: false if record doesn't exist
	bool GetRecord(std::string &dst, uint16_t recordNumber) {
		bool rc = true;
		openToRead();
		flights.seekg(RECORD_OFFSET*(recordNumber - 1));
		flights.read(&dst[0], RECORD_LENGTH);
		if(flights.eof()) {
			rc = false;
		}
		closeFile();
		dst.insert(DEPARTURE_DATE_OFFSET + 2, "/");
		dst.insert(DEPARTURE_DATE_OFFSET + 5, "/");
		dst.insert(DEPARTURE_DATE_OFFSET + 6, "20");
		dst.insert(DEPARTURE_TIME_OFFSET + 4, " ");
		dst.insert(DEPARTURE_TIME_OFFSET + 7, ":");
		return rc;
	}

	std::string search(SearchBy key, const std::string) {
		string str(RECORD_LENGTH, '\0');

		return str;
	}

	uint32_t SearchGreatestNo() {
		openToRead();
		uint32_t greatest = 0;
		uint32_t i = 0;
		while(!flights.eof()) {
			flights.seekg(RECORD_OFFSET*i);
			i++;
			string output(NUMBER_LENGTH, '\0');
		    flights.read(&output[0], NUMBER_LENGTH);
		    if(!flights.eof()) {
				try {
					if(greatest < std::stoul(output)) {
						greatest = std::stoul(output);
					}
				}
				catch(...) {
					cout << "FAIL SEARCHING FOR NUMBER " << output << endl;
				}
		    }
		}

		closeFile();
		return greatest;
	}

	bool SearchDetail(string & dst, uint32_t offset, uint16_t length) {
		bool rc = false;
		openToRead();
		flights.seekg(offset);
		string str(length, SEPARATOR);
		//str.replace(0, dst.size(), dst);
		flights.read(&str[0], length);
		if(!flights.eof()) {
			if(str.length() > length)  {
				rc = false;
			} else {
				UI.rtrim(str);
				dst = str;
			}
			rc = true;
		}
		closeFile();
		return rc;
	}

	void SearchFlight() {
		string depatrureCity(DEPARTURE_AIRPORT_LENGTH, SEPARATOR);
		string arrivalCity(ARRIVAL_AIRPORT_LENGTH, SEPARATOR);

	//	string date = UI.GetDate();
		UI.RegisterRecord(depatrureCity, departureCityReq, 0, DEPARTURE_AIRPORT_LENGTH);
		UI.rtrim(depatrureCity);
		UI.RegisterRecord(arrivalCity, arrivalCityReq, 0, ARRIVAL_AIRPORT_LENGTH);
		UI.rtrim(arrivalCity);

		std::vector<string> retVal;
		string output(DEPARTURE_AIRPORT_LENGTH, '\0');
		uint32_t recordOffset = 0;
		while(SearchDetail(output, DEPARTURE_AIRPORT_OFFSET + recordOffset, DEPARTURE_AIRPORT_LENGTH)) {
			if(output == depatrureCity) {\
				output.resize(ARRIVAL_AIRPORT_LENGTH, '\0');
				if(SearchDetail(output, ARRIVAL_AIRPORT_OFFSET + recordOffset, ARRIVAL_AIRPORT_LENGTH)) {
					if(output == arrivalCity) {
						output.clear();
						output.resize(NUMBER_LENGTH, '\0');
					//	SearchDetail(output, recordOffset, RECORD_LENGTH);


						SearchDetail(output,  NUMBER_OFFSET + recordOffset, NUMBER_LENGTH);
						output.resize(RECORD_LENGTH, '\0');
						GetRecord(output, std::stoul(output));
					//	output.resize(RECORD_LENGTH, '\0');


						retVal.push_back(output);
						cout << output;
					}
				}
			}
			output.clear();
			output.resize(DEPARTURE_AIRPORT_LENGTH, '\0');
			recordOffset += RECORD_OFFSET; //TODO: do we need it
		}
		if(retVal.empty()) {
			cout << "NOT found: " << depatrureCity << ", output: " <<  output << endl;
		}
	}

	void writeFlights(const string input, uint8_t length) {
		openToWrite();
		string text(length, '\0');
		text.replace(0, length, input);
		flights.write(  text.c_str(), length  );	//.c_str() too get C like NULL TERMINED string
		closeFile();
	}
};

#include <sstream>
#include <stdexcept>
class FlightCenter {
	UserInterface UI;
	FileInterface File;
public:
	uint8_t MainMenu() {
		uint8_t choice = 0;
		do {
			//memcpy(&text[0], " ", 1);	//It's allowed since c++11
			string text =
			{ "\n"
			"--------------------------------------------------------\n"
			"***************FLIGHT CENTER POKAHONTAS****************\n"
			"--------------------------------------------------------\n"
			"What would you like to do: (chose with numeric keypad)\n"
			"1 - Book new fligt            2 - Check-in\n"
			"3 - Check your fligt          4 - Check flight schedule\n"
			"5 - Register new flight       6 - Delete flight\n"
			"7 - Exit system\n" };
			UI.Display(text);

			string input(1, '\0');
			//TODO: find solution for below
//			getline(cin, input); //In debug session input is not clear and this eats cin buffer//TODO: check why
			getline(cin, input);

			try {
				choice = std::stoul(input);
			}
			catch(...) {
				choice = 255; //Invalid index
			}
			if(7 < choice-'0') {
				text = { "\n\n\n\n\n\nInvalid number, please enter right digit\n\n" };
				cout << "\n\n\n Entered digit:   " <<choice << endl;
				UI.Display(text);
			}
		} while(7 < (choice-'0'));
		return choice;
	}

	uint32_t GeteGreatestFlightNo(FileInterface & file) {
		return file.SearchGreatestNo();
	}

	void DisplayAllRecords(FileInterface & file) {
		uint8_t getIndex = 1;
		string output(RECORD_LENGTH, '\0');
		while(file.GetRecord(output, getIndex)) {
			getIndex +=1;
			cout << output;
			output.resize(RECORD_OFFSET, '\0');
		}
	}

	string search(SearchBy key) {
		string str(RECORD_LENGTH, '\0');

		return str;
	}

	void Book() {
/*		string str(DEPARTURE_AIRPORT_LENGTH ,'\0');
		UI.Display("From where do you want to departure? Enter city name: ");
		getline(cin, str);
		str.empty();
		UI.Display("Where do you want to go? Enter city name: ");
		getline(cin, str);*/
		File.SearchFlight();
		//TODO: continue with booking
	}

	void RegisterNew() {

		string record(RECORD_LENGTH, '\0');

		string numberStr(NUMBER_LENGTH+1, ' ');
		uint32_t flightNo = GeteGreatestFlightNo(File) + 1;
		numberStr.replace(0, std::to_string(flightNo).size(), std::to_string(flightNo)); //TODO: exception handling?
		record.replace(NUMBER_OFFSET, NUMBER_LENGTH, numberStr);

		UI.RegisterRecord(record, "Insert company name:\n\n", COMPANY_NAME_OFFSET, COMPANY_NAME_LENGTH);
		UI.RegisterRecord(record, departureCityReq, DEPARTURE_AIRPORT_OFFSET, DEPARTURE_AIRPORT_LENGTH);
		UI.RegisterRecord(record, arrivalCityReq, ARRIVAL_AIRPORT_OFFSET, ARRIVAL_AIRPORT_LENGTH);

		try {
			record.replace(DEPARTURE_DATE_OFFSET, DEPARTURE_DATE_LENGTH, UI.GetDate());
			record.replace(NEW_LINE_OFFSET, NEW_LINE_LENGTH, "\n");
		}
		catch(std::out_of_range & arg) {
			cout << "\trecord.size(): " <<record.size() << endl;
			cout << "NEW_LINE_OFFSET: " << NEW_LINE_OFFSET << "\tNEW_LINE_LENGTH: " << NEW_LINE_LENGTH << endl;
		}
		catch(const char* message) {
			cout << "\n\n\n" << message;
		};

		File.writeFlights(record, RECORD_LENGTH);
	}

	void ChooseAction(uint8_t mainChoice) {
		switch(mainChoice) {
		case 1:    //Book new fligt
			Book();
			break;
		case 2:    //Check-in
			assert(0); //TODO: fill case
			break;
		case 3:    //Check your fligt
			assert(0);
			break;
		case 4:    //Check flight schedule
			DisplayAllRecords(File);
			break;
		case 5:    //Register new flight
			RegisterNew();
			break;
		case 6:    //Delete flight
			assert(0); //TODO: fill case
			break;
		case 7:    //Exit program
			break;
		default:
			assert(0);
		}
	}

	UserInterface & GetUI() {
		return UI;
	}
};

int main() {
	FlightCenter flightCent;
	uint8_t index = 0;
	while(index != 7) {
		index = flightCent.MainMenu();
		flightCent.ChooseAction(index);
		flightCent.GetUI().Display("\nPress enter in order to continue");
		if(7 != index) {
			string str;
			std::getline(cin, str);
		}
	}
}
