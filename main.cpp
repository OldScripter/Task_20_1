#include <iostream>
#include <fstream>
#include <sstream>

const int MIN_YEAR = 1987;
const int MAX_YEAR = 2022;
const char* FILE_PATH = "..\\Output.txt";

/*
 * Check if payment format is OK.
 * Returns the payment after transform to integer.
 * Puts 'errorFlag' to true if input is incorrect.
 */
int checkIfPaymentFormatIsCorrect(const std::string& paymentInput, bool& errorFlag)
{
    try
    {
        return std::stoi(paymentInput);
    }
    catch (const std::invalid_argument& ia)
    {
        errorFlag = true;
        std::cerr << "Payment value error\n";
        return -1;
    }
}
//John Dow 15.11.2020 7900
/*
 * Check if dateInput format is OK.
 * Returns the date after transform to integer of day, month and year.
 * Puts 'errorFlag' to true if input is incorrect.
 */
std::string checkIfDateFormatIsOk(const std::string& dateInput, bool& errorFlag)
{
    if (dateInput.length() < 10)
    {
        errorFlag = true;
        std::cerr << "Length error\n";
        return "Length error";

    }

    std::string dayStr = dateInput.substr(0, 2);
    std::string monthStr = dateInput.substr(3, 2);
    std::string yearStr = dateInput.substr(6, 4);

    try
    {
        int day = std::stoi(dayStr);
        int month = std::stoi(monthStr);
        int year = std::stoi(yearStr);

        if (day > 0 && day < 32 &&
            month > 0 && month < 13 &&
            year > MIN_YEAR && year < MAX_YEAR)
        {
            dayStr = (day < 10 ? "0" + std::to_string(day) : std::to_string(day)) + ".";
            monthStr = (month < 10 ? "0" + std::to_string(month) : std::to_string(month)) + ".";
            yearStr = std::to_string(year);
            return dayStr + monthStr + yearStr;
        }
        else
        {
            errorFlag = true;
            std::cerr << "Date values error\n";
            return "Date values error";
        }
    }
    catch (const std::invalid_argument& ia)
    {
        errorFlag = true;
        std::cerr << "Date invalid arguments error\n";
        return "Date invalid arguments error";
    }
}

/*
 * Writes the string stream to file.
 */
void writeStreamToFile(const std::stringstream& stream, const char* filePath)
{
    std::ofstream outStream (filePath, std::ios::app);
    if (outStream.is_open())
        outStream << stream.rdbuf();
    else
        std::cout << "Error while opening the file.\n";
    outStream.close();
        std::cout << "File is saved.\n";
}

int main() {
    bool inputError;
    std::string name;
    std::string surname;
    std::string date;
    std::string paymentStr;
    int payment;
    do
    {
        inputError = false;

        //Get input:
        std::string input;
        std::cout << "Please enter the data line in format [name] [surname] [dd.mm.yyyy] [payment]:\n";
        getline(std::cin, input);
        std::stringstream inputStream(input);
        inputStream >> name >> surname >> date >> paymentStr;


        //Check if input error appears:
        date = checkIfDateFormatIsOk(date, inputError);
        payment = checkIfPaymentFormatIsCorrect(paymentStr, inputError);

        if (inputError)
            std::cout << "Input error in date or payment format, please try again.\n";

    }   while (inputError);

    //Forming the stream for output:
    std::stringstream streamToWrite;
    streamToWrite << name << " " << surname << " " << date << " " << payment << '\n';

    //Write data in file:
    writeStreamToFile(streamToWrite, FILE_PATH);

    return 0;
}
