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

            ForegroundFormatColor _foregroundColor = ForegroundFormatColor::FG_DEFAULT;
            BackgroundFormatColor _backgroundColor = BackgroundFormatColor::BG_DEFAULT;
            bool _isMessageBold;
            bool _isMessageItalic;
            bool _isMessageStrikethrough;
            bool _isMessageUnderline;


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
