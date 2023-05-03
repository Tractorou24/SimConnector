#pragma once

#include <core/interfaces/IRequest.h>
#include <core/mpl/factory.h>
#include <core/Export.h>

class CORE_EXPORT RequestFactory
{
    template <typename RequestType, typename... Args>
    using RequestCreator = mpl::DerivedCreator<RequestType, core::interfaces::IRequest, Args...>;

public:
    /**
     * \brief Creates the characteristics factory and register all usable types
     */
    RequestFactory();
    ~RequestFactory() = default;

    RequestFactory(const RequestFactory& other) = delete;
    RequestFactory(RequestFactory&& other) noexcept = delete;
    RequestFactory& operator=(const RequestFactory& other) = delete;
    RequestFactory& operator=(RequestFactory&& other) noexcept = delete;

    /**
     * \brief Instantiates a new characteristics structure from the given typename and memory buffer
     * \param name The registered name of the characteristics
     * \return The new empty characteristics structure
     */
    std::unique_ptr<core::interfaces::IRequest> create(const std::string& name);

private:
    mpl::Factory<std::string, core::interfaces::IRequest> m_factory;
};
