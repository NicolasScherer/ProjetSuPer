-- Nom de la bdd : bdd_super
-- Utilisateur de la bdd : user_super
-- Mot de passe de l'utilisateur : mdp_super

CREATE DATABASE IF NOT EXISTS bdd_super CHARACTER SET 'utf8' COLLATE utf8_bin;
        
USE bdd_super;

DROP TABLE IF EXISTS lieu;

CREATE TABLE lieu
(
   num_lieu	INT UNSIGNED 	NOT NULL,
   legende	VARCHAR(100) 	NOT NULL,
   
   PRIMARY KEY (num_lieu, legende)
   
)ENGINE=INNODB;


DROP TABLE IF EXISTS lecteur;

CREATE TABLE lecteur
(
   num_lecteur 	INT UNSIGNED 		NOT NULL,
   num_lieu 	INT UNSIGNED UNIQUE	NOT NULL,
   ip 		VARCHAR (15) UNIQUE	NOT NULL,
   estConnecte 	TINYINT UNSIGNED	NOT NULL,
   constraint estConnecte_is_bool	check(estConnecte BETWEEN 0 and 1),
   
   PRIMARY KEY (num_lecteur)
   
)ENGINE=INNODB;


DROP TABLE IF EXISTS vue;

CREATE TABLE vue
(
   num_vue	INT UNSIGNED	NOT NULL,
   legende	VARCHAR(100)	NOT NULL,
   image	VARCHAR(100)	NOT NULL,
   
   PRIMARY KEY (num_vue)
   
)ENGINE=INNODB;


DROP TABLE IF EXISTS representationLieuSurVue;

CREATE TABLE representationLieuSurVue
(
   num_vue	INT UNSIGNED 	NOT NULL,
   num_lieu	INT UNSIGNED 	NOT NULL,
   x		INT		NOT NULL,
   y		INT		NOT NULL,
   xA		INT		NOT NULL,
   yA		INT		NOT NULL,
   xB		INT		NOT NULL,
   yB		INT		NOT NULL,
   
   PRIMARY KEY (num_vue, num_lieu)
   
)ENGINE=INNODB;

DROP TABLE IF EXISTS personne;

CREATE TABLE personne
(
   nom		VARCHAR(50)	NOT NULL,
   prenom	VARCHAR(50)	NOT NULL,
   societe	VARCHAR(50)	NOT NULL,
   dateDebut	DATE		NOT NULL,
   dateFin	DATE		NOT NULL,
   num_pers	INT UNSIGNED 	NOT NULL,
   photo	VARCHAR(100)	NOT NULL,
   
   PRIMARY KEY (num_pers)
   
)ENGINE=INNODB;

DROP TABLE IF EXISTS badge;

CREATE TABLE badge
(
   num_badge	INT UNSIGNED	NOT NULL,
   num_pers	INT UNSIGNED	NOT NULL,
   dateMiseEnService	DATE	NOT NULL,
   dateChangePile	DATE	NOT NULL,
   estActif	TINYINT UNSIGNED	NOT NULL,
   constraint estActif_is_bool	check(estActif BETWEEN 0 and 1),
   
   PRIMARY KEY (num_badge, num_pers)
   
)ENGINE=INNODB;


-- Interdiction de supprimer une personne auquel un badge est lié
-- Une personne modifiée est aussi modifiée dans badge
alter table badge add constraint fk_badge_num_pers foreign key (num_pers)
      references personne (num_pers) on delete restrict on update cascade;

-- Interdiction de supprimer un lieu auquel un lecteur est lié
-- Un lieu modifié est aussi modifié dans lecteur
alter table lecteur add constraint fk_lecteur_num_lieu foreign key (num_lieu)
      references lieu (num_lieu) on delete restrict on update cascade;

-- La suppression d'une vue supprime toutes les lignes concernant cette vue
alter table representationLieuSurVue add constraint fk_representationLieuSurVue_num_vue foreign key (num_vue)
      references vue (num_vue) on delete cascade on update cascade;

-- La suppression d'un lieu entraine la perte d'un lieu dans une vue qui l'affichait
alter table representationLieuSurVue add constraint fk_representationLieuSurVue_num_lieu foreign key (num_lieu)
      references lieu (num_lieu) on delete cascade on update cascade;


INSERT INTO lieu (num_lieu, legende) VALUE
  (1, "Entree tunnel zone 1"),
  (2, "Angle tunnel zone 2"),
  (3, "Dans tunnel zone 3, en face des dependances");


INSERT INTO lecteur (num_lecteur, num_lieu, ip, estConnecte) VALUE
  (1, 1, '192.168.0.1', 0),
  (2, 2, '192.168.0.2', 0),
  (3, 3, '192.168.0.3', 0);


INSERT INTO vue (num_vue, legende, image) VALUE
  (1, "Vue globale", "../ressources/vue_generale.jpg"),
  (2, "Vue zoomant de l'entree aux dependances", "../ressources/vue_lieu_1-2-3.jpg");


INSERT INTO representationLieuSurVue (num_vue, num_lieu, x, y) VALUE
  (1, 1, 580, 472),
  (1, 2, 540, 442),
  (1, 3, 520, 432),
  (2, 1, 580, 488),
  (2, 2, 220, 128),
  (2, 3, 60, 28);
  
INSERT INTO personne (nom, prenom, societe, dateDebut, dateFin, num_pers) VALUE
  ("scherer", "nicolas", "LAB", 0, 0, 1);

INSERT INTO badge (num_badge, num_pers, dateMiseEnService, dateChangePile, estActif) VALUE
  (01, 1, 0, 0, 0);