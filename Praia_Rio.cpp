#include "Praia_Rio.h"


////////////////
//constructors//
////////////////

Praia_Rio::Praia_Rio(string concelho, string nome, Coordenadas coordenadas, vector<Servico> servicos, bool bandeira_azul, int capacidade_max, float largura, float caudal, float profundidade) :Praia_Fluvial(concelho, nome, coordenadas, servicos, bandeira_azul, capacidade_max)
{
	this->largura = largura;
	this->caudal = caudal;
	this->profundidade = profundidade;
}


///////////////
//set_methods//
///////////////

void Praia_Rio::set_largura(float largura)
{
	this->largura = largura;
}

void Praia_Rio::set_caudal(float caudal)
{
	this->caudal = caudal;
}

void Praia_Rio::set_profundidade(float profundidade)
{
	this->profundidade = profundidade;
}

///////////////
//get_methods//
///////////////

float Praia_Rio::get_largura() const
{
	return largura;
}

float Praia_Rio::get_caudal() const
{
	return caudal;
}

float Praia_Rio::get_profundidade() const
{
	return profundidade;
}

void Praia_Rio::show_informacao_praia()
{
	cout << endl << "Informacoes sobre a praia " << nome << ":(praia baseada num rio)" << endl;
	cout << endl;
	cout << "Esta praia pertence ao Concelho de " << concelho << "." << endl;
	cout << "As suas coordenadas sao: " << "latitude - " << coordenadas.get_latitude() << " / longitude - " << coordenadas.get_longitude() << endl;

	if (servicos.size() == 0)
			cout << "A praia nao possui quaisquer servicos." << endl;
		else
		{
			cout << "A praia tem os seguintes servicos:(Tipo - Nome) " << endl << endl;

			if(servicos.size() == 1)
				cout << servicos.at(0).getTipo() << " - " << servicos.at(0).getNome();

			else
			{
				for (unsigned int i = 0; i < servicos.size(); i++)
				{
					cout << servicos.at(i).getTipo() << " - " << servicos.at(i).getNome() << endl;
				}

				cout << endl;
			}
		}

	if (bandeira_azul)
		cout << "Possui bandeira azul." << endl;
	else
		cout << "Nao possui bandeira azul." << endl;

	if (capacidade_max == 1)
		cout << "Tem uma capacidade de " << capacidade_max << " pessoa." << endl;
	else
		cout << "Tem uma capacidade de " << capacidade_max << " pessoas." << endl;

	cout << "Tem uma proundidade de " << profundidade << " metros, um caudal de " << caudal << " metros cubicos por segundo e uma largura de " << largura << " metros." << endl;


}

void Praia_Rio::editar_praia(string nome_praia, Coordenadas coord, vector<Servico> servs, bool bandeira, int capacidade)
{
	nome = nome_praia;
	coordenadas = coord;
	servicos = servs;
	bandeira_azul = bandeira;
	capacidade_max = capacidade;


	char answer;
	double profund, caud, larg;

	cout << "Deseja alterar a profundidade da praia?[Y/N]: ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira uma nova profundidade: ";
		cin >> profund;

		while (cin.fail())
		{
			cout << "Valor nao numerico. Por favor tente outra vez: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> profund;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		profundidade = profund;
	}

	cout << "Deseja alterar a largura da praia?[Y/N]: ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira uma nova largura: ";
		cin >> larg;

		while (cin.fail())
		{
			cout << "Valor nao numerico. Por favor tente outra vez: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> larg;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		largura = larg;
	}

	cout << "Deseja alterar o caudal da praia?[Y/N]: ";
	cin >> answer;

	while (answer != 'Y' && answer != 'y' && answer != 'N'  && answer != 'n')
	{
		cout << "Input invalida. Por favor tente outra vez: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}

	cin.ignore(10000, '\n');

	if (answer == 'Y' || answer == 'y')
	{
		cout << "Insira um novo caudal: ";
		cin >> caud;

		while (cin.fail())
		{
			cout << "Valor nao numerico. Por favor tente outra vez: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> caud;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		caudal = caud;
	}
}

void Praia_Rio::escreve_ficheiro_derivadas(ofstream &stream_praias)
{
	stream_praias << 1 << " ; " <<  largura << " ; " << caudal << " ; " << profundidade << " ;";
}

