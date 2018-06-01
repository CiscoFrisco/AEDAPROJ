#pragma once
#ifndef GUIA_DE_PRAIAS_H_
#define GUIA_DE_PRAIAS_H_

#include "Concelho.h"
#include <string>
#include <vector>
#include "ExceptionHandling.h"
#include "Praia_Fluvial.h"
#include "Praia_Rio.h"
#include "Praia_Albufeira.h"
#include "Pontos_Interesse.h"
#include <unordered_set>
#include "Inspecoes.h"

using namespace std;

struct eqAloj {
	bool operator() (const Alojamento &pf1, const Alojamento &pf2) const {
		return pf1.get_nome()== pf2.get_nome();
	}
};

struct eqRest {
	bool operator() (const Restauracao &pf1, const Restauracao &pf2) const {
		return pf1.get_nome()== pf2.get_nome();
	}
};

struct hAloj {
	int operator() (const Alojamento &pf1) const {
		string s1=pf1.get_nome();
		int v = 0;
		for ( unsigned int i=0; i< s1.size(); i++ )
			v = 37*v + s1[i];
		return v;
	}
};

struct hRest {
	int operator() (const Restauracao &pf1) const {
		string s1=pf1.get_nome();
		int v = 0;
		for ( unsigned int i=0; i< s1.size(); i++ )
			v = 37*v + s1[i];
		return v;
	}
};


typedef unordered_set<Alojamento, hAloj, eqAloj> HashTabFechadosAloj;
typedef unordered_set<Restauracao, hRest, eqRest> HashTabFechadosRest;




/**
 * @class Guia_de_Praias
 * @brief Classe que contem todas as outras classes e onde estao implementados os metodos principais deste projeto
 * @param nome Nome do objeto.
 * @param concelhos Vetor concelhos em que cada elemento e um concelho.
 */
class Guia_de_Praias {

	string nome;

	vector<Concelho> concelhos;

	HashTabFechadosAloj aloj_fechados;
	HashTabFechadosRest rest_fechados;

	vector<Inspecoes> inspecoes;

public:

	//constructor
	/**
	 * @brief Construtor da classe Guia_de_Praias.
	 * @param nome Nome do guia.
	 * @param fichconcelhos Ficheiro onde tem a informacao sobre cada Concelho.
	 * @param fichpraias Ficheiro onde tem a informacao sobre as praias de cada Concelho.
	 */
	Guia_de_Praias(string nome, string fichconcelhos, string fichpraias, string fich_hash, Data *curr_data);

	//set_methods

	/**
	 * @brief O parametro concelhos e atribuido ao atributo concelhos do guia de praias.
	 * @param concelhos Vetor de concelhos.
	 */
	void set_concelhos(vector<Concelho> concelhos);

	void set_aloj_fechados(HashTabFechadosAloj aloj_fechados);

	void set_rest_fechados(HashTabFechadosRest rest_fechados);

	void set_inspecoes(vector<Inspecoes> inspecoes);

	//get_methods

	/**
	 * @brief Vai buscar os concelhos do guia de praias.
	 * @return Retorna um vetor de concelhos do guia de praias.
	 */
	vector<Concelho> get_concelhos() const;

	HashTabFechadosAloj get_aloj_fechados() const;

	HashTabFechadosRest get_rest_fechados() const;

	vector<Inspecoes> get_inspecoes() const;

	//search_methods

	/**
	 * @brief Esta funcao recebe um tipo de local que refere o tipo de Ponto de Iteresse(Turismo, Alojamento, Restauracao ou Praia_Fluvial) e chama
	 * a funcao search_pontos_de interesse_proximos com um vetor do tipo de Ponto de Interesse recebido.
	 * Esse vetor tem todos os pontos de interesse desse tipo presentes na base de dados.
	 * @param tipo_de_local Inteiro que indica o tipo de local
	 */
	void search_ponto_interesse_proximos_auxiliar(int tipo_de_local);

	/**
	 * @brief Esta funcao pesquisa as praias mais proximas de uma praia. Equivalente a funcao search_pontos_interesse_proximos()
	 * @brief Esta funcao foi criada devido ao diferente tipo de acesso necessario para as praias em reelacao aos pontos de interesse
	 * @param praias_totais Vetor com todas as praias de todos os concelhos.
	 * @param coord_praia Coordenadas em relacao as quais se vai gerar um vetor com locais proximos destas
	 * @param nome_praia Nome da praia em relacao a qual se calculam as praias proximas
	 */
	void search_pontos_interesse_proximos_versao_praias(BST<Praia_FluvialPtr> praias_totais, Coordenadas coord_praia, string nome_praia);


	/**
	 * @brief Esta funcao pesquisa os pontos de interesse mais proximos de uma praia.
	 * @param locais_totais Vetor com todos os pontos de interesse (Alojamento, Restauracao ou Turismo) de um determinado tipo
	 * @param coord_praia Coordenadas em relacao as quais se vai gerar um vetor com locais proximos destas
	 * @param tipo_de_local Indica o tipo de ponto de interesse
	 * @param nome_praia Nome da praia em relacao a qual se calculam os locais proximos
	 */
	template<class T>
	void search_pontos_interesse_proximos(vector<T> locais_totais, Coordenadas coord_praia, int tipo_de_local, string nome_praia);

