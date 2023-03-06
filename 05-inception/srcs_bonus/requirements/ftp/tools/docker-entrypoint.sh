#!/bin/bash

mkdir -p "/var/run/vsftpd/empty"
mkdir -p "/home"
chown -R ftp:ftp "/home"

echo -e "${FTP_USER}\n${FTP_PASS}" > /etc/virtual_users.txt
db_load -T -t hash -f /etc/virtual_users.txt /etc/virtual_users.db

echo "pasv_max_port=${PASV_MAX_PORT}" >> /etc/vsftpd.conf
echo "pasv_min_port=${PASV_MIN_PORT}" >> /etc/vsftpd.conf

vsftpd /etc/vsftpd.conf
