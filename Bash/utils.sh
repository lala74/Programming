#!/bin/bash

root_ca_dir="."
home_dir="."
algorithm="genrsa"
COUNTRY="FR"
STATE=""
LOCALITY="LHorme"
ORGANIZATION_NAME="Haulotte"
root_ca_password="1hiqbYVWajO1TxXQyFl4"
key_bits_length="4096"
days_till_expire=3650
ca_chain_prefix="haulotte-develop-chain.ca"
intermediate_ca_dir="."
openssl_root_config_file="./openssl_root_ca.cnf"
openssl_intermediate_config_file="./openssl_device_intermediate_ca.cnf"
intermediate_ca_password="cKVoc1o9lSSInAml5B4f"
root_ca_prefix="haulotte_iot.root.ca"
lintermediate_ca_prefix="haulotte_factory_vaise.intermediate"

function full_verify()
{
        openssl verify \
                -CAfile ./certs/haulotte_iot.root.ca.cert.pem \
                -untrusted ./certs/haulotte_factory_vaise.intermediate.cert.pem \
                ./certs/new-ic-device.cert.pem
}

function verify()
{
        openssl verify \
                -CAfile ./certs/haulotte-develop-chain.ca.cert.pem \
                ./certs/new-ic-device.cert.pem
}

function create_chain()
{
        cat ${intermediate_ca_dir}/certs/${lintermediate_ca_prefix}.cert.pem \
                ${root_ca_dir}/certs/${root_ca_prefix}.cert.pem > \
                ${intermediate_ca_dir}/certs/${ca_chain_prefix}.cert.pem
}

function erase_key_cert()
{
        rm ./certs/* -f
        rm ./csr/* -f
        rm ./newcerts/* -f
        rm ./private/haulotte_factory_vaise.intermediate.key.pem -f
        rm ./private/haulotte_iot.root.ca.key.pem -f
}

function copy_key_cert()
{
        cp ./../*.cert.pem ./certs
        cp ./../*key.pem ./private
}

function clean()
{
        rm ./certs/*
        rm ./csr/*
        rm ./newcerts/*
        rm ./private/*
        rm index.txt*
        rm serial*
}

if [ "${1}" == "full_verify" ]; then
        full_verify
elif [ "${1}" == "verify" ]; then
        verify
elif [ "${1}" == "create_chain" ]; then
        create_chain
elif [ "${1}" == "clean" ]; then
        clean
elif [ "${1}" == "erase_key_cert" ]; then
        erase_key_cert
elif [ "${1}" == "copy_key_cert" ]; then
        copy_key_cert
else
        echo "Usage: full_verify        #"
        echo "       verify             #"
        echo "       create_chain       #" 
        echo "       clean              #" 
        echo "       erase_key_cert              #" 
        echo "       copy_key_cert              #" 
        exit 1
fi