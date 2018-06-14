#!/bin/bash

# https://stackoverflow.com/questions/696839/how-do-i-write-a-bash-script-to-restart-a-process-if-it-dies
CMD="./DipperPointMapper ./demo.xml"

until eval $CMD; do
        echo "Server \"$CMD\" crashed with exit code $?.  Respawning.." >&2
        sleep 1
done

