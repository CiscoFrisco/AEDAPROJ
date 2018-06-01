#pragma once
#ifndef INSPECAO_H_
#define INSPECAO_H_

#include <iostream>
#include "Data.h"
#include "Servico.h"

using namespace std;

/**
 * @class Inspecao
 * @brief Classe com a informacao sobre uma inspecao.
 * @param data Objeto da classe data que indica a data em que foi realizada a inspecao
 * @param servico Objeto da classe Servico que indica o servico ao qual e realizada a inspecao
 * @param praia String que indica o nome da praia a que pertence o servico
 * @param concelho String que indica o nome do concelho a que pertence o servico
 */
class Inspecao{
private:
	Data data;
	Servico servico;
	string praia;
	string concelho;

public:
	//constructor

	/**
	 * @brief Construtor da classe Inspecao.
	 * @brief Cria um objeto da classe Inspecao e inciaiza os seus atributos com os parametros recebidos.
	 *
	 * @param d Data de Inspecao
	 * @param s Servico que foi inspecionado
	 * @param p Nome da praia
	 * @param c Nome do concelho
	 */
	Inspecao(Data d, Servico s, string p, string c)
{
		data = d;
		servico = s;
		praia = p;
		concelho = c;
};

	//set_methods

	/**
	 * @brief Coloca o parametro d como a data da inspecao.
	 * @param d Data da inspecao.
	 */
	void setData(Data d){data = d;};

	/**
	 * @brief Coloca o parametro s como o servico que foi inspecionado.
	 * @param s Servico que foi inspecionado.
	 */
	void setServico(Servico s){servico = s;};

	/**
	 * @brief Coloca o parametro p como o nome da praia.
	 * @param p Nome da praia.
	 */
	void setPraia(string p){praia = p;};

	/**
	 * @brief Coloca o parametro c como o nome do concelho.
	 * @param c Nome do concelho.
	 */
	void setConcelho(string c){concelho = c;};

	//get_methods

	/**
	 * @brief Vai buscar a data da inspecao.
	 * @return Retorna a data da inspecao.
	 */
	Data getData() const { return data;};

	/**
	 * @brief Vai buscar o servico que foi inspecionado.
	 * @return Retorna o servico que foi inspecionado.
	 */
	Servico getServico() const { return servico;};

	/**
	 * @brief Vai buscar o nome da praia onde ocorreu a inspecao.
	 * @return Retorna o nome da praia onde ocorreu a inspecao.
	 */
	string getPraia(){return praia;};

	/**
	 * @brief Vai buscar o nome do concelho onde ocorreu a inspecao.
	 * @return Retorna o nome do concelho onde ocorreu a inspecao.
	 */
	string getConcelho(){return concelho;};

	/**
	 * @brief Operador de igualdade que verifica se duas inspecoes sao equivalentes.
	 * @param insp Inspecao a qual se vai comparar
	 * @return Retorna um booleano que indica se as duas inspecoes sao equivalentes ou nao.
	 */
	bool operator==(Inspecao insp)
			{
		if(data == insp.getData() && praia == insp.getPraia() && concelho == insp.getConcelho() && servico ==insp.getServico())
			return true;
		return false;
			};

	/**
	 * @brief Operador menor que verifica se uma inspecao e menor que outra.
	 * @param insp Inspecao a qual se vai comparar
	 * @return Retorna um booleano que indica se a primeira inspecao e menor que a segunda (argumento).
	 */
	bool operator<(Inspecao insp) const
	{
		return  data < insp.getData();
	};

};

#endif //INSPECAO_H_
