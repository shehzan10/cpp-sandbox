set -e

echo_and_run () {
    echo "\$ $@"
    "$@"
}

echo_and_run mkdir build
echo_and_run cd build

echo travis_fold:start:script.cmake && echo "cmake"
echo_and_run cmake .. -G "Visual Studio 15 2017 Win64"
echo travis_fold:end:script.cmake

echo travis_fold:start:script.build && echo "build"
echo_and_run cmake --build . --target ALL_BUILD --config Release
echo travis_fold:end:script.build

echo travis_fold:start:script.run && echo "run"
echo_and_run ./bin/Release/cpp-sandbox
echo travis_fold:end:script.run
