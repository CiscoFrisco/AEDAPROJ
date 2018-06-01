#include "Praia_Fluvial.h"

////////////////
//constructors//
////////////////

Praia_Fluvial::Praia_Fluvial(string concelho, string nome, Coordenadas coordenadas, vector<Servico> servicos, bool bandeira_azul, int capacidade_max)
{
	this->concelho = concelho;
	this->nome = nome;
	this->coordenadas = coordenadas;
	this->servicos = servicos;
	this->bandeira_azul = bandeira_azul;
	this->capacidade_max = capacidade_max;
}

///////////////
//set_methods//
///////////////

void Praia_Fluvial::set_concelho(string concelho)
{
	this->concelho = concelho;
}

void Praia_Fluvial::set_nome(string nome)
{
	this->nome = nome;
}

void Praia_Fluvial::set_coordenadas(Coordenadas coordenadas)
{
	this->coordenadas = coordenadas;
}

void Praia_Fluvial::set_servicos(vector<Servico> servicos)
{
	this->servicos = servicos;
}

void Praia_Fluvial::set_bandeira_azul(bool bandeira_azul)
{
	this->bandeira_azul = bandeira_azul;
}

void Praia_Fluvial::set_capacidade_max(int capacidade_max)
{
	this->capacidade_max = capacidade_max;
}

///////////////
//get_methods//
///////////////

string Praia_Fluvial::get_concelho() const
{
	return concelho;
}

string Praia_Fluvial::get_nome() const
{
	return nome;
}

Coordenadas Praia_Fluvial::get_coordenadas() const
{
	return coordenadas;
}

vector<Servico> Praia_Fluvial::get_servicos() const
{
	return servicos;
}

bool Praia_Fluvial::get_bandeira_azul() const
{
	return bandeira_azul;
}

int Praia_Fluvial::get_capacidade_max() const
{
	return capacidade_max;
}

bool Praia_FluvialPtr:: operator<(Praia_FluvialPtr praia2) const{

	bool bandeira_azul = praia->get_bandeira_azul();
	bool bandeira_azul_2 = praia2.praia->get_bandeira_azul();

	if(bandeira_azul && !bandeira_azul_2)
		return true;
	else if(!bandeira_azul && bandeira_azul_2)
		return false;
	else
		return praia->get_nome() < praia2.praia->get_nome();
}

void Praia_Fluvial::show_servicos_praia()
{
	cout << "Servicos desta praia: (Tipo - Nome do Servico) " << endl << endl;

	for(unsigned int i = 0; i < servicos.size(); i++)
	{
		cout << servicos.at(i).getTipo() << " - " << servicos.at(i).getNome() << endl;
	}

	cout << endl;
}
