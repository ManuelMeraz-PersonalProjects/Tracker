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


## cmake_format.py

Formats cmake files in the tracker project and makes them 
look prettier. 

Requires python 3.6 and `cmake-format` installed.

You may install with pip by entering the following command:

`sudo pip install cmake-format` 

Usage:

`cmake_format.py`

After running the script, do a `git diff` to see what changes were made.
If no changes were made, then all the files were formatted correctly.
