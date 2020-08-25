#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import os
import getpass
import pprint
import hashlib
import paramiko
import subprocess

username = getpass.getuser()
PW_FILE_NAME = "pw_to_decrypt_secret_key.bin"
PW_FILE_PATH = os.path.dirname(os.path.abspath(PW_FILE_NAME)) + "/" + PW_FILE_NAME
USB_STICK_BASE_PATH = "/media/" + username
ROOT_PASSWORD_SECRET_FILENAME = "secret.bin"

TGU_IP = '192.168.24.101'
HLT_PASSWD = 'Haulotte42*'

list_TGU_SN = [
    '23710593464070'
]

# Print list of TGU SN to avoid mistake while entering SN
def print_TGU_SN():
    list_tgu_file = open('list_tgu.txt', 'r') 
    list_tgu = list_tgu_file.readlines()
    print "--------------"
    print "List of TGU SN"
    print(''.join(list_tgu))
    print "--------------"
    list_tgu_file.close()


def search_secret_file():
    for root, _, files in os.walk(USB_STICK_BASE_PATH):
        for name in files:
            if name == ROOT_PASSWORD_SECRET_FILENAME:
                return os.path.join(root, name)
    return -1


def md5_secret_file(file):
    with open(file, 'rb') as f:
        file_as_bytes = f.read()
    return hashlib.md5(file_as_bytes).hexdigest()


def get_contents(filename):
    if os.path.exists(filename):
        fp = open(filename, "r")
        content = fp.read()
        fp.close()
        # openssl enc -aes256 -base64 -md sha1 -in secret.bin.aes -out secret.bin.plaintext -pass file:key.bin -d

        return content

def decrypt_aes(filename):
    fileSecretKey = "./secret.bin.plaintext"
    if os.path.exists(filename):
        cmd = "openssl enc -aes256 -base64 -md sha1 -in " + filename + " -out " + fileSecretKey + " -pass file:" + PW_FILE_PATH + " -d"
        os.system(cmd)
        content = get_contents(fileSecretKey)
        try:
            os.remove(fileSecretKey)
        except OSError:
            pass
        return content


def generate_passwd(tguSN, secretKey):
    strConcatenated = tguSN + secretKey
    hashSHA256 = hashlib.sha256(strConcatenated.encode())
    passwd = hashSHA256.hexdigest()[0:24]
    return passwd


def SSH_connect_exec_cmd(passwd, cmd):
    # Initialize ssh client by using paramiko of python
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    response = ""
    e = ""

    try:
        ssh.connect(TGU_IP, username='root', password=passwd)
    except Exception as e:
        # There is an error
        print e
    else:
        # Connect to TGU successfully
        ssh_stdin, ssh_stdout, ssh_stderr = ssh.exec_command(cmd)
        response = ssh_stdout.readlines()

    return response


def main(argv):
    print_TGU_SN()

    print "Find PATH of secret file in USB stick"
    PATH = search_secret_file()

    if PATH == -1:
        print "We cannot find secret file"
        exit()
    else:
        print "Check MD5 checksum of secret file"
        md5_secret_file_origin = get_contents(PATH + ".md5")
        if (md5_secret_file(PATH) == md5_secret_file_origin):
            print "Get secret file contents"
            secretKey = decrypt_aes(PATH)
            print secretKey
        else:
            print "Secret key has been changed !!!!"
            exit()

    print_TGU_SN()
    tguSN = raw_input("Enter TGU Serial Number: ")

    print "Hash and generate password"
    passwd = generate_passwd(tguSN, secretKey)

    print "Connect to TGU and change to Haulotte default password"
    # Delete Haulotte config file
    cmd = "rm /media/data_current/etc/HLT_conf.ini"
    response = SSH_connect_exec_cmd(passwd, cmd)
    print '\n'.join(response)
    # Change password
    cmd = "echo " + "root" + ":" + HLT_PASSWD + " | chpasswd 2>&1"
    response = SSH_connect_exec_cmd(passwd, cmd)
    print '\n'.join(response)


if __name__ == '__main__':
    main(sys.argv[1:])
