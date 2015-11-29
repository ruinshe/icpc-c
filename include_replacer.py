#! /usr/bin/env python2
from sys import argv
from os import path

def dfs(name):
    fp = open(name, 'r')
    while True:
        line = fp.readline()
        if not line:
            break
        if line.startswith('#include'):
            next_name = line.split()[1]
            if next_name[0] == '"' and next_name[-1] == '"':
                dfs(path.abspath(path.dirname(name)) + "/" + next_name[1 : -1])
            else:
                print line[ : -1]
        else:
            print line[ : -1]
    fp.close()

dfs(argv[1])
