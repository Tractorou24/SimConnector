#pragma once

#include <boost/preprocessor.hpp>

#include <nlohmann/json.hpp>
namespace json = nlohmann;

template <typename T>
class ISerializable
{
public:
    [[nodiscard]] virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& str) = 0;
    virtual ~ISerializable() = default;
};

// Serializer / Deserializer
#define START_SERIALIZATION(class_name)                                                                 \
    public:                                                                                             \
    std::string serialize() const override                                                              \
    {                                                                                                   \
        json::json obj;                                                                                 \
        obj["class_name"] = typeid(*this).name();
#define END_SERIALIZATION                                                                               \
        return obj.dump();                                                                              \
    }

#define START_DESERIALIZATION(class_name)                                                               \
    void deserialize(const std::string& str) override                                                   \
    {                                                                                                   \
        const auto object = json::json::parse(str);
#define END_DESERIALIZATION                                                                             \
    }                                                                                                   \
    private:

// Helper for simple class
#define SERIALIZE_FULL_CLASS_HELPER(r, data, elem) obj[BOOST_PP_STRINGIZE(elem)] = elem;
#define DESERIALIZE_FULL_CLASS_HELPER(r, data, elem) ptr->elem = object[BOOST_PP_STRINGIZE(elem)];

#define SERIALIZE_FULL_CLASS(class_name, ...)                                                           \
    public:                                                                                             \
    virtual std::string serialize()                                                                     \
    {                                                                                                   \
        json::json obj;                                                                                 \
        obj["class_name"] = BOOST_PP_STRINGIZE(class_name);                                             \
        BOOST_PP_SEQ_FOR_EACH(SERIALIZE_FULL_CLASS_HELPER, , BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))     \
        return obj.dump();                                                                              \
    }                                                                                                   \
    static std::shared_ptr<class_name> deserialize(const std::string& str)                              \
    {                                                                                                   \
        const auto object = json::json::parse(str);                                                     \
        auto ptr = std::make_shared<class_name>();                                                      \
        BOOST_PP_SEQ_FOR_EACH(DESERIALIZE_FULL_CLASS_HELPER, , BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))   \
        return ptr;                                                                                     \
    }                                                                                                   \
    private:

// Helpers
#define SERIALIZE_PTR(class_name, object_ptr) std::static_pointer_cast<class_name>(object_ptr)->serialize()
#define DESERIALIZE_PTR(class_name, json) std::static_pointer_cast<class_name>(class_name::deserialize(json))
