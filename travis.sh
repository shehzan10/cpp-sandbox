set -ex

mkdir build && cd build

travis_fold start "script.cmake" && echo "cmake"
if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then cmake .. -G "Visual Studio 15 2017 Win64" ; else cmake .. ; fi
travis_fold end "script.cmake"

travis_fold start "script.build" && echo "build"
if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then cmake --build . --target ALL_BUILD --config Release ; else make -j2 ; fi
travis_fold end "script.build"

travis_fold start "script.run" && echo "run"
if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then ./bin/Release/cpp-sandbox ; else ./bin/cpp-sandbox ; fi
travis_fold end "script.run"

