#!/bin/sh
"$@"

./serverEXE

exec "$SHELL"

