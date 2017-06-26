--
-- File generated with SQLiteStudio v3.1.1 on seg jun 26 01:37:02 2017
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: abastecimento
CREATE TABLE abastecimento (idabastecimento INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, idmatricula varchar (10) REFERENCES automoveis (idmatricula) ON DELETE CASCADE ON UPDATE CASCADE, local varchar (45), data date NOT NULL, kms double NOT NULL, litros double NOT NULL, precolitro double);
INSERT INTO abastecimento (idabastecimento, idmatricula, local, data, kms, litros, precolitro) VALUES (29, '10-bb-11', 'Faro', '20/06/2017', 10000, 1, 2);
INSERT INTO abastecimento (idabastecimento, idmatricula, local, data, kms, litros, precolitro) VALUES (30, '10-bb-11', 'Albufeira', '20/06/2017', 5000, 15, 20);
INSERT INTO abastecimento (idabastecimento, idmatricula, local, data, kms, litros, precolitro) VALUES (31, '10-cc-15', 'Loulé', '19/06/2017', 15000, 15, 5);
INSERT INTO abastecimento (idabastecimento, idmatricula, local, data, kms, litros, precolitro) VALUES (32, '10-cc-15', 'Estoi', '22/06/2017', 21222, 15, 15);
INSERT INTO abastecimento (idabastecimento, idmatricula, local, data, kms, litros, precolitro) VALUES (33, '11-aa-10', 'Almada', '14/06/2017', 121320, 15, 55);
INSERT INTO abastecimento (idabastecimento, idmatricula, local, data, kms, litros, precolitro) VALUES (34, '11-aq-13', 'Fuseta', '13/06/2017', 5000, 1, 1.5);
INSERT INTO abastecimento (idabastecimento, idmatricula, local, data, kms, litros, precolitro) VALUES (35, '10-bb-11', 'Faro', '21/06/2017', 10000, 1, 1.5);

-- Table: automoveis
CREATE TABLE automoveis (idmatricula varchar (10) PRIMARY KEY UNIQUE, idcaracteristica INTEGER REFERENCES caracteristicas (idcaracteristica) ON DELETE CASCADE ON UPDATE CASCADE, data_aquisicao date, data_venda date, preco_aquisicao double, preco_venda double, status BOOLEAN DEFAULT (0));
INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, data_venda, preco_aquisicao, preco_venda, status) VALUES ('10-bb-11', 1, '10/05/2005', NULL, 5000, NULL, 0);
INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, data_venda, preco_aquisicao, preco_venda, status) VALUES ('11-aa-10', 3, '01/01/2015', NULL, 20000, NULL, 0);
INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, data_venda, preco_aquisicao, preco_venda, status) VALUES ('10-cc-15', 10, '01/01/2005', NULL, 1000, NULL, 0);
INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, data_venda, preco_aquisicao, preco_venda, status) VALUES ('56-AB-10', 5, '01/01/2015', NULL, 100000, NULL, 0);
INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, data_venda, preco_aquisicao, preco_venda, status) VALUES ('45-SS-10', 4, '03/01/2003', '15/01/2015', 5454, 10000, 1);
INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, data_venda, preco_aquisicao, preco_venda, status) VALUES ('45-aa-45', 7, '04/01/2015', '01/01/2015', 14545, 151, 1);
INSERT INTO automoveis (idmatricula, idcaracteristica, data_aquisicao, data_venda, preco_aquisicao, preco_venda, status) VALUES ('11-aq-13', 1, '01/01/2015', '26/06/2017', 20000, 1000, 1);

-- Table: caracteristicas
CREATE TABLE caracteristicas (idcaracteristica INTEGER PRIMARY KEY ASC AUTOINCREMENT NOT NULL UNIQUE, marca VARCHAR (20) NOT NULL, modelo VARCHAR (20) NOT NULL, cilindrada VARCHAR (10) NOT NULL, cor VARCHAR (10) NOT NULL, combustivel VARCHAR (10) NOT NULL);
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (1, 'VW', 'Golf', '1100', 'Vermelho', 'Gasolina');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (2, 'VW', 'Polo', '1100', 'Azul', 'Gasolina');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (3, 'Fiat', 'Punto', '1500', 'Azul', 'Diesel');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (4, 'Ford', 'Fiesta', '1200', 'Branco', 'Gasolina');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (5, 'Subaru', 'V1', '1588', 'Bronze', 'Alcool');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (6, 'Peugeot', '206', '1300', 'Prateado', 'Gasolina');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (7, 'Toyota', 'Yaris', '1500', 'Vermelho', 'Gasolina');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (9, 'Toyota', 'Ayris', '1200', 'Creme', 'Gasolina');
INSERT INTO caracteristicas (idcaracteristica, marca, modelo, cilindrada, cor, combustivel) VALUES (10, 'Fiat', 'Panda', '1000', 'Azul', 'Diesel');

