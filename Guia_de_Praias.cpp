#include "Guia_de_Praias.h"
#include <fstream>
#include <sstream>


////////////////
//constructors//////////////////

Guia_de_Praias::Guia_de_Praias(string nome, string fichconcelhos, string fichpraias, string fich_hash, Data *curr_data) : nome(nome)
{
	ifstream fichconcelhos_file;

	//Abrir ficheiro de concelhos, se falhar encerra programa com erro

	fichconcelhos_file.open(fichconcelhos);
	if (fichconcelhos_file.fail())
	{
		cerr << "O ficheiro de Concelhos nao pode ser aberto. Verifique o nome e tente de novo\n";
		exit(1);
	}
	while (!fichconcelhos_file.eof())
	{
		string linha_concelho = "";
		getline(fichconcelhos_file, linha_concelho);
		Concelho concelho(linha_concelho);
		//fichconcelhos_file.ignore(1);
		concelhos.push_back(concelho);
	}

	//Fecha ficheiro
	fichconcelhos_file.close();

	//abertura do ficheiro de praias

	ifstream fichpraias_file;

	//Abrir ficheiro de concelhos, se falhar encerra programa com erro

	fichpraias_file.open(fichpraias);

	if (fichpraias_file.fail())
	{
		cerr << "O ficheiro de Praias nao pode ser aberto. Verifique o nome e tente de novo\n";
		exit(1);
	}

	fichpraias_file.ignore(1000, '\n');

	while (!fichpraias_file.eof())
	{
		string linha_praia = "";
		getline(fichpraias_file, linha_praia);
		if(linha_praia != "END")
			read_praias_file(linha_praia);
		//fichpraias_file.ignore(1);
	}

	//Fecha ficheiro
	fichpraias_file.close();

	//abertura do ficheiro de praias

	ifstream fich_hash_file;

	//Abrir ficheiro de concelhos, se falhar encerra programa com erro

	fich_hash_file.open(fich_hash);

	if (fich_hash_file.fail())
	{
		cerr << "O ficheiro de Hash nao pode ser aberto. Verifique o nome e tente de novo\n";
		exit(1);
	}

	string linha_hash = "";
	int dia, mes, ano;
	char barra;

	getline(fich_hash_file, linha_hash);

	stringstream hash_stream(linha_hash);

	hash_stream >> dia >> barra >> mes >> barra >> ano;

	curr_data->setDia(dia);
	curr_data->setMes(mes);
	curr_data->setAno(ano);

	while (!fich_hash_file.eof())
	{
		linha_hash = "";
		getline(fich_hash_file, linha_hash);
		if(linha_hash != "END")
			read_hash_file(linha_hash);
		//fichpraias_file.ignore(1);
	}

	//Fecha ficheiro
	fichpraias_file.close();
}

void Guia_de_Praias::read_praias_file(string line_praia)
{
	stringstream praia_stream(line_praia); //stringstream com a linha que contém a informacao da praia

	//strings que vão inicializar os argumentos do objeto
	string concelho, nome_praia;
	string servico_tipo, servico_nome;
	int tipo, bandeira, largura, caudal, profundidade, area, capacidade;
	long double latitude, longitude; // coordenadas

	vector<Servico> servs; //vetor de serviços

	bool bandeira_bool; //bandeira azul
	//carateres de separacao da stringstream
	char  parentesis, character, p_virgula, virgula;

	Praia_FluvialPtr praia;
	character = praia_stream.get();
	//lê o concelho da stringstream
	while (character != ';') {
		concelho += character;
		character = praia_stream.get();
	}

	// ignora tudo o que foi lido até agora
	praia_stream.ignore();

	character = praia_stream.get();

	//vai buscar à stringstream o nome da praia
	while (character != ';') {
		nome_praia += character;
		character = praia_stream.get();
	}
	//elimina os espaços
	nome_praia.erase(nome_praia.size() -1);
	nome_praia.erase(0, 0);

	// ignora tudo o que foi lido até agora
	praia_stream.ignore();

	praia_stream >> capacidade >> p_virgula >> latitude >> virgula >> longitude >> p_virgula >> bandeira >> p_virgula;

	//se a bandeira for 1 a praia possui bandeira azul
	if (bandeira == 1)
		bandeira_bool = true;
	else
		bandeira_bool = false;

	//ignora tudo o que foi lido até agora
	//praia_stream.ignore();
	//character = praia_stream.get();

	//lê os servicos da stringstream e coloca no vetor de serviços

	while (true)
	{
		servico_tipo = "";
		servico_nome = "";

		praia_stream >> parentesis;

		praia_stream.ignore();
		character = praia_stream.get();

		//parentesis significam que a seguir vêm as coordenadas
		while (character != '/')
		{
			servico_tipo += character;
			character = praia_stream.get();
		}
		//elimina os espaços
		servico_tipo.erase(servico_tipo.size() - 1);

		praia_stream.ignore();
		character = praia_stream.get();

		while (character != ')')
		{
			servico_nome += character;
			character = praia_stream.get();
		}
		//elimina os espaços
		servico_nome.erase(servico_nome.size() - 1);

		//fazer push_back ao vetor de turismo
		servs.push_back(Servico(servico_tipo, servico_nome));

		praia_stream.ignore();
		character = praia_stream.get();

		//ponto e virgula assinala o fim dos pontos de interesse turísticos
		if (character == ';')
			break;
	}

	praia_stream >> tipo >> p_virgula;

	//cria uma praia baseada num rio
	if (tipo == 1)
	{
		praia_stream >> largura >> p_virgula >> caudal >> p_virgula >> profundidade >> p_virgula;
		praia.praia = new Praia_Rio(concelho, nome_praia, Coordenadas(latitude, longitude), servs, bandeira_bool, capacidade, largura, caudal, profundidade);
	}
	else
	{
		praia_stream >> area >> p_virgula;
		praia.praia = new Praia_Albufeira(concelho, nome_praia, Coordenadas(latitude, longitude), servs, bandeira_bool, capacidade, area);
	}
	//coloca a praia dentro do concelho que lhe corresponde
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		if (concelhos.at(i).get_nome() == praia.praia->get_concelho())
		{
			concelhos.at(i).add_praia(praia);
			break;
		}
	}
}


