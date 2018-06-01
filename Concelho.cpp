#include "Concelho.h"
#include <sstream>

////////////////
//constructors//
////////////////

Concelho::Concelho(string line_concelho): praias(Praia_FluvialPtr())
{
	stringstream concelho_stream(line_concelho);
	char  barra, parentesis;
	char character = concelho_stream.get();

	string tur;
	string rest;
	string aloj;

	long double latitude;
	long double longitude;

	//vai buscar � stringstream o nome do concelho
	while (character != ';') {
		nome += character;
		character = concelho_stream.get();
	}
	// ignora tudo o que foi lido at� agora
	concelho_stream.ignore();

	character = concelho_stream.get();


	//virgula separa cada um dos pontos de interesse do mesmo tipo
	while (character != ',')
	{
		tur = "";
		//parentesis significam que a seguir v�m as coordenadas
		while (character != '(')
		{
			tur += character;
			character = concelho_stream.get();
		}
		//elimina os espa�os
		tur.erase(tur.size() - 1);
		tur.erase(0, 0);

		// ignora tudo o que foi lido at� agora
		//concelho_stream.ignore();

		//le da stringstream as coordenadas do ponto de interesse
		concelho_stream >> latitude >> barra >> longitude >> parentesis;

		//fazer push_back ao vetor de turismo
		turismo.push_back(Turismo(tur, Coordenadas(latitude, longitude)));

		concelho_stream.ignore();
		character = concelho_stream.get();

		//ponto e virgula assinala o fim dos pontos de interesse tur�sticos
		if (character == ';')
			break;

		concelho_stream.ignore();
		character = concelho_stream.get();
	}

	concelho_stream.ignore();
	character = concelho_stream.get();

	//virgula separa cada um dos pontos de interesse do mesmo tipo
	while (character != ',')
	{
		rest = "";
		//parentesis significam que a seguir v�m as coordenadas
		while (character != '(')
		{
			rest += character;
			character = concelho_stream.get();
		}
		//elimina os espa�os
		rest.erase(rest.size() - 1);
		rest.erase(0, 0);

		// ignora tudo o que foi lido at� agora
		//concelho_stream.ignore();

		//lê da stringstream as coordenadas do ponto de interesse
		concelho_stream >> latitude >> barra >> longitude >> parentesis;

		//fazer push_back ao vetor de restauracao
		restauracao.push_back(Restauracao(rest, Coordenadas(latitude, longitude), true));

		concelho_stream.ignore();
		character = concelho_stream.get();
		//ponto e virgula assinala o fim dos restaurantes
		if (character == ';')
			break;

		concelho_stream.ignore();
		character = concelho_stream.get();
	}

	concelho_stream.ignore();
	character = concelho_stream.get();

	//virgula separa cada um dos pontos de interesse do mesmo tipo
	while (character != ',')
	{
		aloj = "";
		//parentesis significam que a seguir v�m as coordenadas
		while (character != '(')
		{
			aloj += character;
			character = concelho_stream.get();
		}

		//elimina os espa�os
		aloj.erase(aloj.size() - 1);
		aloj.erase(0, 0);

		// ignora tudo o que foi lido at� agora
		//concelho_stream.ignore();

		concelho_stream >> latitude >> barra >> longitude >> parentesis;

		//fazer push_back ao vetor de alojamentos
		alojamento.push_back(Alojamento(aloj, Coordenadas(latitude, longitude), true));

		concelho_stream.ignore();
		character = concelho_stream.get();

		//ponto e virgula assinala o fim dos alojamentos
		if (character == ';')
			break;

		concelho_stream.ignore();
		character = concelho_stream.get();
	}
}

Concelho::Concelho(): praias(Praia_FluvialPtr())
{
	string nome_concelho;
	cout << "Insira o nome do concelho: ";
	getline(cin, nome_concelho);

	this->nome = nome_concelho;
}

///////////////
//set_methods//
///////////////

void Concelho::set_nome(string nome)
{
	this->nome = nome;
}

void Concelho::set_praias(BST<Praia_FluvialPtr> praias)
{
	this->praias = praias;
}

void Concelho::set_turismo(vector<Turismo> turismo)
{
	this->turismo = turismo;
}

void Concelho::set_alojamento(vector<Alojamento> alojamento)
{
	this->alojamento = alojamento;
}

void Concelho::set_restauracao(vector<Restauracao> restauracao)
{
	this->restauracao = restauracao;
}

///////////////
//get_methods//
///////////////

string Concelho::get_nome() const
{
	return nome;
}

BST<Praia_FluvialPtr> Concelho::get_praias() const
{
	return praias;
}