	/**
	 * @brief Esta funcao pesquisa a praia mais proxima de um dado local.
	 * @param ponto_interesse  String que representa o ponto de interesse de referencia para encontrar a praia mais praxima.
	 */
	void search_praia_mais_proxima(int tipo_de_local);

	/**
	 * @brief Esta funcao verifica se as duas coordenadas estao dentro do limite de proximidade (aproximadamente 50 km ou  0.47672 em graus decimais)
	 * @param coord1 Coordenadas de um dos locais
	 * @param coord2 Coordenadas do outro local a comparar
	 * @return Retorna um booleano que indica se as duas coordenadas estao proximas(true) ou nao(false)
	 */
	bool esta_proximo(Coordenadas coord1, Coordenadas coord2);


	//sort method

	/**
	 * @brief Funcao que ordena um vetor de classes (Turismo,Restauracao, Alojamento).
	 * @param ponto_interesse Vetor a ser ordenado, passado por referencia.
	 */
	template<class T>
	void sort_pontos_interesse(vector<T> &ponto_interesse, Coordenadas coord);

	/**
	 * @brief Funcao que ordena um vetor de Praias. Semelhante a funcao sort_pontos_interesse.
	 * @brief Esta funcao foi criada devido ao diferente acesso aos atributos das praias em relacao ao pontos de interesse.
	 * @param praias Vetor a ser ordenado, passado por referencia.
	 */

	void sort_praias(vector<Praia_Fluvial*> &praias, Coordenadas coord);

	//show_methods

	/**
	 * @brief Funcao que mostra todas as praias presentes na base de dados agrupadas por concelho.
	 */
	void show_praias();

	/**
	 * @brief Funcao que mostra todos os concelhos presentes na base de dados.
	 */
	void show_concelhos();

	/**
	 * @brief Funcao que mostra os pontos de interesse de um concelho selecionados pelo utilizador (apenas chama funcoes que fazem o show na classe Concelho).
	 * @param praia String que representa o nome do concelho do qual se quer visualizar a informacao.
	 */
	void show_informacao_concelho(int ponto_de_interesse);

	/**
	 * @brief Funcao que mostra a informacao de uma praia.
	 */
	void show_informacao_praia();

	/**
	 * @brief Funcao que adiciona uma praia ao vetor de praias de um concelho. Caso a praia ja exista em qualquer um dos concelhos, lanca uma excecao
	 * @param tipo Tipo de praia que vai adicionar (Albufeira ou Rio)
	 */
	void add_praia(int tipo);

	/**
	 * @brief Funcao que adiciona um concelho ao vetor de concelhos do guia de praias. Caso o concelho ja exista no vetor, lanca uma excecao
	 */
	void add_concelho();

	/**
	 * @brief Funcao que remove uma praia ao vetor de praias de um concelho. Caso a praia nao exista no vetor, lanca uma excecao
	 */
	void remove_praia();

	/**
	 * @brief Funcao que remove um concelho do vetor de concelhos. Caso o concelho nao exista no vetor, lanca uma excecao
	 */
	void remove_concelho();

	/**
	 * @brief Funcao que pede ao utilizador para editar uma praia. Caso a praia nao exista, lanca uma excecao
	 */
	void editar_praia();

	/**
	 * @brief Funcao que pede ao utilizador para editar um concelho. Caso o concelho nao exista, lanca uma excecao
	 */
	void editar_concelho();

	/**
	 * @brief Funcao que le o ficheiro de praias e constroi as praias
	 * @param line_praia String que contem uma linha do ficheiro de praias com a informacao de uma praia
	 */
	void read_praias_file(string line_praia);

	/**
	 * @brief Funcao que le o ficheiro de hash e atualiza os pontos de interesse com os dados respetivos
	 * @param hash String que contem uma linha do ficheiro de hash com dados de abertura e fecho de pontos de interesse
	 */
	void read_hash_file(string hash_line);

	/**
	 * @brief Funcao que guarda as alteracoes feitas pelo utilizador nos ficheiros correspondentes
	 * @param nome_ficheiro_concelhos Ficheiro que contem os concelhos
	 * @param nome_ficheiro_concelhos Ficheiro que contem as praias
	 */
	void guardar_ficheiros(string nome_ficheiro_concelhos, string nome_ficheiro_praias, string nome_ficheiro_hash, Data curr_data);

	void fechar_alojamento(Data current_data);

	void fechar_restauracao(Data current_data);

	void reabrir_alojamento();

	void reabrir_restauracao();

	void avanca_data(Data *current_data);

	void add_inspecao(Data *current_data);

	void show_inspecao_geral();

	void show_inspecao_concelho();

	void show_inspecao_praia();

	string pergunta_tipo();

	void show_inspecao_tipo(string tipo);
};

/**
 * @brief Funcao que verifica se as coordenadas sao validas
 * @param coordenada String que cont�m as coordenadas
 * @param tipo Se a coordenada e latitude ou longitude para verificar os intervalos validos destas
 */
bool valid_coordinates(string coordenada, string tipo);

#endif //GUIA_DE_PRAIAS_H_
