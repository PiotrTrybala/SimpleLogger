#include <iostream>
#include <string>
#include <cstdlib>
#include "FormatterTypes.h"
#include <sstream>

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
            bool _isColoringUsed;
            bool _isStylingUsed;

            bool IsStylingEnabled() {
                return this->_isMessageBold;
            }

            bool IsColoringEnabled() {
                return this->_backgroundColor != BackgroundFormatColor::BG_DEFAULT 
                    || this->_foregroundColor != ForegroundFormatColor::FG_DEFAULT;
            }


        public:
            FormatterColorsBuilder();
            FormatterColorsBuilder(const std::string& _message);
            ~FormatterColorsBuilder();
            FormatterColorsBuilder(const FormatterColorsBuilder &rhs);
            FormatterColorsBuilder operator=(const FormatterColorsBuilder &rhs);

            FormatterColorsBuilder& AddBuilderMessage(const std::string& _message) {
                this->_builderMessage = _message;
                return *this;
            }

            FormatterColorsBuilder &Color(ForegroundFormatColor fgColor, BackgroundFormatColor bgColor  = BackgroundFormatColor::BG_DEFAULT);
            FormatterColorsBuilder &Bold();
            FormatterColorsBuilder &Italic();
            FormatterColorsBuilder &UnderLine();
            FormatterColorsBuilder &Strikethrough();
            const std::string ToString();
        };

    }
}
