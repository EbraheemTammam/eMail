#pragma once

#include "PCH.h"

namespace eMail::Core::Utilities { template<typename DataType> class Queue; }

template<typename DataType>
class eMail::Core::Utilities::Queue
{
private:
    std::array<DataType, Q_SIZE> queue_;
    std::mutex mutex_;
    std::size_t front_ = 0;
    std::size_t back_ = 0;

    void AlignFront_();

public:
    Queue() = default;
    Queue(const Queue&) = delete;
    Queue(Queue&) = delete;

    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&) = delete;

    const DataType& Front() const;
    const DataType& Back() const;
    void Push(const DataType& data);
    DataType Pop();

    bool IsEmpty() const;
    std::size_t Size() const;
};
