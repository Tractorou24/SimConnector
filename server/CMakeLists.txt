set (TARGET_NAME ${SERVER_NAME})
set (HEADER_DIR include)
set (SOURCE_DIR src)

set (HEADERS
    ${HEADER_DIR}/${SERVER_NAME}/NetworkConnection.h
    ${HEADER_DIR}/${SERVER_NAME}/Runner.h
    ${HEADER_DIR}/SimConnectLoader.h
)

set (SOURCES
    ${SOURCE_DIR}/${SERVER_NAME}/NetworkConnection.cpp
    ${SOURCE_DIR}/${SERVER_NAME}/Runner.cpp
    ${SOURCE_DIR}/SimConnectLoader.cpp
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
)
