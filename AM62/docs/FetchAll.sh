#!/bin/bash

# Local Trismed Git access configuration
GIT_SERVER="192.168.10.251"

# Function to print usage
print_usage() {
    echo "Usage: $0 <username> <password>"
    echo
    echo "Creates a ~/.netrc file with Git credentials for machine $GIT_SERVER."
    echo
    echo "Arguments:"
    echo "  username    Git username"
    echo "  password    Git password"
    echo
    echo "Example:"
    echo "  $0 ronny superStrongPassword"
}

# Show help if requested
if [[ "$1" == "--help" || "$1" == "-h" ]]; then
    print_usage
    exit 0
fi

# Check for exactly 2 arguments
if [ "$#" -ne 2 ]; then
    echo "Error: Invalid number of arguments."
    print_usage
    exit 1
fi

GIT_USERNAME="$1"
GIT_PASSWORD="$2"

# Write to ~/.netrc
cat > ~/.netrc <<EOF
machine $GIT_SERVER
login $GIT_USERNAME
password $GIT_PASSWORD
EOF

# Secure the file
chmod 600 ~/.netrc

echo "~/.netrc created successfully with restricted permissions."

# Variables
YOCTO_REPO_URL="https://github.com/varigit/oe-layersetup"
YOCTO_BRANCH="master_var01"

META_TRISMED_REPO_URL="http://192.168.10.251/Bonobo.Git.Server/meta-trismed.git"
META_TRISMED_BRANCH="master"

# Directory setup
YOCTO_TRISMED_DIR="$PWD"

YOCTO_DIR="$PWD/var-ti-yocto"
BUILD_DIR="$YOCTO_DIR/build"
META_TRISMED_DIR="meta-trismed"

# Clone the Variscite Yocto repository
echo "Cloning Variscite Yocto repository..."
git clone -b $YOCTO_BRANCH $YOCTO_REPO_URL $YOCTO_DIR

# Clone meta-trismed layer
echo "Cloning custom meta-trismed layer..."
git clone -b $META_TRISMED_BRANCH $META_TRISMED_REPO_URL $META_TRISMED_DIR

# Enter the Yocto directory
cd $YOCTO_DIR

./oe-layertool-setup.sh -f configs/variscite/processor-sdk-09.02.01.10-config_var01.txt

# Source the environment setup script
echo "Setting up the build environment..."
cd $BUILD_DIR
. conf/setenv

# Add meta-company layer to bblayers.conf
echo "Adding Trismed's custom layer to bblayers.conf..."
echo "BBLAYERS += \"${YOCTO_TRISMED_DIR}/${META_TRISMED_DIR}\"" >> conf/bblayers.conf

# Add custom configurations to local.conf if needed
echo "Configuring local.conf..."
cat <<EOT >> conf/local.conf

# Custom configurations
MACHINE="am62x-var-som"

EOT

# Start the build
echo "Everything has been setup"
