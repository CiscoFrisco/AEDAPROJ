#pragma once
/*
 * Praia.h
 */
#ifndef PRAIA_FLUVIAL_H_
#define PRAIA_FLUVIAL_H_

#include "Coordenadas.h"
#include "Servico.h"
#include <string>
#include<vector>

using namespace std;
/**
 * @class Praia_Fluvial
 * @brief Classe com a informacao de cada Praia fluvial.
 * @param concelho Nome do concelho ao qual a praia pertence.
 * @param nome Nome da praia fluvial.
 * @param coordenadas Coordenadas GPS da praia
 * @param servicos Vetor de strings em que cada string representa um servico presente na praia(Nadador Salvador, WC, Bar, etc).
 * @param bandeira_azul Booleano que indica se a praia apresenta ou nao bandeira azul.
 * @param capacidade_max Capacidade maxima da praia.
 */
class Praia_Fluvial {

protected:
	string concelho;
	string nome;
	Coordenadas coordenadas;
	bool bandeira_azul;
	vector<Servico> servicos;
	int capacidade_max;

public:

	//constructors
	/**
	 * @brief Construtor da classe Praia_Fluvial.
	 * @param nome Nome da praia.
	 * @param coordenadas Coordenadas GPS da praia
	 * @param bandeira_azul Booleano que indica se a praia apresenta ou nao bandeira azul.
	 * @param capacidade_max Capacidade maxima da praia.
	 */
	Praia_Fluvial(string concelho, string nome, Coordenadas coordenadas, vector<Servico> servicos, bool bandeira_azul, int capacidade_max);

	//set_methods

	/**
	 * @brief Coloca o parametro nome como o nome do concelho.
	 * @param concelho Nome do concelho.
	 */
	void set_concelho(string concelho);

	/**
	 * @brief Coloca o parametro nome como o nome da praia.
	 * @param nome Nome da praia.
	 */
	void set_nome(string nome);

	/**
	 * @brief Coloca o parametro coordenadas como as coordenadas da praia.
	 * @param coordenadas Coordenadas da praia.
	 */
	void set_coordenadas(Coordenadas coordenadas);

	/**
	 * @brief Coloca o parametro servicos como os servicos da praia.
	 * @param servicos Vetor de strings em que cada string representa um servico presente na praia(Nadador Salvador, WC, Bar, etc).
	 */
	void set_servicos(vector<Servico> servicos);

	/**
	 * @brief Coloca o bandeira_azul como existente ou nao na praia.
	 * @param bandeira_azul Booleano que indica se a praia apresenta ou nao bandeira azul.
	 */
	void set_bandeira_azul(bool bandeira_azul);

	/**
	 * @brief Coloca o parametro capacidade_max como a capacidade maxima da praia.
	 * @param capacidade_max Capacidade maxima da praia.
	 */
	void set_capacidade_max(int capacidade_max);

	//get_methods

	/**
	 * @brief Vai buscar o nome do concelho.
	 * @return Retorna uma string que representa o nome do concelho.
	 */
	string get_concelho() const;

	/**
	 * @brief Vai buscar o nome da praia.
	 * @return Retorna uma string que representa o nome da praia.
	 */
	string get_nome() const;

	/**
	 * @brief Vai buscar as coordenadas da praia.
	 * @return Retorna um objeto que representa as coordenadas da praia.
	 */
	Coordenadas get_coordenadas() const;

	/**
	 * @brief Vai buscar os servicos da praia.
	 * @return Retorna um vetor de strings em que cada string representa um servico presente na praia(Nadador Salvador, WC, Bar, etc).
	 */
	vector<Servico> get_servicos() const;

	/**
	 * @brief Vai buscar o booleano que representa a bandeira_azul da praia.
	 * @return Retorna um booleano que indica se a praia apresenta ou nao bandeira azul.
	 */
	bool get_bandeira_azul() const;

	/**
	 * @brief Vai buscar a capacidade maxima da praia.
	 * @return Retorna a Capacidade maxima da praia.
	 */
	int get_capacidade_max() const;

	//show_methods

	/*
	 * @brief Mostra a informacao da praia
	 */
	virtual void show_informacao_praia() = 0;

	/*
	 * @brief Edita a informacao da praia
	 * @return Retorna uma string com o nome do concelho
	 */
	virtual void editar_praia(string nome_praia, Coordenadas coord, vector<Servico> servs, bool bandeira, int capacidade) = 0;

	/**
	 * @brief Funcao que reescreve a informacao presente na base de dados no ficheiro de texto original com a devida formatacao
	 * @param stream_praias Ofstream para onde e enviada a informacao
	 */
	virtual void escreve_ficheiro_derivadas(ofstream &stream_praias) = 0;

	/*
	 * @brief Mostra os servicos de uma praia
	 */
	void show_servicos_praia();
};

class Praia_FluvialPtr {
public:
	Praia_Fluvial *praia;
	Praia_FluvialPtr(){praia = NULL;};
	bool operator<(Praia_FluvialPtr praia2) const;
};


#endif //PRAIA_FLUVIAL_H_
