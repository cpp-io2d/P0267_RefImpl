#!/bin/bash -e

# Always start with the cwd being the same directory as the script
cd "$(dirname "$0")"
SCRIPT_NAME="$(basename "${0}")"

# Init other script-internal vars
MAKE_FLAGS=""

# Parse command line args
while [ $# -gt 0 ]; do
    case "$1" in
        -\?|-h|--help)
            echo "what?"
            cat << EOF
Usage: ${SCRIPT_NAME} [options]

    -d | -D | --debug       Build Debug, rather than Release
    -v |      --verbose     Show verbose output
    -h | -? | --help        Show script's help text

EOF
            exit 0
            ;;

        -v|--verbose)
            MAKE_FLAGS="${MAKE_FLAGS} VERBOSE=1"
            ;;

        -d|-D|--debug)
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
make ${MAKE_FLAGS}
# make VERBOSE=1
popd
