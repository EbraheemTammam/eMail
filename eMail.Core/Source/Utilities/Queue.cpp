#include "Queue.h"

namespace eMail::Core::Utilities
{
    template<typename DataType>
    const DataType& Queue<DataType>::Front() const
    {
        std::scoped_lock lock(mutex_);
        if (front_ == back_) throw std::runtime_error("Queue is empty");
        return &queue_[front_];
    }

    template<typename DataType>
    const DataType& Queue<DataType>::Back() const
    {
        std::scoped_lock lock(mutex_);
        if (front_ == back_) throw std::runtime_error("Queue is empty");
        return &queue_[back_];
    }

    template<typename DataType>
    void Queue<DataType>::Push(const DataType& data)
    {
        std::scoped_lock lock(mutex_);
        if (back_ == Q_SIZE)
        {
            if(front_ == 0)
                throw std::runtime_error("Queue is full");
            else
                AlignFront_();
        }
        queue_[back_] = data;
        ++back_;
    }

    template<typename DataType>
    DataType Queue<DataType>::Pop()
    {
        std::scoped_lock lock(mutex_);
        if (front_ == back_) throw std::runtime_error("Queue is empty");
        return queue_[front_++];
    }

    template<typename DataType>
    bool Queue<DataType>::IsEmpty() const
    {
        std::scoped_lock lock(mutex_);
        return front_ == back_;
    }

    template<typename DataType>
    std::size_t Queue<DataType>::Size() const
    {
        std::scoped_lock lock(mutex_);
        return back_ - front_;
    }

    template<typename DataType>
    void Queue<DataType>::AlignFront_()
    {
        uint32_t segment = back_ - front_;
        for(int i = 0; i < segment; ++i)
            queue_[i] = queue_[i + front_];

        front_ = 0;
        back_ = segment;
    }
}
