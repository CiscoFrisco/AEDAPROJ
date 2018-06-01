#pragma once
#ifndef INSPECOES_H_
#define INSPECOES_H_

#include <iostream>
#include "Inspecao.h"
#include <queue>

using namespace std;

/**
 * @class Inspecoes
 * @brief Classe com a informacao de cada tipo de Inspecoes.
 * @param tipo String indicando o tipo de servico.
 * @param inspecoes Fila de Prioridade que guarda cada uma das inspecoes do mesmo tipo.
 */
class Inspecoes{
private:
	string tipo; //tipo de servicos inspecionados
	priority_queue<Inspecao> inspecoes;

public:

	//constructor
	/**
	 * @brief Construtor da classe Inspecoes.
	 * @param tipo Tipo de servicos inspecionados no objeto a ser construido.
	 */
	Inspecoes(string tipo):tipo(tipo){};

	//set_methods

	/**
	 * @brief Coloca o parametro tipo como o tipo de servicos a que correspondem as inspecoes guardadas nesta classe.
	 * @param tipo Tipo de servico.
	 */
	void setTipo(string tipo){this->tipo = tipo;};

	/**
	 * @brief Coloca o parametro in como sendo a fila de prioridade com as inspecoes do tipo especificado como atributp desta classe.
	 * @param in Fila de prioridade com as inspecoes correspondentes.
	 */
	void setInspec(priority_queue<Inspecao> in){inspecoes = in;};

	//get_methods

	/**
	 * @brief Vai buscar o tipo de servico.
	 * @return Retorna uma string que representa o tipo de servico.
	 */
	string getTipo() const {return tipo;};

	/**
	 * @brief Vai buscar uma fila de prioridades com as inspecoes do tipo indicado como atributo do objeto.
	 * @return Retorna uma fila de prioridade de objetos da classe inspecao referente as inspecoes daquele tipo.
	 */
	priority_queue<Inspecao> getInspec() const {return inspecoes;};

	/**
	 * @brief Adiciona uma inspecao a fila de prioridade correspondente
	 * @param in Inspecao a ser adicionada.
	 */
	void addInspecao(Inspecao in)
	{
		inspecoes.push(in);
	};
};

#endif //INSPECOES_H_