BST<Praia_FluvialPtr>* Concelho::getPraias()
{
	return &praias;
}

vector<Turismo> Concelho::get_turismo() const
{
	return turismo;
}

vector<Alojamento> Concelho::get_alojamento() const
{
	return alojamento;
}

vector<Restauracao> Concelho::get_restauracao() const
{
	return restauracao;
}

vector<Alojamento>* Concelho::getAlojamento()
{
	return &alojamento;
}

vector<Restauracao>* Concelho::getRestauracao()
{
	return &restauracao;
}

void Concelho::show_praias_concelho()
{
	BSTItrIn<Praia_FluvialPtr> it(praias); //iterador em ordem para percorrer as praias fluviais

	int count = 0; //contabiliza o n�mero de praias existentes no concelho

	while(!it.isAtEnd())
	{
		count++;
		Praia_FluvialPtr praia_atual = it.retrieve();

		cout << count << ". ";
		cout << praia_atual.praia->get_nome() << " - ";
		cout << "latitude: " << praia_atual.praia->get_coordenadas().get_latitude();
		cout << " / ";
		cout << "longitude: " << praia_atual.praia->get_coordenadas().get_longitude() << " ::::: ";

		if(praia_atual.praia->get_bandeira_azul())
			cout << "tem bandeira azul"<< endl;
		else
			cout << "nao tem bandeira azul" << endl;

		it.advance();
	}

	if(count == 0)
		cout << nome << " nao tem praias disponiveis." << endl;

	cout << endl;

	return;
}

void Concelho::show_turismo_concelho()
{
	int number;

	if (turismo.size() == 0)
	{
		cout << nome << " nao tem pontos tur�sticos disponiveis." << endl;
		return;
	}

	cout << nome << " tem os seguintes pontos de turismo:(coordenadas em graus decimais)";
	cout << endl << endl;
	for (unsigned int i = 0; i < turismo.size(); i++)
	{
		number = i + 1;
		cout << number << ". ";
		cout << turismo.at(i).get_nome() << " -";
		cout << " latitude: " << turismo.at(i).get_coordenadas().get_latitude();
		cout << " / ";
		cout << "longitude: " << turismo.at(i).get_coordenadas().get_longitude() << endl;
	}

	cout << endl;

}

void Concelho::show_alojamento_concelho()
{
	int number;

	if (alojamento.size() == 0)
	{
		cout << nome << " nao tem alojamentos disponiveis." << endl;
		return;
	}

	cout << nome << " tem os seguintes alojamentos:(coordenadas em graus decimais)";
	cout << endl << endl;
	for (unsigned int i = 0; i < alojamento.size(); i++)
	{
		number = i + 1;
		cout << number << ". ";
		cout << alojamento.at(i).get_nome() << " -";
		cout << " latitude: " << alojamento.at(i).get_coordenadas().get_latitude();
		cout << " / ";
		cout << "longitude: " << alojamento.at(i).get_coordenadas().get_longitude();

		if(alojamento.at(i).get_aberto() == true)
			cout << " :::: aberto" << endl;
		else if(alojamento.at(i).get_data_abertura().getDia() == 0 )
			cout << " :::: fechado permanentemente" << endl;
		else
			cout << " :::: fechado temporariamente (ate " << alojamento.at(i).get_data_abertura().getDia() << "/" << alojamento.at(i).get_data_abertura().getMes() << "/" << alojamento.at(i).get_data_abertura().getAno() << ")" << endl;
	}

	cout << endl;

	return;
}

void Concelho::show_restauracao_concelho()
{
	int number;

	if (restauracao.size() == 0)
	{
		cout << nome << " nao tem restaurantes disponiveis." << endl;
		return;
	}

	cout << nome << " tem os seguintes restaurantes:(coordenadas em graus decimais)";
	cout << endl << endl;
	for (unsigned int i = 0; i < restauracao.size(); i++)
	{
		number = i + 1;
		cout << number << ". ";
		cout << restauracao.at(i).get_nome() << " -";
		cout << " latitude: " << restauracao.at(i).get_coordenadas().get_latitude();
		cout << " / ";
		cout << "longitude: " << restauracao.at(i).get_coordenadas().get_longitude();

		if(restauracao.at(i).get_aberto() == true)
			cout << " :::: aberto" << endl;
		else if(restauracao.at(i).get_data_abertura().getDia() == 0 )
			cout << " :::: fechado permanentemente" << endl;
		else
			cout << " :::: fechado temporariamente (ate " << restauracao.at(i).get_data_abertura().getDia() << "/" << restauracao.at(i).get_data_abertura().getMes() << "/" << restauracao.at(i).get_data_abertura().getAno() << ")" << endl;
	}

	cout << endl;
}

