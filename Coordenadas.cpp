#include"Coordenadas.h"


////////////////
//constructors//
////////////////

Coordenadas::Coordenadas(long double latitude, long double longitude)
{
	this->latitude = latitude;
	this->longitude = longitude;
}

Coordenadas::Coordenadas() : latitude(0.0), longitude(0.0) {}


///////////////
//set_methods//
///////////////

void Coordenadas::set_latitude(long double latitude)
{
	this->latitude = latitude;
}

void Coordenadas::set_longitude(long double longitude)
{
	this->longitude = longitude;
}

///////////////
//get_methods//
///////////////

long double Coordenadas::get_latitude() const
{
	return latitude;
}

long double Coordenadas::get_longitude() const
{
	return longitude;
}

long double Coordenadas::distancia_entre_coord(Coordenadas coordenadas)
{
	long double distancia;//variavel de retorno, onde se guarda a distancia entre dois pontos.

	distancia = sqrt(pow(latitude - coordenadas.get_latitude(), 2) + pow(longitude - coordenadas.get_longitude(), 2));

	return distancia;
}




