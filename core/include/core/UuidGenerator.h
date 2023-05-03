#pragma once

#include "core/Export.h"
#include "core/Uuid.h"

#include <random>

namespace core
{
    /**
     * \brief Generates UUIDs from C++11 <random> module.
     */
    class CORE_EXPORT UuidGenerator final
    {
    public:
        /**
         * \brief Instantiates a new uuid generator with a base seed.
         */
        explicit UuidGenerator();

        /**
         * \brief Instantiates a new uuid generator with a provided seed.
         * \param seed The seed to use for the random generator.
         */
        explicit UuidGenerator(uint64_t seed);

        /**
         * \brief Generates a new uuid.
         * \return The generated uuid.
         */
        Uuid generate();

    private:
        std::mt19937_64 m_generator;
        std::uniform_int_distribution<uint64_t> m_distribution;
    };
}