void Guia_de_Praias::read_hash_file(string hash_line)
{
	stringstream hash_stream(hash_line);

	string ponto_interesse;
	char  barra, p_virgula;
	char character = hash_stream.get();
	int dia, mes, ano; //para ler do ficheiro os atributos da data
	Data fecho, abertura; //datas que vão ser retiradas do ficheiro
	bool found = false; // booleano que indica se encontrou o ponto de interesse ou não

	while (character != ';')
	{
		ponto_interesse += character;
		character = hash_stream.get();
	}

	hash_stream.ignore();

	hash_stream >> dia >> barra >> mes >> barra >> ano >> p_virgula;
	fecho = Data(dia,mes,ano);

	hash_stream.ignore();

	hash_stream >> dia >> barra >> mes >> barra >> ano >> p_virgula;
	abertura = Data(dia, mes, ano);

	for(unsigned int i = 0; i < concelhos.size(); i++)
	{

		//pesquisa o ponto de interesse dentro dos vetores de alojamentos e de restauração do concelho e quando encontra sai
		for(unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
		{
			if(concelhos.at(i).get_alojamento().at(j).get_nome() == ponto_interesse)
			{
				found = true;
				concelhos.at(i).getAlojamento()->at(j).set_aberto(false);
				concelhos.at(i).getAlojamento()->at(j).set_data_fecho(fecho);
				concelhos.at(i).getAlojamento()->at(j).set_data_abertura(abertura);
				break;
			}
		}

		if(found)
			break;

		for(unsigned int j = 0; j < concelhos.at(i).get_restauracao().size(); j++)
		{
			if(concelhos.at(i).get_restauracao().at(j).get_nome() == ponto_interesse)
			{
				found = true;
				concelhos.at(i).getRestauracao()->at(j).set_aberto(false);
				concelhos.at(i).getRestauracao()->at(j).set_data_fecho(fecho);
				concelhos.at(i).getRestauracao()->at(j).set_data_abertura(abertura);
				break;
			}
		}

		if(found)
			break;
	}
}
///////////////
//set_methods//
///////////////

void Guia_de_Praias::set_concelhos(vector<Concelho> concelhos)
{
	this->concelhos = concelhos;
}

void Guia_de_Praias::set_aloj_fechados(HashTabFechadosAloj fechados)
{
	this->aloj_fechados = fechados;
}

void Guia_de_Praias::set_rest_fechados(HashTabFechadosRest fechados)
{
	this->rest_fechados = fechados;
}

void Guia_de_Praias::set_inspecoes(vector<Inspecoes> inspecoes)
{
	this->inspecoes = inspecoes;
}

///////////////
//get_methods//
///////////////

vector<Concelho> Guia_de_Praias::get_concelhos() const
{
	return concelhos;
}


HashTabFechadosAloj Guia_de_Praias::get_aloj_fechados() const
{
	return aloj_fechados;
}

HashTabFechadosRest Guia_de_Praias::get_rest_fechados() const
{
	return rest_fechados;
}

vector<Inspecoes> Guia_de_Praias::get_inspecoes() const
{
	return inspecoes;
}
/////////////////
//other methods//
/////////////////

bool Guia_de_Praias::esta_proximo(Coordenadas coord1, Coordenadas coord2)
{
	//se estiver num raio de 50km (o valor 0.47672) são os valores de 50km  em coordenadas decimais
	if (coord1.distancia_entre_coord(coord2) <= 0.47672)
		return true;

	return false;
}

template<class T>
void Guia_de_Praias::sort_pontos_interesse(vector<T> &ponto_interesse, Coordenadas coord)
{
	//calcular as distancias de cada praia do vetor praias às coordenadas apresentadas como argumento e colocar no vetor de distancias
	vector<long double> dist;
	long double distancia;
	cout << ponto_interesse.size() << endl;
	for(unsigned int i = 0; i < ponto_interesse.size(); i++)
	{
		distancia = ponto_interesse.at(i).get_coordenadas().distancia_entre_coord(coord);
		dist.push_back(distancia);
	}
	for (unsigned int i = ponto_interesse.size() - 1; i > 0; i--)
	{
		bool troca = false;

		for (unsigned int j = 0; j < i; j++)
		{
			if (dist.at(j + 1) < dist.at(j))
			{
				swap(dist.at(j), dist.at(j + 1));
				swap(ponto_interesse.at(j), ponto_interesse.at(j + 1));
				troca = true;
			}
		}
		if (!troca) return;
	}
}

void Guia_de_Praias::sort_praias(vector<Praia_Fluvial*> &praias, Coordenadas coord)
{
	//calcular as distancias de cada praia do vetor praias às coordenadas apresentadas como argumento e colocar no vetor de distancias
	vector<long double> dist;
	long double distancia;
	for(unsigned int i = 0; i < praias.size(); i++)
	{
		distancia = praias.at(i)->get_coordenadas().distancia_entre_coord(coord);
		dist.push_back(distancia);
	}

	for (unsigned int i = praias.size() - 1; i > 0; i--)
	{
		bool troca = false;

		for (unsigned int j = 0; j < i; j++)
		{
			if (dist.at(j + 1) < dist.at(j))
			{
				swap(dist.at(j), dist.at(j + 1));
				swap(praias.at(j), praias.at(j + 1));
				troca = true;
			}
		}
		if (!troca) return;
	}
}

void Guia_de_Praias::search_ponto_interesse_proximos_auxiliar(int tipo_de_local)
{

	show_praias();

	string nome_praia; //string que contem o nome da praia

	Coordenadas coord_praia; // variavel que guarda as coordenadas da praia inserida para mais tarde comparar com as coordenadas dos pontos de interesse

	cout << "Introduza o nome da Praia: ";
	getline(cin, nome_praia);
	cout << endl;

	bool found = false; //booleano que indica se encontrou o nome da praia ou não

	//ciclo que pesquisa o nome da praia nos concelhos até encontrar a praia com nome igual ao inserido pelo utilizado se não encontrar lança uma exceção
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

		BSTItrIn<Praia_FluvialPtr> it(*praias);

		while(!it.isAtEnd())
		{
			Praia_FluvialPtr praia_atual = it.retrieve();

			if(praia_atual.praia->get_nome() == nome_praia)
			{
				coord_praia = praia_atual.praia->get_coordenadas();
				found = true;
				break;
			}

			it.advance();
		}

		if (found)
			break;
	}
	if (!found)
		throw(PraiaNaoExistente(nome_praia));

	//se nenhuma exceção ocorrer então o programa segue e cria um vetor com todos os pontos de interesse que o utilizador quer visualizar(de acordo com o argumento da função)
	if (tipo_de_local == 1)
	{
		//criar um vetor que vai ter todos os alojamentos de todos os concelhos
		vector<Alojamento> aloj_totais;
		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			for (unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
				if(concelhos.at(i).get_alojamento().at(j).get_aberto() == true)
					aloj_totais.push_back(concelhos.at(i).get_alojamento().at(j));
		}

		//chama a funcao que calcula e mostra os pontos de interesse mais proximos da praia inserida
		search_pontos_interesse_proximos<Alojamento>(aloj_totais, coord_praia, tipo_de_local, nome_praia);
	}

	else if (tipo_de_local == 2)
	{
		//criar um vetor que vai ter todos os restaurantes de todos os concelhos
		vector<Restauracao> rest_totais;
		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			for (unsigned int j = 0; j < concelhos.at(i).get_restauracao().size(); j++)
				if(concelhos.at(i).get_restauracao().at(j).get_aberto() == true)
					rest_totais.push_back(concelhos.at(i).get_restauracao().at(j));
		}

		//chama a funcao que calcula e mostra os pontos de interesse mais proximos da praia inserida
		search_pontos_interesse_proximos<Restauracao>(rest_totais, coord_praia, tipo_de_local, nome_praia);
	}

	else if (tipo_de_local == 3)
	{
		//criar um vetor que vai ter todos os pontos turisticos de todos os concelhos
		vector<Turismo> tur_totais;
		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			for (unsigned int j = 0; j < concelhos.at(i).get_turismo().size(); j++)
				tur_totais.push_back(concelhos.at(i).get_turismo().at(j));
		}

		//chama a funcao que calcula e mostra os pontos de interesse mais proximos da praia inserida
		search_pontos_interesse_proximos<Turismo>(tur_totais, coord_praia, tipo_de_local, nome_praia);
	}

	else if (tipo_de_local == 4)
	{
		//criar um vetor que vai ter todas as praias de todos os concelhos

		Praia_FluvialPtr null_praia = Praia_FluvialPtr();
		BST<Praia_FluvialPtr> praias_totais(null_praia);

		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

			BSTItrIn<Praia_FluvialPtr> it(*praias);

			while(!it.isAtEnd())
			{
				Praia_FluvialPtr praia_atual = it.retrieve();

				praias_totais.insert(praia_atual);

				it.advance();
			}
		}

		//chama a funcao que calcula e mostra os pontos de interesse mais proximos da praia inserida
		search_pontos_interesse_proximos_versao_praias(praias_totais, coord_praia, nome_praia);
	}
}

void Guia_de_Praias::search_pontos_interesse_proximos_versao_praias(BST<Praia_FluvialPtr> praias_totais, Coordenadas coord_praia, string nome_praia)
{
	vector<Praia_Fluvial*> praias_proximas;

	//o vetor vindo da função anterior (search_pontos_interesse_proximos_auxiliar) é filtrado para o vetor praias_proximas
	//e apenas os pontos de interesse próximos são visualizados
	BSTItrIn<Praia_FluvialPtr> it(praias_totais);

	while(!it.isAtEnd())
	{
		Praia_FluvialPtr praia_atual = it.retrieve();

		if (esta_proximo(coord_praia, praia_atual.praia->get_coordenadas()))
		{
			praias_proximas.push_back(praia_atual.praia);
		}

		it.advance();
	}

	//sort do vetor de praias próximas por ordem crescente de distância
	if(praias_proximas.size() > 1)
		sort_praias(praias_proximas, coord_praia);

	cout << "Praias proximas da " << nome_praia << " (" << coord_praia.get_latitude() << ", " << coord_praia.get_longitude() << ") num raio de 50km:" << endl << endl;


	for (unsigned int i = 0; i < praias_proximas.size(); i++)
	{
		if(praias_proximas.at(i)->get_nome() != nome_praia)
		{
			cout << praias_proximas.at(i)->get_nome() << " - " << "latitude: " << praias_proximas.at(i)->get_coordenadas().get_latitude();
			cout << ", longitude: " << praias_proximas.at(i)->get_coordenadas().get_latitude() << endl;
		}
	}

	if(praias_proximas.size() > 1)
		cout << endl << "Os locais mostrados estao por ordem crescente de distancia em relacao a  praia " << nome_praia << endl;
	else if(praias_proximas.size() == 0)
		cout << "Nao foram encontradas praias perto da " << nome_praia << " num raio de aproximadamente 50 km." << endl;
}

template <class T>
void Guia_de_Praias::search_pontos_interesse_proximos(vector<T> locais_totais, Coordenadas coord_praia, int tipo_de_local, string nome_praia)
{
	vector<T> locais_proximos;
	//o vetor vindo da função anterior (search_pontos_interesse_proximos_auxiliar) é filtrado para o vetor locais_proximos
	//e apenas os pontos de interesse próximos são visualizados
	for (unsigned int i = 0; i < locais_totais.size(); i++)
	{
		if (esta_proximo(coord_praia, locais_totais.at(i).get_coordenadas()))
		{
			locais_proximos.push_back(locais_totais.at(i));
		}
	}

	//sort do vetor de praias próximas por ordem crescente de distância
	if(locais_proximos.size() > 1)
		sort_pontos_interesse<T>(locais_proximos, coord_praia);

	//display dos locais próximos por ordem crescente de distância
	switch (tipo_de_local)
	{
	case 1:
		cout << "Alojamentos ";
		break;
	case 2:
		cout << "Restaurantes ";
		break;
	case 3:
		cout << "Pontos Turisticos ";
		break;
	}

	cout << "proximos da " << nome_praia << " (" << coord_praia.get_latitude() << ", " << coord_praia.get_longitude() << ") num raio de 50 km:" << endl << endl;

	for (unsigned int i = 0; i < locais_proximos.size(); i++)
	{
		cout << locais_proximos.at(i).get_nome() << " - " << "latitude: " << locais_proximos.at(i).get_coordenadas().get_latitude();
		cout << ", longitude: " << locais_proximos.at(i).get_coordenadas().get_longitude() << endl;
	}

	if(locais_proximos.size() > 1)
		cout << endl << "Os locais mostrados estao por ordem crescente de distancia em relacao a  praia " << nome_praia << endl;
	else if(locais_proximos.size() == 0)
		cout << "Nao foram encontrados pontos de interesse perto da " << nome_praia << " num raio de aproximadamente 50 km." << endl;


	return;
}


