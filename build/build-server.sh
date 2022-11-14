#!/bin/sh

SCRIPT_PATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 || exit 1 ; pwd -P )"

WORK_DIR="$(
  cd "$(dirname "$SCRIPT_PATH")" || exit 1
  pwd -P
)"

TESTS=0
CONAN_PROFILE=""
BUILD_TYPE=""

AVAILABLE_BUILDS="debug|release|relwithdebinfo"
usage() {
  echo "Usage: $(basename "$0") [-t|--tests] [-c|--conan_profile arg] [-b|--build_type $AVAILABLE_BUILDS] [-h|--help]"
  exit 1
}

PARSED_ARGUMENTS=$(getopt -a -n "$(basename "$0")" -o tc:b:h --long tests,conan_profile:,build_type:,help -- "$@")
VALID_ARGUMENTS=$?
if [ "$VALID_ARGUMENTS" != "0" ]; then
  usage
fi

eval set -- "$PARSED_ARGUMENTS"
while [ : ]; do
  case "$1" in
  -t | --tests)
    echo "Processing 'tests' option"
    TESTS=1
    shift
    ;;
  -c | --conan_profile)
    echo "Processing 'conan_profile' option. Input argument is '$2'"
    CONAN_PROFILE="$2"
    shift 2
    ;;
  -b | --build_type)
    echo "Processing 'build_type' option. Input argument is '$2'"
    BUILD_TYPE=$(echo "$2" | tr '[:upper:]' '[:lower:]')
    case $BUILD_TYPE in
    debug | release | relwithdebinfo) ;;
    *)
      echo "Argument must be $AVAILABLE_BUILDS. Exit."
      exit 1
      ;;
    esac
    shift 2
    ;;
  :)
    echo "Option requires an argument."
    usage
    ;;
  -h | --help)
    usage
    ;;
  --)
    shift
    break
    ;;
  esac
done

BUILD_DETAILS=""

if [ -n "$BUILD_TYPE" ]; then
  BUILD_DETAILS=$BUILD_DETAILS" -DCMAKE_BUILD_TYPE=$BUILD_TYPE"
  BUILD_DIR="$WORK_DIR/cmake-build-$BUILD_TYPE"
else
  echo "Build type is required! Exit."
  exit 1
fi

if [ -z "$CONAN_PROFILE" ]; then
  echo "Conan profile is required! Exit."
  exit 1
fi

if [ "$TESTS" = "1" ]; then
  BUILD_DETAILS=$BUILD_DETAILS" -DTESTS=1"
else
  BUILD_DETAILS=$BUILD_DETAILS" -DTESTS=0"
fi

rm -rf $BUILD_DIR
mkdir $BUILD_DIR

if ! conan install "$WORK_DIR" "-if=""$BUILD_DIR" "-pr=""$CONAN_PROFILE"; then
  exit
fi

if ! cmake -G "Unix Makefiles" $BUILD_DETAILS -S "$WORK_DIR" -B "$BUILD_DIR" || ! make -C "$BUILD_DIR" -j4; then
  exit
fi

if [ "$TESTS" = "1" ]; then
  TESTS_DIR="$WORK_DIR/out/tests"
  for file in "$TESTS_DIR"/*; do
    $file
  done
fi
