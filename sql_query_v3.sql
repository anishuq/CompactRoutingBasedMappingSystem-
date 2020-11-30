/*
In order to run this file, use the following at
the "mysql prompt": mysql> SOURCE /home/ahug/TCPClient/sql_query_v3.sql;
*/

USE LMIDstructure;

START TRANSACTION;

drop table if exists EIDList;

/*The table with the foreign key must be deleted first*/
drop table if exists LMIDTable;

CREATE TABLE LMIDTable (LMID VARCHAR(19) NOT NULL UNIQUE,
HASH_VALUE INT NOT NULL DEFAULT 0, PRIMARY KEY(LMID) )
ENGINE=InnoDB ;

CREATE TABLE EIDList (LMID VARCHAR(19) NOT NULL,
EIDPrefix VARCHAR(40) NOT NULL, EIDPrefixLength
VARCHAR(3) NOT NULL DEFAULT '0' ,Is_ Delegated CHAR NOT NULL
DEFAULT 'N', Delegated _RLOC VAROHAR(19) NOT NULL DEFAULT 'X',
UNIQUE(LMID, EIDPrefix , EIDPrefixLength) ,FOREIGN KEY(LMID)
REFERENCES LMIDTable(LMID)) ENGINE=InnoDB ;

drop table if exists ServerAddress;

CREATE TABLE ServerAddress(IpId INT NOT NULL AUTO_INCREMENT,
IP VARCHAR(19) NOT NULL UNIQUE, PRIMARY KEY(IpId )) ENGINE=InnoDB ;

COMMIT;

START TRANSACTION;

drop table if exists DelegatedLM;

CREATE TABLE DelegatedLM (LMID VARCHAR(19) NOT NULL, EIDPrefix
VARCHAR( 40) NOT NULL, EIDPrefixLength VARCHAR(3) NOT NULL DEFAULT '0' ,
Is_Used CHAR NOT NULL DEFAULT 'N' , UNIQUE(LMID, EIDPrefix )) ENGINE=InnoDB;

COMMIT;

