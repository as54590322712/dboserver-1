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
  `ID` BIGINT UNSIGNED NULL AUTO_INCREMENT,
  `userName` VARCHAR(20) NOT NULL,
  `passWord` VARCHAR(20) NOT NULL,
  `AcLevel` INT(11) NOT NULL DEFAULT '0',
  `AllowedRace` INT(11) NOT NULL DEFAULT '255',
  `LastServerID` INT(11) NOT NULL DEFAULT '255',
  `State` INT(11) NOT NULL DEFAULT '0',
  `isGameMaster` TINYINT(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC))
ENGINE = InnoDB
AUTO_INCREMENT = 9
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`character`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`character` ;

CREATE TABLE IF NOT EXISTS `dbo`.`character` (
  `ID` BIGINT UNSIGNED NULL AUTO_INCREMENT,
  `AccID` BIGINT UNSIGNED NOT NULL DEFAULT '0',
  `GuildID` BIGINT NOT NULL DEFAULT '0',
  `ServerID` INT NOT NULL DEFAULT '0',
  `Name` VARCHAR(20) NOT NULL,
  `Race` INT NOT NULL DEFAULT '0',
  `Class` INT NOT NULL DEFAULT '0',
  `Gender` INT NOT NULL DEFAULT '0',
  `Face` INT NOT NULL DEFAULT '0',
  `Hair` INT NOT NULL DEFAULT '0',
  `HairColor` INT NOT NULL DEFAULT '0',
  `SkinColor` INT NOT NULL DEFAULT '0',
  `Level` INT NOT NULL DEFAULT '1',
  `CurExp` BIGINT NOT NULL DEFAULT '0',
  `MapInfoId` BIGINT NOT NULL DEFAULT '0',
  `worldTblidx` BIGINT NOT NULL DEFAULT '0',
  `worldId` BIGINT NOT NULL DEFAULT '0',
  `BindType` INT NOT NULL DEFAULT '0',
  `bindWorldId` BIGINT NOT NULL DEFAULT '0',
  `bindObjectTblid` BIGINT NOT NULL DEFAULT '0',
  `PositionX` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `PositionY` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `PositionZ` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionX` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionY` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `DirectionZ` FLOAT(11,6) NOT NULL DEFAULT '0.000000',
  `Money` BIGINT NOT NULL DEFAULT '0',
  `MoneyBank` BIGINT NOT NULL DEFAULT '0',
  `Marking` INT NOT NULL DEFAULT '255',
  `Adult` TINYINT(1) NOT NULL DEFAULT '0',
  `TutorialFlag` TINYINT(1) NOT NULL DEFAULT '0',
  `NeedNameChange` TINYINT(1) NOT NULL DEFAULT '0',
  `ToDelete` TINYINT(1) NOT NULL DEFAULT '0',
  `ChangeClass` TINYINT(1) NOT NULL DEFAULT '0',
  `IsGameMaster` TINYINT(1) NOT NULL DEFAULT '0',
  `TutorialHint` BIGINT NOT NULL DEFAULT '0',
  `Reputation` BIGINT NOT NULL DEFAULT '0',
  `MudosaPoint` BIGINT NOT NULL DEFAULT '0',
  `SpPoint` INT NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`, `AccID`),
  INDEX `fk_character_account_idx` (`AccID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_character_account_id`
    FOREIGN KEY (`AccID`)
    REFERENCES `dbo`.`account` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 49
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`inventory`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`inventory` ;

CREATE TABLE IF NOT EXISTS `dbo`.`inventory` (
  `ID` BIGINT UNSIGNED NULL AUTO_INCREMENT,
  `CharID` BIGINT UNSIGNED NOT NULL,
  `ItemID` BIGINT UNSIGNED NOT NULL,
  `Place` INT NOT NULL DEFAULT '0',
  `Slot` INT NOT NULL DEFAULT '0',
  `Stack` INT NOT NULL DEFAULT '0',
  `Rank` INT NOT NULL DEFAULT '1',
  `CurDur` INT NOT NULL DEFAULT '100',
  `NeedToIdentify` TINYINT(1) NOT NULL DEFAULT '0',
  `Grade` INT NOT NULL DEFAULT '0',
  `BattleAttribute` INT NOT NULL DEFAULT '0',
  `RestrictType` INT NOT NULL DEFAULT '0',
  `Maker` VARCHAR(20) NULL DEFAULT '""',
  `Opt1` BIGINT NOT NULL DEFAULT '0',
  `Opt2` BIGINT NOT NULL DEFAULT '0',
  `DurationType` INT NOT NULL DEFAULT '0',
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
AUTO_INCREMENT = 79
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`quickslot`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`quickslot` ;

CREATE TABLE IF NOT EXISTS `dbo`.`quickslot` (
  `ID` BIGINT UNSIGNED NULL AUTO_INCREMENT,
  `CharID` BIGINT UNSIGNED NOT NULL,
  `TblID` BIGINT UNSIGNED NOT NULL,
  `Slot` INT UNSIGNED NOT NULL DEFAULT '0',
  `Type` INT UNSIGNED NOT NULL DEFAULT '0',
  `Item` BIGINT UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`, `CharID`),
  INDEX `fk_quickslot_character_id_idx` (`CharID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_quickslot_character_id`
    FOREIGN KEY (`CharID`)
    REFERENCES `dbo`.`character` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 86
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`skills`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`skills` ;

CREATE TABLE IF NOT EXISTS `dbo`.`skills` (
  `ID` BIGINT UNSIGNED NULL AUTO_INCREMENT,
  `CharID` BIGINT UNSIGNED NOT NULL,
  `SkillID` BIGINT UNSIGNED NOT NULL,
  `Slot` INT UNSIGNED NOT NULL DEFAULT '0',
  `RpBonusType` INT UNSIGNED NOT NULL DEFAULT '0',
  `IsRpBonusAuto` INT UNSIGNED NOT NULL DEFAULT '0',
  `RemainSec` INT UNSIGNED NOT NULL DEFAULT '0',
  `Exp` BIGINT UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`, `CharID`),
  INDEX `fk_character_id_idx` (`CharID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_character_id`
    FOREIGN KEY (`CharID`)
    REFERENCES `dbo`.`character` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 18
DEFAULT CHARACTER SET = utf8;


-- -----------------------------------------------------
-- Table `dbo`.`online`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`online` ;

CREATE TABLE IF NOT EXISTS `dbo`.`online` (
  `AccountID` BIGINT UNSIGNED NOT NULL,
  `CharID` BIGINT UNSIGNED NOT NULL,
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


-- -----------------------------------------------------
-- Table `dbo`.`warfog`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dbo`.`warfog` ;

CREATE TABLE IF NOT EXISTS `dbo`.`warfog` (
  `ID` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `CharID` BIGINT UNSIGNED NOT NULL,
  `Object` BIGINT NOT NULL,
  PRIMARY KEY (`ID`, `CharID`),
  INDEX `pkey_warfog_charid` (`CharID` ASC),
  UNIQUE INDEX `ID_UNIQUE` (`ID` ASC),
  CONSTRAINT `fk_warfog_charid`
    FOREIGN KEY (`CharID`)
    REFERENCES `dbo`.`character` (`ID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

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
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spUpdateDirection
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spUpdateDirection`;

DELIMITER $$
USE `dbo`$$
CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdateDirection`(IN CharID BIGINT, IN DirX FLOAT(11,6), IN DirY FLOAT(11,6), IN DirZ FLOAT(11,6))
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
CREATE DEFINER=`root`@`localhost` PROCEDURE `spUpdatePosition`(in CharID BIGINT, IN PosX float(11,6), in PosY float(11,6), in PosZ float(11,6))
BEGIN
	update `character` set `PositionX` = PosX, `PositionY` = PosY,`PositionZ` = PosZ where `ID` = CharID;
    END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure spQueryInsertItem
-- -----------------------------------------------------

USE `dbo`;
DROP procedure IF EXISTS `dbo`.`spQueryInsertItem`;

DELIMITER $$
USE `dbo`$$
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
