#! /usr/bin/env python3
import os
import sys
import subprocess
import argparse

project_dir = os.environ['TRACKER_PROJECT']

if not project_dir:
    print("Please source the set_env.bash script in the scripts/ directory to "
          "set the $TRACKER_PROJECT environment variable, which keep track of "
          "the project directory.")
    sys.exit(1)


def cmake_filter(file):
    '''
    @brief Used for checking if a file is a cmake file
    @param file A potential file to be filtered
    @return true if file is a cmake file
    '''
    return 'CMakeLists.txt'in file or file.endswith('.cmake')


def cpp_filter(file):
    '''
    @brief Used for checking if a file is a C++ file
    @param file A potential file to be filtered
    @return true if file is a C++ file
    '''
    cpp_extensions = ['.h', '.hpp', '.hh', '.hxx', '.cc', '.cpp', '.tpp']
    return [extension for extension in cpp_extensions if extension in file]


def get_files_if(file_filter):
    '''
    @brief Searches for all files in tracker project and formats
           them if they pass through the filter

    @param file_filter a function that returns true if file
                       name satisfies the requirements

    @return A Set of full file paths that passed the filter
    '''

    # Don't format the files in these directories
    ignore_dirs = ['extern', 'include', 'scripts', 'build']

    filtered_files = set([])
    for root, dirs, files in os.walk(project_dir):

        # Ignore hidden directories and if it is an ignored directory
        if (os.path.basename(root).startswith('.')
                or [d for d in ignore_dirs if d in root]):
            continue

        # In place modify the directories we will explore
        # same as above, ignore hidden directories and if they're
        # in the ignore list
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        dirs[:] = [d for ignore in ignore_dirs for d in dirs
                   if ignore not in root + '/' + d]

        files[:] = [f for f in files if file_filter(f)]

        for file in files:
            filtered_files.add(root + '/' + file)

    return filtered_files


# Grab the tracker project directory path
# if it user called set_env.bash
if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument("-cmake-format",
                        help="Run cmake-format on the code base",
                        action="store_true")

    parser.add_argument("-clang-format",
                        help="Run clang-format on the code base",
                        action="store_true")

    cmake_files = get_files_if(cmake_filter)
    print("Finding your cmake files to format....")
    # Make sure we don't get any repeats with a set

    print("\nFormatting the following files:")
    for file in cmake_files:
        print(file)
        command = ["cmake-format", "-i", file]

        try:
            process = subprocess.run(command, stdout=subprocess.PIPE,
                                     check=True,
                                     universal_newlines=True)

        except FileNotFoundError:
            print("\nAttempted to use cmake-format, but it looks like it's "
                  "not installed!\nPlease install with pip by entering the "
                  "following command:\n\n    pip install cmake_format")
            sys.exit(1)

    print("Done!\nPlease do a 'git diff' to make sure the files were "
          "formatted to your liking.\nUse 'git checkout -- /path/to/file' "
          "to undo any changes or 'git add -p' to\ninteractively add the "
          "changes you do want to keep.")

    print("\nIf 'git diff' shows no changes then the cmake files were already "
          "formatted correctly.")
