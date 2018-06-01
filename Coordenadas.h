#pragma once
/*
* Coordenadas.h
*/
#ifndef COORDENADAS_H_
#define COORDENADAS_H_

#include <iostream>
#include<math.h>

using namespace std;

/**
* @class Coordenadas
* @brief Classe que carateriza as coordenadas GPS.
* @param latitude Latitude de uma coordenada.
* @param longitude Longitude de uma coordenada.
*/
class Coordenadas {

	long double latitude; //Norte (+), Sul(-)
	long double longitude; //Este (+), Oeste(-)

public:

	//constructors
	/**
	* @brief Construtor da classe Coordenadas.
	* @param latitude Latitude de uma coordenada.
	* @param longitude Longitude de uma coordenada.
	*/
	Coordenadas(long double latitude, long double longitude);

	/**
	 * @brief Construtor vazio da classe coordenadas que coloca os valores de latitude e longitude a 0.
	 */
	Coordenadas();

	//set_methods
	/**
	* @brief Coloca o parametro latitude como a latitude de um local
	* @param latitude Latitude de um local
	*/
	void set_latitude(long double latitude);

	/**
	* @brief Coloca o parametro longitude como a longitude de um local
	* @param longitude Longitude de um local
	*/
	void set_longitude(long double longitude);

	//get_methods
	/**
	* @brief Vai buscar a latitude do local
	* @return Retorna um long double que representa a latitude do local
	*/
	long double get_latitude() const;

	/**
	* @brief Vai buscar a longitude do local
	* @return Retorna um long double que representa a longitude do local
	*/
	long double get_longitude() const;

	/**
	* @brief Calcula a distancia entre duas coordenadas
	* @param coordenadas Coordenada do segundo local para calcular com o primeiro (objeto ao qual e aplicado o membro-funcao)
	* @return Retorna um long double que representa a distancia entre as duas coordenadas em graus decimais.
	*/
	long double distancia_entre_coord(Coordenadas coordenadas);
};
#endif //COORDENADAS_H_