void Guia_de_Praias::search_praia_mais_proxima(int tipo_de_local) {

	string nome_ponto_interesse; //string que contem o nome da praia

	//caso o utilizador queira visualizar praias os vetores usados para as armazenar já não vão ser os anteriores, mas estes seguintes (pois vão ser vetores de apontadores)
	vector<Praia_Fluvial*> praias_totais;

	Praia_Fluvial* praia_mais_proxima; // praia que vai ser mostrada no ecrã como resultado desta função

	Coordenadas coord_ponto_interesse; // variavel que guarda as coordenadas da praia inserida para mais tarde comparar com as coordenadas dos pontos de interesse

	string latitude, longitude; //parametros usados caso o utilizador tenha selecionado opção de escolher a praia mais proxima de um ponto de interesse aleatório(selecionar por coordenadas)


	if (tipo_de_local == 1)
		cout << "Introduza o nome do Alojamento: ";
	else if (tipo_de_local == 2)
		cout << "Introduza o nome do Restaurante: ";
	else if (tipo_de_local == 3)
		cout << "Introduza o nome do Ponto Turístico: ";
	else if (tipo_de_local == 4)
		cout << "Introduza o nome da Praia: ";
	else
		cout << "Introduza as coordenadas: ";

	if (tipo_de_local == 5)
	{
		cout << endl << "Latitude: ";
		getline(cin, latitude);

		while (!valid_coordinates(latitude, "latitude"))
		{
			cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
			getline(cin, latitude);
		}

		cout << endl << "Longitude: ";
		getline(cin, longitude);

		while (!valid_coordinates(longitude, "longitude"))
		{
			cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
			getline(cin, longitude);
		}
	}

	else
		getline(cin, nome_ponto_interesse);

	cout << endl;

	bool found = false; //booleano que indica se encontrou ponto de interesse ou não

	//procura o alojamento no vetor de alojamentos de cada concelho
	if (tipo_de_local == 1)
	{
		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			for (unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
			{

				if (concelhos.at(i).get_alojamento().at(j).get_nome() == nome_ponto_interesse)
				{
					coord_ponto_interesse = concelhos.at(i).get_alojamento().at(j).get_coordenadas();
					found = true;
					break;
				}
			}

			if (found)
				break;
		}
	}

	//procura o restaurante no vetor de restaurantes de cada concelho
	else if (tipo_de_local == 2)
	{
		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			for (unsigned int j = 0; j < concelhos.at(i).get_restauracao().size(); j++)
			{

				if (concelhos.at(i).get_restauracao().at(j).get_nome() == nome_ponto_interesse)
				{
					coord_ponto_interesse = concelhos.at(i).get_restauracao().at(j).get_coordenadas();
					found = true;
					break;
				}
			}

			if (found)
				break;
		}
	}

	//procura o ponto de interesse turistico no vetor de turismo de cada concelho
	else if (tipo_de_local == 3)
	{
		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			for (unsigned int j = 0; j < concelhos.at(i).get_turismo().size(); j++)
			{

				if (concelhos.at(i).get_turismo().at(j).get_nome() == nome_ponto_interesse)
				{
					coord_ponto_interesse = concelhos.at(i).get_turismo().at(j).get_coordenadas();
					found = true;
					break;
				}
			}

			if (found)
				break;
		}
	}

	//procura a praia no vetor de praias de cada concelho
	else if (tipo_de_local == 4)
	{
		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

			BSTItrIn<Praia_FluvialPtr> it(*praias);

			while(!it.isAtEnd())
			{
				Praia_FluvialPtr praia_atual = it.retrieve();

				if (praia_atual.praia->get_nome() == nome_ponto_interesse)
				{
					coord_ponto_interesse = praia_atual.praia->get_coordenadas();
					found = true;
					break;
				}
				it.advance();
			}

			if (found)
				break;
		}
	}


	else if (tipo_de_local == 5)
		coord_ponto_interesse = Coordenadas(stold(latitude), stold(longitude));

	else
	{
		//se não encontrar o ponto de interesse em nenhum dos vetores de cada concelho faz throw de uma exceção
		if (!found)
			throw(PontoInteresseNaoExistente(nome_ponto_interesse));
	}

	//se nenhuma exceção ocorrer então o programa segue e cria um vetor com todas as praias de todos os concelhos
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

		BSTItrIn<Praia_FluvialPtr> it(*praias);

		while(!it.isAtEnd())
		{
			Praia_FluvialPtr praia_atual = it.retrieve();

			praias_totais.push_back(praia_atual.praia);

			it.advance();
		}
	}


	//procura a praia mais próxima do ponto de interesse/praia/coordenada aleatória.
	int dist_min_index = 0; //vai guardaro índice do ponto que está mais perto

	for (unsigned int i = 0; i < praias_totais.size(); i++)
	{
		//compara o ponto atual com o ponto que está mais perto e se o primeiro estiver mais perto atualiza o dist_min_index
		if (praias_totais.at(i)->get_coordenadas().distancia_entre_coord(coord_ponto_interesse) < praias_totais.at(dist_min_index)->get_coordenadas().distancia_entre_coord(coord_ponto_interesse) &&
				praias_totais.at(i)->get_nome() != nome_ponto_interesse)
		{
			dist_min_index = i;
		}
	}

	praia_mais_proxima = praias_totais.at(dist_min_index);

	//display da praia mais próxima do ponto de interesse
	cout << "A praia mais proxima de " << nome_ponto_interesse << " (" << coord_ponto_interesse.get_latitude() << ", " << coord_ponto_interesse.get_longitude() << "):" << endl << endl;

	cout << praia_mais_proxima->get_nome() << " - " << "latitude: " << praia_mais_proxima->get_coordenadas().get_latitude() << ", longitude: " << praia_mais_proxima->get_coordenadas().get_longitude() << endl;

	return;
}

void Guia_de_Praias::show_praias()
{
	cout << "As praias presentes na base de dados sao os seguintes: " << endl << endl;

	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		cout << concelhos.at(i).get_nome() << ":" << endl;

		concelhos.at(i).show_praias_concelho();

		cout << endl;
	}
}

void Guia_de_Praias::show_concelhos()
{
	cout << "Os concelhos presentes na base de dados sao os seguintes: " << endl << endl;

	for (unsigned int i = 0; i < concelhos.size(); i++)
		cout << i + 1 << ". " << concelhos.at(i).get_nome() << endl << endl;
}

void Guia_de_Praias::show_informacao_concelho(int ponto_de_interesse) {

	string nome_Concelho;
	bool found = false;

	cout << "Inserir nome do concelho: ";
	getline(cin, nome_Concelho);
	cout << endl;
	//pesquisa o nome do concelho no vetor de concelhos
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		if (concelhos.at(i).get_nome() == nome_Concelho)
		{
			switch (ponto_de_interesse)
			{
			case 1:
				concelhos.at(i).show_restauracao_concelho();
				cout << endl;
				break;
			case 2:
				concelhos.at(i).show_alojamento_concelho();
				cout << endl;
				break;

			case 3:
				concelhos.at(i).show_turismo_concelho();
				cout << endl;
				break;

			case 4:
				concelhos.at(i).show_praias_concelho();
				cout << endl;
				break;
			case 5:
				concelhos.at(i).show_everything();
				cout << endl;
				break;
			case 6:
				concelhos.at(i).show_abertos(1);
				cout << endl;
				break;
			case 7:
				concelhos.at(i).show_fechados(1);
				cout << endl;
				break;

			case 8:
				concelhos.at(i).show_abertos(2);
				cout << endl;
				break;

			case 9:
				concelhos.at(i).show_abertos(2);
				cout << endl;
				break;

			}

			found = true;
			break;
		}
	}
	// se não encontrar o concelho lança uma exceção
	if (!found)
		throw ConcelhoNaoExistente(nome_Concelho);


}

void Guia_de_Praias::show_informacao_praia()
{
	string nome_praia;
	bool found = false;

	cout << "Inserir nome da praia: ";
	getline(cin, nome_praia);

	//pesquisa o nome do concelho no vetor de concelhos
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

		BSTItrIn<Praia_FluvialPtr> it(*praias);

		while(!it.isAtEnd())
		{
			Praia_FluvialPtr praia_atual = it.retrieve();

			if (praia_atual.praia->get_nome() == nome_praia)
			{
				praia_atual.praia->show_informacao_praia();
				found = true;
				break;
			}

			it.advance();
		}

		if (found)
			break;
	}

	if (!found)
		throw PraiaNaoExistente(nome_praia);
}

