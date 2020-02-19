#/bin/bash

ORA='SYSTEM@BSCSDB'
sqlplus ${ORA} @create-user-SYSADM.sql
ORA="SYSADM/SYSADM@BSCSDB"
sqlplus ${ORA} @create-table-ORDERCOTRAILER.sql
