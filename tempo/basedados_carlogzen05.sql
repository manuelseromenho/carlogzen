CREATE DATABASE  IF NOT EXISTS `carlogzendb4` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `carlogzendb4`;
-- MySQL dump 10.13  Distrib 5.7.9, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: carlogzendb4
-- ------------------------------------------------------
-- Server version	5.7.18-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `abastecimento`
--

DROP TABLE IF EXISTS `abastecimento`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `abastecimento` (
  `idabastecimento` int(11) NOT NULL AUTO_INCREMENT,
  `local` varchar(45) NOT NULL,
  `data` date NOT NULL,
  `kms` double NOT NULL,
  `litros` double NOT NULL,
  `precolitro` double NOT NULL,
  `idmatricula` varchar(10) NOT NULL,
  PRIMARY KEY (`idabastecimento`),
  UNIQUE KEY `idAbastecimento_UNIQUE` (`idabastecimento`),
  KEY `idmatricula_idx` (`idmatricula`),
  CONSTRAINT `idmatricula` FOREIGN KEY (`idmatricula`) REFERENCES `automoveis` (`idmatricula`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `abastecimento`
--

LOCK TABLES `abastecimento` WRITE;
/*!40000 ALTER TABLE `abastecimento` DISABLE KEYS */;
/*!40000 ALTER TABLE `abastecimento` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `automoveis`
--

DROP TABLE IF EXISTS `automoveis`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `automoveis` (
  `idmatricula` varchar(10) NOT NULL,
  `idcaracteristica` int(11) NOT NULL,
  `data_aquisicao` date NOT NULL,
  `data_venda` date NOT NULL,
  `preco_aquisicao` double NOT NULL,
  `preco_venda` double NOT NULL,
  PRIMARY KEY (`idmatricula`),
  UNIQUE KEY `idautomovel_UNIQUE` (`idmatricula`),
  KEY `idcaracteristica_idx` (`idcaracteristica`),
  CONSTRAINT `idcaracteristica` FOREIGN KEY (`idcaracteristica`) REFERENCES `caracteristicas` (`idcaracteristica`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `automoveis`
--

LOCK TABLES `automoveis` WRITE;
/*!40000 ALTER TABLE `automoveis` DISABLE KEYS */;
/*!40000 ALTER TABLE `automoveis` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `caracteristicas`
--

DROP TABLE IF EXISTS `caracteristicas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `caracteristicas` (
  `idcaracteristica` int(11) NOT NULL AUTO_INCREMENT,
  `modelo` varchar(45) NOT NULL,
  `combustivel` varchar(45) NOT NULL,
  `cilindrada` varchar(45) NOT NULL,
  `cor` varchar(45) NOT NULL,
  PRIMARY KEY (`idcaracteristica`),
  UNIQUE KEY `idcaracteristicas_UNIQUE` (`idcaracteristica`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `caracteristicas`
--

LOCK TABLES `caracteristicas` WRITE;
/*!40000 ALTER TABLE `caracteristicas` DISABLE KEYS */;
/*!40000 ALTER TABLE `caracteristicas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `detalhes_revisao`
--

DROP TABLE IF EXISTS `detalhes_revisao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `detalhes_revisao` (
  `iddetalhe` int(11) NOT NULL AUTO_INCREMENT,
  `idrevisao` int(11) NOT NULL,
  `idpeca` int(11) NOT NULL,
  `idmanutencao` int(11) NOT NULL,
  `quantidade_peca` int(11) NOT NULL,
  `quantidade_manutencao` int(11) NOT NULL,
  PRIMARY KEY (`iddetalhe`),
  UNIQUE KEY `iddetalhe_UNIQUE` (`iddetalhe`),
  KEY `idmanutencao_idx` (`idmanutencao`),
  KEY `idpeca_idx` (`idpeca`),
  KEY `idrevisao_idx` (`idrevisao`),
  CONSTRAINT `idmanutencao` FOREIGN KEY (`idmanutencao`) REFERENCES `manutencao` (`idmanutencao`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `idpeca` FOREIGN KEY (`idpeca`) REFERENCES `pecas` (`idpecas`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `idrevisao` FOREIGN KEY (`idrevisao`) REFERENCES `revisoes` (`idrevisao`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `detalhes_revisao`
--

LOCK TABLES `detalhes_revisao` WRITE;
/*!40000 ALTER TABLE `detalhes_revisao` DISABLE KEYS */;
/*!40000 ALTER TABLE `detalhes_revisao` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `manutencao`
--

DROP TABLE IF EXISTS `manutencao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `manutencao` (
  `idmanutencao` int(11) NOT NULL AUTO_INCREMENT,
  `tipomanutencao` varchar(45) NOT NULL,
  `preco` varchar(45) NOT NULL,
  PRIMARY KEY (`idmanutencao`),
  UNIQUE KEY `idmanutencao_UNIQUE` (`idmanutencao`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `manutencao`
--

LOCK TABLES `manutencao` WRITE;
/*!40000 ALTER TABLE `manutencao` DISABLE KEYS */;
/*!40000 ALTER TABLE `manutencao` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pecas`
--

DROP TABLE IF EXISTS `pecas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pecas` (
  `idpecas` int(11) NOT NULL AUTO_INCREMENT,
  `peca` varchar(45) NOT NULL,
  `precopeca` double NOT NULL,
  PRIMARY KEY (`idpecas`),
  UNIQUE KEY `idpecas_UNIQUE` (`idpecas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pecas`
--

LOCK TABLES `pecas` WRITE;
/*!40000 ALTER TABLE `pecas` DISABLE KEYS */;
/*!40000 ALTER TABLE `pecas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `revisoes`
--

DROP TABLE IF EXISTS `revisoes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `revisoes` (
  `idrevisao` int(11) NOT NULL AUTO_INCREMENT,
  `idmatricula` varchar(10) NOT NULL,
  `oficina` varchar(45) NOT NULL,
  `kms` double NOT NULL,
  `datarevisao` date NOT NULL,
  `observacoes` varchar(300) NOT NULL,
  PRIMARY KEY (`idrevisao`),
  UNIQUE KEY `idrevisao_UNIQUE` (`idrevisao`),
  KEY `idmatricula_idx` (`idmatricula`),
  KEY `idmatricula_revisoes_idx` (`idmatricula`),
  CONSTRAINT `idmatricula_revisoes` FOREIGN KEY (`idmatricula`) REFERENCES `automoveis` (`idmatricula`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `revisoes`
--

LOCK TABLES `revisoes` WRITE;
/*!40000 ALTER TABLE `revisoes` DISABLE KEYS */;
/*!40000 ALTER TABLE `revisoes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `iduser` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(45) NOT NULL,
  `password` varchar(45) NOT NULL,
  PRIMARY KEY (`iduser`),
  UNIQUE KEY `idusers_UNIQUE` (`iduser`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'carlogzendb4'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-06-18 23:29:12
