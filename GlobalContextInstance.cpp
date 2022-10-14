#include "include/GlobalContextInstance.h"

namespace NFCServer {
    namespace Logger {

        LoggingContext* context{};
        LoggingContext* GetContextInstance()
        {
            if (context == nullptr)
                context = new LoggingContext();
            return context;
        }

        void DestroyInstance() {
            delete context;
        }
    }
}