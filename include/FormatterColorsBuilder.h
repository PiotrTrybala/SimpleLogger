#include <iostream>
#include <string>
#include <cstdlib>
#include "FormatterType.h"

using std::string;

namespace NFCServer
{
    namespace Logger
    {

        class FormatterColorsBuilder
        {

            string _builderMessage;

        public:
            FormatterColorsBuilder();
            ~FormatterColorsBuilder();
            FormatterColorsBuilder(const FormatterColorsBuilder &rhs);
            FormatterColorsBuilder operator=(const FormatterColorsBuilder &rhs);

            FormatterColorsBuilder &Color(ForegroundFormatColor fgColor, BackgroundFormatColor bgColor = BackgroundFormatColor::BG_DEFAULT);
            FormatterColorsBuilder &Bold();
            FormatterColorsBuilder &Italic();
            FormatterColorsBuilder &UnderLine();
            FormatterColorsBuilder &Strikethrough();
            const std::string &ToString();
        };

    }
}
