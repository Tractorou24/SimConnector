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

#include <core/events/Slot.h>

#include <map>

namespace core
{
    template <typename ...Args>
    class Signal final
    {
    public:
        Signal() : m_connections(), m_sequence(0) { }

        ~Signal()
        {
            this->clear();
        }

        Signal(const Signal& signal) = delete;
        Signal(Signal&& signal) = delete;
        Signal& operator =(const Signal& signal) = delete;
        Signal& operator =(Signal&& signal) = delete;

        void operator()(Args ... args) const
        {
            this->emitSignal(args...);
        }

        size_t connect(Slot<Args...>* slot)
        {
            return this->connect(slot, false);
        }

        size_t connect(Slot<Args...>& slot)
        {
            return this->connect(&slot, false);
        }

        size_t connect(Slot<Args...>&& slot)
        {
            auto* slot2 = new Slot<Args...>(std::move(slot));
            return this->connect(slot2, true);
        }

        void disconnect(size_t key)
        {
            auto it = this->m_connections.find(key);
            if (it != this->m_connections.end())
            {
                it->second.releaseSlot();
                this->m_connections.erase(it);
            }
        }

        void disconnect(Slot<Args...>* slot)
        {
            if (slot != nullptr && slot->m_connection != nullptr &&
                slot->m_connection->signal == this)
            {
                this->disconnect(slot->m_connection->key);
            }
        }

        void disconnect(Slot<Args...>& slot)
        {
            this->disconnect(&slot);
        }

        void clear()
        {
            for (auto& conn : this->m_connections)
            {
                conn.second.releaseSlot();
            }
            this->m_connections.clear();
        }

        void emitSignal(Args ... args) const
        {
            for (const auto& conn : this->m_connections)
            {
                if (conn.second.slot->m_callback)
                {
                    conn.second.slot->m_callback(std::forward<Args>(args)...);
                }
            }
        }

    private:
        using Connection = typename Slot<Args...>::Connection;

        std::map<std::size_t, Connection> m_connections;
        size_t m_sequence;

        size_t connect(Slot<Args...>* slot, bool managed)
        {
            if (slot == nullptr)
            {
                return 0;
            }
            if (slot->m_connection != nullptr)
            {
                if (slot->m_connection->signal == this)
                {
                    return slot->m_connection->key;
                }
                slot->disconnect();
            }

            ++this->m_sequence;
            auto res = this->m_connections.emplace(
                std::make_pair(
                    this->m_sequence,
                    Connection(this, slot, this->m_sequence, managed)
                )
            );

            slot->m_connection = &res.first->second;
            return this->m_sequence;
        }

        void move(Signal* signal)
        {
            this->clear();
            this->m_connections = std::move(signal->m_connections);
            this->m_sequence = signal->m_sequence;

            for (auto& connection : this->m_connections)
            {
                connection.second.signal = this;
            }

            signal->m_sequence = 0;
            signal->m_connections.clear();
        }
    };
}
