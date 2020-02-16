--------------------------------------------------------
--  DDL for Table
--------------------------------------------------------

CREATE TABLE "SYSADM"."ORDERCOTRAILER" (
	DOC_ID VARCHAR2(32),
	CUSTOMER_ID VARCHAR2(32),
	CO_ID VARCHAR2(32),
	OTNAME VARCHAR2(256),
	CHARGE NUMBER,									
	ENTRY_DATE DATE,
	ENTRY_OWNER VARCHAR2(16)
);

--------------------------------------------------------
--  DDL for Index
--------------------------------------------------------

CREATE UNIQUE INDEX "SYSADM"."PK_ORDERCOTRL_IDX" ON "SYSADM"."ORDERCOTRAILER"
("DOC_ID", "CUSTOMER_ID", "CO_ID", "OTNAME");

--------------------------------------------------------
--  DDL for Constraints
--------------------------------------------------------

--------------------------------------------------------
--  DDL for Grants
--------------------------------------------------------

GRANT SELECT, INSERT, UPDATE, DELETE ON "SYSADM"."ORDERCOTRAILER" TO ASH;

--------------------------------------------------------
--  DDL for Synoyms
--------------------------------------------------------

CREATE OR REPLACE PUBLIC SYNONYM ORDERCOTRAILER FOR "SYSADM"."ORDERCOTRAILER";

QUIT
/
