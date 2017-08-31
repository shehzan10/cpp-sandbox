CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(cpp-sandbox)

FILE(GLOB CPPSandboxHeaders
    "./*.hpp"
    "./*.h"
    )

FILE(GLOB CPPSandboxSources
    "./*.cpp"
    )

LIST(SORT CPPSandboxHeaders)
LIST(SORT CPPSandboxSources)

SOURCE_GROUP(Headers FILES ${CPPSandboxHeaders})
SOURCE_GROUP(Sources FILES ${CPPSandboxSources})

SET(CPPSandboxIncludeDirectories
    ${GLM_INCLUDE_DIR}
    ${NLOHMANN_JSON_INCLUDE_DIR}
    )

SET(CPPSandboxLibraries
    ${GLOBAL_LINK_LIBRARIES}
    )

SET(CPPSandboxDefinitions GLM_FORCE_RADIANS)

ADD_EXECUTABLE(cpp-sandbox ${CPPSandboxHeaders} ${CPPSandboxSources})

TARGET_INCLUDE_DIRECTORIES(cpp-sandbox PUBLIC ${CPPSandboxIncludeDirectories})
TARGET_LINK_LIBRARIES(cpp-sandbox ${CPPSandboxLibraries})
SET_TARGET_PROPERTIES(cpp-sandbox PROPERTIES COMPILE_DEFINITIONS "${CPPSandboxDefinitions}")