-- Table: detalhes_revisao
CREATE TABLE detalhes_revisao (iddetalhe INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, idrevisao INTEGER NOT NULL REFERENCES revisoes (idrevisao) ON DELETE CASCADE ON UPDATE CASCADE, idpeca INTEGER REFERENCES pecas (idpeca) ON DELETE CASCADE ON UPDATE CASCADE, idmanutencao INTEGER NOT NULL REFERENCES manutencao (idmanutencao) ON DELETE CASCADE ON UPDATE CASCADE DEFAULT (1), quantidade_peca INTEGER, quantidade_manutencao INTEGER NOT NULL DEFAULT (1));
INSERT INTO detalhes_revisao (iddetalhe, idrevisao, idpeca, idmanutencao, quantidade_peca, quantidade_manutencao) VALUES (1, 62, 7, 1, 1, 1);
INSERT INTO detalhes_revisao (iddetalhe, idrevisao, idpeca, idmanutencao, quantidade_peca, quantidade_manutencao) VALUES (2, 65, NULL, 1, NULL, 1);
INSERT INTO detalhes_revisao (iddetalhe, idrevisao, idpeca, idmanutencao, quantidade_peca, quantidade_manutencao) VALUES (3, 62, 4, 1, 2, 1);
INSERT INTO detalhes_revisao (iddetalhe, idrevisao, idpeca, idmanutencao, quantidade_peca, quantidade_manutencao) VALUES (4, 62, 10, 3, 4, 1);
INSERT INTO detalhes_revisao (iddetalhe, idrevisao, idpeca, idmanutencao, quantidade_peca, quantidade_manutencao) VALUES (5, 76, 4, 2, 1, 1);

-- Table: manutencao
CREATE TABLE manutencao (idmanutencao INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, tipomanutencao varchar (45) NOT NULL, preco varchar (45) NOT NULL);
INSERT INTO manutencao (idmanutencao, tipomanutencao, preco) VALUES (1, 'assistencia geral', '20');
INSERT INTO manutencao (idmanutencao, tipomanutencao, preco) VALUES (2, 'assistencia electrica', '50');
INSERT INTO manutencao (idmanutencao, tipomanutencao, preco) VALUES (3, 'assistencia pneus', '5');

-- Table: pecas
CREATE TABLE pecas (idpeca INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, peca varchar (45) NOT NULL, precopeca double NOT NULL);
INSERT INTO pecas (idpeca, peca, precopeca) VALUES (4, 'vela', 5);
INSERT INTO pecas (idpeca, peca, precopeca) VALUES (7, 'pneu michelin 1', 60);
INSERT INTO pecas (idpeca, peca, precopeca) VALUES (8, 'pneu michelin 2', 70);
INSERT INTO pecas (idpeca, peca, precopeca) VALUES (9, 'pneu continental 1', 50);
INSERT INTO pecas (idpeca, peca, precopeca) VALUES (10, 'pneu continental 1', 60);

-- Table: revisoes
CREATE TABLE revisoes (idrevisao INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, idmatricula varchar (10) REFERENCES automoveis (idmatricula) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL, oficina varchar (45), kms double, datarevisao date, observacoes INT (50) DEFAULT (0));
INSERT INTO revisoes (idrevisao, idmatricula, oficina, kms, datarevisao, observacoes) VALUES (62, '11-aa-10', 'Honda', 'hh', '01/01/2017', 0);
INSERT INTO revisoes (idrevisao, idmatricula, oficina, kms, datarevisao, observacoes) VALUES (65, '56-AB-10', 'MScar', 89, '01/01/2016', 0);
INSERT INTO revisoes (idrevisao, idmatricula, oficina, kms, datarevisao, observacoes) VALUES (66, '10-cc-15', 'Albufeira', 10000, '01/01/2015', 'Pneus');
INSERT INTO revisoes (idrevisao, idmatricula, oficina, kms, datarevisao, observacoes) VALUES (72, '10-cc-15', 'Faro', 50000, '05/06/2017', 'Houve uma avaria');
INSERT INTO revisoes (idrevisao, idmatricula, oficina, kms, datarevisao, observacoes) VALUES (74, '56-AB-10', 'Loulé', 100000, '05/06/2017', 'Ignição');
INSERT INTO revisoes (idrevisao, idmatricula, oficina, kms, datarevisao, observacoes) VALUES (76, '11-aa-10', 'Almancil', 4545646, '29/05/2017', 'Tubos');

-- Table: users
CREATE TABLE users (iduser INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, username varchar (45) NOT NULL, password varchar (45) NOT NULL);
INSERT INTO users (iduser, username, password) VALUES (1, 'admin', 'admin');
INSERT INTO users (iduser, username, password) VALUES (2, 'gerente', 'gerente');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
