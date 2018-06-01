#pragma once
#ifndef PONTOS_INTERESSE_H_
#define PONTOS_INTERESSE_H_

#include "Data.h"
#include "Coordenadas.h"
#include <string>
#include <iostream>

//using namespace std;

/**
 * @class Turismo
 * @brief Classe referente aos Pontos de Interesse Turisticos.
 * @param nome Nome do objeto.
 * @param coordenadas Coordenadas de um ponto turistico.
 */
class Turismo {
	string nome;
	Coordenadas coordenadas;
public:

	//constructors
	/**
	 * @brief Construtor da classe Turismo.
	 * @param nome Nome do ponto turistico.
	 * @param coordenadas Coordenadas GPS do ponto turistico
	 */
	Turismo(string nome, Coordenadas coordenadas);

	//set_methods

	/**
	 * @brief Coloca o parametro nome como o nome do ponto turistico.
	 * @param nome Nome do ponto turistico.
	 */
	void set_nome(string nome);

	/**
	 * @brief Coloca o parametro coordenadas como as coordenadas do ponto turistico.
	 * @param coordenadas Coordenadas do ponto turistico.
	 */
	void set_coordenadas(Coordenadas coordenadas);

	//get_methods

	/**
	 * @brief Vai buscar o nome do ponto turistico.
	 * @return Retorna uma string que representa o nome do ponto turistico.
	 */
	string get_nome() const;

	/**
	 * @brief Vai buscar as coordenadas do ponto turistico.
	 * @return Retorna um objeto que representa as coordenadas do ponto turistico.
	 */
	Coordenadas get_coordenadas() const;
};

/**
 * @class Alojamento
 * @brief Classe referente aos Alojamentos.
 * @param nome Nome do objeto.
 * @param coordenadas Coordenadas de um alojamento.
 */
class Alojamento {
	string nome;
	Coordenadas coordenadas;
	bool aberto;
	Data abertura;
	Data fecho;
public:

	//constructors
	/**
	 * @brief Construtor da classe Alojamento.
	 * @param nome Nome do alojamento.
	 * @param coordenadas Coordenadas GPS do alojamento
	 */
	Alojamento(string nome, Coordenadas coordenadas, bool aberto);

	//set_methods

	/**
	 * @brief Coloca o parametro nome como o nome do alojamento.
	 * @param nome Nome do alojamento.
	 */
	void set_nome(string nome);

	/**
	 * @brief Coloca o parametro coordenadas como as coordenadas do alojamento.
	 * @param coordenadas Coordenadas do alojamento.
	 */
	void set_coordenadas(Coordenadas coordenadas);

	/**
	 * @brief Coloca o parametro aberto no atributo da classe indicando se um alojamento se encontra de momento aberto.
	 * @param aberto Booleano indicando se um alojamento se encontra de momento aberto.
	 */
	void set_aberto(bool aberto);

	/**
	 * @brief Coloca o parametro fecho como a data de fecho de um alojamento.
	 * @param fecho Data de fecho do alojamento.
	 */
	void set_data_fecho(Data fecho);

	/**
	 * @brief Coloca o parametro abertura como a data de abertura de um alojamento.
	 * @param abertura Data de abertura do alojamento.
	 */
	void set_data_abertura(Data abertura);


	//get_methods

	/**
	 * @brief Vai buscar o nome do alojamento.
	 * @return Retorna uma string que representa o nome do alojamento.
	 */
	string get_nome() const;

	/**
	 * @brief Vai buscar as coordenadas do alojamento.
	 * @return Retorna um objeto que representa as coordenadas do alojamento.
	 */
	Coordenadas get_coordenadas() const;

	/**
	 * @brief Vai buscar um booleano indicando se um alojamento se encontra aberto de momento.
	 * @return Retorna um booleano indicando se um alojamento se encontra aberto de momento.
	 */
	bool get_aberto();

	/**
	 * @brief Vai buscar a data de fecho do alojamento.
	 * @return Retorna um objeto que representa a data de fecho do alojamento.
	 */
	Data get_data_fecho() const;

	/**
	 * @brief Vai buscar a data de abertura do alojamento.
	 * @return Retorna um objeto que representa a data de abertura do alojamento.
	 */
	Data get_data_abertura() const;
};

/**
 * @class Restauracao
 * @brief Classe referente aos Restaurantes.
 * @param nome Nome do objeto.
 * @param coordenadas Coordenadas de um restaurante.
 */
class Restauracao {
	string nome;
	Coordenadas coordenadas;
	bool aberto;
	Data abertura;
	Data fecho;
public:

	//constructors
	/**
	 * @brief Construtor da classe Restauracao.
	 * @param nome Nome do restaurante.
	 * @param coordenadas Coordenadas GPS do restaurante
	 */
	Restauracao(string nome, Coordenadas coordenadas, bool aberto);

	//set_methods

	/**
	 * @brief Coloca o parametro nome como o nome do restaurante.
	 * @param nome Nome do restaurante.
	 */
	void set_nome(string nome);

	/**
	 * @brief Coloca o parametro coordenadas como as coordenadas do restaurante.
	 * @param coordenadas Coordenadas do restaurante.
	 */
	void set_coordenadas(Coordenadas coordenadas);

	/**
	 * @brief Coloca o parametro aberto no atributo da classe indicando se um restaurante se encontra de momento aberto.
	 * @param aberto Booleano indicando se um restaurante se encontra de momento aberto.
	 */
	void set_aberto(bool aberto);

	/**
	 * @brief Coloca o parametro fecho como a data de fecho de um restaurante.
	 * @param fecho Data de fecho do restaurante.
	 */
	void set_data_fecho(Data fecho);

	/**
	 * @brief Coloca o parametro abertura como a data de abertura de um restaurante.
	 * @param abertura Data de abertura do restaurante.
	 */
	void set_data_abertura(Data abertura);


	//get_methods

	/**
	 * @brief Vai buscar o nome do restaurante.
	 * @return Retorna uma string que representa o nome do restaurante.
	 */
	string get_nome() const;

	/**
	 * @brief Vai buscar as coordenadas do restaurante.
	 * @return Retorna um objeto que representa as coordenadas do restaurante.
	 */
	Coordenadas get_coordenadas() const;

	/**
	 * @brief Vai buscar um booleano indicando se um restaurante se encontra aberto de momento.
	 * @return Retorna um booleano indicando se um restaurante se encontra aberto de momento.
	 */
	bool get_aberto();

	/**
	 * @brief Vai buscar a data de fecho do restaurante.
	 * @return Retorna um objeto que representa a data de fecho do restaurante.
	 */
	Data get_data_fecho() const;

	/**
	 * @brief Vai buscar a data de abertura do restaurante.
	 * @return Retorna um objeto que representa a data de abertura do restaurante.
	 */
	Data get_data_abertura() const;
};

#endif //PONTOS_INTERESSE_H_
