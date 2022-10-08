#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

namespace NFCServer {
    namespace Logger {
        template<class T>
        class TsQueue {
            private:

                mutable std::mutex _queueMutex;
                std::queue<T> _queue;
                std::condition_variable _queueCondition;

            public:

                TsQueue() : _queueMutex(), _queue(), _queueCondition() {}
                ~TsQueue() {}

                void Enqueue(T t) {

                    std::lock_quard<std::mutex> lock(m);
                    _queue.push(t);
                    _queueCondition.notify_one();
                }

                T Dequeue(void) {
                    
                    std::unique_lock<std::mutex> lock(_queueMutex);

                    while(_queue.empty()) {
                        _queueCondition.wait(lock);
                    }

                    T val = _queue.front();
                    _queue.pop();
                    return val;
                }

        };
    }
}