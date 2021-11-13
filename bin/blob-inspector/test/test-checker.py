#!/usr/bin/python

#./blob-inspector-test --gtest_list_tests

import subprocess
process = subprocess.Popen(['./blob-inspector-test', '--gtest_list_tests'],
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE)

stdout, stderr = process.communicate()

testCases = set (stdout.split()[1:])

process = subprocess.Popen(['ls', '../../test-files'],
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE)

stdout, stderr = process.communicate()

files = set (stdout.split())

missing = files - testCases
print (missing)

