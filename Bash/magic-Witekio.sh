#!/bin/bash

version=$(cat src/packages/release/CustomerSetup/com.haulotte.cmewp/bin/release)
image_name="CustomerSetup-${version}.tgz"

# Execute another function and check output
function execute() {
    msg="-----------------------\n"
    "$@"
    if (($? != 0)); then
        msg+="Error, exit code $?"
    else
        msg+="DONE"
    fi
    echo -e ${msg}
    sleep 1
}

function clearScreen() {
    echo -e "\r\n\n\n\n\n\n\n"
    echo "${1}"
    echo "-----------------------"
}

clearScreen "Build project"
cd cmake-build-release-actia
execute make
cd ..

clearScreen "Create image"
rm install-dir/CustomerSetup-0.2.8.tgz
execute ./dev-tools/release-scripts/create-release-package.sh

clearScreen "Copy image"
execute sshpass -p "Actia*2017" scp install-dir/${image_name} root@192.168.24.101:/media/maps

clearScreen "Extract and change name of containedapp"
execute sshpass -p "Actia*2017" ssh root@192.168.24.101 rm -r /media/apps/com.haulotte.cmewp
execute sshpass -p "Actia*2017" ssh root@192.168.24.101 tar -xzvf /media/maps/${image_name} -C /media/apps
execute sshpass -p "Actia*2017" ssh root@192.168.24.101 mv /media/apps/com.haulotte.cmewp/bin/containedapp /media/apps/com.haulotte.cmewp/bin/mainapp

