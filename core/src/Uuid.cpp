#include "core/Uuid.h"

#include "core/Endianness.h"
#include "core/UuidGenerator.h"

#include <sstream>

// ReSharper disable CppClangTidyCppCoreGuidelinesProTypeMemberInit

/**
 * \brief Converts a 128-bits unsigned int to an UUID string representation.
 * \details Uses SIMD (Single Instruction Multiple Data) with Intel's AVX2 instruction set.
 *
 * \param x The 128-bits unsigned int to convert
 * \param mem The start of the memory block where the string representation will be stored
 */
void inline m128itos(__m128i x, char* mem)
{
    // Expand each byte in x to two bytes in res
    // i.e. 0x12345678 -> 0x0102030405060708
    // Then translate each byte to its hex ascii representation
    // i.e. 0x0102030405060708 -> 0x3132333435363738
    const __m256i mask = _mm256_set1_epi8(0x0F);
    const __m256i add = _mm256_set1_epi8(0x06);
    const __m256i alpha_mask = _mm256_set1_epi8(0x10);
    const __m256i alpha_offset = _mm256_set1_epi8(0x57);

    __m256i a = _mm256_castsi128_si256(x);
    __m256i as = _mm256_srli_epi64(a, 4);
    __m256i lo = _mm256_unpacklo_epi8(as, a);
    __m128i hi = _mm256_castsi256_si128(_mm256_unpackhi_epi8(as, a));
    __m256i c = _mm256_inserti128_si256(lo, hi, 1);
    __m256i d = _mm256_and_si256(c, mask);
    __m256i alpha = _mm256_slli_epi64(_mm256_and_si256(_mm256_add_epi8(d, add), alpha_mask), 3);
    __m256i offset = _mm256_blendv_epi8(_mm256_slli_epi64(add, 3), alpha_offset, alpha);
    __m256i res = _mm256_add_epi8(d, offset);

    // Add dashes between blocks as specified in RFC-4122
    // 8-4-4-4-12
    const __m256i dash_shuffle = _mm256_set_epi32(0x0b0a0908, 0x07060504, 0x80030201, 0x00808080, 0x0d0c800b, 0x0a090880, 0x07060504, 0x03020100);
    const __m256i dash = _mm256_set_epi64x(0x0000000000000000ull, 0x2d000000002d0000ull, 0x00002d000000002d, 0x0000000000000000ull);

    __m256i resd = _mm256_shuffle_epi8(res, dash_shuffle);
    resd = _mm256_or_si256(resd, dash);

    _mm256_storeu_si256((__m256i*)mem, betole256(resd));
    *(uint16_t*)(mem + 16) = static_cast<uint16_t>(betole16(_mm256_extract_epi16(res, 7)));
    *(uint32_t*)(mem + 32) = static_cast<uint16_t>(betole32(_mm256_extract_epi32(res, 7)));
}

/**
 * \brief Converts an UUID string representation to a 128-bits unsigned int.
 * \details Uses SIMD (Single Instruction Multiple Data) with Intel's AVX2 instruction set.
 *
 * \param mem The start of the memory block where the string representation is stored
 * \return The 128-bits unsigned int
 */
