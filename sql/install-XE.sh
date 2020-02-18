#/bin/bash

ORA='SYSTEM/oracle@XE'
sqlplus ${ORA} @create-user-SYSADM.sql
ORA="SYSADM/SYSADM@XE"
sqlplus ${ORA} @create-table-ORDERCOTRAILER.sql
