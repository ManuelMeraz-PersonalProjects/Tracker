SETUP_ENV_PATH=$(realpath ${BASH_SOURCE[0]})
TRACKER_PROJECT=$(dirname $(dirname ${SETUP_ENV_PATH}))

export TRACKER_PROJECT=${TRACKER_PROJECT}

if ! grep -q "source ${SETUP_ENV_PATH}" ~/.bashrc
then 
echo "source ${SETUP_ENV_PATH}" >> ~/.bashrc
fi
