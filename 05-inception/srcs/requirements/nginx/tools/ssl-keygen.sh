#!/bin/sh

set -e

mkdir -p /etc/nginx/ssl

if [ ! -e /etc/nginx/ssl/junkpark.42.fr.crt ]; then
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/junkpark.42.fr.key -out /etc/nginx/ssl/junkpark.42.fr.crt -subj "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=JunkPark/CN=junkpark.42.fr"
fi
