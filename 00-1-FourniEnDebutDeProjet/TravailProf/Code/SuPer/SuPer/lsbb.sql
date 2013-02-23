-- phpMyAdmin SQL Dump
-- version 3.5.0
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le: Jeu 19 Avril 2012 à 11:42
-- Version du serveur: 5.5.16-log
-- Version de PHP: 5.3.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `lsbb`
--

-- --------------------------------------------------------

--
-- Structure de la table `badges`
--

CREATE TABLE IF NOT EXISTS `badges` (
  `noEnr` int(11) NOT NULL AUTO_INCREMENT,
  `ref` varchar(50) NOT NULL,
  `datemes` date NOT NULL,
  `noBadge` varchar(50) NOT NULL,
  `carac` text NOT NULL,
  `enCours` int(11) NOT NULL,
  PRIMARY KEY (`noEnr`),
  UNIQUE KEY `noBadge` (`noBadge`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `ident`
--

CREATE TABLE IF NOT EXISTS `ident` (
  `noEnr` int(11) NOT NULL AUTO_INCREMENT,
  `ident` varchar(50) NOT NULL,
  `mdp` varchar(50) NOT NULL,
  `nom` varchar(50) NOT NULL,
  `pnom` varchar(50) NOT NULL,
  `comment` text NOT NULL,
  PRIMARY KEY (`noEnr`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `ident`
--

INSERT INTO `ident` (`noEnr`, `ident`, `mdp`, `nom`, `pnom`, `comment`) VALUES
(1, 'lsbb', 'lsbb', 'ANTOINE', 'Philippe', 'pantoine1@ac-aix-marseille.fr');

-- --------------------------------------------------------

--
-- Structure de la table `lectcapt`
--

CREATE TABLE IF NOT EXISTS `lectcapt` (
  `noEnr` int(11) NOT NULL AUTO_INCREMENT,
  `noCapteur` int(11) NOT NULL,
  `type` enum('R','V') NOT NULL DEFAULT 'R',
  `adresseIp` varchar(50) NOT NULL,
  `ref` varchar(50) NOT NULL,
  `marque` varchar(50) NOT NULL,
  `comment` varchar(50) NOT NULL,
  `port` int(11) NOT NULL,
  `reseau` enum('C','S') NOT NULL DEFAULT 'C',
  `dateInst` date NOT NULL,
  `situation` text NOT NULL,
  PRIMARY KEY (`noEnr`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `personnes`
--

CREATE TABLE IF NOT EXISTS `personnes` (
  `noEnr` int(11) NOT NULL AUTO_INCREMENT,
  `nom` varchar(50) NOT NULL,
  `pnom` varchar(50) NOT NULL,
  `societe` varchar(50) NOT NULL,
  `dateDeb` date NOT NULL,
  `dateFin` date NOT NULL,
  `noPers` int(11) NOT NULL,
  PRIMARY KEY (`noEnr`),
  UNIQUE KEY `noPers` (`noPers`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `useBadges`
--

CREATE TABLE IF NOT EXISTS `useBadges` (
  `noEnr` int(11) NOT NULL AUTO_INCREMENT,
  `noPers` int(11) NOT NULL,
  `noBadge` int(11) NOT NULL,
  `dateDeb` date NOT NULL,
  `dateFin` date NOT NULL,
  `noIdent` int(11) NOT NULL,
  PRIMARY KEY (`noEnr`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `vieBadges`
--

CREATE TABLE IF NOT EXISTS `vieBadges` (
  `noEnr` int(11) NOT NULL AUTO_INCREMENT,
  `dateOp` date NOT NULL,
  `dateChangePile` date NOT NULL,
  `noIdent` int(11) NOT NULL,
  `noBadge` int(11) NOT NULL,
  `comment` text NOT NULL,
  PRIMARY KEY (`noEnr`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
