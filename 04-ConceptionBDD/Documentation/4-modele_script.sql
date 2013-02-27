/*
Conserver les informations suivante pour chaque étudiant :
? Classe (BTS SE OU IRIS)
? Nom, prénom, date de naissance
? N° de téléphone, portable
? Adresse mail
? Date d'entrée/sortie de l'établissement
? Entreprise de stage
? Parcours POST BTS
? Un champ information libre.
*/


DROP DATABASE IF EXISTS bdd_etudiant;

CREATE DATABASE bdd_etudiant CHARACTER SET 'utf8';

USE bdd_etudiant;

/*
	nomSection	le nom de sa section : BTS SE, IRIS
	dateEntree	date d'entree dans l'etablissement
	dateSortie	date de sortie de l'etablissement
	info		champ d'information libre		
*/

CREATE TABLE etudiant
(
	id				INT AUTO_INCREMENT,
	f_categorie_id	INT,
	nomSection		VARCHAR(20)			NOT NULL,
	nom				VARCHAR(40)			NOT NULL,
	prenom			VARCHAR(40)			NOT NULL,
	dateNaissance	DATETIME			NOT NULL,
	telFixe			VARCHAR(20),
	telPortable		VARCHAR(20),
	mail			VARCHAR(50)			NOT NULL,
	dateEntree		DATETIME			NOT NULL,
	dateSortie		DATETIME,
	infoLibre		TEXT,
	
	PRIMARY KEY (id)
	
)ENGINE=INNODB;

CREATE TABLE parcours
(
	f_etudiant_id 	INT					NOT NULL,
	dateDebut		DATE				NOT NULL,
	dateFin			DATE,
	etablissement	VARCHAR(40)			NOT NULL,
	pays			VARCHAR(40)			NOT NULL,
	departement		VARCHAR(40)			NOT NULL,
	ville			VARCHAR(40)			NOT NULL,
	adresse			VARCHAR(40),
	tel				VARCHAR(20),
	statut			VARCHAR(40),
	infos 			TEXT
	
	/*
		TODO : Lier parcours à etudiant
	*/
	
)ENGINE=INNODB;

CREATE TABLE compte
(
	id					INT AUTO_INCREMENT,
	nom					VARCHAR(40),
	mdp					VARCHAR(40),
	mail				VARCHAR(50),
	dateCreation		DATETIME,
	dateDerniereVisite	DATETIME,
	
	PRIMARY KEY (id)
	
)ENGINE=INNODB;

CREATE TABLE categorie
(
	id	INT,
	nom	VARCHAR(40)
	
	PRIMARY KEY (f_compte_id)
)