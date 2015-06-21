/*
Navicat MySQL Data Transfer

Source Server         : Dragonball dbase
Source Server Version : 50534
Source Host           : localhost:3306
Source Database       : dbosnaity

Target Server Type    : MYSQL
Target Server Version : 50534
File Encoding         : 65001

Date: 2015-06-20 21:53:12
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `account`
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `userName` varchar(20) NOT NULL,
  `passWord` varchar(20) NOT NULL,
  `AcLevel` int(11) NOT NULL DEFAULT '0',
  `AllowedRace` int(11) NOT NULL DEFAULT '255',
  `LastServerID` int(11) NOT NULL DEFAULT '255',
  `State` int(11) NOT NULL DEFAULT '0',
  `isGameMaster` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of account
-- ----------------------------
INSERT INTO `account` VALUES ('1', 'luizoe', 'luizoe', '0', '255', '0', '3', '1');
INSERT INTO `account` VALUES ('2', '1', '1', '0', '255', '0', '3', '0');

-- ----------------------------
-- Table structure for `blacklist`
-- ----------------------------
DROP TABLE IF EXISTS `blacklist`;
CREATE TABLE `blacklist` (
  `pkID` int(11) NOT NULL AUTO_INCREMENT,
  `owner_id` int(10) NOT NULL,
  `target_id` int(10) NOT NULL,
  PRIMARY KEY (`pkID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of blacklist
-- ----------------------------

-- ----------------------------
-- Table structure for `character`
-- ----------------------------
DROP TABLE IF EXISTS `character`;
CREATE TABLE `character` (
  `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `AccID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `GuildID` bigint(20) NOT NULL DEFAULT '0',
  `ServerID` int(11) NOT NULL DEFAULT '0',
  `Name` varchar(20) NOT NULL,
  `Race` int(11) NOT NULL DEFAULT '0',
  `Class` int(11) NOT NULL DEFAULT '0',
  `Gender` int(11) NOT NULL DEFAULT '0',
  `Face` int(11) NOT NULL DEFAULT '0',
  `Hair` int(11) NOT NULL DEFAULT '0',
  `HairColor` int(11) NOT NULL DEFAULT '0',
  `SkinColor` int(11) NOT NULL DEFAULT '0',
  `Level` int(11) NOT NULL DEFAULT '1',
  `CurExp` bigint(20) NOT NULL DEFAULT '0',
  `MapInfoId` bigint(20) NOT NULL DEFAULT '0',
  `worldTblidx` bigint(20) NOT NULL DEFAULT '0',
  `worldId` bigint(20) NOT NULL DEFAULT '0',
  `BindType` int(11) NOT NULL DEFAULT '0',
  `bindWorldId` bigint(20) NOT NULL DEFAULT '0',
  `bindObjectTblid` bigint(20) NOT NULL DEFAULT '0',
  `PositionX` float(11,6) NOT NULL DEFAULT '0.000000',
  `PositionY` float(11,6) NOT NULL DEFAULT '0.000000',
  `PositionZ` float(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionX` float(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionY` float(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionZ` float(11,6) NOT NULL DEFAULT '0.000000',
  `Money` bigint(20) NOT NULL DEFAULT '0',
  `MoneyBank` bigint(20) NOT NULL DEFAULT '0',
  `Marking` int(11) NOT NULL DEFAULT '255',
  `Adult` tinyint(1) NOT NULL DEFAULT '0',
  `TutorialFlag` tinyint(1) NOT NULL DEFAULT '0',
  `NeedNameChange` tinyint(1) NOT NULL DEFAULT '0',
  `ToDelete` tinyint(1) NOT NULL DEFAULT '0',
  `ChangeClass` tinyint(1) NOT NULL DEFAULT '0',
  `IsGameMaster` tinyint(1) NOT NULL DEFAULT '0',
  `TutorialHint` bigint(20) NOT NULL DEFAULT '0',
  `Reputation` bigint(20) NOT NULL DEFAULT '0',
  `MudosaPoint` bigint(20) NOT NULL DEFAULT '0',
  `SpPoint` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`AccID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`),
  KEY `fk_character_account_idx` (`AccID`),
  CONSTRAINT `fk_character_account_id` FOREIGN KEY (`AccID`) REFERENCES `account` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of character
-- ----------------------------
INSERT INTO `character` VALUES ('1', '1', '0', '0', 'teste', '0', '0', '0', '1', '1', '1', '1', '77', '31930', '200101000', '1', '1', '0', '0', '0', '2048.000000', '57.480820', '2048.000000', '-0.636172', '0.000000', '-0.771501', '10000', '100000', '255', '0', '1', '0', '0', '0', '1', '290459648', '0', '0', '0');
INSERT INTO `character` VALUES ('2', '1', '0', '0', 'tadf', '0', '0', '0', '1', '1', '1', '1', '9', '90', '200101000', '1', '1', '0', '0', '0', '4633.508301', '-68.229599', '4326.203125', '-0.995366', '0.000000', '0.095816', '10000', '100000', '255', '0', '1', '0', '0', '0', '1', '22020096', '0', '0', '0');
INSERT INTO `character` VALUES ('3', '2', '0', '0', 'fff', '0', '0', '0', '1', '1', '1', '1', '1', '0', '200101000', '1', '1', '0', '0', '0', '4693.416016', '-53.131866', '4477.039062', '-0.920355', '0.000000', '0.391284', '10000', '100000', '255', '0', '1', '0', '0', '0', '0', '4194304', '0', '0', '0');
INSERT INTO `character` VALUES ('4', '2', '0', '0', 'test', '1', '3', '2', '1', '1', '1', '1', '3', '270', '200105000', '1', '1', '0', '0', '0', '2927.796387', '21.408035', '-2507.627441', '0.453687', '0.000000', '0.891203', '10000', '100000', '255', '0', '1', '0', '0', '0', '0', '22020096', '0', '0', '0');

-- ----------------------------
-- Table structure for `friendlist`
-- ----------------------------
DROP TABLE IF EXISTS `friendlist`;
CREATE TABLE `friendlist` (
  `pkID` int(11) NOT NULL AUTO_INCREMENT,
  `owner_id` int(10) NOT NULL,
  `friend_id` int(10) NOT NULL,
  `toBlackList` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`pkID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of friendlist
-- ----------------------------

-- ----------------------------
-- Table structure for `inventory`
-- ----------------------------
DROP TABLE IF EXISTS `inventory`;
CREATE TABLE `inventory` (
  `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `CharID` bigint(20) unsigned NOT NULL,
  `ItemID` bigint(20) unsigned NOT NULL,
  `Place` int(11) NOT NULL DEFAULT '0',
  `Slot` int(11) NOT NULL DEFAULT '0',
  `Stack` int(11) NOT NULL DEFAULT '0',
  `Rank` int(11) NOT NULL DEFAULT '1',
  `CurDur` int(11) NOT NULL DEFAULT '100',
  `NeedToIdentify` tinyint(1) NOT NULL DEFAULT '0',
  `Grade` int(11) NOT NULL DEFAULT '0',
  `BattleAttribute` int(11) NOT NULL DEFAULT '0',
  `RestrictType` int(11) NOT NULL DEFAULT '0',
  `Maker` varchar(20) DEFAULT '""',
  `Opt1` bigint(20) NOT NULL DEFAULT '0',
  `Opt2` bigint(20) NOT NULL DEFAULT '0',
  `DurationType` int(11) NOT NULL DEFAULT '0',
  `UseStartTime` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `UseEndTime` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`ID`,`CharID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`),
  KEY `fk_inventory_character_idx` (`CharID`),
  CONSTRAINT `fk_inventory_character_id` FOREIGN KEY (`CharID`) REFERENCES `character` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inventory
-- ----------------------------
INSERT INTO `inventory` VALUES ('1', '1', '19901', '0', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:03:40', null);
INSERT INTO `inventory` VALUES ('2', '1', '19991', '9', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:03:40', null);
INSERT INTO `inventory` VALUES ('3', '1', '10045', '7', '0', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:03:40', null);
INSERT INTO `inventory` VALUES ('4', '1', '14001', '7', '2', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:03:40', null);
INSERT INTO `inventory` VALUES ('5', '1', '14002', '7', '3', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:03:40', null);
INSERT INTO `inventory` VALUES ('6', '1', '14003', '7', '4', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:03:41', null);
INSERT INTO `inventory` VALUES ('7', '1', '17001', '7', '5', '1', '1', '50', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:03:41', null);
INSERT INTO `inventory` VALUES ('8', '2', '19901', '0', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:05:55', null);
INSERT INTO `inventory` VALUES ('9', '2', '19991', '9', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:05:55', null);
INSERT INTO `inventory` VALUES ('10', '2', '10045', '7', '0', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:05:55', null);
INSERT INTO `inventory` VALUES ('11', '2', '14001', '7', '2', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:05:55', null);
INSERT INTO `inventory` VALUES ('12', '2', '14002', '7', '3', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:05:55', null);
INSERT INTO `inventory` VALUES ('13', '2', '14003', '7', '4', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:05:55', null);
INSERT INTO `inventory` VALUES ('14', '2', '17001', '7', '5', '1', '1', '50', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:05:55', null);
INSERT INTO `inventory` VALUES ('15', '3', '19901', '0', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:27:38', null);
INSERT INTO `inventory` VALUES ('16', '3', '19991', '9', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:27:38', null);
INSERT INTO `inventory` VALUES ('17', '3', '10045', '7', '0', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:27:38', null);
INSERT INTO `inventory` VALUES ('18', '3', '14001', '7', '2', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:27:38', null);
INSERT INTO `inventory` VALUES ('19', '3', '14002', '7', '3', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:27:38', null);
INSERT INTO `inventory` VALUES ('20', '3', '14003', '7', '4', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:27:38', null);
INSERT INTO `inventory` VALUES ('21', '3', '17001', '7', '5', '1', '1', '50', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-18 00:27:38', null);
INSERT INTO `inventory` VALUES ('22', '4', '19901', '0', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-19 22:30:08', null);
INSERT INTO `inventory` VALUES ('23', '4', '19991', '9', '0', '1', '0', '255', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-19 22:30:08', null);
INSERT INTO `inventory` VALUES ('24', '4', '500045', '7', '0', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-19 22:30:08', null);
INSERT INTO `inventory` VALUES ('25', '4', '13001', '7', '2', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-19 22:30:08', null);
INSERT INTO `inventory` VALUES ('26', '4', '13002', '7', '3', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-19 22:30:08', null);
INSERT INTO `inventory` VALUES ('27', '4', '13003', '7', '4', '1', '1', '100', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-19 22:30:08', null);
INSERT INTO `inventory` VALUES ('28', '4', '17001', '7', '5', '1', '1', '50', '0', '0', '0', '0', '', '4294967295', '0', '0', '2015-06-19 22:30:08', null);

-- ----------------------------
-- Table structure for `online`
-- ----------------------------
DROP TABLE IF EXISTS `online`;
CREATE TABLE `online` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `CharID` bigint(20) unsigned NOT NULL,
  `ServerID` int(11) DEFAULT NULL,
  `ChannelID` int(11) DEFAULT NULL,
  `Handle` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`AccountID`,`CharID`),
  KEY `fk_online_character_idx` (`CharID`),
  KEY `fk_online_account_idx` (`AccountID`),
  CONSTRAINT `fk_online_account_id` FOREIGN KEY (`AccountID`) REFERENCES `account` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_online_character_id` FOREIGN KEY (`CharID`) REFERENCES `character` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of online
-- ----------------------------
INSERT INTO `online` VALUES ('1', '2', '0', '0', '29674');

-- ----------------------------
-- Table structure for `quickslot`
-- ----------------------------
DROP TABLE IF EXISTS `quickslot`;
CREATE TABLE `quickslot` (
  `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `CharID` bigint(20) unsigned NOT NULL,
  `TblID` bigint(20) unsigned NOT NULL,
  `Slot` int(10) unsigned NOT NULL DEFAULT '0',
  `Type` int(10) unsigned NOT NULL DEFAULT '0',
  `Item` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`CharID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`),
  KEY `fk_quickslot_character_id_idx` (`CharID`),
  CONSTRAINT `fk_quickslot_character_id` FOREIGN KEY (`CharID`) REFERENCES `character` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of quickslot
-- ----------------------------
INSERT INTO `quickslot` VALUES ('1', '1', '103', '1', '3', '0');
INSERT INTO `quickslot` VALUES ('2', '1', '104', '2', '3', '0');
INSERT INTO `quickslot` VALUES ('3', '1', '10111', '0', '1', '0');
INSERT INTO `quickslot` VALUES ('4', '1', '105', '3', '3', '0');
INSERT INTO `quickslot` VALUES ('5', '1', '106', '11', '3', '0');
INSERT INTO `quickslot` VALUES ('6', '2', '103', '1', '3', '0');
INSERT INTO `quickslot` VALUES ('7', '2', '104', '2', '3', '0');
INSERT INTO `quickslot` VALUES ('8', '2', '10111', '0', '1', '0');
INSERT INTO `quickslot` VALUES ('9', '2', '105', '3', '3', '0');
INSERT INTO `quickslot` VALUES ('10', '2', '106', '11', '3', '0');
INSERT INTO `quickslot` VALUES ('11', '3', '103', '1', '3', '0');
INSERT INTO `quickslot` VALUES ('12', '3', '104', '2', '3', '0');
INSERT INTO `quickslot` VALUES ('13', '3', '10111', '0', '1', '0');
INSERT INTO `quickslot` VALUES ('14', '3', '105', '3', '3', '0');
INSERT INTO `quickslot` VALUES ('15', '3', '106', '11', '3', '0');
INSERT INTO `quickslot` VALUES ('16', '4', '103', '1', '3', '0');
INSERT INTO `quickslot` VALUES ('17', '4', '104', '2', '3', '0');
INSERT INTO `quickslot` VALUES ('18', '4', '310111', '0', '1', '0');
INSERT INTO `quickslot` VALUES ('19', '4', '105', '3', '3', '0');
INSERT INTO `quickslot` VALUES ('20', '4', '106', '11', '3', '0');

-- ----------------------------
-- Table structure for `skills`
-- ----------------------------
DROP TABLE IF EXISTS `skills`;
CREATE TABLE `skills` (
  `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `CharID` bigint(20) unsigned NOT NULL,
  `SkillID` bigint(20) unsigned NOT NULL,
  `Slot` int(10) unsigned NOT NULL DEFAULT '0',
  `RpBonusType` int(10) unsigned NOT NULL DEFAULT '0',
  `IsRpBonusAuto` int(10) unsigned NOT NULL DEFAULT '0',
  `RemainSec` int(10) unsigned NOT NULL DEFAULT '0',
  `Exp` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`CharID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`),
  KEY `fk_character_id_idx` (`CharID`),
  CONSTRAINT `fk_character_id` FOREIGN KEY (`CharID`) REFERENCES `character` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of skills
-- ----------------------------
INSERT INTO `skills` VALUES ('1', '1', '10111', '1', '0', '0', '0', '0');
INSERT INTO `skills` VALUES ('2', '2', '10111', '1', '0', '0', '0', '0');
INSERT INTO `skills` VALUES ('3', '3', '10111', '1', '0', '0', '0', '0');
INSERT INTO `skills` VALUES ('4', '4', '310111', '1', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `warfog`
-- ----------------------------
DROP TABLE IF EXISTS `warfog`;
CREATE TABLE `warfog` (
  `ID` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `CharID` bigint(20) unsigned NOT NULL,
  `Object` bigint(20) NOT NULL,
  PRIMARY KEY (`ID`,`CharID`),
  UNIQUE KEY `ID_UNIQUE` (`ID`),
  KEY `pkey_warfog_charid` (`CharID`),
  CONSTRAINT `fk_warfog_charid` FOREIGN KEY (`CharID`) REFERENCES `character` (`ID`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of warfog
-- ----------------------------
INSERT INTO `warfog` VALUES ('1', '1', '100007');

-- ----------------------------
-- Procedure structure for `spClearOnline`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spClearOnline`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spClearOnline`(IN SrvID INT)
BEGIN
	DELETE FROM `online` WHERE `ServerID` = SrvID;
    END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `spDeleteOnline`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spDeleteOnline`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spDeleteOnline`(in AccId int, in CharId int)
BEGIN
	DELETE FROM `online` WHERE `AccountID` = AccId AND `CharID` = CharId;
    END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `spInsertCharacter`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spInsertCharacter`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spInsertCharacter`( 
	in nAccID bigint, 
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
	in nCurExp bigint, 
	in nMapInfoId bigint, 
	in nworldTblidx bigint, 
	in nworldId bigint, 
	in nBindType int, 
	in nbindWorldId bigint, 
	in nbindObjectTblid bigint, 
	in fPositionX float(11,6), 
	in fPositionY float(11,6), 
	in fPositionZ float(11,6), 
	in fDirectionX float(11,6), 
	in fDirectionY float(11,6), 
	in fDirectionZ float(11,6), 
	in nMoney bigint, 
	in nMoneyBank bigint, 
	in nMarking int, 
	in nAdult int, 
	in nTutorialFlag int, 
	in nNeedNameChange int, 
	in nToDelete int, 
	in nChangeClass int, 
	in nIsGameMaster int, 
	in nTutorialHint bigint, 
	in nReputation bigint, 
	in nMudosaPoint bigint, 
	in nSpPoint int)
BEGIN
	INSERT INTO `character` 
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
	`SpPoint`
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
	nSpPoint
	);
    END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `spInsertItem`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spInsertItem`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spInsertItem`(
	IN nItemID BIGINT,
	IN nCharID BIGINT,
	IN nPlace INT,
	IN nSlot INT,
	IN nStack INT,
	IN nRank INT,
	IN nCurDur INT,
	IN nNeedToIdentify INT,
	IN nGrade INT,
	IN nBattleAttribute INT,
	IN nRestrictType INT,
	IN nMaker VARCHAR(20),
	IN nOpt1 BIGINT,
	IN nOpt2 BIGINT,
	IN nDurationType INT)
BEGIN
	INSERT INTO `inventory` 
	(`ItemID`, 
	`CharID`, 
	`Place`, 
	`Slot`, 
	`Stack`, 
	`Rank`, 
	`CurDur`, 
	`NeedToIdentify`, 
	`Grade`, 
	`BattleAttribute`, 
	`RestrictType`, 
	`Maker`, 
	`Opt1`, 
	`Opt2`, 
	`DurationType`)
	VALUES
	(nItemID,
	nCharID,
	nPlace,
	nSlot,
	nStack,
	nRank,
	nCurDur,
	nNeedToIdentify,
	nGrade,
	nBattleAttribute,
	nRestrictType,
	nMaker,
	nOpt1,
	nOpt2,
	nDurationType);
	SELECT LAST_INSERT_ID() AS `LastID` LIMIT 1;
    END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `spInsertOnline`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spInsertOnline`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spInsertOnline`(
		in AccId bigint,
		in CharId bigint,
		in SrvId int,
		in ChanId bigint,
		in Handle bigint)
BEGIN
	INSERT INTO `online` 
	(`AccountID`, 
	`CharID`, 
	`ServerID`, 
	`ChannelID`, 
	`Handle`
	)
	VALUES
	(AccId, 
	 CharId, 
	 SrvId, 
	 ChanId, 
	 Handle
	);
    END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `spQueryInsertItem`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spQueryInsertItem`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spQueryInsertItem`(
	IN nItemID BIGINT,
	IN nCharID BIGINT,
	IN nPlace INT,
	IN nSlot INT,
	IN nStack INT,
	IN nRank INT,
	IN nCurDur INT,
	IN nNeedToIdentify INT,
	IN nGrade INT,
	IN nBattleAttribute INT,
	IN nRestrictType INT,
	IN nMaker VARCHAR(20),
	IN nOpt1 BIGINT,
	IN nOpt2 BIGINT,
	IN nDurationType INT)
BEGIN
	INSERT INTO `inventory` 
	(`ItemID`, 
	`CharID`, 
	`Place`, 
	`Slot`, 
	`Stack`, 
	`Rank`, 
	`CurDur`, 
	`NeedToIdentify`, 
	`Grade`, 
	`BattleAttribute`, 
	`RestrictType`, 
	`Maker`, 
	`Opt1`, 
	`Opt2`, 
	`DurationType`)
	VALUES
	(nItemID,
	nCharID,
	nPlace,
	nSlot,
	nStack,
	nRank,
	nCurDur,
	nNeedToIdentify,
	nGrade,
	nBattleAttribute,
	nRestrictType,
	nMaker,
	nOpt1,
	nOpt2,
	nDurationType);
    END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `spUpdateDirection`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spUpdateDirection`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdateDirection`(IN CharID BIGINT, IN DirX FLOAT(11,6), IN DirY FLOAT(11,6), IN DirZ FLOAT(11,6))
BEGIN
	UPDATE `character` SET `DirectionX` = DirX, `DirectionY` = DirY, `DirectionZ` = DirZ WHERE `ID` = CharID;
    END
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `spUpdatePosition`
-- ----------------------------
DROP PROCEDURE IF EXISTS `spUpdatePosition`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdatePosition`(in CharID BIGINT, IN PosX float(11,6), in PosY float(11,6), in PosZ float(11,6))
BEGIN
	update `character` set `PositionX` = PosX, `PositionY` = PosY,`PositionZ` = PosZ where `ID` = CharID;
    END
;;
DELIMITER ;
