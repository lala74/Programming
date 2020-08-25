# OpenSSL_Compilation

## Information

Version of OpenSSL
<https://www.openssl.org/source/>

## How to build OpenSSL for Haulotte

```bash
build_openssl() {
    echo "===== Build OpenSSL ====="

    export LIBRPATH="/media/apps/com.vendor.app1/lib"
    export CROSS_COMPILE="arm-gad-linux-gnueabi-"
    export SDK_PATH="/opt/gad/1.0.0"

    cd openssl
    ./Configure linux-generic32 shared \
        --prefix="${SYSROOT}/usr/local/ssl" --openssldir="/usr/lib/ssl" \
        --cross-compile-prefix="${SDK_PATH}/sysroots/x86_64-gadsdk-linux/usr/bin/arm-gad-linux-gnueabi/${CROSS_COMPILE}" \
        -Wl,-rpath=${LIBRPATH}
    make clean
    make depend
    make -j
    make install_sw

    cd -
}
```

## Attention

We shouldn't use `tgu_dev` command to create tgu_dev environment because Perl of Haulotte's SDK miss some module (ex: FindBin.pm)

After compiling OpenSSL:

- Copy `openssl` executable file in `/usr/local/ssl/bin/` to `/Fleet_factory_edge_software/Customerapp/com.vendor.app1/bin`

- Copy `libcrypto.so` + `libcrypto.so.1.1` + `libssl.so` + `libssl.so.1.1` libraries in `/usr/local/ssl/bin/lib` to `/Fleet_factory_edge_software/Customerapp/com.vendor.app1/lib`

- Make image file and flash it to tgu

Done !

```bash
# In TGU terminal
# openssl binary is in /media/apps/com.vendor.app1/bin

# Add new executable openssl path to env variable PATH
export PATH="/media/apps/com.vendor.app1/bin:$PATH"
# Execute openssl
ldd ./openssl       # pour vois les libraries manquants
./openssl           # execute openssl
```

### Run openssl temporally on tgu

After copying your openssl, extract it to your directory

#### Solution 1

Use **vi command** to edit file `/etc/ld.so.cnf` to add your directory PATH `PATH_DIRECTORY/ssl/lib`

Run `ldconfig -v` to load new libraries

Run `openssl` by using `./PATH_DIRECTORY/ssl/bin/openssl`

#### Solution 2

export LD_LIBRARY_PATH=`PATH_DIRECTORY/ssl/lib`

Run `openssl` by using `./PATH_DIRECTORY/ssl/bin/openssl`