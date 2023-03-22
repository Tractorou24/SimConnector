#pragma once

#include <boost/preprocessor.hpp>

#include <nlohmann/json.hpp>
namespace json = nlohmann;

template <typename T>
class ISerializable
{
public:
    [[nodiscard]] virtual json::json serialize() const = 0;
    virtual void deserialize(const std::string& str) = 0;
    virtual ~ISerializable() = default;
};

// Serializer / Deserializer
#define START_SERIALIZATION(class_name)                                                                 \
    public:                                                                                             \
    json::json serialize() const override                                                               \
    {                                                                                                   \
        json::json obj;                                                                                 \
        obj["class_name"] = typeid(*this).name();
#define END_SERIALIZATION                                                                               \
        return obj;                                                                                     \
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
#define DESERIALIZE_FULL_CLASS_HELPER(r, data, elem) elem = object[BOOST_PP_STRINGIZE(elem)];

#define SERIALIZE_FULL_CLASS(class_name, ...)                                                           \
    public:                                                                                             \
    json::json serialize() const override                                                               \
    {                                                                                                   \
        json::json obj;                                                                                 \
        obj["class_name"] = BOOST_PP_STRINGIZE(class_name);                                             \
        BOOST_PP_SEQ_FOR_EACH(SERIALIZE_FULL_CLASS_HELPER, , BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))     \
        return obj;                                                                                     \
    }                                                                                                   \
    void deserialize(const std::string& str) override                                                   \
    {                                                                                                   \
        const auto object = json::json::parse(str);                                                     \
        BOOST_PP_SEQ_FOR_EACH(DESERIALIZE_FULL_CLASS_HELPER, , BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))   \
    }                                                                                                   \
    private:

// Helpers
#define SERIALIZE_PTR(class_name, object_ptr) std::static_pointer_cast<class_name>(object_ptr)->serialize()
