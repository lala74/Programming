#!/bin/bash
#################################################
# README
#################################################
# Add this line to .bashrc to update all function
# source /path/to/this/file
#

#################################################
# Initialize constant
#################################################
PASSWORD="Laminhduc1997*"
website="https://outlook.office365.com/mail/inbox"
export NOTE_PATH=~/Desktop/TODO.md
export TGU_PASSWORD=Actia*2017
export NOW=""

HOUR_NOW=$(date +%H:%M)
if [[ "08:00" < "${HOUR_NOW}" && "${HOUR_NOW}" < "11:30" ]]; then
    NOW="morning"
elif [[ "15:00" < "${HOUR_NOW}" && "${HOUR_NOW}" < "19:30" ]]; then
    NOW="afternoon"
elif [[ "20:00" < "${HOUR_NOW}" && "${HOUR_NOW}" < "23:59" ]]; then
    NOW="night"
fi

#################################################
# Main function
#################################################
function md_start_working_day() {
    clearScreen "Set trackstick to off"
    md_trackstick off
    sleep 1

    clearScreen "Open TODO file"
    md_open_TODO
    sleep 1

    clearScreen "Open website"
    open_website ${website}
    sleep 1

    clearScreen "Open soft"
    open_vscode
    sleep 1

    clearScreen "Update and upgrade Ubuntu"
    md_update_ubuntu
    sleep 1
    
    message_from_love
}

##################################################
# Hidden function
##################################################
# Clear screen by enter 7 lines
function clearScreen() {
    echo -e "\r\n\n\n\n\n\n\n"
    echo "${1}"
    echo "-----------------------"
}

function terminal_new_tab() {
    gnome-terminal --tab
    gnome-terminal --tab
}

function open_website() {
    xdg-open ${1}
    check_return_value $?
}

function open_vscode() {
    code ~/Workspace/Fleet_factory_edge_software/
    check_return_value $?
}

function message_from_love() {
    case ${NOW} in
    "morning")
        clearScreen "Enjoy your working day !!!"
        ;;
    "afternoon")
        clearScreen "See you later !!!"
        ;;
    "night")
        clearScreen "You should sleep soonner, dear"
        ;;
    *)
        clearScreen "Always love you"
        ;;
    esac
}

function check_argument_and_print_usage() {
    if [ "$#" -ne 3 ]; then
        echo "Usage:"
        echo "  ${FUNCNAME[0]} <functionName> <numberArgumentActual> <exampleArgument>"
        return -1
    fi

    functionName="${1}"
    numberArgumentActual="${2}"
    exampleArgument="${3}"
    numberArgumentExpected=$(wc -w <<<"${exampleArgument}")

    if [ "${numberArgumentActual}" -ne "${numberArgumentExpected}" ]; then
        echo "Usage:"
        echo "  ${functionName} ${exampleArgument}"
        return -1
    fi

    return 0
}

function check_return_value() {
    msg="---------------------------------\n"
    [ ${1} -eq 0 ] && msg+="DONE" || msg+="FAILED, exit code: ${1}"
    echo -e ${msg}
}

#################################################
# Useful function
#################################################
# Disable trackstick to prevent the mouse moving by itself
function md_trackstick() {
    arguments="<stateTrackstick>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    case ${1} in
    "on")
        STATE=1
        ;;
    "off")
        STATE=0
        ;;
    *)
        echo -e "You have to choose between on and off, you bastard !!"
        return -1
        ;;
    esac
    xinput -set-prop "AlpsPS/2 ALPS DualPoint Stick" "Device Enabled" ${STATE}
    check_return_value $?
}

function md_open_TODO() {
    xdg-open /home/lala/Desktop/TODO.md
    check_return_value $?
}

function md_update_ubuntu() {
    echo ${PASSWORD} | sudo -u root --stdin apt-get update
    check_return_value $?
    sleep 1
    echo ${PASSWORD} | sudo -u root --stdin apt-get upgrade -y
    check_return_value $?
    sleep 1
    echo ${PASSWORD} | sudo -u root --stdin apt --fix-broken install
    check_return_value $?
    sleep 1
}

function md_git_lazy() {
    arguments="<message>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    git add .
    git commit -a -m "${1}"
    git push
    check_return_value $?
}

function md_git_not_so_lazy() {
    arguments="<message> <file>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    echo "Msg: ${1}"
    echo "File: ${2}"
    git add ${2}
    git commit -m "${1}"
    git push
    check_return_value $?
}

function md_set_title_for_terminal_tab() {
    arguments="<tabName>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    if [[ -z "$ORIG" ]]; then
        ORIG=$PS1
    fi
    TITLE="\[\e]2;$*\a\]"
    PS1=${ORIG}${TITLE}
    check_return_value $?
}

function md_update_PATH() {
    arguments="<PATH>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    case ":${PATH:=$1}:" in
    *:"$1":*) ;;

    *)
        PATH="$1:$PATH"
        ;;
    esac
    check_return_value $?
}

function md_hotspot() {
    arguments="<hotspotState>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    hotspotStatus="off"
    connectionInfo=$(nmcli -t device wifi)
    connectionSignalStrength=$(echo ${connectionInfo} | cut -d':' -f6)

    if ((${connectionSignalStrength} == 0)); then
        hotspotStatus="on"
    else
        hotspotStatus="off"
    fi

    case ${1} in
    "on")
        if [[ $hotspotStatus == "off" ]]; then
            nmcli device wifi hotspot con-name DucLaptop ssid DucLaptop band bg password MinhDuc1997
            check_return_value $?
            nmcli dev wifi show-password
        else
            echo "Hotspot is already on, dumbass !"
        fi
        ;;
    "off")
        if [[ $hotspotStatus == "on" ]]; then
            nmcli connection down DucLaptop
            check_return_value $?
        else
            echo "There is no hotspot for you to turn it off ?? :D ??"
        fi
        ;;
    *)
        echo "You should enter on/off bastard !!!"
        ;;
    esac
}

# Add ssh key to ssh-agent
function md_add_ssh_key_to_ssh_agent() {
    arguments="<sshKeyPath>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    eval "$(ssh-agent -s)"
    ssh-add ${1}
    check_return_value $?
}

function md_remove_software() {
    arguments="<softwareName>"
    check_argument_and_print_usage ${FUNCNAME[0]} $# ${arguments}
    [ $? -ne 0 ] && return

    echo ${PASSWORD} | sudo -u root --stdin apt autoremove ${1} -y
    check_return_value $?
    echo ${PASSWORD} | sudo -u root --stdin apt remove ${1}
    check_return_value $?
    echo ${PASSWORD} | sudo -u root --stdin apt purge ${1}
    check_return_value $?
}

function md_connect_HLT_azure_vm() {
    sshpass -p '$Minh42duc' ssh DevBE@52.233.130.26
}

function md_send_file_to_HLT_azure_vm() {
    sshpass -p '$Minh42duc' scp ${1} DevBE@52.233.130.26:${2}
}

function md_start_xampp() {
    echo ${PASSWORD} | sudo -u root --stdin /opt/lampp/lampp start
}