find_package(Boost REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set (TARGET_NAME ${CORE_NAME})
set (HEADER_DIR include)
set (SOURCE_DIR src)

set (HEADERS
    ${HEADER_DIR}/${CORE_NAME}/events/Signal.h
    ${HEADER_DIR}/${CORE_NAME}/events/Slot.h
    ${HEADER_DIR}/${CORE_NAME}/interfaces/IConnection.h
    ${HEADER_DIR}/${CORE_NAME}/interfaces/IRequest.h
    ${HEADER_DIR}/${CORE_NAME}/interfaces/IResponse.h
    ${HEADER_DIR}/${CORE_NAME}/mpl/callback.h
    ${HEADER_DIR}/${CORE_NAME}/mpl/factory.h
    ${HEADER_DIR}/${CORE_NAME}/request/ReadRequest.h
    ${HEADER_DIR}/${CORE_NAME}/request/WriteRequest.h
    ${HEADER_DIR}/${CORE_NAME}/response/ReadResponse.h
    ${HEADER_DIR}/${CORE_NAME}/response/WriteResponse.h
    ${HEADER_DIR}/${CORE_NAME}/ser/serialize.h
    ${HEADER_DIR}/${CORE_NAME}/simconnect/SimVar.h
)

set (SOURCES
    ${SOURCE_DIR}/request/ReadRequest.cpp
    ${SOURCE_DIR}/request/WriteRequest.cpp
    ${SOURCE_DIR}/response/ReadResponse.cpp
    ${SOURCE_DIR}/response/WriteResponse.cpp
    ${SOURCE_DIR}/response/ResponseFactory.cpp
)

spark_add_library(${TARGET_NAME}
    CXX_SOURCES
        ${SOURCES}
    PUBLIC_HEADERS
        ${HEADERS}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC
        ${CMAKE_PROJECT_NAME}::SimConnect
        Boost::boost
        nlohmann_json::nlohmann_json
)
