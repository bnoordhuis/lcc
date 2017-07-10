#!/usr/bin/python

import itertools
import sys

from difflib import unified_diff
from subprocess import PIPE, Popen

builddir = 'build'

targets = '''bytecode alpha/osf mips/irix sparc/solaris x86/linux'''.split()

# Note: the paranoia and yacc tests are omitted because they depend
# on <stdio.h> and <signal.h> and cannot be run in isolation.
tests = '''8q arith array cf cq cvt fields front incr init limits
           sort spill stdarg struct switch wf1'''.split()

def diff(actual, filename):
    expect = open(filename).read()
    delta = unified_diff(expect.split('\n'),
                         actual.split('\n'),
                         lineterm='',
                         fromfile='expect/{0}'.format(filename),
                         tofile='actual/{0}'.format(filename))
    return '\n'.join(delta)

def run_test(test, target):
    args = '''{builddir}/lcc -B{builddir}/ -C{builddir}/
              -Iinclude/{target} -target={target} -S -o - tst/{test}.c
              '''.format(builddir=builddir, **locals()).split()
    stdout, stderr = Popen(args, stdout=PIPE, stderr=PIPE).communicate()
    stdout_diff = diff(stdout, '{target}/tst/{test}.sbk'.format(**locals()))
    stderr_diff = diff(stderr, '{target}/tst/{test}.2bk'.format(**locals()))
    if stdout_diff: sys.stderr.write(stdout_diff + '\n')
    if stderr_diff: sys.stderr.write(stderr_diff + '\n')
    return not (stdout_diff or stderr_diff)

def run_tests():
    failed = []
    for test, target in itertools.product(tests, targets):
        if (test == 'arith') ^ (target == 'bytecode'):
            continue
        sys.stdout.write('# {test} {target}\n'.format(**locals()))
        if not run_test(test, target):
            failed.append((test, target))
    return failed

if __name__ == '__main__':
    rest = []
    for arg in sys.argv[1:]:
        if arg.startswith('--builddir='):
            builddir = arg[len('--builddir='):]
        elif arg.startswith('--targets='):
            targets = arg[len('--targets='):].split(',')
        elif arg.startswith('-'):
            sys.stderr.write('Bad option: ' + arg)
            sys.exit(1)
        else:
            rest.append(arg)
    tests = rest or tests
    sys.exit(len(run_tests()))
