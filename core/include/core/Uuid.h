#pragma once

#include "core/Endianness.h"
#include "core/Export.h"

#include <string>

namespace core
{
    /**
     * \brief A 128-bit universally unique identifier (UUID).
     *
     * Uses Uses SIMD (Single Instruction Multiple Data) with Intel's AVX2 instruction set to generate UUIDs.
     * UUIDs are stored as a 16-byte array, representing a 128-bit number in memory.
     *
     * See: https://www.rfc-editor.org/rfc/rfc4122
     */
    class CORE_EXPORT Uuid final
    {
    public:
        /**
         * \brief Instantiates a new random uuid.
         */
        explicit Uuid();
        ~Uuid() = default;

        /**
         * \brief Instantiates a new uuid from a 128-bit number.
         * \param uuid The 128-bit number to use as uuid.
         */
        explicit Uuid(__m128i uuid);

        /**
         * \brief Instantiates a new uuid from a byte string.
         * \param bytes A raw array of bytes (size 16) containing the uuid.
         */
        explicit Uuid(const uint8_t* bytes);

        /**
         * \brief Instantiates a new uuid from a byte string.
         * \param bytes A std::string containing the uuid.
         */
        explicit Uuid(const std::string& bytes);

        Uuid(const Uuid& other);
        Uuid(Uuid&& other) noexcept;
        Uuid& operator=(const Uuid& other);
        Uuid& operator=(Uuid&& other) noexcept;

        friend bool operator==(const Uuid& lhs, const Uuid& rhs);
        friend bool operator!=(const Uuid& lhs, const Uuid& rhs);

        friend std::ostream& operator<<(std::ostream& os, const Uuid& uuid);

        /**
         * \brief Serializes the uuid to a byte std::string (16 bytes).
         * \return The std::string containing the 16 bytes of the uuid.
         */
        [[nodiscard]] std::string bytes() const;

        /**
         * \brief Converts the uuid to its string representation.
         * \return The std::string representation of the uuid.
         */
        [[nodiscard]] std::string str() const;

        /**
         * \brief Converts the uuid to its string representation.
         * \param res A char array of size 36 to store the result in.
         */
        void str(char* res) const;

    private:
        void bytes(std::string& out) const;
        void bytes(char* bytes) const;

    private:
        alignas(128) uint8_t m_data[16];
    };

    inline bool operator==(const Uuid& lhs, const Uuid& rhs)
    {
        const __m128i x = _mm_load_si128(reinterpret_cast<const __m128i*>(lhs.m_data));
        const __m128i y = _mm_load_si128(reinterpret_cast<const __m128i*>(rhs.m_data));
        const __m128i neq = _mm_xor_si128(x, y);

        return _mm_test_all_zeros(neq, neq);
    }

    inline bool operator!=(const Uuid& lhs, const Uuid& rhs)
    {
        return !(lhs == rhs);
    }
}
