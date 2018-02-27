#!/usr/bin/python3


"""
Access and modify a processes virtual memory.

Usage: sudo ./read_write_heap.py pid "search_string" "replace_string"

"""

import os
import pdb
from sys import argv, exit

if len(argv) is not 4:
    print('Usage: {} pid search_string replace_string'.format(argv[0]))
    exit(1)

# Add error checking on these arguments.
pid = argv[1]
search_str = bytes(argv[2], 'UTF-8')
replace_str = bytes(argv[3], 'UTF-8')


def get_heap_addr(pid):
    with open('/proc/{}/maps'.format(pid), 'r') as maps:
        for line in maps:
            if '[heap]' in line:
                addr = line[:17].split('-')
                print('Heap located at: {}'.format(addr[0]))
                return(addr)
    print('Heap memory address was not found')
    exit(1)


def write_to_memory(search_str, replace_str, addr):
    with open('/proc/{}/mem'.format(pid), 'rb+') as mem:
        mem.seek(int(addr[0], 16))
        block = mem.read(int(addr[1], 16) - int(addr[0], 16))

        if search_str in block:
            offset = block.find(search_str)
            # write to memory
            mem.seek(int(addr[0], 16) + offset)
            mem.write(replace_str)
            return
    exit(1)


if __name__ == "__main__":
    addr = get_heap_addr(pid)
    write_to_memory(search_str, replace_str, addr)
    exit(1)
