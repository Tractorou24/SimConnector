#pragma once

#include <core/interfaces/IResponse.h>
#include <core/mpl/factory.h>

class ResponseFactory
{
    template <typename ResponseType, typename... Args>
    using ResponseCreator = mpl::DerivedCreator<ResponseType, core::interfaces::IResponse, Args...>;

public:
    /**
     * \brief Creates the characteristics factory and register all usable types
     */
    ResponseFactory();
    ~ResponseFactory() = default;

    ResponseFactory(const ResponseFactory& other) = delete;
    ResponseFactory(ResponseFactory&& other) noexcept = delete;
    ResponseFactory& operator=(const ResponseFactory& other) = delete;
    ResponseFactory& operator=(ResponseFactory&& other) noexcept = delete;

    /**
     * \brief Instantiates a new characteristics structure from the given typename and memory buffer
     * \param name The registered name of the characteristics
     * \return The new empty characteristics structure
     */
    std::unique_ptr<core::interfaces::IResponse> create(const std::string& name);

private:
    mpl::Factory<std::string, core::interfaces::IResponse> m_factory;
};
