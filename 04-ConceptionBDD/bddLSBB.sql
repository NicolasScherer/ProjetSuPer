-- DROP DATABASE IF EXISTS bdd_super;

CREATE DATABASE IF NOT EXISTS bdd_super CHARACTER SET 'utf8';

USE bdd_super;

CREATE TABLE Lecteur
(
   num_lecteur	UNSIGNED INT,
   num_lieu 	UNSIGNED INT UNIQUE,
   ip		VARCHAR (15),
   estConnecte	UNSIGNED TINYINT,
   
   PRIMARY KEY (num_lecteur)
   
)ENGINE=INNODB;

CREATE TABLE Lieu
(
   num_lieu	UNSIGNED INT,
   legende	VARCHAR(50),
   
   PRIMARY KEY (num_lieu, legende)
   
)ENGINE=INNODB;

CREATE TABLE Vue
(
   num_vue	UNSIGNED INT,
   legende	VARCHAR(50),
   
   PRIMARY KEY (num_vue)
   
)ENGINE=INNODB;

CREATE TABLE RepresentationLieuSurVue
(
   num_vue	UNSIGNED INT,
   num_lieu	VARCHAR(50),
   x		INT,
   y		INT,
   
   PRIMARY KEY (num_vue, num_lieu)
   
)ENGINE=INNODB;
