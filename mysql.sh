#!/bin/expect
spawn mysql -h 129.211.69.209 -u root -p
expect "*password*"
send "Hhcl199904020\n"
expect "MySQL*"
send "USE HFTS;\n"
interact
