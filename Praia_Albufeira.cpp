#include "Praia_Albufeira.h"


////////////////
//constructors//
////////////////

Praia_Albufeira::Praia_Albufeira(string concelho, string nome, Coordenadas coordenadas, vector<Servico> servicos, bool bandeira_azul, int capacidade_max, float area_aquatica) : Praia_Fluvial(concelho, nome, coordenadas, servicos, bandeira_azul, capacidade_max)
{
	this->area_aquatica = area_aquatica;
}


///////////////
//set_methods//
///////////////

void Praia_Albufeira::set_area_aquatica(float area_aquatica)
{
	this->area_aquatica = area_aquatica;
}

///////////////
//get_methods//
///////////////

float Praia_Albufeira::get_area_aquatica() const
{
	return area_aquatica;
}

////////////////
//show_methods//
////////////////

void Praia_Albufeira::show_informacao_praia()
{
	cout << endl << "Informacoes sobre a praia " << nome << ":(praia baseada numa albufeira)" << endl;
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

	cout << "Tem uma area aquatica de " << area_aquatica << " metros quadrados." << endl;

}

/////////////////
//other_methods//
/////////////////

void Praia_Albufeira::editar_praia(string nome_praia, Coordenadas coord, vector<Servico> servs, bool bandeira, int capacidade)
{
	nome = nome_praia;
	coordenadas = coord;
	servicos = servs;
	bandeira_azul = bandeira;
	capacidade_max = capacidade;

	char answer;
	double area;

	cout << "Deseja alterar a area aquatica da praia?[Y/N]: ";
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
		cout << "Insira uma nova area aquatica: ";
		cin >> area;

		while (cin.fail())
		{
			cout << "Valor nao numerico. Por favor tente outra vez: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> area;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		area_aquatica = area;
	}
}

void Praia_Albufeira::escreve_ficheiro_derivadas(ofstream &stream_praias)
{
	stream_praias << 2 << " ; " << area_aquatica << " ;" ;
}

