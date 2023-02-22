#pragma once

namespace mpl
{
    /**
     * \brief A base class for all creators.
     * \tparam BaseType The type of the base class.
     * \tparam Args The types of the arguments passed to the constructor of the derived class.
     */
    template <typename BaseType, typename... Args>
    class BaseCreator
    {
    public:
        using BasePtr = std::unique_ptr<BaseType>;

    public:
        virtual ~BaseCreator() = default;
        virtual BasePtr create(const Args&... args) = 0;
    };

    /**
     * \brief The creator for a derived class.
     * \tparam DerivedType The type of the derived class.
     * \tparam BaseType The type of the base class.
     * \tparam Args The types of the arguments passed to the constructor of the derived class.
     */
    template <typename DerivedType, typename BaseType, typename... Args>
    class DerivedCreator final : public BaseCreator<BaseType, Args...>
    {
    public:
        typename BaseCreator<BaseType, Args...>::BasePtr create(const Args&... args) override;
    };

    /**
     * \brief A factory class that creates objects of type \tparam BaseType.
     * \tparam Key The type of the key used to register objects.
     * \tparam BaseType The type of the base class.
     * \tparam Args The types of the arguments passed to the constructor of the derived class.
     */
    template <typename Key, typename BaseType, typename... Args>
    class Factory
    {
        using BasePtr = std::unique_ptr<BaseType>;
        using CreatorPtr = std::unique_ptr<BaseCreator<BaseType, Args...>>;

    public:
        /**
         * \brief Registers a type the factory can create.
         * \param key The key of type \tparam Key used to create the object.
         * \param ptr The std::unique_ptr to the creator of the object.
         */
        void registerType(const Key& key, CreatorPtr ptr);

        /**
         * \brief Creates an object of type \tparam BaseType.
         * \param key The key of type \tparam Key used to create the object.
         * \param args The arguments passed to the constructor of the derived class.
         * \return A std::unique_ptr to the created object.
         */
        BasePtr create(const Key& key, const Args&... args);

    private:
        std::unordered_map<Key, CreatorPtr> m_creators;
    };

    template <typename DerivedType, typename BaseType, typename... Args>
    typename BaseCreator<BaseType, Args...>::BasePtr DerivedCreator<DerivedType, BaseType, Args...>::create(const Args&... args)
    {
        return std::make_unique<DerivedType>(args...);
    }

    template <typename Key, typename BaseType, typename... Args>
    void Factory<Key, BaseType, Args...>::registerType(const Key& key, CreatorPtr ptr)
    {
        if (m_creators.contains(key))
            throw std::runtime_error("Type already registered");
        m_creators.insert({key, std::move(ptr)});
    }

    template <typename Key, typename BaseType, typename... Args>
    typename Factory<Key, BaseType, Args...>::BasePtr Factory<Key, BaseType, Args...>::create(const Key& key, const Args&... args)
    {
        if (!m_creators.contains(key))
            throw std::runtime_error("Type not registered");
        return m_creators.at(key)->create(args...);
    }
}
