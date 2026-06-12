#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

int main()
{

    std::string secretPin = "";
    std::cout << "Please create a PIN: ";
    std::cin >> secretPin;
    int pinLength = 4;

    int maxAttempts = 1;
    for (int i = 0; i < pinLength; i++)
    {
        maxAttempts *= 10;
    }

    for (int i = 0; i < maxAttempts; i++)
    {
        std::stringstream ss;
        ss << std::setw(pinLength) << std::setfill('0') << i;

        std::string guess = ss.str();

        std::cout << "Trying: " << guess << std::endl;

        if (guess == secretPin)
        {
            std::cout << "PIN found: " << guess << std::endl;
            std::cout << "Attempts: " << i + 1 << std::endl;
            break;
        }
    }

    return 0;
}