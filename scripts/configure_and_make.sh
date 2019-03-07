# You can run this script from anywhere and it will configure and build your code
if [ -z "${TRACKER_PROJECT}" ]; then
	cat <<-EOS
	Please run the following command from the root directory
	of the project:
		source scripts/set_env.bash

	Following that, the script should work just fine.
	EOS
	exit 1
fi

if [ ! -d ${TRACKER_PROJECT}/build ]; then
	mkdir ${TRACKER_PROJECT}/build
elif [ -e ${TRACKER_PROJECT}/build/CMakeCache.txt ]; then
	rm ${TRACKER_PROJECT}/build/CMakeCache.txt 
fi

cd ${TRACKER_PROJECT}/build || exit
# Set CMAKE settings here
cmake \
-DCMAKE_BUILD_TYPE=Debug \
-DENABLE_DOCUMENTATION=OFF \
-DENABLE_TESTS=ON \
.. 

# Useful flag for make -j<# threads> for parallel build
make
cd - || exit
