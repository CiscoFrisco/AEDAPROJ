#pragma once

#include <iostream>
#include "Data.h"

//using namespace std;

////////Praias//////////////////

/**
 * @brief Classe que trata da excecao Praia Nao Existente
 */
class PraiaNaoExistente {
	string nome;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param nome Nome da praia em questao
	 */
	PraiaNaoExistente(string nome) { this->nome = nome; }
	/**
	 * @brief Vai buscar o atributo nome referente ao nome da praia
	 * @return Retorna o nome da praia
	 */
	string getNome() const { return nome; }
};

/**
 * @brief Classe que trata da excecao Praia Existente
 */
class PraiaExistente {
	string nome;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param nome Nome da praia em questao
	 */
	PraiaExistente(string nome) { this->nome = nome; }
	/**
	 * @brief Vai buscar o atributo nome referente ao nome da praia
	 * @return Retorna o nome da praia
	 */
	string getNome() const { return nome; }
};

///////Pontos de Interesse///////////////

/**
 * @brief Classe que trata da excecao Ponto de Interesse Nao Existente
 */
class PontoInteresseNaoExistente {
	string nome;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param nome Nome do ponto de interesse em questao
	 */
	PontoInteresseNaoExistente(string nome) { this->nome = nome; }
	/**
	 * @brief Vai buscar o atributo nome referente ao nome do ponto de interesse
	 * @return Retorna o nome do ponto de interesse
	 */
	string getNome() const { return nome; }
};
/*
class PontoInteresseExistente {
	string nome;
public:
	PontoInteresseExistente(string nome) { this->nome = nome; }
	string getNome() const { return nome; }
};*/

////////Concelhos///////////////

/**
 * @brief Classe que trata da excecao Concelho Nao Existente
 */
class ConcelhoNaoExistente {
	string nome;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param nome Nome do concelho em questao
	 */
	ConcelhoNaoExistente(string nome) { this->nome = nome; }

	/**
	 * @brief Vai buscar o atributo nome referente ao nome do ponto de interesse
	 * @return Retorna o nome do ponto de interesse
	 */
	string getNome() const { return nome; }
};

/**
 * @brief Classe que trata da excecao Concelho Existente
 */
class ConcelhoExistente {
	string nome;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param nome Nome do concelho em questao
	 */
	ConcelhoExistente(string nome) { this->nome = nome; }

	/**
	 * @brief Vai buscar o atributo nome referente ao nome do concelho
	 * @return Retorna o nome do concelho
	 */
	string getNome() const { return nome; }
};

///////////Data////////////

/**
 * @brief Classe que trata da excecao Data Invalida
 */
class DataInvalida {
	Data data;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param data Data introduzida pelo utilizador
	 */
	DataInvalida(Data data) { this->data = data; };

	/**
	 * @brief Vai buscar a data introduzida pelo utilizador
	 * @return Retorna a data
	 */
	Data getData(){return data;};
};

/**
 * @brief Classe que trata da excecao Data Impossivel. Quando a data introduzida é menor que a data atual
 */
class DataImpossivel{
	Data data;
	Data current_data;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param data Data introduzida pelo utilizador
	 */
	DataImpossivel(Data data, Data current_data) { this->data = data; this->current_data = current_data; };

	/**
	 * @brief Vai buscar a data introduzida pelo utilizador
	 * @return Retorna a data
	 */
	Data getDataUser(){return data;};

	/**
	 * @brief Vai buscar a data atual
	 * @return Retorna a data atual
	 */
	Data getDataCurr(){return current_data;};

};

/**
 * @brief Classe que trata da excecao Data Imcompativel. Quando a data de reabertura antecede a data de fecho de um ponto de interesse
 */
class DataIncompativel{
	Data fecho;
	Data abertura;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param data Data introduzida pelo utilizador
	 */
	DataIncompativel(Data fecho, Data abertura) { this->fecho = fecho; this->abertura = abertura; };

	/**
	 * @brief Vai buscar a data de fecho
	 * @return Retorna a data de fecho
	 */
	Data getDataFecho(){return fecho;};

	/**
	 * @brief Vai buscar a data de reabertura
	 * @return Retorna a data de reabertura
	 */
	Data getDataAbertura(){return abertura;};

};


////////////Servico///////////////
/**
 * @brief Classe que trata da excecao Servico Nao Existente
 */
class ServicoNaoExistente {
	string nome;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param nome Nome do Servico em questao
	 */
	ServicoNaoExistente(string nome) { this->nome = nome; }

	/**
	 * @brief Vai buscar o atributo nome referente ao nome do Servico
	 * @return Retorna o nome do Servico
	 */
	string getNome() const { return nome; }
};



/**
 * @brief Classe que trata da excecao Tipo Nao Existente
 */
class TipoNaoExistente {
	string nome;
public:

	/**
	 * @brief Contrutor da excecao a ser lancada
	 * @param nome Nome do tipo de servico em questao
	 */
	TipoNaoExistente(string nome) { this->nome = nome; }

	/**
	 * @brief Vai buscar o atributo nome referente ao nome do Servico
	 * @return Retorna o nome do tipo de Servico
	 */
	string getNome() const { return nome; }
};

