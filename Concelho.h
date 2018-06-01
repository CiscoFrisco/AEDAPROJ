/*
 * Concelho.h
 */
#ifndef CONCELHO_H_
#define CONCELHO_H_

#include "BST.h"
#include "Praia_Fluvial.h"
#include "Pontos_Interesse.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @class Concelho
 * @brief Classe com a informacao de cada Concelho.
 * @param nome Nome do Concelho.
 * @param praias Vetor de apontadores de praias. Sao utilizados apontadores porque existem dois tipos de praias fluviais (Praias baseadas em rios ou em albufeiras).
 * @param turismo Vetor de pontos de interesse do ponto de vista turistico.
 * @param turismo Vetor de pontos de interesse do ponto de vista de alojamento.
 * @param turismo Vetor de pontos de interesse do ponto de vista  da restauracao.
 */
class Concelho {

	string nome;
	BST<Praia_FluvialPtr> praias;

	//pontos de interesse
	vector<Turismo> turismo;
	vector<Alojamento> alojamento;
	vector<Restauracao > restauracao;

public:
	//constructors
	/**
	 * @brief Construtor da classe Concelho.
	 * @param line_concelho linha vinda do ficheiro que contem a informa��o de um Concelho.
	 */
	Concelho(string line_concelho);

	/**
	 * @brief Construtor da classe Concelho.
	 */
	Concelho();


	//set_methods

	/**
	 * @brief Coloca o parametro nome como nome do Concelho
	 * @param nome Nome do Concelho
	 */
	void set_nome(string nome);

	/**
	 * @brief Coloca o parametro praias como as praias do Concelho
	 * @param praias Praias do Concelho
	 */
	void set_praias(BST<Praia_FluvialPtr> praias);

	/**
	 * @brief Coloca o parametro turismo como nos pontos de interesse turisticos do Concelho
	 * @param turismo Pontos de interesse turisticos do Concelho
	 */
	void set_turismo(vector<Turismo> turismo);

	/**
	 * @brief Coloca o parametro alojamento como os locais do Concelho caraterizados como alojamento
	 * @param alojamento Pontos de interesse de alojamento do Concelho
	 */
	void set_alojamento(vector<Alojamento> alojamento);

	/**
	 * @brief Coloca o parametro restauracao como os locais de restauracao do Concelho
	 * @param restauracao  Pontos de interesse de restauracao do Concelho
	 */
	void set_restauracao(vector<Restauracao> restauracao);

	//get_methods

	/**
	 * @brief Vai buscar o nome do Concelho
	 * @return Retorna uma string que representa o nome do Concelho
	 */
	string get_nome() const;

	/**
	 * @brief Vai buscar o vetor de praias do Concelho
	 * @return Retorna um vetor de classes em que cada objeto representa uma praia (coordenadas e nome) do Concelho
	 */

	BST<Praia_FluvialPtr> get_praias() const;

	/**
	 * @brief Vai buscar o vetor de praias do Concelho
	 *
	 * Foi adicionda esta função uma vez que a funcao get_praias() nao estava a retornar todas as praias da BST (por razoes que nos desconhecemos).
	 * Esta funcao ao contrario da get_praias(), em vez de retornar uma copia da BST praias, retorna por um apontador a BST original.
	 * @return Retorna um vetor de classes em que cada objeto representa uma praia (coordenadas e nome) do Concelho
	 */
	BST<Praia_FluvialPtr>* getPraias();

	/**
	 * @brief Vai buscar o vetor de locais turisticos do Concelho
	 * @return Retorna um vetor de classes em que cada objeto representa um ponto de interesse turistico do Concelho
	 */
	vector<Turismo > get_turismo() const;

	/**
	 * @brief Vai buscar o vetor de alojamento do Concelho
	 * @return Retorna um vetor classes em que cada objeto representa um ponto de interesse de alojamento do Concelho
	 */
	vector<Alojamento> get_alojamento() const;

	/**
	 * @brief Vai buscar o vetor de restauracao do Concelho
	 * @return Retorna um vetor classes em que cada objetorepresenta um ponto de interesse de restauracao do Concelho
	 */
	vector<Restauracao> get_restauracao() const;

	/**
	 * @brief Vai buscar o vetor de alojamento do Concelho por referência
	 * @return Retorna um vetor classes em que cada objeto representa um ponto de interesse de alojamento do Concelho
	 */
	vector<Alojamento>* getAlojamento();

	/**
	 * @brief Vai buscar o vetor de restauracao do Concelho por referência
	 * @return Retorna um vetor classes em que cada objetorepresenta um ponto de interesse de restauracao do Concelho
	 */
	vector<Restauracao>* getRestauracao();

	//show_methods
	/**
	 * @brief Funcao que mostra as praias presentes num concelho dividindo-as segundo a sua carateristica(albufeira ou rio).
	 */
	void show_praias_concelho();

	/**
	 * @brief Funcao que mostra os locais turisticos presentes num concelho.
	 */
	void show_turismo_concelho();

	/**
	 * @brief Funcao que mostra os locais de alojamento presentes num concelho.
	 */
	void show_alojamento_concelho();

	/**
	 * @brief Funcao que mostra os locais de restauracao presentes num concelho.
	 */
	void show_restauracao_concelho();

	/**
	 * @brief Funcao que mostra a informacao toda de um concelho.Todos os seus pontos de interesse
	 */
	void show_everything();

	/**
	 * @brief Funcao que mostra a informacao dos pontos de interesse (alojamentos ou restauracao) de um concelho que se encontrem abertos.
	 * @param ponto_interesse Tipo de ponto de interesse (1 -> Restauracao, 2 -> Alojamento)
	 */
	void show_abertos(int ponto_interesse);

	/**
	 * @brief Funcao que mostra a informacao dos pontos de interesse (alojamentos ou restauracao) de um concelho que se encontrem fechados.
	 * @param ponto_interesse Tipo de ponto de interesse (1 -> Restauracao, 2 -> Alojamento)
	 */
	void show_fechados(int ponto_interesse);

	/**
	 * @brief Adiciona uma nova praia ao vetor de apontadores para Praias
	 * @param praia Praia que vai ser adicionada ao vetor de praias
	 */
	void add_praia(Praia_FluvialPtr praia);

	/**
	 * @brief Remove uma praia do vetor de praias do concelho em questao
	 * @param praia_index Indice da praia que se pretende remover no vetor de praias
	 */
	void remove_praia(Praia_FluvialPtr praia_a_remover);

};
#endif //CONCELHO_H_
