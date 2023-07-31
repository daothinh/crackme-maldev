# Round 1
## Blue Build: Website OWASP Juice Shop
1. Def
- Log sys
- Detect file .sh -> very late when red attack

2. bWAPP


## RedTeam:
1. Exploit
- Lo hong RCE qua MARrsDB //
    + RCE?
    + MarsDB, khai thac loi tu nha phat trien => CSDL lquan NodeJS
- POC?

2. Persistence - Bang moi cach, giu quyen truy cap sau khi bi phat hien (vi du: backdoor)
- SSH Authorzied Key: Them public key -> /.ssh/authorized_key (default) = quyen root -> (quyen root chi co sys moi co, vi vay se ko bi phat hien khi check user)
    -> Khi su dung duong dan mac dinh de luu key -> rat de dang phat hien
    -> Nen tuy bien directory ssh key -> HInt: `giu directory ssh key cu, tai directory moi copy key cu & tao key attacker tai duong dan moi va copy key cu de dam bao victim van su dung dc ssh key -> vua dam bao co key ssh attcker, vua dam bao victim van co the su dung` - hint nay co the bi phat hien neu sysad su dung theo doi thay doi doc ghi file

- T1503.003|Crontab

- SSH -> rat hay
- Chen malware vao $PATH (thu tu doc tu tren xuong duoi, trai sang phai), khi thuc thi cau lenh `ls`, se goi toi $PATH, vo hinh chung se thuc thi luon ca malware

`//NOte: Shell binh thuong kha ngu, de timeout hoac crash khi dung sai lenh hoac cac lenh ko dc phep, de reconnect lien toi, can su dung hash key -> cai thien cac han che cua shell ban dau`
    (ko show port?) 
- Han che revese shell qua nhieu lan, vi nguoi dung neu su dung script fake `ls` -> shell thuc thi qua nhieu -> crash

