# crackme-maldev 过春风十里，眼中仍为你

 ... From Crackmes.one and anything everywhere

Compiler 32-bit with WSL: `gcc -m32 input.c -o output`

- sudo apt-get update
- sudo apt install gcc
- sudo apt-get install build-essential libc6-dev-i386

Compiler 64-bit with WSl: `gcc input.c -o ouput`

Compiler when use socket: `gcc bind-shell.c -o bind-shell -lws2_32`

## Config Network Ubuntu

 network:
  version: 2
  renderer: networkd
  ethernets:

    # Interface ens33 kết nối VMnet NAT
    ens33:
      dhcp4: yes
      dhcp6: no

    # Interface ens36 kết nối VMnet host-only 
    ens36:
      addresses: [192.168.1.100/24]

      # Cấu hình DNS server
      nameservers:
         addresses: [192.168.1.100]

      # Cấu hình định tuyến mặc định
      routes:
       - to: 0.0.0.0/0
         via: 192.168.1.1
         metric: 100

## OpenSSL

Install Certificate
Tạo thư mục chứa key và chứng chỉ:
  `mkdir certs`
  `cd certs`
  
Tạo private key RSA 2048 bit:
  `openssl genrsa -out server.key 2048`

Tao file request chung chi
  `openssl req -new -key server.key -out server.csr`

Tạo chứng chỉ tự ký sử dụng CSR:

  `openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt`

Gộp private key và chứng chỉ thành file .pem duy nhất:
  `cat server.key server.crt > server.pem`

OpenSSL

  `openssl s_server -accept 443 -cert server.pem`

# Shared Folder VMware

Modify file
    `sudo nano /etc/ftfs`

In last line add string
    vmhgfs-fuse    /mnt/hgfs    fuse    defaults,allow_other    0    0

Create folder
    `mkdir /mnt/hgfs`

Mount file
    `mount -a `