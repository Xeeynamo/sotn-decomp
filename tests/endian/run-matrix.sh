#!/usr/bin/env bash
set -euo pipefail

repo_root=$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)
build_root=${SOTN_ENDIAN_BUILD_ROOT:-"${repo_root}/build/endian-matrix"}

run_native() {
    local name=$1
    shift
    cmake -S "${repo_root}" -B "${build_root}/${name}" \
        -DSOTN_ENDIAN_TESTS_ONLY=ON "$@"
    cmake --build "${build_root}/${name}" --parallel
    ctest --test-dir "${build_root}/${name}" --output-on-failure
}

require_tool() {
    if ! command -v "$1" >/dev/null 2>&1; then
        echo "endian test matrix requires '$1'" >&2
        exit 1
    fi
}

run_cross() {
    local name=$1
    local prefix=$2
    local qemu=$3
    local sysroot=$4

    require_tool "${prefix}-gcc"
    require_tool "${prefix}-g++"
    require_tool "${qemu}"
    cmake -S "${repo_root}" -B "${build_root}/${name}" \
        -DSOTN_ENDIAN_TESTS_ONLY=ON \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_SYSTEM_NAME=Linux \
        -DCMAKE_C_COMPILER="${prefix}-gcc" \
        -DCMAKE_CXX_COMPILER="${prefix}-g++" \
        -DCMAKE_CROSSCOMPILING_EMULATOR="${qemu};-L;${sysroot}"
    cmake --build "${build_root}/${name}" --parallel
    ctest --test-dir "${build_root}/${name}" --output-on-failure
}

run_native native-debug -DCMAKE_BUILD_TYPE=Debug
run_native native-sanitized -DCMAKE_BUILD_TYPE=Debug \
    -DSOTN_ENDIAN_SANITIZERS=ON
run_native native-optimized -DCMAKE_BUILD_TYPE=Release
run_cross s390x-be s390x-linux-gnu qemu-s390x /usr/s390x-linux-gnu
run_cross ppc32-be powerpc-linux-gnu qemu-ppc /usr/powerpc-linux-gnu
