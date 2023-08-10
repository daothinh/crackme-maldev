# crackme-maldev 过春风十里，眼中仍为你

 ... From Crackmes.one and anything everywhere

Compiler 32-bit with WSL: `gcc -m32 input.c -o output`

- `sudo apt-get update`
- `sudo apt install gcc`
- `sudo apt-get install build-essential libc6-dev-i386`

Install WSL for all User in Windows:
Open PowerShell as admin

- check distro: `wsl --list --online`
- mov distro to User: `wsl --set-default <Distro>`
- run distro: `wsl`

Install WSL in User

- Compiler 64-bit with WSl: `gcc input.c -o ouput`

- Compiler when use socket: `gcc bind-shell.c -o bind-shell -lws2_32`

## Config Network Ubuntu

```yaml
# Config netplan:

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
```

## Config OpenSSL

Install Certificate
Tạo thư mục chứa key và chứng chỉ:
`mkdir certs && cd certs`
  
Create private key RSA 2048 bit:
  `openssl genrsa -out server.key 2048`

Create Certification File
  `openssl req -new -key server.key -out server.csr`

Create Cer with CSR:

  `openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt`

Append private key và Cer to only file <.pem> :
  `cat server.key server.crt > server.pem`

OpenSSL

`openssl s_server -accept <port> -cert server.pem`

## Config Network Kali Linux

```yaml
auto eth0
  iface eth0 inet dhcp
auto eth1
  iface eth1 inet static
  address 192.168.1.68
  netmask 255.255.255.0
```

## Shared Folder in VMWare

Modify: `sudo nano /etc/fstab`

Add String to last file:
`vmhgfs-fuse    /mnt/hgfs    fuse    defaults,allow_other    0    0`

Create file: `mkdir /mnt/hgfs`

Mount: `mount -a`

## Take it Easy on Anything

Fix Yara rule:
  `sudo -u cape poetry run extra/poetry_yara_installer.sh`

Compile Yara rule:
  `sudo -u cape poetry run extra/poetry_yara_installer.sh`

Disable port 2042

```bash
netstat -putana | grep 2042
sudo fuser -n tcp -k 2042
```

Restart all service: `systemctl daemon-reload`

## Config SSH Authentication

VM Client, create SSH Key

- `ssh-keygen -t rsa -b 4096`

Copy & paste SSH Key to Server (Maybe request password)

- `cat ~/.ssh/id_rsa.pub | ssh username@server "mkdir -p ~/.ssh && chmod 700 ~/.ssh && cat >>  ~/.ssh/authorized_keys"`

In Server, Pemission SSH Key

- `chmod 600 ~/.ssh/authorized_keys`

In Client, Create new file config in `~./ssh`

```bash
# New config if not exist
nano ~/.ssh/config
#Paste to nano-editor
Host *
  IdentityFile ~/.ssh/id_rsa
```

## => To be Continued
