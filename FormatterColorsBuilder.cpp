#include "include/FormatterColorsBuilder.h"

namespace NFCServer
{
    namespace Logger
    {

        FormatterColorsBuilder::FormatterColorsBuilder(const std::string& _message) {
            this->_builderMessage = _message;
            this->_foregroundColor = ForegroundFormatColor::FG_DEFAULT;
            this->_backgroundColor = BackgroundFormatColor::BG_DEFAULT;
            this->_isMessageBold = false;
            this->_isMessageItalic = false;
            this->_isMessageStrikethrough = false;
            this->_isMessageUnderline = false;
        }
        FormatterColorsBuilder::~FormatterColorsBuilder() {}
        FormatterColorsBuilder::FormatterColorsBuilder(const FormatterColorsBuilder &rhs)
        {
            this->_builderMessage = rhs._builderMessage;
        }
        FormatterColorsBuilder FormatterColorsBuilder::operator=(const FormatterColorsBuilder &rhs)
        {
            if (this == &rhs) return *this;
            this->_builderMessage = rhs._builderMessage;
            return *this;
        }
        FormatterColorsBuilder &FormatterColorsBuilder::Color(ForegroundFormatColor fgColor, BackgroundFormatColor bgColor)
        {
            this->_backgroundColor = bgColor;
            this->_foregroundColor = fgColor;
            return *this;
        }
        FormatterColorsBuilder &FormatterColorsBuilder::Bold() {
            this->_isMessageBold = true;
            return *this;
        }

        FormatterColorsBuilder &FormatterColorsBuilder::Italic() {
            this->_isMessageItalic = true;
            return *this;
        }

        FormatterColorsBuilder &FormatterColorsBuilder::UnderLine() {
            this->_isMessageUnderline = true;
            return *this;
        }

        FormatterColorsBuilder &FormatterColorsBuilder::Strikethrough() {
            this->_isMessageStrikethrough = true;
            return *this;
        }

        const std::string FormatterColorsBuilder::ToString() {

            std::stringstream ss;

            std::string _foregroundColor = std::to_string((int) this->_foregroundColor);
            std::string _backgroundColor = std::to_string((int) this->_backgroundColor);

            ss << "\033[";

            // TODO: multiple applicable styles on message
            if (this->_isMessageBold) ss << "1";
            else if (this->_isMessageItalic) ss << "3";
            else if (this->_isMessageStrikethrough) ss << "9";
            else if (this->_isMessageUnderline) ss << "4";
            // TODO: serve background color
            ss << ";" << _foregroundColor;

            ss << "m";
            
            ss << this->_builderMessage;
            ss << "\033[0m";
            return ss.str();
        }
    }
}