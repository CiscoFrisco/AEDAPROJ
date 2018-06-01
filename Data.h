#pragma once
#ifndef DATA_H_
#define DATA_H_

#include <iostream>


/**
 * @class Data
 * @brief Classe com a informacao necessaria para caraterizar uma data.
 * @param dia Dia da data
 * @param mes Mes da data
 * @param ano Ano da data
 */
class Data{
private:
	int dia;
	int mes;
	int ano;

public:
	//constructors
	/**
	 * @brief Construtor default da classe Data.
	 * @brief Cria uma data com todos os elementos  da data nulos.
	 */
	Data(): dia(0), mes(0), ano(0) {};

	/**
	 * @brief Construtor da classe Data.
	 * @brief Recebe cada um dos parametros necessarios e cria um objeto da classe data.
	 *
	 * @param dia Dia da data
	 * @param mes Mes da data
	 * @param ano Ano da data
	 */
	Data(int dia, int mes, int ano)
	{
		this->dia = dia;
		this->mes = mes;
		this->ano = ano;
	};

	//set_method

	/**
	 * @brief Coloca o parametro dia como o dia da data.
	 * @param dia Dia da data.
	 */
	void setDia(int dia){this->dia = dia;};

	/**
	 * @brief Coloca o parametro mes como o mes da data.
	 * @param mes Mes da data.
	 */
	void setMes(int mes){this->mes = mes;};

	/**
	 * @brief Coloca o parametro ano como o ano da data.
	 * @param ano Ano da data.
	 */
	void setAno(int ano){this->ano = ano;};

	//get_methods

	/**
	 * @brief Vai buscar o dia da data.
	 * @return Retorna um inteiro que indica o dia da data.
	 */
	int getDia() const {return dia;};

	/**
	 * @brief Vai buscar o mes da data.
	 * @return Retorna um inteiro que indica o mes da data.
	 */

	int getMes() const {return mes;};

	/**
	 * @brief Vai buscar o ano da data.
	 * @return Retorna um inteiro que indica o ano da data.
	 */
	int getAno() const {return ano;};

	/**
	 * @brief Verifica se uma data e valida.
	 * @return Retorna um booleano que indica se uma data e valida ou nao.
	 */
	bool validData()
	{
		int maxDia;

		if(mes > 12 || mes < 0 || ano <= 0)
			return false;

		if(mes == 2) //Mes de Fevereiro (considerando sempre anos comuns)
			maxDia = 28;
		else if(mes == 11 || mes == 4 || mes ==  6 || mes == 9) //Meses de Abril, Junho, Setembro e Novembro
			maxDia = 30;
		else //restantes meses
			maxDia = 31;

		if(dia > maxDia && dia <= 0)
			return false;

		return true;
	};


	/**
	 * @brief Operador menor da classe data para comparar duas datas.
	 * @param d data com a qual se vai comparar.
	 * @return Retorna um booleano que indica se a primeira data e menor que a segunda.
	 */
	bool operator<(Data d) const
	{
		if(ano == d.getAno())
		{
			if(mes == d.getMes())
				return dia < d.getDia();
			else
				return mes < d.getMes();
		}
		else
			return ano < d.getAno();
	};

	/**
	 * @brief Operador de igualdade da classe data para comparar duas datas.
	 * @param d data com a qual se vai comparar.
	 * @return Retorna um booleano que indica se a primeira data e igual a segunda.
	 */
	bool operator==(Data d)
	{
		if(dia == d.getDia() && mes == d.getMes() && ano == d.getAno())
			return true;

		return false;
	};
};
#endif //DATA_H_
