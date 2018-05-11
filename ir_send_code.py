#!/usr/bin/env python

import json
import os
import sys

import ir_send

def parse_codes(code_file):
    with open(os.path.join(os.path.dirname(__file__), code_file)) as f:
        return json.load(f)

def main():
    port = sys.argv[1]
    command = sys.argv[2]
    times = sys.argv[3]
    sleep = sys.argv[4]
    code = parse_codes("codes.json")["codes"][command]
    ir_send.send(port, code["protocol"], code["code"], code["bits"], times, sleep)

if __name__ == "__main__":
    main()
