#!/usr/bin/python3
# -*- coding: utf-8 -*-
import sys
import getopt
import logging
import unittest
import json
import jsonrpc_pyclient
import threading
import socket
import http.server
import socketserver
import datetime
import subprocess
import sys
import time
import os, errno
import os.path
from os import path
from jsonrpc_pyclient.connectors import socketclient
# client stub created by libjson-rpc-cpp stubgenerator
from FactoryClientStub import FactoryClientStub

logging.basicConfig()
target = ""
dst_ip_address = ""
dst_port = 2500
own_ip_address = ""
HTTP_PORT = 8000
myHTTPserver = socketserver.TCPServer
imageFile = ""


def usage():
    print("usage: auto-tests.py (--target=tgu|desktop | \
--target_ip=<ip_addr>) --image=<file> <test>")
    print("       ex: ./auto-tests.py \
--target=desktop TestFactoryApp.test_jsonrpc_basic")
    print("       'auto-tests.py --list' displays all available tests")
    print("       Plus use Unittest args")


def myHttpServer():
    # Start Http server
    global HTTP_PORT
    global myHTTPserver
    # web_dir = os.path.join(os.path.dirname(__file__), 'web')
    # os.chdir(web_dir)
    Handler = http.server.SimpleHTTPRequestHandler
    myHTTPserver.allow_reuse_address = True
    with socketserver.TCPServer(("", HTTP_PORT), Handler) as myHTTPserver:
        print("Http serving on all interfaces at port", HTTP_PORT)
        myHTTPserver.serve_forever()
    print("Http server: closing")
    myHTTPserver.server_close()


def my_ip(dest):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect((dest, 1027))
    except socket.error:
        return None
    return s.getsockname()[0]


def get_target():
    global target
    return target

def symlink_force(target, link_name):
    try:
        os.symlink(target, link_name)
    except OSError as e:
        if e.errno == errno.EEXIST:
            os.remove(link_name)
            os.symlink(target, link_name)
        else:
            raise e

def main(argv):
    global target
    global dst_ip_address
    global own_ip_address
    global imageFile;
    target = "tgu"
    target_ip = ""
    #  print('argv=', argv)
    try:
        opts, args = getopt.getopt(sys.argv[1:], "vh", ["target=", "target_ip=",
                                   "image=", "help", "list"])
    except getopt.GetoptError:
        usage()
        sys.exit(2)

    if len(opts) == 0:
        usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            unittest.main(exit=True)
        elif opt in ("--list"):
            method_list = [func for func in dir(TestFactoryApp) if callable(getattr(TestFactoryApp, func)) and func.startswith("test_")]
            print("Available tests are:")
            for i in method_list:
                print("  TestFactoryApp." + i)
            sys.exit(0)
        else:
            if opt in ("--target"):
                valid_targets = ['tgu', 'desktop']
                if arg not in valid_targets:
                    usage()
                    sys.exit(2)
                target = arg
                sys.argv.remove(opt+'='+arg)
            elif opt in ("--target_ip"):
                target_ip = arg
                sys.argv.remove(opt+'='+arg)
            if opt in ("--image"):
                imageFile = arg
                sys.argv.remove(opt+'='+arg)

    print('Target is', target)
    if len(target_ip) != 0:
        dst_ip_address = target_ip
    elif target == 'tgu':
        dst_ip_address = "192.168.1.1"
    elif target == 'desktop':
        dst_ip_address = "127.0.0.1"
    else:
        assert False, "Incorrect target value"
    print('Target IP address is', dst_ip_address)
    own_ip_address = my_ip(dst_ip_address)
    print('My own IP address is', own_ip_address)

    # Start HTTP server
    myHTTPthread = threading.Thread(name='HTTPdaemon', target=myHttpServer)
    myHTTPthread.setDaemon(True)
    myHTTPthread.start()
    time.sleep(0.5)

    unittest.main(exit=False)
    # time.sleep(120)
    # Shutdown server
    print("Http server: shutdown")
    myHTTPserver.shutdown()
    myHTTPthread.join()


