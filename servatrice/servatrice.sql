-- phpMyAdmin SQL Dump
-- version 2.11.8.1deb1ubuntu0.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 11. Oktober 2010 um 23:57
-- Server Version: 5.0.67
-- PHP-Version: 5.2.6-2ubuntu4.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Datenbank: `servatrice`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `decklist_files`
--

CREATE TABLE IF NOT EXISTS `decklist_files` (
  `id` int(7) unsigned zerofill NOT NULL auto_increment,
  `id_folder` int(7) unsigned zerofill NOT NULL,
  `user` varchar(30) NOT NULL,
  `name` varchar(50) NOT NULL,
  `upload_time` datetime NOT NULL,
  `content` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=550 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `decklist_folders`
--

CREATE TABLE IF NOT EXISTS `decklist_folders` (
  `id` int(7) unsigned zerofill NOT NULL auto_increment,
  `id_parent` int(7) unsigned zerofill NOT NULL,
  `user` varchar(30) NOT NULL,
  `name` varchar(30) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `id_parent` (`id_parent`,`name`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=80 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `games`
--

CREATE TABLE IF NOT EXISTS `games` (
  `id` int(7) unsigned zerofill NOT NULL,
  `descr` varchar(50) default NULL,
  `password` tinyint(1) default NULL,
  `time_started` datetime default NULL,
  `time_finished` datetime default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `games_players`
--

CREATE TABLE IF NOT EXISTS `games_players` (
  `id_game` int(7) unsigned zerofill NOT NULL,
  `player` varchar(30) default NULL,
  KEY `id_game` (`id_game`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `news`
--

CREATE TABLE IF NOT EXISTS `news` (
  `id` int(7) unsigned zerofill NOT NULL auto_increment,
  `id_user` int(7) unsigned zerofill NOT NULL,
  `news_date` datetime NOT NULL,
  `subject` varchar(255) NOT NULL,
  `content` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=17 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(7) unsigned zerofill NOT NULL auto_increment,
  `admin` tinyint(1) NOT NULL,
  `name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `country` char(2) NOT NULL,
  `avatar_bmp` blob NOT NULL,
  `registrationDate` datetime NOT NULL,
  `active` tinyint(1) NOT NULL,
  `token` char(32) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=915 ;

CREATE TABLE `cockatrice_uptime` (
  `timest` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `uptime` int(11) DEFAULT NULL,
  `users_count` int(11) DEFAULT NULL,
  `games_count` int(11) DEFAULT NULL,
  PRIMARY KEY (`timest`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
