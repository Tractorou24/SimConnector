find_package(Boost REQUIRED)

set (TARGET_NAME ${CLIENT_NAME})
set (HEADER_DIR include)
set (SOURCE_DIR src)

set (HEADERS
)

set (SOURCES
    ${SOURCE_DIR}/main.cpp
)

spark_add_executable(${TARGET_NAME}
    CXX_SOURCES
        ${SOURCES}
    PUBLIC_HEADERS
        ${HEADERS}
)

target_link_libraries(${TARGET_NAME}
	PUBLIC
        ${CMAKE_PROJECT_NAME}::${CORE_NAME}
        Boost::boost
)

target_link_options(${TARGET_NAME}
	PUBLIC
		-lpthread
)
