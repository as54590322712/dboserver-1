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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

/*Table structure for table `character` */

DROP TABLE IF EXISTS `character`;

CREATE TABLE `character` (
  `ID` int(11) NOT NULL auto_increment,
  `AccID` int(11) NOT NULL default '0',
  `ServerID` int(11) NOT NULL default '0',
  `Name` varchar(20) NOT NULL,
  `Race` int(11) NOT NULL default '0',
  `Class` int(11) NOT NULL default '0',
  `Gender` int(11) NOT NULL default '0',
  `Face` int(11) NOT NULL default '0',
  `Hair` int(11) NOT NULL default '0',
  `HairColor` int(11) NOT NULL default '0',
  `SkinColor` int(11) NOT NULL default '0',
  `Level` int(11) NOT NULL default '1',
  `CurExp` bigint(20) NOT NULL default '0',
  `MapInfoId` bigint(20) NOT NULL default '0',
  `worldTblidx` bigint(11) NOT NULL default '0',
  `worldId` bigint(11) NOT NULL default '0',
  `BindType` int(11) NOT NULL default '0',
  `bindWorldId` bigint(20) NOT NULL default '0',
  `bindObjectTblid` bigint(20) NOT NULL default '0',
  `PositionX` float(11,6) NOT NULL default '0.000000',
  `PositionY` float(11,6) NOT NULL default '0.000000',
  `PositionZ` float(11,6) NOT NULL default '0.000000',
  `DirectionX` float(11,6) NOT NULL default '0.000000',
  `DirectionY` float(11,6) NOT NULL default '0.000000',
  `DirectionZ` float(11,6) NOT NULL default '0.000000',
  `Money` bigint(20) NOT NULL default '0',
  `MoneyBank` bigint(20) NOT NULL default '0',
  `Marking` int(11) NOT NULL default '0',
  `Adult` tinyint(1) NOT NULL default '0',
  `TutorialFlag` tinyint(1) NOT NULL default '0',
  `NeedNameChange` tinyint(1) NOT NULL default '0',
  `ToDelete` tinyint(1) NOT NULL default '0',
  `ChangeClass` tinyint(1) NOT NULL default '0',
  `IsGameMaster` tinyint(4) NOT NULL default '0',
  `TutorialHint` bigint(20) NOT NULL default '0',
  `Reputation` int(11) NOT NULL default '0',
  `MudosaPoint` int(11) NOT NULL default '0',
  `SpPoint` int(11) NOT NULL default '0',
  `CurEP` int(11) NOT NULL default '0',
  `MaxEP` int(11) NOT NULL default '0',
  `CurLP` int(11) NOT NULL default '0',
  `MaxLP` int(11) NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=40 DEFAULT CHARSET=utf8;

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
) ENGINE=InnoDB AUTO_INCREMENT=216 DEFAULT CHARSET=utf8;

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
) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=utf8;

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
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

/* Procedure structure for procedure `spInsertCharacter` */

/*!50003 DROP PROCEDURE IF EXISTS  `spInsertCharacter` */;

DELIMITER $$

/*!50003 CREATE DEFINER=`root`@`localhost` PROCEDURE `spInsertCharacter`( 
	in nAccID int, 
	in nServerID int, 
	in strName varchar(20), 
	in nRace int, 
	in nClass int, 
	in nGender int, 
	in nFace int, 
	in nHair int, 
	in nHairColor int, 
	in nSkinColor int, 
	in nLevel int, 
	in nCurExp int, 
	in nMapInfoId int, 
	in nworldTblidx int, 
	in nworldId int, 
	in nBindType int, 
	in nbindWorldId int, 
	in nbindObjectTblid int, 
	in fPositionX float(11,6), 
	in fPositionY float(11,6), 
	in fPositionZ float(11,6), 
	in fDirectionX float(11,6), 
	in fDirectionY float(11,6), 
	in fDirectionZ float(11,6), 
	in nMoney int, 
	in nMoneyBank int, 
	in nMarking int, 
	in nAdult int, 
	in nTutorialFlag int, 
	in nNeedNameChange int, 
	in nToDelete int, 
	in nChangeClass int, 
	in nIsGameMaster int, 
	in nTutorialHint int, 
	in nReputation int, 
	in nMudosaPoint int, 
	in nSpPoint int, 
	in nCurEP int, 
	in nMaxEP int, 
	in nCurLP int, 
	in nMaxLP int)
BEGIN
	INSERT INTO `dbo`.`character` 
	(`AccID`, 
	`ServerID`, 
	`Name`, 
	`Race`, 
	`Class`, 
	`Gender`, 
	`Face`, 
	`Hair`, 
	`HairColor`, 
	`SkinColor`, 
	`Level`, 
	`CurExp`, 
	`MapInfoId`, 
	`worldTblidx`, 
	`worldId`, 
	`BindType`, 
	`bindWorldId`, 
	`bindObjectTblid`, 
	`PositionX`, 
	`PositionY`, 
	`PositionZ`, 
	`DirectionX`, 
	`DirectionY`, 
	`DirectionZ`, 
	`Money`, 
	`MoneyBank`, 
	`Marking`, 
	`Adult`, 
	`TutorialFlag`, 
	`NeedNameChange`, 
	`ToDelete`, 
	`ChangeClass`, 
	`IsGameMaster`, 
	`TutorialHint`, 
	`Reputation`, 
	`MudosaPoint`, 
	`SpPoint`, 
	`CurEP`, 
	`MaxEP`, 
	`CurLP`, 
	`MaxLP`
	)
	VALUES
	(nAccID, 
	nServerID, 
	strName, 
	nRace, 
	nClass, 
	nGender, 
	nFace, 
	nHair, 
	nHairColor, 
	nSkinColor, 
	nLevel, 
	nCurExp, 
	nMapInfoId, 
	nworldTblidx, 
	nworldId, 
	nBindType, 
	nbindWorldId, 
	nbindObjectTblid, 
	fPositionX, 
	fPositionY, 
	fPositionZ, 
	fDirectionX, 
	fDirectionY, 
	fDirectionZ, 
	nMoney, 
	nMoneyBank, 
	nMarking, 
	nAdult, 
	nTutorialFlag, 
	nNeedNameChange, 
	nToDelete, 
	nChangeClass, 
	nIsGameMaster, 
	nTutorialHint, 
	nReputation, 
	nMudosaPoint, 
	nSpPoint, 
	nCurEP, 
	nMaxEP, 
	nCurLP, 
	nMaxLP
	);
    END */$$
DELIMITER ;

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
