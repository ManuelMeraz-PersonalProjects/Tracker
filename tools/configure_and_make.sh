# You can run this script from anywhere and it will configure and build your code

# If an argument is supplied, then the build directory
# name is set to that argument
if [ ! -z "$1" ]; then
  build_dir="$1"
else
  build_dir="build"
fi

# TRACKER_PROJECT contains the root directory of the tracker poject
# if TRACKER_PROJECT not set, then
if [ -z "${TRACKER_PROJECT}" ]; then
	cat <<-EOS
	Please run the following command from the root directory
	of the project:
		source scripts/set_env.bash

	Following that, the script should work just fine.
	EOS
	exit 1
fi

# Build directory does not exist
if [ ! -d ${TRACKER_PROJECT}/$build_dir ]; then
	mkdir ${TRACKER_PROJECT}/$build_dir
# CMakeCache keeps previous build configuration, which can conflict with 
# development when modifying CMakeLists.txt
# Removing this removes any old configuration
elif [ -e ${TRACKER_PROJECT}/$build_dir/CMakeCache.txt ]; then
	rm ${TRACKER_PROJECT}/$build_dir/CMakeCache.txt 
fi

# If cding into build fails, exit the script
cd ${TRACKER_PROJECT}/$build_dir || exit

# Set CMAKE settings here
cmake \
-DCMAKE_BUILD_TYPE=Debug \
-DENABLE_DOCUMENTATION=ON \
-DENABLE_TESTS=ON \
.. 

# Useful flag for make -j<# threads> for parallel build
make -j5
cd - || exit
