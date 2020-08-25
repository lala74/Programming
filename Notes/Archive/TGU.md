# TGU

## Turn on dhcp server

```bash
# Configure your ethernet to manual
Address : 192.168.24.3
Netmask : 255.255.255.0

service isc-dhcp-server start
service isc-dhcp-server status
```

## Debug finding shared libs

```bash
LD_DEBUG=libs ./HLG_Factory_Base_App
```

## Connect to TGU

```bash
dhcp-lease-list
ssh root@IP_of_TGU
```

## Make file

```bash
make                # to make file
make clean
tgu_dev             # to access to tgu dev
make transfer       # transfer binary to machine
make run            # run machine

make image          # make image file to flash to TGU
```

## Load software image through Ethernet port

```bash
# Compile Haulotte application with GHOST_BASE_APP
tgu_dev
make clean
make GHOST_BASE_APP=1
# Make image file
make image

# Compile Haulotte application for debug
make
make transfer
make run

# Change to another tab of terminal
./auto-tests.py --target_ip=192.168.24.101 TestFactoryApp.load_software     # You can see the debug in the last terminal tab
./auto-tests.py -v --image=../CustomerSetup.v0.2-7-gd7b2fe4-dirty.tgz --target_ip=192.168.24.101 TestFactoryApp.load_software
# Open telnet to send command
telnet 192.168.24.101 2500
# Command found in json-rpc-tests.txt
{"jsonrpc": "2.0", "method": "flash_final_software", "id": "8"}             # flash image file, wait for a while
{"jsonrpc": "2.0", "method": "TCUrebootupdate", "id": "11"}                 # reboot
```

## Copy file to TGU

```bash
sshpass -p "Actia*2017" ssh root@192.168.24.101 mkdir -p /media/apps/Haulotte/
sshpass -p "Actia*2017" scp $(FACTORY_BASE_TARGET) root@192.168.24.101:/media/apps/Haulotte/


cd /home/lala/Workspace/b2129-haulotte-infrastructure/certs
sshpass -p "Actia*2017" scp *.sh *.cnf  root@192.168.24.101:/media/apps/Haulotte/
```

## Test TCU through wifi in Window

- Connect to TCU through wifi

- Open Putty and tap IP

```bash
cd /media/apps/demoapps
./gnss_demo -l > /dev/null &        # to open gnss function and run in background
cgps                                # should use gpsmon instead
gpsmon

./modem_demo -a orange.m2m.spec     # open modem demo - display the signal

./can_demo -i can0 -r 250000 -l     # listen in CAN line
```

### Password

Actia*2017 - for Actia application

Haulotte42* - after installing Haulotte application

## Location

### Libraries ATICIA

/opt/gad/1.0.0/sysoots/cortex./

### Certificate

sur nos TGU de dev, je les ai mis dans `/media/data_current/etc/certs`, et chaque module aura son propre fichier de config contenant les chemins nécéssaires à son utilisation

## Json working procedure

File `jsonrpc_methods.cpp`

- Add function
- Add function name to `struct jsonrpc_method_entry_t method_table[]` at the end of file

File `json-rpc-tests.txt`

- Add tram json to get result

File `HLT_repc_spec.json`

- Add json response

File `FactoryClientStub.py`

- Command `source update_stub.sh` to update this file

File `auto-tests.py`

- Add test function

File `Tests.md`

- Add test function name to list of function available

File `jsonRPC.log`

- Add json response

File `S-100504-Haulotte Diag for Fleet`

- Add function command and result to the link below
[S-100504-Haulotte Diag for Fleet](https://teams.microsoft.com/l/file/9F329E3A-9B17-4953-98A6-3EBE9C69AC55?tenantId=1b1f536d-a57e-4484-8a7e-e9ec6ea4fcdd&fileType=docx&objectUrl=https%3A%2F%2Fhaulottegroupsa.sharepoint.com%2Fsites%2FFleetManagement%2FDocuments%20partages%2FTrackeur%2FEtude%20-%20Lot%201A%2FUsine%2FS-100504-Haulotte%20Diag%20for%20Fleet.docx&baseUrl=https%3A%2F%2Fhaulottegroupsa.sharepoint.com%2Fsites%2FFleetManagement&serviceName=teams&threadId=19:a6c3890d93c54b3cb07d356cf94eb124@thread.skype&groupId=27cbd3cc-7965-4e4b-b759-44f1e5fe2ad3)
