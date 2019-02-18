set -e

echo_and_run () {
    echo "\$ $@"
    $@
}

echo_and_run mkdir build
echo_and_run cd build

echo travis_fold:start:script.cmake && echo "cmake"
echo_and_run cmake ..
echo travis_fold:end:script.cmake && echo -e "\n\n"

echo travis_fold:start:script.build && echo "build"
echo_and_run make -j2
echo travis_fold:end:script.build && echo -e "\n\n"

echo travis_fold:start:script.run && echo "run"
echo_and_run ./bin/cpp-sandbox
echo travis_fold:end:script.run && echo -e "\n\n"

