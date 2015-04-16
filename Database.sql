-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema dbo
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `dbo` ;

-- -----------------------------------------------------
-- Schema dbo
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `dbo` DEFAULT CHARACTER SET utf8 ;
USE `dbo` ;

-- -----------------------------------------------------
-- Table `dbo`.`account`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`account` ;

CREATE TABLE IF NOT EXISTS `dbo`.`account` (
  `ID` INT(11) UNSIGNED NULL AUTO_INCREMENT,
  `userName` VARCHAR(20) NOT NULL,
  `passWord` VARCHAR(20) NOT NULL,
  `AcLevel` INT(11) NOT NULL DEFAULT '0',
  `AllowedRace` INT(11) NOT NULL DEFAULT '255',
  `LastServerID` INT(11) NOT NULL DEFAULT '255',
  `State` INT(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`character`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`character` ;

CREATE TABLE IF NOT EXISTS `dbo`.`character` (
  `ID` INT(11) UNSIGNED NULL AUTO_INCREMENT,
  `AccID` INT(11) UNSIGNED NOT NULL DEFAULT '0',
  `ServerID` INT(11) NOT NULL DEFAULT '0',
  `Name` VARCHAR(20) NOT NULL,
  `Race` INT(11) NOT NULL DEFAULT '0',
  `Class` INT(11) NOT NULL DEFAULT '0',
  `Gender` INT(11) NOT NULL DEFAULT '0',
  `Face` INT(11) NOT NULL DEFAULT '0',
  `Hair` INT(11) NOT NULL DEFAULT '0',
  `HairColor` INT(11) NOT NULL DEFAULT '0',
  `SkinColor` INT(11) NOT NULL DEFAULT '0',
  `Level` INT(11) NOT NULL DEFAULT '1',
  `CurExp` BIGINT(20) NOT NULL DEFAULT '0',
  `MapInfoId` BIGINT(20) NOT NULL DEFAULT '0',
  `worldTblidx` BIGINT(11) NOT NULL DEFAULT '0',
  `worldId` BIGINT(11) NOT NULL DEFAULT '0',
  `BindType` INT(11) NOT NULL DEFAULT '0',
  `bindWorldId` BIGINT(20) NOT NULL DEFAULT '0',
  `bindObjectTblid` BIGINT(20) NOT NULL DEFAULT '0',
  `PositionX` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `PositionY` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `PositionZ` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionX` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionY` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionZ` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `Money` BIGINT(20) NOT NULL DEFAULT '0',
  `MoneyBank` BIGINT(20) NOT NULL DEFAULT '0',
  `Marking` INT(11) NOT NULL DEFAULT '0',
  `Adult` TINYINT(1) NOT NULL DEFAULT '0',
  `TutorialFlag` TINYINT(1) NOT NULL DEFAULT '0',
  `NeedNameChange` TINYINT(1) NOT NULL DEFAULT '0',
  `ToDelete` TINYINT(1) NOT NULL DEFAULT '0',
  `ChangeClass` TINYINT(1) NOT NULL DEFAULT '0',
  `IsGameMaster` TINYINT(4) NOT NULL DEFAULT '0',
  `TutorialHint` BIGINT(20) NOT NULL DEFAULT '0',
  `Reputation` INT(11) NOT NULL DEFAULT '0',
  `MudosaPoint` INT(11) NOT NULL DEFAULT '0',
  `SpPoint` INT(11) NOT NULL DEFAULT '0',
  `CurEP` INT(11) NOT NULL DEFAULT '0',
  `MaxEP` INT(11) NOT NULL DEFAULT '0',
  `CurLP` INT(11) NOT NULL DEFAULT '0',
  `MaxLP` INT(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`, `AccID`),
  INDEX `fk_character_account_idx` (`AccID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_character_account_id`
    FOREIGN KEY (`AccID`)
    REFERENCES `dbo`.`account` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`inventory`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`inventory` ;

CREATE TABLE IF NOT EXISTS `dbo`.`inventory` (
  `ID` INT(10) UNSIGNED NULL AUTO_INCREMENT,
  `CharID` INT(11) UNSIGNED NOT NULL,
  `ItemID` INT(11) UNSIGNED NOT NULL,
  `Place` TINYINT(4) NOT NULL DEFAULT '0',
  `Slot` TINYINT(4) NOT NULL DEFAULT '0',
  `Stack` TINYINT(4) NOT NULL DEFAULT '0',
  `Rank` TINYINT(4) NOT NULL DEFAULT '1',
  `CurDur` TINYINT(4) NOT NULL DEFAULT '100',
  `NeedToIdentify` TINYINT(4) NOT NULL DEFAULT '0',
  `Grade` TINYINT(4) NOT NULL DEFAULT '0',
  `BattleAttribute` TINYINT(4) NOT NULL DEFAULT '0',
  `RestrictType` TINYINT(4) NOT NULL DEFAULT '0',
  `Maker` VARCHAR(20) NULL DEFAULT '""',
  `Opt1` INT(11) NOT NULL DEFAULT '0',
  `Opt2` INT(11) NOT NULL DEFAULT '0',
  `DurationType` TINYINT(4) NOT NULL DEFAULT '0',
  `UseStartTime` TIMESTAMP NULL DEFAULT CURRENT_TIMESTAMP,
  `UseEndTime` TIMESTAMP NULL DEFAULT NULL,
  PRIMARY KEY (`ID`, `CharID`),
  INDEX `fk_inventory_character_idx` (`CharID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_inventory_character_id`
    FOREIGN KEY (`CharID`)
    REFERENCES `dbo`.`character` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`quickslot`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`quickslot` ;

CREATE TABLE IF NOT EXISTS `dbo`.`quickslot` (
  `ID` INT(10) UNSIGNED NULL AUTO_INCREMENT,
  `CharID` INT(10) UNSIGNED NOT NULL,
  `TblID` INT(10) UNSIGNED NOT NULL,
  `Slot` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `Type` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `Item` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`, `CharID`),
  INDEX `fk_quickslot_character_id_idx` (`CharID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_quickslot_character_id`
    FOREIGN KEY (`CharID`)
    REFERENCES `dbo`.`character` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`skills`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`skills` ;

CREATE TABLE IF NOT EXISTS `dbo`.`skills` (
  `ID` INT(10) UNSIGNED NULL AUTO_INCREMENT,
  `CharID` INT(10) UNSIGNED NOT NULL,
  `SkillID` INT(10) UNSIGNED NOT NULL,
  `Slot` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `RpBonusType` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `IsRpBonusAuto` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0',
  `RemainSec` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `Exp` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`, `CharID`),
  INDEX `fk_character_id_idx` (`CharID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_character_id`
    FOREIGN KEY (`CharID`)
    REFERENCES `dbo`.`character` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`online`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`online` ;

CREATE TABLE IF NOT EXISTS `dbo`.`online` (
  `AccountID` INT(11) UNSIGNED NOT NULL,
  `CharID` INT(11) UNSIGNED NOT NULL,
  `ServerID` INT NULL,
  `ChannelID` INT NULL,
  `Handle` BIGINT NULL,
  PRIMARY KEY (`AccountID`, `CharID`),
  INDEX `fk_online_character_idx` (`CharID` ASC),
  INDEX `fk_online_account_idx` (`AccountID` ASC),
  CONSTRAINT `fk_online_account_id`
    FOREIGN KEY (`AccountID`)
    REFERENCES `dbo`.`account` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_online_character_id`
    FOREIGN KEY (`CharID`)
    REFERENCES `dbo`.`character` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

USE `dbo` ;

-- -----------------------------------------------------
-- procedure spClearOnline
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spClearOnline`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spClearOnline`(IN SrvID INT)
BEGIN
	DELETE FROM `online` WHERE `ServerID` = SrvID;
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spDeleteOnline
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spDeleteOnline`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spDeleteOnline`(in AccId int, in CharId int)
BEGIN
	DELETE FROM `online` WHERE `AccountID` = AccId AND `CharID` = CharId;
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spInsertCharacter
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spInsertCharacter`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spInsertCharacter`( 
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
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spInsertItem
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spInsertItem`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spInsertItem`(
	IN nItemID INT,
	IN nCharID INT,
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
	IN nOpt1 INT,
	IN nOpt2 INT,
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
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spInsertOnline
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spInsertOnline`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spInsertOnline`(
		in AccId int,
		in CharId int,
		in SrvId int,
		in ChanId int,
		in Handle int)
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
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spUpdateDirection
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spUpdateDirection`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdateDirection`(IN CharID INT, IN DirX FLOAT(11,6), IN DirY FLOAT(11,6), IN DirZ FLOAT(11,6))
BEGIN
	UPDATE `character` SET `DirectionX` = DirX, `DirectionY` = DirY, `DirectionZ` = DirZ WHERE `ID` = CharID;
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spUpdatePosition
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spUpdatePosition`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdatePosition`(in CharID INT, IN PosX float(11,6), in PosY float(11,6), in PosZ float(11,6))
BEGIN
	update `character` set `PositionX` = PosX, `PositionY` = PosY,`PositionZ` = PosZ where `ID` = CharID;
    END$$

DELIMITER ;
SET SQL_MODE = '';
GRANT USAGE ON *.* TO dboserver;
 DROP USER dboserver;
SET SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';
CREATE USER 'dboserver' IDENTIFIED BY 'dboserver';

GRANT ALL ON `dbo`.* TO 'dboserver';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
