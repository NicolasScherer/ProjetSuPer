-- DROP DATABASE IF EXISTS bdd_super;

-- CREATE DATABASE IF NOT EXISTS bdd_super CHARACTER SET 'utf8';

USE bdd_super;

DROP TABLE IF EXISTS lecteur;

CREATE TABLE lecteur
(
   num_lecteur 	INT UNSIGNED 		NOT NULL,
   num_lieu 	INT UNSIGNED UNIQUE	NOT NULL,
   ip 		VARCHAR (15) UNIQUE	NOT NULL,
   estConnecte 	TINYINT UNSIGNED	NOT NULL,
   
   PRIMARY KEY (num_lecteur)
   
)ENGINE=INNODB;


DROP TABLE IF EXISTS lieu;

CREATE TABLE lieu
(
   num_lieu	INT UNSIGNED 	NOT NULL,
   legende	VARCHAR(50) 	NOT NULL,
   
   PRIMARY KEY (num_lieu, legende)
   
)ENGINE=INNODB;


DROP TABLE IF EXISTS vue;

CREATE TABLE vue
(
   num_vue	INT UNSIGNED	NOT NULL,
   legende	VARCHAR(50)	NOT NULL,
   
   PRIMARY KEY (num_vue)
   
)ENGINE=INNODB;


DROP TABLE IF EXISTS representationLieuSurVue;

CREATE TABLE representationLieuSurVue
(
   num_vue	INT UNSIGNED 	NOT NULL,
   num_lieu	VARCHAR(50) 	NOT NULL,
   x		INT		NOT NULL,
   y		INT		NOT NULL,
   
   PRIMARY KEY (num_vue, num_lieu)
   
)ENGINE=INNODB;

