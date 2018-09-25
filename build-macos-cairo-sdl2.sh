#!/bin/bash -e

# Always start with the cwd being the same directory as the script
cd "$(dirname "$0")"
SCRIPT_NAME="$(basename "${0}")"

# Parse command line args
while [ $# -gt 0 ]; do
    case "$1" in
        -\?|-h|--help)
            echo "what?"
            cat << EOF
Usage: ${SCRIPT_NAME} [options]

    -d      | --debug       Build Debug, rather than Release
    -h | -? | --help        Show script's help text

EOF
            exit 0
            ;;

        -d|--debug)
            CMAKE_BUILD_TYPE=Debug
            ;;

        *)
            >&2 echo "ERROR, Unknown argument: '${1}'"
            exit 1
            ;;
    esac
    shift
done

# Setup common vars
CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE:-Release}"
echo "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
OUTPUT_DIR="${CMAKE_BUILD_TYPE}"

# Build
mkdir -p "${OUTPUT_DIR}" || true
pushd "${OUTPUT_DIR}"
    cmake -G "Xcode" --config "${CMAKE_BUILD_TYPE}" "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}" -DIO2D_DEFAULT=CAIRO_SDL2 -DIO2D_WITHOUT_TESTS=1 ../.

    # Using xcrun to launch xcodebuild, should allow the DEVELOPER_DIR env-var to be respected,
    # which should help allow for Xcode version changes via CI system(s), or other.
    xcrun xcodebuild -configuration "${CMAKE_BUILD_TYPE}"

popd
