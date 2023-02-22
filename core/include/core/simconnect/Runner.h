#pragma once

#include <core/interfaces/IRequest.h>
#include <core/simconnect/SimVar.h>

namespace simconnect
{
    /**
     * @brief A simconnect server runner.
     * It is responsible of communicating with the simulator, making requests and receiving data.
     */
    class Runner
    {
        friend void CALLBACK details::simconnect_callback(raw::SIMCONNECT_RECV* p_data, raw::DWORD cb_data, void* p_context);

    public:
        Runner(const Runner& other) = delete;
        Runner(Runner&& other) noexcept = delete;
        Runner& operator=(const Runner& other) = delete;
        Runner& operator=(Runner&& other) noexcept = delete;

        /**
        * @brief Get the singleton instance of the runner.
         */
        static Runner* GetInstance();

        /**
         * @brief Opens the connection to the running simulator.
      * @return If the connection succeed.
         */
        bool openConnection();

        /**
        * @brief Closes the connection to the running simulator.
      * @return If the disconnection succeed.
         */
        bool closeConnection();

        /**
         * @return The connection status.
         */
        [[nodiscard]] bool isRunning() const { return !m_quit; }

        /**
        * @brief Make all stored requests to the simulator and wait for the data to be received and sent back to the client.
         */
        void pollEvents();

        /**
        * @brief Add a request to the runner.
         * @param request A shared pointer to the request you want to add.
         */
        void addRequest(std::shared_ptr<core::interfaces::IRequest>& request);

        /**
         * @brief Removes a request from the runner
         * @param request A shared pointer to the request you want to remove.
         */
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