void Guia_de_Praias::add_praia(int tipo)
{
	string nome_concelho;
	show_praias();

	//input para criar a praia;
	string nome_praia;
	char bandeira_azul;
	string latitude, longitude;
	int capacidade_max;
	vector<Servico> servicos;
	Servico servico;
	string servico_tipo, servico_nome;

	bool found = false; //booleano que verifica se o concelho inserido está presente no vetor de concelhos
	int concelho_index; //indice do concelho onde vou guardar a praia;

	cout << "Insira o concelho onde quer adicionar a praia: ";
	getline(cin, nome_concelho);

	//procura o nome do concelho inserido no vetor de concelhos, lança exceção se não encontrar
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		if (concelhos.at(i).get_nome() == nome_concelho)
		{
			concelho_index = i;
			found = true;
		}
	}

	if (!found)
		throw ConcelhoNaoExistente(nome_concelho);

	cout << "Insira o nome da praia que quer adicionar: ";
	getline(cin, nome_praia);

	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

		BSTItrIn<Praia_FluvialPtr> it(*praias);

		while(!it.isAtEnd())
		{
			Praia_FluvialPtr praia_atual = it.retrieve();

			if (praia_atual.praia->get_nome() == nome_praia)
			{
				throw PraiaExistente(nome_praia);
			}

			it.advance();
		}
	}

	cout << "Insira as coordenadas da sua praia: ";
	cout << endl << "Latitude: ";
	getline(cin, latitude);

	while (!valid_coordinates(latitude, "latitude"))
	{
		cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
		getline(cin, latitude);
	}

	cout << "Longitude: ";
	getline(cin, longitude);

	while (!valid_coordinates(longitude, "longitude"))
	{
		cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
		getline(cin, longitude);
	}

	cout  << "A praia que vai adicionar tem bandeira azul?(Y/N): ";
	cin >> bandeira_azul;


	while (bandeira_azul != 'y' &&  bandeira_azul != 'Y' && bandeira_azul != 'n' && bandeira_azul != 'N')
	{
		cout << endl << "O valor inserido não e valido. Por favor tente de novo: ";
		cout << endl << "Bandeira azul?(Y/N): ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> bandeira_azul;
	}

	cin.clear();
	cin.ignore(1000, '\n');


	if (bandeira_azul != 'y' || bandeira_azul != 'Y')
		bandeira_azul = (bool)true;
	else
		bandeira_azul = (bool)false;


	cout << "Insira os servicos que a praia possui (Insira o tipo de servico como '0' para terminar): "  << endl << "Tipo: ";
	getline(cin, servico_tipo);

	while (servico_tipo != "0")
	{
		cout << "Nome: ";
		getline(cin,servico_nome);

		servico.setTipo(servico_tipo);
		servico.setNome(servico_nome);

		servicos.push_back(servico);
		cout << "Insira outro servico(Insira o tipo de servico como '0' para terminar) " << endl << "Tipo: ";
		getline(cin, servico_tipo);
	}

	cout << "Insira a capacidade maxima da praia que vai adicionar: ";
	cin >> capacidade_max;

	while (cin.fail())
	{
		cout << endl << "A input inserida nao esta no formato pretendido. Por favor tente de novo: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> capacidade_max;
	}

	cin.clear();
	cin.ignore(1000, '\n');


	if (tipo == 1) //vai adicionar uma praia baseada em rio
	{
		float caudal, profundidade, largura;

		cout << "Insira a produndidade da praia que vai adicionar: ";
		cin >> profundidade;

		while (cin.fail())
		{
			cout << endl << "A input inserida nao esta no formato pretendido. Por favor tente de novo: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> profundidade;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Insira a largura da praia que vai adicionar: ";
		cin >> largura;

		while (cin.fail())
		{
			cout << endl << "A input inserida nao esta no formato pretendido. Por favor tente de novo: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> largura;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		cout << "Insira o caudal da praia que vai adicionar: ";
		cin >> profundidade;

		while (cin.fail())
		{
			cout << endl << "A input inserida nao esta no formato pretendido. Por favor tente de novo: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> caudal;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		Praia_FluvialPtr nova_praia;
		nova_praia.praia = new Praia_Rio(nome_concelho, nome_praia, Coordenadas(stold(latitude), stold(longitude)), servicos, bandeira_azul, capacidade_max, largura, caudal, profundidade);

		concelhos.at(concelho_index).add_praia(nova_praia);
	}

	if (tipo == 2) //vai adicionar uma praia baseada em rio
	{
		float area_aquatica;

		cout << endl << "Insira a area aquatica da praia que vai adicionar: ";
		cin >> area_aquatica;

		while (cin.fail())
		{
			cout << endl << "A input inserida nao esta no formato pretendido. Por favor tente de novo: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> area_aquatica;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		Praia_FluvialPtr nova_praia;
		nova_praia.praia = new Praia_Albufeira(nome_concelho, nome_praia, Coordenadas(stold(latitude), stold(longitude)), servicos, bandeira_azul, capacidade_max, area_aquatica);
		concelhos.at(concelho_index).add_praia(nova_praia);
	}

	cout << endl << "A praia " << nome_praia << " foi adicionada com sucesso ao concelho" << nome_concelho << endl;
}

void Guia_de_Praias::add_concelho()
{
	Concelho concelho;
	show_concelhos();

	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		if (concelhos.at(i).get_nome() == concelho.get_nome())
		{
			throw ConcelhoExistente(concelho.get_nome());
		}
	}
	concelhos.push_back(concelho);
	cout << endl << "O concelho " << concelho.get_nome() << " foi adicionado com sucesso." << endl;
}

void Guia_de_Praias::remove_praia()
{
	string nome_praia;
	bool found = false; //indica se já encontrou o praia ou não
	show_praias();
	cout << "Insira o nome da praia que quer remover: ";
	getline(cin, nome_praia);

	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

		BSTItrIn<Praia_FluvialPtr> it(*praias);

		while(!it.isAtEnd())
		{
			Praia_FluvialPtr praia_atual = it.retrieve();

			if (praia_atual.praia->get_nome() == nome_praia)
			{
				concelhos.at(i).remove_praia(praia_atual);
				found = true;
				break;
			}

			it.advance();
		}

		if (found)
			break;
	}

	if (!found)
		throw PraiaNaoExistente(nome_praia);

	cout << "A praia " << nome_praia << " foi removida com sucesso." << endl;
}

void Guia_de_Praias::remove_concelho()
{
	string nome_concelho;
	bool found = false;
	show_concelhos();
	cout << "Insira o nome do concelho: ";
	getline(cin, nome_concelho);

	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		if (concelhos.at(i).get_nome() == nome_concelho)
		{
			concelhos.erase(concelhos.begin() + i);
			found = true;
			break;
		}

		if (found)
			break;
	}
	if (!found)
		throw ConcelhoNaoExistente(nome_concelho);

	cout << endl << "O concelho " << nome_concelho << " foi removido com sucesso" << endl;
}

void Guia_de_Praias::editar_praia()
{
	//faz display ao utilizador de todas as praias na base de dados para evitar erros

	show_praias();

	string nome_praia, nome_praia1;
	bool found = false; // indica se encontrou a praia com nome nome_praia
	int concelho_index;

	cout << "Insira o nome da praia que quer editar: ";
	getline(cin, nome_praia);

	Praia_FluvialPtr praia_a_editar;

	//verifica se a praia existe, se não existir lança exceção
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

		BSTItrIn<Praia_FluvialPtr> it(*praias);

		while(!it.isAtEnd())
		{
			Praia_FluvialPtr praia_atual = it.retrieve();

			if (praia_atual.praia->get_nome() == nome_praia)
			{
				concelho_index = i;
				praia_a_editar = praia_atual;
				concelhos.at(i).remove_praia(praia_atual);
				break;
			}

			it.advance();
		}

		if (found)
			break;
	}


	if (!found)
		throw PraiaNaoExistente(nome_praia);

	cout << endl;
	praia_a_editar.praia->show_informacao_praia();
	cout << endl;

	char answer;
	string latitude, longitude;
	Servico servico;
	string servico_tipo, servico_nome,nome_concelho;
	int capacidade;
	bool bandeira_azul;
	vector<Servico> servicos;

	//alterar o nome da praia
	cout << "Deseja alterar o nome da praia?[Y/N]: ";
	cin >> answer;

	//o utilizador só pode inserir Y/y ou N/n
	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.clear();
	cin.ignore(10000, '\n');

	//se sim...
	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira um novo nome: ";
		getline(cin, nome_praia1);

		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

			BSTItrIn<Praia_FluvialPtr> it(*praias);

			while(!it.isAtEnd())
			{
				Praia_FluvialPtr praia_atual = it.retrieve();

				if (praia_atual.praia->get_nome() == nome_praia1)
					throw PraiaExistente(nome_praia1);

				it.advance();
			}
		}
	}

	else
		nome_praia1 = praia_a_editar.praia->get_nome();

	//alterar as coordenadas
	cout << "Deseja alterar as coordenadas da praia?[Y/N]: ";
	cin >> answer;

	//o utilizador só pode inserir Y/y ou N/n
	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');
	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira umas novas coordenadas:" << endl << "Latitude: ";
		getline(cin, latitude);

		while (!valid_coordinates(latitude, "latitude"))
		{
			cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
			getline(cin, latitude);
		}

		cout << "Longitude: ";
		getline(cin, longitude);

		while (!valid_coordinates(longitude, "longitude"))
		{
			cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
			getline(cin, longitude);
		}
	}
	else
	{
		latitude = to_string(praia_a_editar.praia->get_coordenadas().get_latitude());
		longitude = to_string(praia_a_editar.praia->get_coordenadas().get_longitude());
	}

	Coordenadas coordenadas(stold(latitude), stold(longitude));

	//alterar os servicos
	cout << "Deseja alterar os servicos da praia?[Y/N]: ";
	cin >> answer;

	//o utilizador só pode inserir Y/y ou N/n
	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira o primeiro servico(Insira o tipo de servico como '0' para terminar) " << endl << "Tipo: ";
		getline(cin, servico_tipo);

		while (servico_tipo != "0")
		{
			cout << "Nome: ";
			getline(cin,servico_nome);

			servico.setTipo(servico_tipo);
			servico.setNome(servico_nome);

			servicos.push_back(servico);
			cout << "Insira outro servico(Insira o tipo de servico como '0' para terminar) " << endl << "Tipo: ";
			getline(cin, servico_tipo);
		}
	}
	else
		servicos = 	praia_a_editar.praia->get_servicos();

	//alterar o estado da bandeira azul
	if (praia_a_editar.praia->get_bandeira_azul())
		cout << "Deseja retirar a bandeira azul?[Y/N]: ";
	else
		cout << "Deseja colocar a bandeira azul?[Y/N]: ";

	cin >> answer;

	//o utilizador só pode inserir Y/y ou N/n
	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		if (praia_a_editar.praia->get_bandeira_azul())
			bandeira_azul = false;
		else
			bandeira_azul = true;
	}
	else
		bandeira_azul = praia_a_editar.praia->get_bandeira_azul();

	//alterar a capacidade maxima da praia
	cout << "Deseja alterar a capacidade maxima da praia?[Y/N]: ";
	cin >> answer;

	//o utilizador só pode inserir Y/y ou N/n
	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira a nova capacidade maxima: ";
		cin >> capacidade;

		while (cin.fail())
		{
			cout << "Valor nao numerico. Por favor tente outra vez: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> capacidade;
		}

		cin.clear();
		cin.ignore(1000, '\n');
	}
	else
		capacidade = praia_a_editar.praia->get_capacidade_max();


	praia_a_editar.praia->editar_praia(nome_praia1, coordenadas, servicos, bandeira_azul, capacidade);
	concelhos.at(concelho_index).add_praia(praia_a_editar);
}

