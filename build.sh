#!/bin/bash

HELP="Usage: build.sh COMMAND
COMMANDS
    build: builds the current project into the build directory.
    
    rebuild: removes all build files and builds the project.
    
    build-test: runs 'build' and then runs the default test suite.
    
    help: prints this help message."

function cmd_build() {
    cmake --build build
}

function cmd_run_tests() {
    ./build/tests
}

function cmd_rebuild() {
    rm -rf build/*
    cmake -G 'Unix Makefiles' -B build
    cmd_build
}

function cmd_loop() {
    echo "Entering command runner mode."
    while true 
    do
        select cmd in build rebuild build-test exit
        do 
            if [[ "$cmd" == "exit" ]]
            then
                exit
            fi
            check_command $cmd
        done
    done
}

function check_command() {
    case $1 in
        build | b)
            cmd_build;;
        rebuild | rb)
            cmd_rebuild;;
        test | t)
            cmd_run_tests;;
        loop | l)
            cmd_loop;;
        build-test)
            cmd_build
            cmd_run_tests;;
        *)
            printf '%s\n' "$HELP";;
    esac
}

if [[ "$1" == "" ]]
then
    check_command "loop"
else
    check_command $1
fi