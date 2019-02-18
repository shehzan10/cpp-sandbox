set -e

echo_and_run () {
    echo '\$ $@'
    $@
}

echo_and_run mkdir build && cd build

travis_fold start "script.cmake" && echo "cmake"
echo_and_run cmake ..
travis_fold end "script.cmake"

travis_fold start "script.build" && echo "build"
echo_and_run make -j2
travis_fold end "script.build"

travis_fold start "script.run" && echo "run"
echo_and_run ./bin/cpp-sandbox
travis_fold end "script.run"

