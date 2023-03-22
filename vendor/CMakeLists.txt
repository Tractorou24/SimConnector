set (TARGET_NAME SimConnect)
set (HEADER_DIR include)
set (SOURCE_DIR src)

set (HEADERS
    ${HEADER_DIR}/SimConnect/SimConnect.h
)

spark_add_library(${TARGET_NAME} INTERFACE
    PUBLIC_HEADERS
        ${HEADERS}
)