void Guia_de_Praias::editar_concelho(){

	//faz display ao utilizador de todos os concelhos na base de dados para evitar erros
	show_concelhos();

	string nome_concelho, nome_concelho1, nome_praia, nome_ponto_interesse, tipo_praia;
	bool found = false; // indica se encontrou o concelho com o nome nome_concelho
	int concelho_index;

	//atributos do concelho
	vector<Turismo> tur;
	vector<Alojamento> aloj;
	vector< Restauracao> rest;
	Praia_FluvialPtr null_praia = Praia_FluvialPtr();
	BST<Praia_FluvialPtr> praias(null_praia);

	//atributos da praia
	string servico_tipo, servico_nome;
	Servico servico;
	vector<Servico> servicos;
	bool bandeira_azul;
	int cap_max;
	double largura, profundidade, caudal, area_aquatica;
	Praia_FluvialPtr praia;

	bool more= true, change = false; //verifica se fez alteração ao atributo


	cout << "Insira o nome do concelho que quer editar: ";
	getline(cin, nome_concelho);

	//verifica se a praia existe, se não existir lança exceção
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		if (concelhos.at(i).get_nome() == nome_concelho)
		{
			concelho_index = i;
			found = true;
			break;
		}
	}

	if (!found)
		throw ConcelhoNaoExistente(nome_concelho);// EXCEPÇÃO

	cout << endl;
	concelhos.at(concelho_index).show_everything();
	cout << endl;

	char answer;
	string latitude, longitude;

	//alterar o nome do Concelho
	cout << "Deseja alterar o nome do Concelho? [Y/N]: ";
	cin >> answer;
	cout << endl;

	//o utilizador só pode inserir Y/y ou N/n
	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.clear();
	cin.ignore(10000, '\n');

	//se sim...
	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira um novo nome: ";
		getline(cin, nome_concelho1);

		for (unsigned int i = 0; i < concelhos.size(); i++)
		{
			if (concelhos.at(i).get_nome() == nome_concelho1)
				throw ConcelhoExistente(nome_concelho1); // EXCEPÇÃO
		}

		concelhos.at(concelho_index).set_nome(nome_concelho1);
	}

	else
		nome_concelho1 = concelhos.at(concelho_index).get_nome();


	//alterar a lista de pontos turísticos do concelho
	cout << "Deseja alterar a lista de Pontos Turisticos do concelho?[Y/N]" << endl;
	cout <<	"Inserindo 'y' ou 'Y' implica reescrever todos os pontos de interesse deste tipo:  ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		change = true;
		more = true;
		while(more)
		{
			cout << endl << "Insira o nome do Ponto Turistico: ";
			getline(cin, nome_ponto_interesse);

			cout<< endl << "Insira as coordenadas" << endl << "Latitude: ";
			getline(cin, latitude);

			while (!valid_coordinates(latitude, "latitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
				getline(cin, latitude);
			}

			cout << "Longitude: ";
			cin >> longitude;

			while (!valid_coordinates(longitude, "longitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
				getline(cin, longitude);
			}

			Coordenadas coordenadas(stold(latitude), stold(longitude));
			tur.push_back(Turismo(nome_ponto_interesse, coordenadas));

			cout << "Deseja continuar editar a lista de pontos turísticos?[Y/N]: ";
			cin >> answer;

			while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
			{
				cout << "Input invalida. Por favor tente outra vez: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> answer;
			}

			cin.ignore(10000, '\n');

			// se não...
			if (answer == 'N' || answer == 'n')
				more = false;
		}
	}

	cout << endl;

	if(change)
		concelhos.at(concelho_index).set_turismo(tur);

	change = false;
	//alterar a lista de restaurantes do concelho
	cout << "Deseja alterar a lista de restaurantes do concelho?[Y/N]" << endl;
	cout <<	"Inserindo 'y' ou 'Y' implica reescrever todos os pontos de interesse deste tipo:  ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		change = true;
		more = true;
		while(more)
		{
			cout << endl << "Insira o nome do Restaurante: ";
			getline(cin, nome_ponto_interesse);

			cout<< endl << "Insira as coordenadas" << endl << "Latitude: ";
			getline(cin, latitude);

			while (!valid_coordinates(latitude, "latitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
				getline(cin, latitude);
			}

			cout << "Longitude: ";
			getline(cin, longitude);

			while (!valid_coordinates(longitude, "longitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
				getline(cin, longitude);
			}

			Coordenadas coordenadas(stold(latitude), stold(longitude));
			rest.push_back(Restauracao(nome_ponto_interesse, coordenadas, false));

			cout << "Deseja continuar editar a lista de restaurantes?[Y/N]: ";
			cin >> answer;

			while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
			{
				cout << "Input invalida. Por favor tente outra vez: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> answer;
			}

			cin.ignore(10000, '\n');

			// se não...
			if (answer == 'N' || answer == 'n')
				more = false;
		}
	}

	cout << endl;

	if(change)
		concelhos.at(concelho_index).set_restauracao(rest);

	change = false;

	//alterar a lista de alojamentos do concelho
	cout << "Deseja alterar a lista de Alojamentos do concelho?[Y/N]" << endl;
	cout <<	"Inserindo 'y' ou 'Y' implica reescrever todos os pontos de interesse deste tipo:  ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		change = true;
		more = true;
		while(more)
		{
			cout << endl << "Insira o nome do Alojamento: ";
			getline(cin, nome_ponto_interesse);

			cout<< endl << "Insira as coordenadas" << endl << "Latitude: ";
			getline(cin, latitude);

			while (!valid_coordinates(latitude, "latitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
				getline(cin, latitude);
			}

			cout << "Longitude: ";
			getline(cin, longitude);

			while (!valid_coordinates(longitude, "longitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
				getline(cin, longitude);
			}

			Coordenadas coordenadas(stold(latitude), stold(longitude));
			aloj.push_back(Alojamento(nome_ponto_interesse, coordenadas, false));

			cout << "Deseja continuar editar a lista de alojamentos?[Y/N]: ";
			cin >> answer;

			while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
			{
				cout << "Input invalida. Por favor tente outra vez: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> answer;
			}

			cin.ignore(10000, '\n');

			// se não...
			if (answer == 'N' || answer == 'n')
				more = false;
		}
	}

	cout << endl;

	if(change)
		concelhos.at(concelho_index).set_alojamento(aloj);

	change = false;
	//alterar a lista de praias do concelho
	cout << "Deseja alterar a lista de Praias Fluviais do concelho?[Y/N]" <<endl;
	cout <<	"Inserindo 'y' ou 'Y' implica reescrever todos os pontos de interesse deste tipo:  ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	// se sim...
	if (answer == 'Y' || answer == 'y')
	{
		change = true;
		more = true;
		while(more)
		{
			cout << endl << "Insira o nome da Praia: ";
			getline(cin, nome_praia);

			cout<< endl << "Insira as coordenadas" << endl << "Latitude: ";
			getline(cin, latitude);

			while (!valid_coordinates(latitude, "latitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez: ";
				getline(cin, latitude);
			}

			cout << "Longitude: ";
			getline(cin, longitude);

			while (!valid_coordinates(longitude, "longitude"))
			{
				cout << "Input nao e uma opcao valida (verifique o formato e o intervalo). Por favor tente outra vez:";
				getline(cin, longitude);
			}

			Coordenadas coordenadas(stold(latitude), stold(longitude));

			cout << "Insira o primeiro servico(Insira o tipo de servico como '0' para terminar) " << endl << "Tipo: ";
			getline(cin, servico_tipo);

			while (servico_tipo != "0")
			{
				cout << "Nome: ";
				getline(cin,servico_nome);

				servico.setTipo(servico_tipo);
				servico.setNome(servico_nome);

				servicos.push_back(servico);
				cout << "Insira outro servico(Insira o tipo de servico como '0' para terminar) " << endl << "Tipo: ";
				getline(cin, servico_tipo);
			}

			cout << "Deseja colocar a bandeira azul?[Y/N]: ";

			cin >> answer;

			//o utilizador só pode inserir Y/y ou N/n
			while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
			{
				cout << "Input invalida. Por favor tente outra vez: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> answer;
			}

			cin.ignore(10000, '\n');

			// se sim...
			if (answer == 'Y' || answer == 'y')
				bandeira_azul = true;
			else
				bandeira_azul = false;

			cout << "Insira a capacidade maxima da praia: ";
			cin >> cap_max;

			while(cin.fail())
			{
				cout <<"Input nao e um valor numerico. Tente outra vez: ";
				cin.clear();
				cin.ignore(1000,'\n');
				cin >> cap_max;

			}

			cin.ignore(1000, '\n');

			cout << "Que tipo de praia vai ser " << nome_praia << " ?[Rio/Albufeira]: ";
			getline(cin, tipo_praia);

			while(tipo_praia != "Rio" && tipo_praia != "Albufeira")
			{
				cout << "A input inserida nao e um tipo de praia valido. Tente outra vez: ";
				getline(cin, tipo_praia);
			}

			if(tipo_praia == "Rio")
			{
				cout << "Insira a largura da praia: ";
				cin >> largura;

				while(cin.fail())
				{
					cout <<"Input nao e um valor numerico. Tente outra vez: ";
					cin.clear();
					cin.ignore(1000,'\n');
					cin >> largura;

				}

				cin.ignore(1000, '\n');

				cout << "Insira o caudal da praia: ";
				cin >> caudal;

				while(cin.fail())
				{
					cout <<"Input nao e um valor numerico. Tente outra vez: ";
					cin.clear();
					cin.ignore(1000,'\n');
					cin >> caudal;

				}

				cin.ignore(1000, '\n');


				cout << "Insira a profundidade da praia: ";
				cin >> profundidade;

				while(cin.fail())
				{
					cout <<"Input nao e um valor numerico. Tente outra vez: ";
					cin.clear();
					cin.ignore(1000,'\n');
					cin >> profundidade;
				}

				cin.ignore(1000, '\n');

				praia.praia = new Praia_Rio(nome_concelho1, nome_praia, coordenadas, servicos, bandeira_azul, cap_max, largura, caudal, profundidade);
			}

			else
			{
				cout << "Insira a area aquatica da praia: ";
				cin >> area_aquatica;

				while(cin.fail())
				{
					cout <<"Input nao e um valor numerico. Tente outra vez: ";
					cin.clear();
					cin.ignore(1000,'\n');
					cin >> area_aquatica;

				}

				cin.ignore(1000, '\n');

				praia.praia = new Praia_Albufeira(nome_concelho1, nome_praia, coordenadas, servicos, bandeira_azul, cap_max, area_aquatica);
			}

			praias.insert(praia);

			cout << "Deseja continuar editar a lista de praias?[Y/N]: ";
			cin >> answer;

			while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
			{
				cout << "Input invalida. Por favor tente outra vez: ";
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> answer;
			}

			cin.ignore(10000, '\n');

			// se não...
			if (answer == 'N' || answer == 'n')
				more = false;
		}
	}

	if(change)
		concelhos.at(concelho_index).set_praias(praias);
}

bool valid_coordinates(string coordenada, string tipo)
{
	vector<char> carateres;
	int cnt_ponto = 0;

	for (unsigned int i = 0; i < coordenada.size(); i++)
	{
		carateres.push_back(coordenada.at(i));
	}

	for (unsigned int i = 0; i < carateres.size(); i++)
	{
		if ((carateres.at(0) < '0' || carateres.at(0) > '9') && carateres.at(0) != '.' && carateres.at(0) != '-')
		{
			//if(carateres.at(0) == '-' &&  i > 0 && (carateres.at(i) < '0' || carateres.at(i) > '9'))
			return false;
		}

		else if(i > 0)
		{
			if((carateres.at(i) < '0' || carateres.at(i) > '9') && carateres.at(i) != '.')
				return false;
		}

		else if(carateres.size() == 1 && (carateres.at(i) < '0' || carateres.at(i) > '9'))
			return false;

		else if (carateres.at(i) == '.')
			cnt_ponto++;
	}

	if (cnt_ponto > 1)
		return false;

	if (tipo == "latitude")
		if (stold(coordenada) > 90 || stold(coordenada) < -90)
			return false;

	if (tipo == "longitude")
		if (stold(coordenada) > 180 || stold(coordenada) < -180)
			return false;
	return true;
}

void Guia_de_Praias::guardar_ficheiros(string nome_ficheiro_concelhos, string nome_ficheiro_praias, string nome_ficheiro_hash, Data curr_data)
{
	//Guardar ficheiro concelhos

	ofstream ficheiro_concelhos_stream;

	ficheiro_concelhos_stream.open(nome_ficheiro_concelhos);

	for (unsigned int i = 0; i <= concelhos.size() - 1; i++)
	{
		ficheiro_concelhos_stream << concelhos.at(i).get_nome() << "; ";

		for(unsigned int j = 0; j < concelhos.at(i).get_turismo().size(); j++)
		{
			ficheiro_concelhos_stream << concelhos.at(i).get_turismo().at(j).get_nome() <<  " (";
			ficheiro_concelhos_stream << concelhos.at(i).get_turismo().at(j).get_coordenadas().get_latitude() << " / ";
			ficheiro_concelhos_stream << concelhos.at(i).get_turismo().at(j).get_coordenadas().get_longitude() << ") ";

			if(j ==concelhos.at(i).get_turismo().size() - 1)
				ficheiro_concelhos_stream << "; ";

			else
				ficheiro_concelhos_stream << ", ";
		}


		for(unsigned int j = 0; j < concelhos.at(i).get_restauracao().size(); j++)
		{
			ficheiro_concelhos_stream << concelhos.at(i).get_restauracao().at(j).get_nome() <<  " (";
			ficheiro_concelhos_stream << concelhos.at(i).get_restauracao().at(j).get_coordenadas().get_latitude() << " / ";
			ficheiro_concelhos_stream << concelhos.at(i).get_restauracao().at(j).get_coordenadas().get_longitude() << ") ";

			if(j ==concelhos.at(i).get_restauracao().size() - 1)
				ficheiro_concelhos_stream << "; ";
			else
				ficheiro_concelhos_stream << ", ";
		}

		for(unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
		{
			ficheiro_concelhos_stream << concelhos.at(i).get_alojamento().at(j).get_nome() <<  " (";
			ficheiro_concelhos_stream << concelhos.at(i).get_alojamento().at(j).get_coordenadas().get_latitude() << " / ";
			ficheiro_concelhos_stream << concelhos.at(i).get_alojamento().at(j).get_coordenadas().get_longitude() << ") ";

			if(j ==concelhos.at(i).get_alojamento().size() - 1)
				ficheiro_concelhos_stream << "; ";
			else
				ficheiro_concelhos_stream << ", ";
		}

		if (i != concelhos.size() - 1)
			ficheiro_concelhos_stream << endl;
	}

	ficheiro_concelhos_stream.close();

	//Guardar ficheiro praias

	ofstream ficheiro_praias_stream;

	ficheiro_praias_stream.open(nome_ficheiro_praias);

	ficheiro_praias_stream << "Praias:" << endl;

	//fazer o ciclo que percorre todos os concelhos e coloca cada uma das praias no ficheiro de praias
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		BST<Praia_FluvialPtr>* praias = concelhos.at(i).getPraias();

		BSTItrIn<Praia_FluvialPtr> it(*praias);

		//ler cada uma das praias de um concelho para o ficheiro
		while(!it.isAtEnd())
		{
			Praia_FluvialPtr praia_atual = it.retrieve();

			ficheiro_praias_stream << concelhos.at(i).get_nome() << "; ";
			ficheiro_praias_stream << praia_atual.praia->get_nome() << " ; ";
			ficheiro_praias_stream << praia_atual.praia->get_capacidade_max() << " ; ";
			ficheiro_praias_stream << praia_atual.praia->get_coordenadas().get_latitude() << ",";
			ficheiro_praias_stream << praia_atual.praia->get_coordenadas().get_longitude() << " ; ";

			bool bandeira = praia_atual.praia->get_bandeira_azul();
			int bandeira_azul;

			if(bandeira)
				bandeira_azul = 1;
			else
				bandeira_azul = 0;

			ficheiro_praias_stream << bandeira_azul << " ; ";

			vector<Servico> servicos = praia_atual.praia->get_servicos();

			//ler os servicos de cada praia

			for(unsigned int k = 0; k < servicos.size(); k++)
			{
				ficheiro_praias_stream <<  "( " << servicos.at(k).getTipo();
				ficheiro_praias_stream <<" / ";
				ficheiro_praias_stream << servicos.at(k).getNome() << " ) ";

				if(k ==servicos.size() - 1)
					ficheiro_praias_stream << "; ";

				else
					ficheiro_praias_stream << ", ";
			}

			praia_atual.praia->escreve_ficheiro_derivadas(ficheiro_praias_stream);

			ficheiro_praias_stream << endl;

			it.advance();
		}
	}

	ficheiro_praias_stream << "END";

	ficheiro_praias_stream.close();


	//Guardar ficheiro hash

	ofstream ficheiro_hash_stream;

	ficheiro_hash_stream.open(nome_ficheiro_hash);

	ficheiro_hash_stream << curr_data.getDia() << " / " << curr_data.getMes() << " / " << curr_data.getAno() << endl;

	HashTabFechadosAloj::iterator it_aloj = aloj_fechados.begin();

	for(;it_aloj != aloj_fechados.end(); it_aloj++)
	{
		ficheiro_hash_stream << it_aloj->get_nome() << "; ";
		ficheiro_hash_stream << it_aloj->get_data_fecho().getDia() << " / " << it_aloj->get_data_fecho().getMes() << " / " << it_aloj->get_data_fecho().getAno() << " ; ";
		ficheiro_hash_stream << it_aloj->get_data_abertura().getDia() << " / " << it_aloj->get_data_abertura().getMes() << " / " << it_aloj->get_data_abertura().getAno() << " ; ";
		ficheiro_hash_stream << endl;
	}

	HashTabFechadosRest::iterator it_rest = rest_fechados.begin();

	for(;it_rest != rest_fechados.end(); it_rest++)
	{
		ficheiro_hash_stream << it_rest->get_nome() << "; ";
		ficheiro_hash_stream << it_rest->get_data_fecho().getDia() << " / " << it_rest->get_data_fecho().getMes() << " / " << it_rest->get_data_fecho().getAno() << " ; ";
		ficheiro_hash_stream << it_rest->get_data_abertura().getDia() << " / " << it_rest->get_data_abertura().getMes() << " / " << it_rest->get_data_abertura().getAno() << " ; ";
		ficheiro_hash_stream << endl;
	}

	ficheiro_hash_stream << "END";

	ficheiro_hash_stream.close();
}

void Guia_de_Praias::fechar_alojamento(Data current_data){

	string alojamento;
	Data abertura, fecho;
	int dia, mes, ano;
	int info1;

	int concelho_index, aloj_index;

	cout<<"Insira o nome do alojamento a alterar:";
	getline(cin,alojamento);

	bool found = false; //booleano que indica se encontrou o nome do alojamento ou nao

	//ciclo que pesquisa o nome do alojamento nos concelhos at� encontrar o alojamento com nome igual ao inserido pelo utilizado se n�o encontrar lan�a uma exce��o
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		for (unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
		{
			if (concelhos.at(i).get_alojamento().at(j).get_nome() == alojamento)
			{
				concelho_index = i;
				aloj_index = j;
				found = true;
				break;
			}
		}

		if(found)
			break;
	}

	if (found == false){
		throw PontoInteresseNaoExistente(alojamento);
	}

	if(concelhos.at(concelho_index).get_alojamento().at(aloj_index).get_aberto() == false)
	{
		cout << "O alojamento inserido já se encontra fechado" << endl;
		return;
	}

	cout<<"Insira a data em que pretende fechar: (DD/MM/AAAA)"<<endl;
	cout<<"Ano: ";
	cin >> ano;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> ano;
	}

	cout<<"Mes: ";
	cin >> mes;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> mes;
	}

	cout<<"Dia: ";
	cin >> dia;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> dia;
	}

	fecho = Data(dia, mes, ano);

	if(!fecho.validData())
		throw DataInvalida(fecho);

	if(fecho < current_data)
		throw DataImpossivel(fecho, current_data);

	cout << endl <<"Insira 1 para encerrar permanentemente ou 2 para encerrar temporariamente: "<< endl;
	cin>>info1;

	while(cin.fail() || (info1 != 2 && info1 != 1))
	{
		cout << "Input invalida. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> info1;
	}

	if(info1 == 1){ // permanentemente

		if(fecho == current_data)
		{
			concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_aberto(false);
			aloj_fechados.insert(concelhos.at(concelho_index).get_alojamento().at(aloj_index));
		}
		concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_data_fecho(fecho);
		concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_data_abertura(Data(0,0,0));
	}

	else{ //temporariamente, insere data de reabertura

		cout<<"Insira a data em que pretende reabrir: (DD/MM/AAAA)"<<endl;
		cout<<"Ano: ";
		cin >> ano;

		while(cin.fail())
		{
			cout << "Input nao e um inteiro. Por favor tente de novo.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> ano;
		}

		cout<<"Mes: ";
		cin >> mes;

		while(cin.fail())
		{
			cout << "Input nao e um inteiro. Por favor tente de novo.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> mes;
		}

		cout<<"Dia: ";
		cin >> dia;

		while(cin.fail())
		{
			cout << "Input nao e um inteiro. Por favor tente de novo.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> dia;
		}

		abertura = Data(dia, mes, ano);

		if(!abertura.validData())
			throw DataInvalida(abertura);

		if(abertura < current_data)
			throw DataImpossivel(fecho, current_data);

		if(abertura < fecho)
			throw DataIncompativel(fecho, abertura);

		if(fecho == current_data)
		{
			concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_aberto(false);
			aloj_fechados.insert(concelhos.at(concelho_index).get_alojamento().at(aloj_index));
		}
		concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_data_fecho(fecho);
		concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_data_abertura(abertura);

	}
}


