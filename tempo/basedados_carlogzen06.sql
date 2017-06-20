DROP TABLE IF EXISTS 'abastecimento';
CREATE TABLE 'abastecimento' (
  'idabastecimento' int(11) NOT NULL AUTOINCREMENT,
  'local' varchar(45) NOT NULL,
  'data' date NOT NULL,
  'kms' double NOT NULL,
  'litros' double NOT NULL,
  'precolitro' double NOT NULL,
  'idmatricula' varchar(10) NOT NULL,
  PRIMARY KEY ('idabastecimento'),
  UNIQUE KEY 'idAbastecimento_UNIQUE' ('idabastecimento'),
  KEY 'idmatricula_idx' ('idmatricula'),
  CONSTRAINT 'idmatricula' FOREIGN KEY ('idmatricula') REFERENCES 'automoveis' ('idmatricula') ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


LOCK TABLES 'abastecimento' WRITE;
UNLOCK TABLES;



DROP TABLE IF EXISTS 'automoveis';
CREATE TABLE 'automoveis' (
  'idmatricula' varchar(10) NOT NULL,
  'idcaracteristica' int(11) NOT NULL,
  'data_aquisicao' date NOT NULL,
  'data_venda' date NOT NULL,
  'preco_aquisicao' double NOT NULL,
  'preco_venda' double NOT NULL,
  PRIMARY KEY ('idmatricula'),
  UNIQUE KEY 'idautomovel_UNIQUE' ('idmatricula'),
  KEY 'idcaracteristica_idx' ('idcaracteristica'),
  CONSTRAINT 'idcaracteristica' FOREIGN KEY ('idcaracteristica') REFERENCES 'caracteristicas' ('idcaracteristica') ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES 'automoveis' WRITE;
UNLOCK TABLES;



DROP TABLE IF EXISTS 'caracteristicas';
CREATE TABLE 'caracteristicas' (
  'idcaracteristica' int(11) NOT NULL AUTOINCREMENT,
  'modelo' varchar(45) NOT NULL,
  'combustivel' varchar(45) NOT NULL,
  'cilindrada' varchar(45) NOT NULL,
  'cor' varchar(45) NOT NULL,
  PRIMARY KEY ('idcaracteristica'),
  UNIQUE KEY 'idcaracteristicas_UNIQUE' ('idcaracteristica')
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES 'caracteristicas' WRITE;
UNLOCK TABLES;



DROP TABLE IF EXISTS 'detalhes_revisao';
CREATE TABLE 'detalhes_revisao' (
  'iddetalhe' int(11) NOT NULL AUTOINCREMENT,
  'idrevisao' int(11) NOT NULL,
  'idpeca' int(11) NOT NULL,
  'idmanutencao' int(11) NOT NULL,
  'quantidade_peca' int(11) NOT NULL,
  'quantidade_manutencao' int(11) NOT NULL,
  PRIMARY KEY ('iddetalhe'),
  UNIQUE KEY 'iddetalhe_UNIQUE' ('iddetalhe'),
  KEY 'idmanutencao_idx' ('idmanutencao'),
  KEY 'idpeca_idx' ('idpeca'),
  KEY 'idrevisao_idx' ('idrevisao'),
  CONSTRAINT 'idmanutencao' FOREIGN KEY ('idmanutencao') REFERENCES 'manutencao' ('idmanutencao') ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT 'idpeca' FOREIGN KEY ('idpeca') REFERENCES 'pecas' ('idpecas') ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT 'idrevisao' FOREIGN KEY ('idrevisao') REFERENCES 'revisoes' ('idrevisao') ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES 'detalhes_revisao' WRITE;
UNLOCK TABLES;



DROP TABLE IF EXISTS 'manutencao';
CREATE TABLE 'manutencao' (
  'idmanutencao' int(11) NOT NULL AUTOINCREMENT,
  'tipomanutencao' varchar(45) NOT NULL,
  'preco' varchar(45) NOT NULL,
  PRIMARY KEY ('idmanutencao'),
  UNIQUE KEY 'idmanutencao_UNIQUE' ('idmanutencao')
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES 'manutencao' WRITE;
UNLOCK TABLES;



DROP TABLE IF EXISTS 'pecas';
CREATE TABLE 'pecas' (
  'idpecas' int(11) NOT NULL AUTOINCREMENT,
  'peca' varchar(45) NOT NULL,
  'precopeca' double NOT NULL,
  PRIMARY KEY ('idpecas'),
  UNIQUE KEY 'idpecas_UNIQUE' ('idpecas')
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

LOCK TABLES 'pecas' WRITE;
UNLOCK TABLES;



DROP TABLE IF EXISTS 'revisoes';
CREATE TABLE 'revisoes' (
  'idrevisao' int(11) NOT NULL AUTOINCREMENT,
  'idmatricula' varchar(10) NOT NULL,
  'oficina' varchar(45) NOT NULL,
  'kms' double NOT NULL,
  'datarevisao' date NOT NULL,
  'observacoes' varchar(300) NOT NULL,
  PRIMARY KEY ('idrevisao'),
  UNIQUE KEY 'idrevisao_UNIQUE' ('idrevisao'),
  KEY 'idmatricula_idx' ('idmatricula'),
  KEY 'idmatricula_revisoes_idx' ('idmatricula'),
  CONSTRAINT 'idmatricula_revisoes' FOREIGN KEY ('idmatricula') REFERENCES 'automoveis' ('idmatricula') ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


LOCK TABLES 'revisoes' WRITE;
UNLOCK TABLES;


DROP TABLE IF EXISTS 'users';
CREATE TABLE 'users' (
  'iduser' int(11) NOT NULL AUTOINCREMENT,
  'username' varchar(45) NOT NULL,
  'password' varchar(45) NOT NULL,
  PRIMARY KEY ('iduser'),
  UNIQUE KEY 'idusers_UNIQUE' ('iduser')
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


LOCK TABLES 'users' WRITE;
UNLOCK TABLES;
