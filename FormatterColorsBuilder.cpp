#include "include/FormatterColorsBuilder.h"

namespace NFCServer
{
    namespace Logger
    {
        FormatterColorsBuilder::FormatterColorsBuilder() {

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

        FormatterColorsBuilder &FormatterColorsBuilder::Color(ForegroundFormatColor fgColor, BackgroundFormatColor bgColor = BackgroundFormatColor::BG_DEFAULT)
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
        }

        const std::string &FormatterColorsBuilder::ToString() {}
    }
}