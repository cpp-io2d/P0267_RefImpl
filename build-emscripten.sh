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
# OUTPUT_DIR="${CMAKE_BUILD_TYPE}_www"
OUTPUT_DIR="${CMAKE_BUILD_TYPE}"

# Build
mkdir -p "${OUTPUT_DIR}" || true
pushd "${OUTPUT_DIR}"
emcmake cmake -G "Unix Makefiles" --config "${CMAKE_BUILD_TYPE}" "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}" -DIO2D_DEFAULT=CAIRO_SDL2 ../.
make
# make VERBOSE=1
popd
