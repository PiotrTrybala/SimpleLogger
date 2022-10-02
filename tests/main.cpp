#include "../include/FormatterColorsBuilder.h"

#include <iostream>

using namespace NFCServer::Logger;
using namespace std;

int main() {
    
    FormatterColorsBuilder builder {"This is simple message"};
    
    string _formattedMessage = builder
        .Color(ForegroundFormatColor::FG_CYAN)
        .Bold()
        .ToString();

    std::cout << _formattedMessage << std::endl;

    return 0;
}