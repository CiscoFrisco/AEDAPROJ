#pragma once
/*
* Praia_Rio.h
*/
#ifndef PRAIA_RIO_H_
#define PRAIA_RIO_H_

#include "Praia_Fluvial.h"
#include <fstream>

using namespace std;

/**
* @class Praia_Rio
* @brief Classe com a informacao de cada praia baseada num rio. Deriva da classe Praia_Fluvial
* @param largura Largura da praia baseada no rio.
* @param caudal Caudal da praia baseada no rio.
* @param profundidade Profundidade da praia baseada no rio.
*/
class Praia_Rio : public Praia_Fluvial {

	float largura;
	float caudal;
	float profundidade;

public:

	//constructors
	/**
	* @brief Construtor da classe Praia_Rio.
	* @brief Utiliza o construtor da classe Praia_Fluvial e adiciona os parametros referentes as praias baseadas em rios (largura, caudal e profundidade).
	* @param largura Largura da praia baseada no rio.
	* @param caudal Caudal da praia baseada no rio.
	* @param profundidade Profundidade da praia baseada no rio.
	*/
	Praia_Rio(string concelho, string nome, Coordenadas coordenadas, vector<Servico> servicos, bool bandeira_azul, int capacidade_max, float largura, float caudal, float profundidade);

	//set_methods

	/**
	* @brief Coloca o parametro largura como a largura da praia.
	* @param largura Largura da praia.
	*/
	void set_largura(float largura);

	/**
	* @brief Coloca o parametro caudal como o caudal da praia.
	* @param caudal Caudal da praia.
	*/
	void set_caudal(float caudal);

	/**
	* @brief Coloca o parametro profundidade como a profundidade da praia.
	* @param profundidade Profundidade da praia.
	*/
	void set_profundidade(float profundidade);

	//get_methods

	/**
	* @brief Vai buscar a largura da praia.
	* @return Retorna um float que representa a largura da praia.
	*/
	float get_largura() const;

	/**
	* @brief Vai buscar o caudal da praia.
	* @return Retorna um float que representa o caudal da praia.
	*/
	float get_caudal() const;

	/**
	* @brief Vai buscar a profundidade da praia.
	* @return Retorna um float que representa a profundidade da praia.
	*/
	float get_profundidade() const;

	//show_methods
	/**
	* @brief Funcao que mostra a informacao de uma praia baseada num rio.
	*/
	void show_informacao_praia();

	/*
	* @brief Edita a informacao de  uma praia baseada num rio
	*/
	void editar_praia(string nome_praia, Coordenadas coord, vector<Servico> servs, bool bandeira, int capacidade);

	/**
	 * @brief Funcao chamada pela funcao que trata da reescrita dos ficheiros e que vai passar para a ofstream os atributos desta classe derivada
	 * @param stream_praias Ofstream que recebe os atributos da classe derivada
	 */
	void escreve_ficheiro_derivadas(ofstream &stream_praias);
};

#endif //PRAIA_RIO_H_
