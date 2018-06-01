#include "Pontos_Interesse.h"


///////////
//Turismo//
///////////

Turismo::Turismo(string nome, Coordenadas coordenadas)
{
	this->nome = nome;
	this->coordenadas = coordenadas;
}

void Turismo::set_nome(string nome)
{
	this->nome = nome;
}

void Turismo::set_coordenadas(Coordenadas coordenadas)
{
	this->coordenadas = coordenadas;
}

string Turismo::get_nome() const
{
	return nome;
}

Coordenadas Turismo::get_coordenadas() const
{
	return coordenadas;
}

//////////////
//Alojamento//
//////////////

Alojamento::Alojamento(string nome, Coordenadas coordenadas, bool aberto)
{
	this->nome = nome;
	this->coordenadas = coordenadas;
	this->aberto = aberto;
}

void Alojamento::set_nome(string nome)
{
	this->nome = nome;
}


void Alojamento::set_coordenadas(Coordenadas coordenadas)
{
	this->coordenadas = coordenadas;
}


void Alojamento::set_aberto(bool aberto)
{
	this->aberto = aberto;
}


void Alojamento::set_data_abertura(Data data_abertura)
{
	this->abertura = data_abertura;
}


void Alojamento::set_data_fecho(Data data_fecho)
{
	this->fecho = data_fecho;
}


string Alojamento::get_nome() const
{
	return nome;
}


Coordenadas Alojamento::get_coordenadas() const
{
	return coordenadas;
}


bool Alojamento::get_aberto()
{
	return aberto;
}


Data Alojamento::get_data_abertura() const
{
	return abertura;
}


Data Alojamento::get_data_fecho() const
{
	return fecho;
}

///////////////
//Restauracao//
///////////////


Restauracao::Restauracao(string nome, Coordenadas coordenadas, bool aberto)
{
	this->nome = nome;
	this->coordenadas = coordenadas;
	this->aberto = aberto;
}


void Restauracao::set_nome(string nome)
{
	this->nome = nome;
}


void Restauracao::set_coordenadas(Coordenadas coordenadas)
{
	this->coordenadas = coordenadas;
}


void Restauracao::set_aberto(bool aberto)
{
	this->aberto = aberto;
}


void Restauracao::set_data_abertura(Data data_abertura)
{
	this->abertura = data_abertura;
}


void Restauracao::set_data_fecho(Data data_fecho)
{
	this->fecho = data_fecho;
}


string Restauracao::get_nome() const
{
	return nome;
}


Coordenadas Restauracao::get_coordenadas() const
{
	return coordenadas;
}


bool Restauracao::get_aberto()
{
	return aberto;
}


Data Restauracao::get_data_abertura() const
{
	return abertura;
}


Data Restauracao::get_data_fecho() const
{
	return fecho;
}
