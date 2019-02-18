set -e

echo_and_run () {
    echo '\$ $@'
    $@
}

echo_and_run mkdir build && cd build

travis_fold start "script.cmake" && echo "cmake"
if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then echo_and_run cmake .. -G "Visual Studio 15 2017 Win64" ; else echo_and_run cmake .. ; fi
travis_fold end "script.cmake"

travis_fold start "script.build" && echo "build"
if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then echo_and_run cmake --build . --target ALL_BUILD --config Release ; else echo_and_run make -j2 ; fi
travis_fold end "script.build"

travis_fold start "script.run" && echo "run"
if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then echo_and_run ./bin/Release/cpp-sandbox ; else echo_and_run ./bin/cpp-sandbox ; fi
travis_fold end "script.run"

