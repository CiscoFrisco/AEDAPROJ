#pragma once
/*
 * Praia_Albufeira.h
 */
#ifndef PRAIA_ALBUFEIRA_H_
#define PRAIA_ALBUFEIRA_H_

#include "Praia_Fluvial.h"
#include <fstream>

using namespace std;

/**
 * @class Praia_Albufeira
 * @brief Classe com a informacao de cada praia baseada numa albufeira. Deriva da classe Praia_Fluvial
 * @param area_aquatica Area aquatica da Praia.
 */
class Praia_Albufeira : public Praia_Fluvial {

	float area_aquatica;

public:
	//constructors
	/**
	 * @brief Construtor da classe Praia_Albufeira.
	 * @brief Utiliza o construtor da classe Praia_Fluvial e adiciona os parametros referentes as praias baseadas em albufeiras (area aquatica).
	 * @param area_aquatica Area aquatica da Praia.
	 */
	Praia_Albufeira(string concelho, string nome, Coordenadas coordenadas, vector<Servico> servicos, bool bandeira_azul, int capacidade_max, float area_aquatica);


	//set_method

	/**
	 * @brief Coloca o parametro area_aquatica como a area aquatica da praia.
	 * @param area_aquatica Area aquatica da praia.
	 */
	void set_area_aquatica(float area_aquatica);

	//get_methods

	/**
	 * @brief Vai buscar a area aquatica da praia.
	 * @return Retorna um float que representa a area aquatica da praia.
	 */
	float get_area_aquatica() const;

	//show_methods
	/**
	 * @brief Funcao que mostra a informacao de uma praia baseada numa albufeira.
	 */
	void show_informacao_praia();

	/*
	 * @brief Edita a informacao da praia
	 */
	void editar_praia(string nome_praia, Coordenadas coord, vector<Servico> servs, bool bandeira, int capacidade);

	/**
	 * @brief Funcao chamada pela funcao que trata da reescrita dos ficheiros e que vai passar para a ofstream os atributos da classe derivada
	 * @param stream_praias Ofstream que recebe os atributos da classe derivada
	 */
	void escreve_ficheiro_derivadas(ofstream &stream_praias);
};
#endif //PRAIA_ALBUFEIRA_H_