void Guia_de_Praias::fechar_restauracao(Data current_data){

	string restauracao;
	Data abertura, fecho;
	int dia, mes, ano;
	int info1;

	int concelho_index, rest_index;

	cout<<"Insira o nome do restaurante a alterar:";
	getline(cin,restauracao);

	bool found = false; //booleano que indica se encontrou o nome do alojamento ou nao

	//ciclo que pesquisa o nome do alojamento nos concelhos at� encontrar o alojamento com nome igual ao inserido pelo utilizado se n�o encontrar lan�a uma exce��o
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		for (unsigned int j = 0; j < concelhos.at(i).get_restauracao().size(); j++)
		{
			if (concelhos.at(i).get_restauracao().at(j).get_nome()== restauracao)
			{
				concelho_index = i;
				rest_index = j;
				found = true;
				break;
			}
		}

		if(found)
			break;
	}

	if (found == false){
		throw PontoInteresseNaoExistente(restauracao);
	}

	if(concelhos.at(concelho_index).get_restauracao().at(rest_index).get_aberto() == false)
	{
		cout << "O restaurante inserido já se encontra fechado" << endl;
		return;
	}

	cout<<"Insira a data em que pretende fechar: (DD/MM/AAAA)"<<endl;
	cout<<"Ano: ";
	cin >> ano;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> ano;
	}

	cout<<"Mes: ";
	cin >> mes;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> mes;
	}

	cout<<"Dia: ";
	cin >> dia;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> dia;
	}

	fecho = Data(dia, mes, ano);

	if(!fecho.validData())
		throw DataInvalida(fecho);

	if(fecho < current_data)
		throw DataImpossivel(fecho, current_data);

	cout<<"Insira 1 para encerrar permanentemente ou 2 para encerrar temporariamente: "<< endl;
	cin>>info1;

	while(cin.fail() || (info1 != 2 && info1 != 1))
	{
		cout << "Input invalida. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> info1;
	}

	if(info1 == 1){ // permanentemente

		if(current_data == fecho)
		{
			concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_aberto(false);
			rest_fechados.insert(concelhos.at(concelho_index).get_restauracao().at(rest_index));
		}
		concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_data_fecho(fecho);
		concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_data_abertura(Data(0,0,0));

	}

	else{ //temporariamente, insere data de reabertura

		cout<<"Insira a data em que pretende reabrir: (DD/MM/AAAA)"<<endl;
		cout<<"Ano: ";
		cin >> ano;

		while(cin.fail())
		{
			cout << "Input nao e um inteiro. Por favor tente de novo.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> ano;
		}

		cout<<"Mes: ";
		cin >> mes;

		while(cin.fail())
		{
			cout << "Input nao e um inteiro. Por favor tente de novo.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> mes;
		}

		cout<<"Dia: ";
		cin >> dia;

		while(cin.fail())
		{
			cout << "Input nao e um inteiro. Por favor tente de novo.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> dia;
		}

		abertura = Data(dia, mes, ano);

		if(!abertura.validData())
			throw DataInvalida(abertura);

		if(abertura < current_data)
			throw DataImpossivel(fecho, current_data);

		if(abertura < fecho)
			throw DataIncompativel(fecho, abertura);

		if(current_data == fecho)
		{
			concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_aberto(false);
			rest_fechados.insert(concelhos.at(concelho_index).get_restauracao().at(rest_index));
		}

		concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_data_fecho(fecho);
		concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_data_abertura(abertura);

	}
}

