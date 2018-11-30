#!/bin/sh

./clientEXE $1 $2

"$@"
exec "$SHELL"

