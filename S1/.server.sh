#!/bin/sh
"$@"

./serverEXE $1

exec "$SHELL"

