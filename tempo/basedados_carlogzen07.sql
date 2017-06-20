--
-- File generated with SQLiteStudio v3.1.1 on seg jun 19 00:29:36 2017
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: abastecimento
CREATE TABLE abastecimento (idabastecimento INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, local varchar (45) NOT NULL, data date NOT NULL, kms double NOT NULL, litros double NOT NULL, precolitro double NOT NULL, idmatricula varchar (10) NOT NULL REFERENCES automoveis (idmatricula) ON DELETE CASCADE ON UPDATE CASCADE);

-- Table: automoveis
CREATE TABLE automoveis (idmatricula varchar (10) PRIMARY KEY NOT NULL UNIQUE, idcaracteristica INTEGER NOT NULL REFERENCES caracteristicas (idcaracteristica) ON DELETE CASCADE ON UPDATE CASCADE, data_aquisicao date NOT NULL, data_venda date NOT NULL, preco_aquisicao double NOT NULL, preco_venda double NOT NULL);

-- Table: caracteristicas
CREATE TABLE caracteristicas (idcaracteristica INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, modelo varchar (45) NOT NULL, combustivel varchar (45) NOT NULL, cilindrada varchar (45) NOT NULL, cor varchar (45) NOT NULL);

-- Table: detalhes_revisao
CREATE TABLE detalhes_revisao (iddetalhe INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, idrevisao INTEGER NOT NULL REFERENCES revisoes (idrevisao) ON DELETE CASCADE ON UPDATE CASCADE, idpeca INTEGER NOT NULL REFERENCES pecas (idpecas) ON DELETE CASCADE ON UPDATE CASCADE, idmanutencao INTEGER NOT NULL REFERENCES manutencao (idmanutencao) ON DELETE CASCADE ON UPDATE CASCADE, quantidade_peca INTEGER NOT NULL, quantidade_manutencao INTEGER NOT NULL);

-- Table: manutencao
CREATE TABLE manutencao (idmanutencao INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, tipomanutencao varchar (45) NOT NULL, preco varchar (45) NOT NULL);

-- Table: pecas
CREATE TABLE pecas (idpecas INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, peca varchar (45) NOT NULL, precopeca double NOT NULL);

-- Table: revisoes
CREATE TABLE revisoes (idrevisao INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, idmatricula varchar (10) NOT NULL REFERENCES automoveis (idmatricula) ON DELETE CASCADE ON UPDATE CASCADE, oficina varchar (45) NOT NULL, kms double NOT NULL, datarevisao date NOT NULL, observacoes varchar (300) NOT NULL);

-- Table: users
CREATE TABLE users (iduser INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, username varchar (45) NOT NULL, password varchar (45) NOT NULL);

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
