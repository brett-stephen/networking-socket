#!/bin/sh

./clientEXE $1 $2 $3 

"$@"
exec "$SHELL"