void Guia_de_Praias::reabrir_alojamento()
{
	string alojamento;

	int concelho_index, aloj_index;

	cout<<"Insira o nome do alojamento a alterar:"<<endl;
	getline(cin,alojamento);

	bool found = false; //booleano que indica se encontrou o nome do alojamento ou nao

	//ciclo que pesquisa o nome do alojamento nos concelhos at� encontrar o alojamento com nome igual ao inserido pelo utilizado se n�o encontrar lan�a uma exce��o
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		for (unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
		{
			if (concelhos.at(i).get_alojamento().at(j).get_nome()== alojamento)
			{
				concelho_index = i;
				aloj_index = j;
				found = true;
				break;
			}
		}
	}

	if (found == false){
		throw PontoInteresseNaoExistente(alojamento);
	}

	if(concelhos.at(concelho_index).get_alojamento().at(aloj_index).get_aberto() == false)
	{
		cout << "O restaurante inserido já se encontra fechado" << endl;
		return;
	}

	concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_aberto(true);
	concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_data_fecho(Data(0,0,0));
	concelhos.at(concelho_index).getAlojamento()->at(aloj_index).set_data_abertura(Data(0,0,0));
	aloj_fechados.erase(concelhos.at(concelho_index).get_alojamento().at(aloj_index));
}

