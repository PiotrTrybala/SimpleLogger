#pragma once
#include "LoggingContext.h"

namespace NFCServer {
    namespace Logger {
        LoggingContext* GetContextInstance();
        void DestroyInstance();
    }
}