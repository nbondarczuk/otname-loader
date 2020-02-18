--------------------------------------------------------
--  DDL for Table
--------------------------------------------------------

CREATE TABLE "ORDERCOTRAILER"
(
	DOCUMENT_ID VARCHAR2(32),
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

CREATE UNIQUE INDEX "PK_ORDERCOTRL_IDX" ON "ORDERCOTRAILER"
(
 "DOCUMENT_ID",
 "CUSTOMER_ID",
 "CO_ID",
 "OTNAME"
);

--------------------------------------------------------
--  DDL for Constraints
--------------------------------------------------------

--------------------------------------------------------
--  DDL for Grants
--------------------------------------------------------

GRANT SELECT, INSERT, UPDATE, DELETE ON "ORDERCOTRAILER" TO SYSADM;

--------------------------------------------------------
--  DDL for Synoyms
--------------------------------------------------------

CREATE OR REPLACE PUBLIC SYNONYM ORDERCOTRAILER FOR "ORDERCOTRAILER";

QUIT
/
