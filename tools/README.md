# Helper Scripts

## set_env.bash

Sets the environment variable for the location of this project. 
This is a requirement to use any of the other scripts. 
All other scripts may be called from any location.

From the root of the project directory use it like so:

`source ./scripts/set_env.bash`

## configure_and_make.sh

Bash script that will do the following:

1. If any argument is passed in, that argument will be the name of the build directory.
   * The default name is `build`.
2. Create the build directory if it doesn't exist
3. Inside the build directory configure and make the project with the settings in the script
4. If rebuilding, it will delete the `CmakeCache.txt` file, and make again

Default script settings are:
* `CMAKE_BUILD_TYPE=Debug`
* `ENABLE_DOCUMENTATION=ON`
* `ENABLE_TESTS=ON`

Requires set_env.bash to have been sourced

Usage:

`configure_and_make.sh`

`configure_and_make.sh build_dir`


## format_code.py

Formats all files in the tracker project and makes them 
look prettier. Clang format and cmake format work fantastic.

Requires python 3.6 
1. Requies`cmake-format` to format cmake files
2. Requires clang-format to format C++ files
3. Requires clang-tidy and clang-apply-replacements to fix C++ files (experimental)

```
usage: format_code.py [-h] [-a] [-cmake] [-cf] [-ct] [-p BUILD_DIR]

optional arguments:
  -h, --help            show this help message and exit
  -a, --all             Format cmake files, and run both clang-format and
                        clang-tidy on files
  -cmake, --cmake-format
                        Run cmake-format on cmake files in code base
  -cf, --clang-format   Run clang-format on C++ files in code base
  -ct, --clang-tidy     Run clang-tidy on C++ files in code base
  -p BUILD_DIR, --build-dir BUILD_DIR
                        Build dir name for clang tidy if not 'build'
                        
```
Example:

`./tools/format_code.py -cf -cake`
