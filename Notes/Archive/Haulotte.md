# Note for work

## Haulotte

### Hide key in software

Cross-platform way of hiding cryptographic keys in C++?
<https://stackoverflow.com/questions/1112456/cross-platform-way-of-hiding-cryptographic-keys-in-c>

Where to store the private key?
<https://softwareengineering.stackexchange.com/questions/220950/where-to-store-the-private-key>

How do you hide secret keys in code?
<https://stackoverflow.com/questions/764012/how-do-you-hide-secret-keys-in-code>

---

## USB

### USB Detection in Linux

How to execute a shellscript when I plug-in a USB-device
<https://unix.stackexchange.com/questions/65891/how-to-execute-a-shellscript-when-i-plug-in-a-usb-device>

How to run custom scripts upon USB device plug-in?
<https://unix.stackexchange.com/questions/28548/how-to-run-custom-scripts-upon-usb-device-plug-in>

UsbDriveDoSomethingHowto
<https://help.ubuntu.com/community/UsbDriveDoSomethingHowto>

Udev rule: ACTION==“add” is working, but ACTION==“remove” isn't working!
<https://unix.stackexchange.com/questions/178341/udev-rule-action-add-is-working-but-action-remove-isnt-working>

**Important !!**File *.sh need authority to run

```bash
chmod +x NAMEFILE.sh
```

#### Get information of mount command

You can get information of mount command in `/proc/mount` file

### USB encryption

<https://linuxconfig.org/usb-stick-encryption-using-linux>

---

## Include PATH for VSCode C++

```
${workspaceFolder}/**
/usr/include/**
/opt/gad/1.0.0/sysroots/x86_64-gadsdk-linux/usr/**
/opt/gad/1.0.0/sysroots/cortexa9hf-vfp-neon-gad-linux-gnueabi/usr/**
```

---

## SSL Certificate

### Digital certificate

<https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs>

Create certificate from certificate parent
<https://jamielinux.com/docs/openssl-certificate-authority/create-the-intermediate-pair.html>

<https://stackoverflow.com/questions/10175812/how-to-create-a-self-signed-certificate-with-openssl>

<https://dadhacks.org/2017/12/27/building-a-root-ca-and-an-intermediate-ca-using-openssl-and-debian-stretch/>

<https://smartnets.wordpress.com/2017/04/27/create-certificate-chain-and-sign-certificates-using-openssl/>

### For certs generator

```bash
function PATH_update() {
    case ":${PATH:=$1}:" in *:"$1":*) ;; *) PATH="$1:$PATH" ;; esac
}

PATH_update "/media/apps/com.vendor.app1/bin"

echo -e "\e[1mEnv variable PATH: \e[22m"
echo -e "\e[32m$PATH\e[0m"

echo -e "\e[1mOpenSSL Version: \e[22m"
echo -e "\e[32m`openssl version`\e[0m"

echo -e "\e[1mUsage for Certs Generator: \e[22m"
```

---

## IoT Hub

Exemple python pour tester iothub 

https://github.com/Azure/azure-iot-sdk-python/blob/master/azure-iot-device/samples/sync-samples/send_message_x509.py

Séquence de provisionning via iot hub dps 

https://docs.microsoft.com/en-us/azure/iot-dps/about-iot-dps

## Encryption aes-256-cbc

```bash
openssl enc -aes256 -base64 -md sha1 -in secret.bin.aes -out secret.bin.plaintext -pass file:key.bin -d
openssl enc -aes256 -base64 -md sha1 -in secret.bin -out secret.bin.aes -pass file:key.bin -e
```
