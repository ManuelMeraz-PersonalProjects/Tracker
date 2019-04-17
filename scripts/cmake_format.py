#! /usr/bin/env python3
import os
import sys
import subprocess

# Grab the tracker project directory path
# if it user called set_env.bash
project_dir = os.environ['TRACKER_PROJECT']

if not project_dir:
    print("Please source the set_env.bash script in the scripts/ directory to "
          "set the $TRACKER_PROJECT environment variable, which keep track of "
          "the project directory.")
    sys.exit(1)

# Don't format the files in these directories
ignore_dirs = ['extern', 'include', 'scripts', 'build']

print("Finding your cmake files to format....")
# Make sure we don't get any repeats with a set
cmake_files = set([])
for root, dirs, files in os.walk(project_dir):

    # Ignore hidden directories and if it is an ignored directory
    if (os.path.basename(root).startswith('.')
            or [dir for dir in ignore_dirs if dir in root]):
        continue

    # In place modify the directories we will explore
    # same as above, ignore hidden directories and if they're
    # in the ignore list
    dirs[:] = [d for d in dirs if not d.startswith('.')]
    dirs[:] = [d for ignore in ignore_dirs for d in dirs
               if ignore not in root + '/' + d]

    files[:] = [file for file in files if 'CMakeLists.txt' in file
                or file.endswith('.cmake')]

    for file in files:
        cmake_files.add(root + '/' + file)

for file in cmake_files:
    print("Formatting the file: " + file)
    command = ["cmake-format", file]

    try:
        process = subprocess.run(command, stdout=subprocess.PIPE, check=True,
                                 universal_newlines=True)

    except FileNotFoundError:
        print("\nAttempted to use cmake-format, but it looks like it's not "
              "installed!\nPlease install with pip by entering the following "
              "command:\n\n    pip install cmake_format")
        sys.exit(1)

    with open(file, 'w') as f:
        f.write(process.stdout)

print("Done")
