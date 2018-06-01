#pragma once
/*
 * Servico.h
 */
#ifndef SERVICO_H_
#define SERVICO_H_

#include <iostream>

using namespace std;

/**
 * @class Servico
 * @brief Classe com a informacao de cada tipo de Inspecoes.
 * @param tipo String indicando o tipo de servico.
 * @param nome String indicando o nome do servico.
 */
class Servico{
private:
	string tipo;
	string nome;

public:

	//constructors
	/**
	 * @brief Construtor default da classe Servico.
	 * Inicializa os atributos da classe como sendo strings vazias.
	 */
	Servico(): tipo(""), nome(""){};

	/**
	 * @brief Construtor da classe Servico.
	 * @param tipo Tipo de servico.
	 * @param nome Nome do servico.
	 */
	Servico(string tipo, string nome)
	{
		this->tipo = tipo;
		this->nome = nome;
	};

	//set_methods

	/**
	 * @brief Coloca o parametro tipo como o tipo de servico nesta classe.
	 * @param tipo Tipo de servico.
	 */
	void setTipo(string tipo){this->tipo = tipo;};

	/**
	 * @brief Coloca o parametro nome como o nome de servico nesta classe.
	 * @param nome Nome de servico.
	 */
	void setNome(string nome){this->nome = nome;};

	//get_methods

	/**
	 * @brief Vai buscar o tipo de servico.
	 * @return Retorna uma string que representa o tipo de servico.
	 */
	string getTipo() const {return tipo;};

	/**
	 * @brief Vai buscar o nome do servico.
	 * @return Retorna uma string que representa o nome do servico.
	 */
	string getNome() const {return nome;};

	/**
	 * @brief Operador de igualdade da classe servico para comparar dois servicos.
	 * @param s Servico com o qual se vai comparar.
	 * @return Retorna um booleano que indica se o primeiro servico e igual ao segundo.
	 */
	bool operator==(Servico s)
			{
		if(tipo == s.getTipo() && nome == s.getNome())
			return true;

		return false;
			};
};

#endif
