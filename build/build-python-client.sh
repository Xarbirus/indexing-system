#!/bin/sh

SCRIPT_PATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 || exit 1 ; pwd -P )"
WORK_DIR="$( cd "$(dirname "$SCRIPT_PATH")" || exit 1 ; pwd -P )"

CLIENT_DIR="$WORK_DIR/pyclient/app"
OUT_DIR="$WORK_DIR/out/bin"
BUILD_DIR="$WORK_DIR/pybuild"

/bin/sh "$SCRIPT_PATH/generate-python-grpc.sh"

pyinstaller --distpath "$OUT_DIR" \
            --specpath "$BUILD_DIR" \
            --workpath "$BUILD_DIR" \
            --paths "$CLIENT_DIR" \
            --noconfirm \
            --log-level WARN \
            --onefile \
            --name pyclient "$CLIENT_DIR/main.py"

rm -rf "$BUILD_DIR"

echo "python client built!"