class TestFactoryApp(unittest.TestCase):
    def setUp(self):
        global dst_ip_address
        global dst_port
        # print("Connecting to TGU Json-RPC server "+dst_ip_address+":"
        #      + str(dst_port))
        self.connector = socketclient.TcpSocketClient(dst_ip_address,
                                                      dst_port,
                                                      None,
                                                      1024)
        self.client = FactoryClientStub(self.connector)

    def test_jsonrpc_basic(self):
        result = self.client.sum(4, 5)
        self.assertEqual(result, 9, "4+5=9")
        result = self.client.echo("Hello")
        self.assertEqual(result, ['Hello'])
        result = self.client.subtract(4, 5)
        self.assertEqual(result, -1)
        result = self.client.sum(5, 5)
        self.assertEqual(result, 10)

    def test_jsonrpc_tguversion(self):
        x = '{"haulotteversion":"B_1.0", "tguversion":"unknown"}'
        y = json.loads(x)
        result = self.client.get_tguversion()
        self.assertRegex(result["haulotteversion"], "B_v\d+\.\d+.*")
        self.assertRegex(result["tguversion"], "unknown|\d{12}")

    def test_jsonrpc_load_final_software(self):
        global HTTP_PORT
        global own_ip_address
        test_file = "test_file.txt"
        f = open(test_file, "w")
        f.write(str(datetime.datetime.now())+'\n')
        for x in range(1024):  # 1k blocks
            f.write('\n'+str(x)+'\n')
            f.write(str(bytearray(b'A' * 1024)))
        f.write('\n'+str(datetime.datetime.now())+'\n')
        f.close()
        url = "http://"+own_ip_address+":"+str(HTTP_PORT)+"/"+test_file
        result = self.client.load_final_software(url)
        self.assertEqual(result["statusok"], True)
        url = "http://"+own_ip_address+":"+str(HTTP_PORT)+"/"+"do_not_exist.txt"
        result = self.client.load_final_software(url)
        self.assertEqual(result["statusok"], False)
        self.assertEqual(result["error"], "HTTP error, download aborted")

#    @unittest.skipUnless(path.exists("../CustomerSetup.tgz"),
#                         "test used for image upload")
    def load_software(self):
        global HTTP_PORT
        global own_ip_address
        global dst_ip_address
        global dst_port
        global imageFile

        if not os.path.isfile(imageFile):
            self.skipTest("Image file not found")     
        symlink_force(imageFile, "CustomerSetup.tgz")
        url = "http://"+own_ip_address+":"+str(HTTP_PORT)+"/"+"CustomerSetup.tgz"
        result = self.client.load_final_software(url)
        self.assertEqual(result["statusok"], True,"load_final_software()")
        result = self.client.flash_final_software()
        self.assertEqual(result["statusok"], True, "flash_final_software()")
        result = self.client.TCUrebootupdate()
        self.assertEqual(result["statusok"], True, "TCUrebootupdate()")
        # KO: Transport endpoint is already connected
        iReady=0;
        s =  socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        while iReady == 0:
            time.sleep(2)
            try:
                #s.setblocking(0)
                s.settimeout(2.0)
                iReady=1
                s.connect((dst_ip_address, dst_port))
            except socket.error as e:
                iReady=0
                print(e)
            if iReady == 0:
                print("Rebooting...")
            else:
                print("Ready")
                time.sleep(2)
        s.close()

    def test_ssh(self):
        global dst_ip_address
        global target
        if target == 'desktop':
            self.skipTest("Not applicable on desktop platform")
        with subprocess.Popen(['sshpass', '-p', 'Haulotte42*', 'ssh',
                               'root@'+dst_ip_address, 'uname', '-n'],
                              shell=False,
                              stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE) as ssh:
            result = ssh.stdout.readlines()
            error = ssh.stderr.readlines()
            # ssh.kill()
            # exit_code = ssh.wait()
        # if result == []:
            # print("ERROR: %s" % error, file=sys.stderr)
        # else:
            # print(result)
        self.assertEqual(result, [b'tgur-access\n'])

    def test_jsonrpc_basic_endurance(self):
        for x in range(1000):
            result = self.client.sum(4, 5)
            self.assertEqual(result, 9, "4+5=9")
            result = self.client.echo("Hello")
            self.assertEqual(result, ['Hello'])
            result = self.client.subtract(4, 5)
            self.assertEqual(result, -1)
            result = self.client.sum(5, 5)
            self.assertEqual(result, 10)

    def test_jsonrpc_io(self):
        result = self.client.get_WakeUpInput()
        self.assertEqual(result,  1, "")


if __name__ == '__main__':
    main(sys.argv[1:])