void Guia_de_Praias::reabrir_restauracao()
{
	string restauracao;

	int concelho_index, rest_index;

	cout<<"Insira o nome do restaurante a alterar:"<<endl;
	getline(cin,restauracao);

	bool found = false; //booleano que indica se encontrou o nome do alojamento ou nao

	//ciclo que pesquisa o nome do alojamento nos concelhos at� encontrar o alojamento com nome igual ao inserido pelo utilizado se n�o encontrar lan�a uma exce��o
	for (unsigned int i = 0; i < concelhos.size(); i++)
	{
		for (unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
		{
			if (concelhos.at(i).get_alojamento().at(j).get_nome()== restauracao)
			{
				concelho_index = i;
				rest_index = j;
				found = true;
				break;
			}
		}
	}

	if (found == false){
		throw PontoInteresseNaoExistente(restauracao);
	}

	if(concelhos.at(concelho_index).get_restauracao().at(rest_index).get_aberto() == true)
	{
		cout << "O restaurante inserido já se encontra aberto" << endl;
		return;
	}

	concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_aberto(true);
	concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_data_fecho(Data(0,0,0));
	concelhos.at(concelho_index).getRestauracao()->at(rest_index).set_data_abertura(Data(0,0,0));
	rest_fechados.erase(concelhos.at(concelho_index).get_restauracao().at(rest_index));
}


void Guia_de_Praias::avanca_data(Data*current_data)
{
	Data new_date;
	Data default_date(0,0,0);
	int dia, mes, ano;

	cout<<"Insira a data para a qual pretende avancar: (DD/MM/AAAA)"<<endl;
	cout<<"Ano: ";
	cin >> ano;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> ano;
	}

	cout<<"Mes: ";
	cin >> mes;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> mes;
	}

	cout<<"Dia: ";
	cin >> dia;

	while(cin.fail())
	{
		cout << "Input nao e um inteiro. Por favor tente de novo.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> dia;
	}

	new_date = Data(dia, mes, ano);

	if(!new_date.validData())
		throw DataInvalida(new_date);

	if(new_date < *current_data)
		throw DataImpossivel(new_date, *current_data);

	//atualizar os restaurantes da hash retirando os que já reabriram e colocando os que entretanto fecharam

	for(unsigned int i = 0; i < concelhos.size(); i++)
	{
		for(unsigned int j = 0; j < concelhos.at(i).get_restauracao().size(); j++)
		{
			if(concelhos.at(i).get_restauracao().at(j).get_aberto() == false)
			{
				if(concelhos.at(i).get_restauracao().at(j).get_data_abertura() < new_date && !(concelhos.at(i).get_restauracao().at(j).get_data_abertura() == default_date))
				{
					concelhos.at(i).getRestauracao()->at(j).set_aberto(true);
					concelhos.at(i).getRestauracao()->at(j).set_data_fecho(default_date);
					concelhos.at(i).getRestauracao()->at(j).set_data_abertura(default_date);
					rest_fechados.erase(concelhos.at(i).get_restauracao().at(j));
				}
			}

			else if(concelhos.at(i).get_restauracao().at(j).get_aberto() == true)
			{
				if(concelhos.at(i).get_restauracao().at(j).get_data_fecho() < new_date && !(concelhos.at(i).get_restauracao().at(j).get_data_fecho() == default_date))
				{
					concelhos.at(i).getRestauracao()->at(j).set_aberto(false);
					rest_fechados.insert(concelhos.at(i).get_restauracao().at(j));
				}
			}
		}
	}

	//atualizar os alojamentos da hash retirando os que já reabriram e colocando os que entretanto fecharam

	for(unsigned int i = 0; i < concelhos.size(); i++)
	{
		for(unsigned int j = 0; j < concelhos.at(i).get_alojamento().size(); j++)
		{
			if(concelhos.at(i).get_alojamento().at(j).get_aberto() == false)
			{
				if(concelhos.at(i).get_alojamento().at(j).get_data_fecho() < *current_data && !(concelhos.at(i).get_alojamento().at(j).get_data_fecho() == default_date))
				{
					concelhos.at(i).getAlojamento()->at(j).set_aberto(true);
					concelhos.at(i).getAlojamento()->at(j).set_data_fecho(default_date);
					concelhos.at(i).getAlojamento()->at(j).set_data_abertura(default_date);
					aloj_fechados.erase(concelhos.at(i).get_alojamento().at(j));
				}
			}

			else if(concelhos.at(i).get_alojamento().at(j).get_aberto() == true)
			{
				if(concelhos.at(i).get_alojamento().at(j).get_data_fecho() < new_date && !(concelhos.at(i).get_alojamento().at(j).get_data_fecho() == default_date))
				{
					concelhos.at(i).getAlojamento()->at(j).set_aberto(false);
					aloj_fechados.insert(concelhos.at(i).get_alojamento().at(j));
				}
			}
		}
	}

	//atualizar a data
	*current_data = new_date;
}

void Guia_de_Praias::add_inspecao(Data *current_data)
{
	string nome_concelho, nome_praia, nome_servico;

	bool found_concelho = false;
	bool found_praia = false;
	bool found_servico = false;
	bool found_inspec = false;

	Servico servico;
	Praia_FluvialPtr praia;
	Data inspec_date;

	int concelho_index;

	show_concelhos();

	cout << "Insira o  nome do concelho onde pretende realizar a inspecao: ";
	getline(cin, nome_concelho);

	cout << endl;

	for(unsigned int i = 0; i< concelhos.size(); i++)
	{
		if(concelhos.at(i).get_nome() == nome_concelho)
		{
			found_concelho = true;
			concelhos.at(i).show_praias_concelho();
			concelho_index = i;
		}
	}

	if (!found_concelho)
		throw ConcelhoNaoExistente(nome_concelho);

	cout << "Insira o nome da praia onde pretende realizar a inspecao: ";
	getline(cin, nome_praia);

	cout << endl;

	BST<Praia_FluvialPtr>* praias = concelhos.at(concelho_index).getPraias();

	BSTItrIn<Praia_FluvialPtr> it(*praias);

	while(!it.isAtEnd())
	{
		Praia_FluvialPtr praia_atual = it.retrieve();

		if(praia_atual.praia->get_nome() == nome_praia)
		{
			found_praia = true;
			praia = praia_atual;
		}

		it.advance();
	}

	if(!found_praia)
		throw PraiaNaoExistente(nome_praia);


	praia.praia->show_servicos_praia();

	cout << "Inserir nome do servico: ";
	getline(cin, nome_servico);


	for(unsigned int i = 0; i < praia.praia->get_servicos().size(); i++)
	{
		if(praia.praia->get_servicos().at(i).getNome() == nome_servico)
		{
			servico = praia.praia->get_servicos().at(i);
			found_servico = true;
		}
	}

	if (!found_servico)
		throw ServicoNaoExistente(nome_servico);

	inspec_date = *current_data;

	if(!inspec_date.validData())
		throw DataInvalida(inspec_date);

	if(inspec_date < *current_data)
		throw DataImpossivel(inspec_date, *current_data);

	Inspecao inspec(inspec_date, servico, nome_praia, nome_concelho);

	for(unsigned int i = 0; i < inspecoes.size(); i++)
	{
		if(inspecoes.at(i).getTipo() == servico.getTipo())
		{
			found_inspec = true;
			inspecoes.at(i).addInspecao(inspec);
			break;
		}
	}

	if(!found_inspec)
	{
		string tipo = servico.getTipo();

		Inspecoes new_inspec(tipo);
		new_inspec.addInspecao(inspec);
		inspecoes.push_back(new_inspec);
	}
}

void Guia_de_Praias::show_inspecao_geral()
{
	for(unsigned int i = 0; i < inspecoes.size(); i++)
	{
		show_inspecao_tipo(inspecoes.at(i).getTipo());
	}
}

void Guia_de_Praias::show_inspecao_concelho()
{
	string concelho;
	bool found = false;

	cout << "Insira o concelho com os servicos que deseja visualizar: ";
	getline(cin, concelho);

	cout << endl << "Inspecoes do concelho " << concelho << ": " << endl << endl;

	for(unsigned int i = 0; i < inspecoes.size(); i++)
	{
		priority_queue<Inspecao> inspec_copy = inspecoes.at(i).getInspec();

		while(!inspec_copy.empty())
		{
			Inspecao current = inspec_copy.top();

			if(current.getConcelho() == concelho)
			{
				found = true;

				cout << "Praia: " << current.getPraia() << endl;
				cout << "Tipo de Servico: " << current.getServico().getTipo() << endl;
				cout << "Nome do Servico: " << current.getServico().getNome() << endl;
				cout << "Data de Inspecao: " << current.getData().getDia() << "/" << current.getData().getMes() << "/" << current.getData().getAno() << endl << endl << endl;
			}

			inspec_copy.pop();
		}
	}

	if(!found)
		throw ConcelhoNaoExistente(concelho);

	cout << endl;
}

void Guia_de_Praias::show_inspecao_praia()
{
	string praia;
	bool found = false;

	cout << "Insira a praia com os servicos que deseja visualizar: ";
	getline(cin, praia);

	cout << endl << "Inspecoes da " << praia << ": " << endl << endl;

	for(unsigned int i = 0; i < inspecoes.size(); i++)
	{
		priority_queue<Inspecao> inspec_copy = inspecoes.at(i).getInspec();

		while(!inspec_copy.empty())
		{
			Inspecao current = inspec_copy.top();

			if(current.getPraia() == praia)
			{
				found = true;

				cout << "Tipo de Servico: " << current.getServico().getTipo() << endl;
				cout << "Nome do Servico: " << current.getServico().getNome() << endl;
				cout << "Data de Inspecao: " << current.getData().getDia() << "/" << current.getData().getMes() << "/" << current.getData().getAno() << endl << endl << endl;
			}

			inspec_copy.pop();
		}
	}

	if(!found)
		throw PraiaNaoExistente(praia);

	cout << endl;
}

string Guia_de_Praias::pergunta_tipo()
{
	string tipo;
	cout << "Insira o tipo de servico que deseja visualizar: ";
	getline(cin, tipo);

	return tipo;
}

void Guia_de_Praias::show_inspecao_tipo(string tipo)
{
	bool found = false;

	cout << "Inspecoes do tipo '" << tipo << "': " << endl << endl;

	for(unsigned int i = 0; i < inspecoes.size(); i++)
	{
		if(tipo == inspecoes.at(i).getTipo())
		{
			found= true;
			priority_queue<Inspecao> inspec_copy = inspecoes.at(i).getInspec();

			while(!inspec_copy.empty())
			{
				Inspecao current = inspec_copy.top();

				cout << "Concelho: " << current.getConcelho() << endl;
				cout << "Praia: " << current.getPraia() << endl;
				cout << "Nome do Servico: " << current.getServico().getNome() << endl;
				cout << "Data de Inspecao: " << current.getData().getDia() << "/" << current.getData().getMes() << "/" << current.getData().getAno() << endl << endl << endl;

				inspec_copy.pop();
			}

			break;
		}
	}

	if(!found)
		throw TipoNaoExistente(tipo);

	cout << endl;
}