__m128i inline stom128i(char* mem)
{
    // Remove dashes and pack hex ascii bytes in a 256-bits int
    const __m256i dash_shuffle = _mm256_set_epi32(0x80808080, 0x0f0e0d0c, 0x0b0a0908, 0x06050403, 0x80800f0e, 0x0c0b0a09, 0x07060504, 0x03020100);

    __m256i x = betole256(_mm256_loadu_si256((__m256i*)mem));
    x = _mm256_shuffle_epi8(x, dash_shuffle);
    x = _mm256_insert_epi16(x, betole16(*(uint16_t*)(mem + 16)), 7);
    x = _mm256_insert_epi32(x, betole32(*(uint32_t*)(mem + 32)), 7);

    // Build a mask to apply a different offset to alphas and digits
    const __m256i sub = _mm256_set1_epi8(0x2F);
    const __m256i mask = _mm256_set1_epi8(0x20);
    const __m256i alpha_offset = _mm256_set1_epi8(0x28);
    const __m256i digits_offset = _mm256_set1_epi8(0x01);
    const __m256i unweave = _mm256_set_epi32(0x0f0d0b09, 0x0e0c0a08, 0x07050301, 0x06040200, 0x0f0d0b09, 0x0e0c0a08, 0x07050301, 0x06040200);
    const __m256i shift = _mm256_set_epi32(0x00000000, 0x00000004, 0x00000000, 0x00000004, 0x00000000, 0x00000004, 0x00000000, 0x00000004);

    // Translate ascii bytes to their value
    // i.e. 0x3132333435363738 -> 0x0102030405060708
    // Shift hi-digits
    // i.e. 0x0102030405060708 -> 0x1002300450067008
    // Horizontal add
    // i.e. 0x1002300450067008 -> 0x12345678
    __m256i a = _mm256_sub_epi8(x, sub);
    __m256i alpha = _mm256_slli_epi64(_mm256_and_si256(a, mask), 2);
    __m256i sub_mask = _mm256_blendv_epi8(digits_offset, alpha_offset, alpha);
    a = _mm256_sub_epi8(a, sub_mask);
    a = _mm256_shuffle_epi8(a, unweave);
    a = _mm256_sllv_epi32(a, shift);
    a = _mm256_hadd_epi32(a, _mm256_setzero_si256());
    a = _mm256_permute4x64_epi64(a, 0b00001000);

    return _mm256_castsi256_si128(a);
}

namespace core
{
    Uuid::Uuid()
    {
        static UuidGenerator generator;
        *this = generator.generate();
    }

    Uuid::Uuid(const __m128i uuid)
    {
        _mm_store_si128(reinterpret_cast<__m128i*>(m_data), uuid);
    }

    Uuid::Uuid(const uint8_t* bytes)
    {
        const __m128i x = _mm_loadu_si128(reinterpret_cast<const __m128i*>(bytes));
        _mm_store_si128(reinterpret_cast<__m128i*>(m_data), x);
    }

    Uuid::Uuid(const std::string& bytes)
    {
        const __m128i x = betole128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(bytes.data())));
        _mm_store_si128(reinterpret_cast<__m128i*>(m_data), x);
    }

    Uuid::Uuid(const Uuid& other)
    {
        const __m128i x = _mm_load_si128(reinterpret_cast<const __m128i*>(other.m_data));
        _mm_store_si128(reinterpret_cast<__m128i*>(m_data), x);
    }

    Uuid::Uuid(Uuid&& other) noexcept
    {
        const __m128i x = _mm_load_si128(reinterpret_cast<const __m128i*>(other.m_data));
        _mm_store_si128(reinterpret_cast<__m128i*>(m_data), x);
    }

    Uuid& Uuid::operator=(const Uuid& other)
    {
        if (&other == this)
            return *this;

        const __m128i x = _mm_load_si128(reinterpret_cast<const __m128i*>(other.m_data));
        _mm_store_si128(reinterpret_cast<__m128i*>(m_data), x);

        return *this;
    }

    Uuid& Uuid::operator=(Uuid&& other) noexcept
    {
        if (&other == this)
            return *this;

        const __m128i x = _mm_load_si128(reinterpret_cast<const __m128i*>(other.m_data));
        _mm_store_si128(reinterpret_cast<__m128i*>(m_data), x);

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Uuid& uuid)
    {
        os << uuid.str();
        return os;
    }

    std::string Uuid::bytes() const
    {
        std::string mem;
        bytes(mem);
        return mem;
    }

    std::string Uuid::str() const
    {
        std::string mem;
        mem.resize(36);
        str(mem.data());
        return mem;
    }

    void Uuid::str(char* res) const
    {
        const __m128i x = _mm_load_si128(reinterpret_cast<const __m128i*>(m_data));
        m128itos(x, res);
    }

    void Uuid::bytes(std::string& out) const
    {
        out.resize(sizeof(m_data));
        bytes(out.data());
    }

    void Uuid::bytes(char* bytes) const
    {
        const __m128i x = betole128(_mm_load_si128(reinterpret_cast<const __m128i*>(m_data)));
        _mm_storeu_si128(reinterpret_cast<__m128i*>(bytes), x);
    }
}
