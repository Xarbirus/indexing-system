#!/bin/sh

SCRIPT_PATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 || exit 1 ; pwd -P )"

WORK_DIR="$(
  cd "$(dirname "$SCRIPT_PATH")" || exit 1
  pwd -P
)"

PROTO_DIR="$WORK_DIR/proto"
OUT_DIR="$WORK_DIR/pyclient/app/"

python3 -m grpc_tools.protoc \
        --proto_path generated/grpc="$PROTO_DIR" \
        --python_out="$OUT_DIR" \
        --pyi_out="$OUT_DIR" \
        --grpc_python_out="$OUT_DIR" \
        "$(find "$PROTO_DIR" -type f)" || exit 1

touch "$OUT_DIR/generated/__init__.py"
touch "$OUT_DIR/generated/grpc/__init__.py"
