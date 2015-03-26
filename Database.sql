/*
SQLyog Community v12.09 (64 bit)
MySQL - 5.0.51b-community-nt-log : Database - dbo
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
/*Table structure for table `account` */

DROP TABLE IF EXISTS `account`;

CREATE TABLE `account` (
  `ID` int(11) NOT NULL auto_increment,
  `userName` varchar(20) NOT NULL,
  `passWord` varchar(20) NOT NULL,
  `AcLevel` int(11) NOT NULL default '0',
  `AllowedRace` int(11) NOT NULL default '255',
  `LastServerID` int(11) NOT NULL default '255',
  `State` int(11) NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

/*Table structure for table `character` */

DROP TABLE IF EXISTS `character`;

CREATE TABLE `character` (
  `ID` int(11) NOT NULL auto_increment,
  `AccID` int(11) NOT NULL,
  `ServerID` int(11) NOT NULL,
  `Name` varchar(20) NOT NULL,
  `Race` int(11) NOT NULL,
  `Class` int(11) NOT NULL,
  `Gender` int(11) NOT NULL,
  `Face` int(11) NOT NULL,
  `Hair` int(11) NOT NULL,
  `HairColor` int(11) NOT NULL,
  `SkinColor` int(11) NOT NULL,
  `Level` int(11) NOT NULL default '1',
  `Exp` bigint(20) NOT NULL default '0',
  `MapInfoId` bigint(20) NOT NULL,
  `worldTblidx` int(11) NOT NULL,
  `worldId` int(11) NOT NULL,
  `PositionX` float(11,6) NOT NULL default '0.000000',
  `PositionY` float(11,6) NOT NULL default '0.000000',
  `PositionZ` float(11,6) NOT NULL default '0.000000',
  `DirectionX` float(11,6) NOT NULL default '0.000000',
  `DirectionY` float(11,6) NOT NULL default '0.000000',
  `DirectionZ` float(11,6) NOT NULL default '0.000000',
  `Money` bigint(20) NOT NULL,
  `MoneyBank` bigint(20) NOT NULL,
  `Marking` int(11) NOT NULL,
  `Adult` tinyint(1) NOT NULL default '0',
  `TutorialFlag` tinyint(1) NOT NULL,
  `NeedNameChange` tinyint(1) NOT NULL default '0',
  `ToDelete` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8;

/*Table structure for table `inventory` */

DROP TABLE IF EXISTS `inventory`;

CREATE TABLE `inventory` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `ItemID` int(11) NOT NULL,
  `CharID` int(11) NOT NULL,
  `Place` tinyint(4) NOT NULL default '0',
  `Slot` tinyint(4) NOT NULL default '0',
  `Stack` tinyint(4) NOT NULL default '0',
  `Rank` tinyint(4) NOT NULL default '1',
  `CurDur` tinyint(4) NOT NULL default '10',
  `NeedToIdentify` tinyint(4) NOT NULL default '0',
  `Grade` tinyint(4) NOT NULL default '0',
  `BattleAttribute` tinyint(4) NOT NULL default '0',
  `RestrictType` tinyint(4) NOT NULL default '0',
  `Maker` varchar(20) default '""',
  `Opt1` int(11) NOT NULL default '0',
  `Opt2` int(11) NOT NULL default '0',
  `DurationType` tinyint(4) NOT NULL default '0',
  `UseStartTime` timestamp NULL default CURRENT_TIMESTAMP,
  `UseEndTime` timestamp NULL default NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=192 DEFAULT CHARSET=utf8;

/*Table structure for table `quickslot` */

DROP TABLE IF EXISTS `quickslot`;

CREATE TABLE `quickslot` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `CharID` int(10) unsigned NOT NULL,
  `TblID` int(10) unsigned NOT NULL,
  `Slot` tinyint(3) unsigned NOT NULL default '0',
  `Type` tinyint(3) unsigned NOT NULL default '0',
  `Item` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=26 DEFAULT CHARSET=utf8;

/*Table structure for table `skills` */

DROP TABLE IF EXISTS `skills`;

CREATE TABLE `skills` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `CharID` int(10) unsigned NOT NULL,
  `SkillID` int(10) unsigned NOT NULL,
  `Slot` tinyint(3) unsigned NOT NULL default '0',
  `RpBonusType` tinyint(3) unsigned NOT NULL default '0',
  `IsRpBonusAuto` tinyint(3) unsigned NOT NULL default '0',
  `RemainSec` int(10) unsigned NOT NULL default '0',
  `Exp` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

/* Procedure structure for procedure `spUpdateDirection` */

/*!50003 DROP PROCEDURE IF EXISTS  `spUpdateDirection` */;

DELIMITER $$

/*!50003 CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdateDirection`(IN CharID INT, IN DirX FLOAT(11,6), IN DirY FLOAT(11,6), IN DirZ FLOAT(11,6))
BEGIN
	UPDATE `character` SET `DirectionX` = DirX, `DirectionY` = DirY, `DirectionZ` = DirZ WHERE `ID` = CharID;
    END */$$
DELIMITER ;

/* Procedure structure for procedure `spUpdatePosition` */

/*!50003 DROP PROCEDURE IF EXISTS  `spUpdatePosition` */;

DELIMITER $$

/*!50003 CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdatePosition`(in CharID INT, IN PosX float(11,6), in PosY float(11,6), in PosZ float(11,6))
BEGIN
	update `character` set `PositionX` = PosX, `PositionY` = PosY,`PositionZ` = PosZ where `ID` = CharID;
    END */$$
DELIMITER ;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
