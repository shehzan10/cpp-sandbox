CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(ThirdParty)

# glm (Header Only)
SET(GLM_INCLUDE_DIR "${ROOT_THIRDPARTY_DIR}/glm" PARENT_SCOPE)

# nlohmann/json (Header Only)
SET(NLOHMANN_JSON_INCLUDE_DIR "${ROOT_THIRDPARTY_DIR}/nlohmann-json/single_include/nlohmann" PARENT_SCOPE)

