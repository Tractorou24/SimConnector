#pragma once

#include <core/interfaces/IRequest.h>
#include <core/simconnect/SimVar.h>

namespace simconnect
{
    class Runner
    {
        friend void CALLBACK details::simconnect_callback(raw::SIMCONNECT_RECV*, raw::DWORD, void*);

    public:
        Runner(const Runner& other) = delete;
        Runner(Runner&& other) noexcept = delete;
        Runner& operator=(const Runner& other) = delete;
        Runner& operator=(Runner&& other) noexcept = delete;

        static Runner* GetInstance();

        bool openConnection();
        bool closeConnection();
        [[nodiscard]] bool isRunning() const { return !m_quit; }
        void pollEvents();

        void addRequest(std::shared_ptr<core::interfaces::IRequest>& request);
        void removeRequest(const std::shared_ptr<core::interfaces::IRequest>& request);

    private:
        explicit Runner() = default;
        ~Runner() = default;

        [[nodiscard]] bool registerRequest(const std::shared_ptr<core::interfaces::IRequest>& request) const;
        [[nodiscard]] bool unregisterRequest(const std::shared_ptr<core::interfaces::IRequest>& request) const;

    private:
        raw::HANDLE m_handle = nullptr;

        std::vector<std::shared_ptr<core::interfaces::IRequest>> m_requests;
        int m_current_definition = 0;
        int m_current_request = 0;
        bool m_quit = false;
    };
}
