#include "include/FormatterColorsBuilder.h"

namespace NFCServer
{
    namespace Logger
    {
        FormatterColorsBuilder::FormatterColorsBuilder() {
            this->_foregroundColor = ForegroundFormatColor::FG_DEFAULT;
            this->_backgroundColor = BackgroundFormatColor::BG_DEFAULT;
            this->_isMessageBold = false;
            this->_isColoringUsed = false;
            this->_isStylingUsed = false;
        }
        FormatterColorsBuilder::FormatterColorsBuilder(const std::string& _message) {
            this->_builderMessage = _message;
            this->_foregroundColor = ForegroundFormatColor::FG_DEFAULT;
            this->_backgroundColor = BackgroundFormatColor::BG_DEFAULT;
            this->_isMessageBold = false;
            this->_isColoringUsed = false;
            this->_isStylingUsed = false;
        }
        FormatterColorsBuilder::~FormatterColorsBuilder() {}
        FormatterColorsBuilder::FormatterColorsBuilder(const FormatterColorsBuilder &rhs)
        {
            this->_builderMessage = rhs._builderMessage;
            this->_isMessageBold = rhs._isMessageBold;
            this->_isMessageBold = rhs._isMessageBold;
            this->_isColoringUsed = rhs._isColoringUsed;
            this->_isStylingUsed = rhs._isStylingUsed;
        }
        FormatterColorsBuilder FormatterColorsBuilder::operator=(const FormatterColorsBuilder &rhs)
        {
            if (this == &rhs) return *this;
            this->_builderMessage = rhs._builderMessage;
            this->_isMessageBold = rhs._isMessageBold;
            this->_isMessageBold = rhs._isMessageBold;
            this->_isColoringUsed = rhs._isColoringUsed;
            this->_isStylingUsed = rhs._isStylingUsed;
            return *this;
        }
        FormatterColorsBuilder &FormatterColorsBuilder::Color(ForegroundFormatColor fgColor, BackgroundFormatColor bgColor)
        {
            this->_isColoringUsed = true;
            this->_backgroundColor = bgColor;
            this->_foregroundColor = fgColor;
            return *this;
        }

        FormatterColorsBuilder &FormatterColorsBuilder::Bold() {
            this->_isStylingUsed = true;
            this->_isMessageBold = true;
            return *this;
        }

        FormatterColorsBuilder &FormatterColorsBuilder::Italic() {
            return *this;
        }

        FormatterColorsBuilder &FormatterColorsBuilder::UnderLine() {
            return *this;
        }

        FormatterColorsBuilder &FormatterColorsBuilder::Strikethrough() {
            return *this;
        }

        const std::string FormatterColorsBuilder::ToString() {

            std::stringstream ss;
            if (!this->_isColoringUsed && !this->_isStylingUsed) {
                ss << this->_builderMessage << "\n";
                return ss.str();
            }

            ss << "\033[";

            std::string _foregroundColor = std::to_string((int) this->_foregroundColor);
            std::string _backgroundColor = std::to_string((int) this->_backgroundColor);

            if (IsStylingEnabled()) {
                if (this->_isMessageBold) ss << "1";
            }

            if (IsColoringEnabled()) {
                if (IsStylingEnabled()) ss << ";";
                if (this->_foregroundColor != ForegroundFormatColor::FG_DEFAULT) { 
                    ss << _foregroundColor;
                    if (this->_backgroundColor != BackgroundFormatColor::BG_DEFAULT) ss << ";";
                }
                if (this->_backgroundColor != BackgroundFormatColor::BG_DEFAULT) ss << _backgroundColor;
            }

            ss << "m" << this->_builderMessage;

            ss << "\033[0m";
            return ss.str();
        }
    }
}