void Concelho::show_everything()
{
	this->show_alojamento_concelho();
	this->show_restauracao_concelho();
	this->show_turismo_concelho();
	this->show_praias_concelho();
}


void Concelho::show_abertos(int ponto_interesse)
{
	bool found = false;
	int number;

	if(ponto_interesse == 1)
	{
		cout << nome << " tem os seguintes restaurantes abertos:(coordenadas em graus decimais)";
		cout << endl << endl;
		for (unsigned int i = 0; i < restauracao.size(); i++)
		{
			if(restauracao.at(i).get_aberto() == true)
			{
				found = true;
				number = i + 1;
				cout << number << ". ";
				cout << restauracao.at(i).get_nome() << " -";
				cout << " latitude: " << restauracao.at(i).get_coordenadas().get_latitude();
				cout << " / ";
				cout << "longitude: " << restauracao.at(i).get_coordenadas().get_longitude() << endl;
			}
		}

		if(!found)
			cout << "Nao existem restaurantes abertos neste concelho" << endl;

		cout << endl;
	}

	else if(ponto_interesse == 2)
	{
		cout << nome << " tem os seguintes alojamentos abertos:(coordenadas em graus decimais)";
		cout << endl << endl;
		for (unsigned int i = 0; i < alojamento.size(); i++)
		{
			if(alojamento.at(i).get_aberto() == true)
			{
				number = i + 1;
				cout << number << ". ";
				cout << alojamento.at(i).get_nome() << " -";
				cout << " latitude: " << alojamento.at(i).get_coordenadas().get_latitude();
				cout << " / ";
				cout << "longitude: " << alojamento.at(i).get_coordenadas().get_longitude() << endl;
			}
		}

		if(!found)
			cout << "Nao existem alojamentos abertos neste concelho" << endl;
		cout << endl;
	}
}

void Concelho::show_fechados(int ponto_interesse)
{
	bool found = false;
	int number;

	if(ponto_interesse == 1)
	{
		cout << nome << " tem os seguintes restaurantes fechados:(coordenadas em graus decimais)";
		cout << endl << endl;
		for (unsigned int i = 0; i < restauracao.size(); i++)
		{
			if(restauracao.at(i).get_aberto() == false)
			{
				found = true;
				number = i + 1;
				cout << number << ". ";
				cout << restauracao.at(i).get_nome() << " -";
				cout << " latitude: " << restauracao.at(i).get_coordenadas().get_latitude();
				cout << " / ";
				cout << "longitude: " << restauracao.at(i).get_coordenadas().get_longitude();

				if(restauracao.at(i).get_data_abertura().getDia() == 0)
					cout << " :::: fechado permanentemente" << endl;
				else
					cout << " :::: fechado temporariamente (ate " << restauracao.at(i).get_data_abertura().getDia() << "/" << restauracao.at(i).get_data_abertura().getMes() << "/" << restauracao.at(i).get_data_abertura().getAno() << ")" << endl;
			}
		}

		if(!found)
			cout << "Nao existem restaurantes fechados neste concelho" << endl;

		cout << endl;
	}

	else if(ponto_interesse == 2)
	{
		cout << nome << " tem os seguintes alojamentos fechados:(coordenadas em graus decimais)";
		cout << endl << endl;
		for (unsigned int i = 0; i < alojamento.size(); i++)
		{
			if(alojamento.at(i).get_aberto() == false)
			{
				number = i + 1;
				cout << number << ". ";
				cout << alojamento.at(i).get_nome() << " -";
				cout << " latitude: " << alojamento.at(i).get_coordenadas().get_latitude();
				cout << " / ";
				cout << "longitude: " << alojamento.at(i).get_coordenadas().get_longitude();

				if(alojamento.at(i).get_data_abertura().getDia() == 0 )
					cout << " :::: fechado permanentemente" << endl;
				else
					cout << " :::: fechado temporariamente (ate " << alojamento.at(i).get_data_abertura().getDia() << "/" << alojamento.at(i).get_data_abertura().getMes() << "/" << alojamento.at(i).get_data_abertura().getAno() << ")" << endl;
			}
		}

		if(!found)
			cout << "Nao existem alojamentos fechados neste concelho" << endl;
		cout << endl;
	}
}

void Concelho::add_praia(Praia_FluvialPtr praia)
{
	praias.insert(praia);
}

void Concelho::remove_praia(Praia_FluvialPtr praia_a_remover)
{
	praias.remove(praia_a_remover);
}
