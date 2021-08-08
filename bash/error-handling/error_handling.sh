#!/usr/bin/env bash
#
# Note: I don't like the test on empty arg or whitespaces only arg:
# 'error_handling.sh ""' and 'error_handling.sh "  "'
# should be faulty, instead of displaying a strange message ("Hello, ")
usage() {
    echo "Usage: ./error_handling <greetee>"
    exit 1
}
(( $# != 1 )) && usage

echo "Hello, $1"
