--
-- File generated with SQLiteStudio v3.1.1 on seg jun 19 12:26:59 2017
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

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

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
