/*
The MIT License (MIT)
Copyright (c) 2019 Adrian-George Bostan <adrg@epistack.com>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#include <functional>

namespace core
{
    template <typename ...Args>
    class Signal;

    template <typename ...Args>
    class Slot final
    {
        friend class Signal<Args...>;

    public:
        Slot() : m_callback() { }

        explicit Slot(const std::function<void(Args ...)>& f) : m_callback(f) { }

        explicit Slot(std::function<void(Args ...)>&& f) : m_callback(f) { }

        template <class T>
        explicit Slot(T* target, void (T::* method)(Args ...))
        {
            setCallback(target, method);
        }

        template <class T>
        explicit Slot(T* target, void (T::* method)(Args ...) const)
        {
            setCallback(target, method);
        }

        ~Slot()
        {
            this->disconnect();
        }

        Slot(const Slot& slot) : m_callback(slot.m_callback) { }

        Slot(Slot&& slot) noexcept
        {
            this->move(&slot);
        }

        Slot& operator=(const Slot& slot)
        {
            this->m_callback = slot.m_callback;
            return *this;
        }

        Slot& operator=(Slot&& slot) noexcept
        {
            this->disconnect();
            this->move(&slot);
            return *this;
        }

        void disconnect()
        {
            if (this->m_connection != nullptr)
                this->m_connection->signal->disconnect(this);
        }

        void setCallback(const std::function<void(Args ...)>& f)
        {
            this->m_callback = f;
        }

        void setCallback(std::function<void(Args ...)>&& f)
        {
            this->m_callback = f;
        }

        template <class T>
        void setCallback(T* target, void (T::* method)(Args ...))
        {
            this->m_callback = [target, method](Args ... args)
            {
                (target->*method)(args...);
            };
        }

        template <class T>
        void setCallback(T* target, void (T::* method)(Args ...) const)
        {
            this->m_callback = [target, method](Args ... args)
            {
                (target->*method)(args...);
            };
        }

    private:
        struct Connection
        {
        public:
            Signal<Args...>* signal;
            Slot<Args...>* slot;
            size_t key;
            bool managed;

            Connection(Signal<Args...>* signal, Slot<Args...>* slot, const size_t& key, const bool& managed) :
                signal(signal), slot(slot), key(key), managed(managed) { }

            void releaseSlot() const
            {
                this->slot->m_connection = nullptr;
                if (this->managed)
                    delete this->slot;
            }
        };

        std::function<void(Args ...)> m_callback;
        Connection* m_connection = nullptr;

        void move(Slot* slot)
        {
            this->m_callback = std::move(slot->m_callback);
            this->m_connection = nullptr;

            if (slot->m_connection != nullptr)
            {
                this->m_connection = slot->m_connection;
                slot->m_connection->releaseSlot();
                this->m_connection->slot = this;
                this->m_connection->managed = false;
            }
        }
    };
}
