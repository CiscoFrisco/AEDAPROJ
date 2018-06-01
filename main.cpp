#include <iostream>
#include "Guia_de_Praias.h"

using namespace std;

int main()
{
	cout << "Va para fora, ca dentro" << endl;

	string nome_ficheiro_concelhos = "Concelhos.txt";
	string nome_ficheiro_praias = "Praias.txt";
	string nome_ficheiro_hash = "Hash.txt";
	Data curr_data;

	Guia_de_Praias Guia_de_Praias("Va para fora, ca dentro", nome_ficheiro_concelhos, nome_ficheiro_praias, nome_ficheiro_hash, &curr_data);

	cout << curr_data.getDia() << "/" << curr_data.getMes() << "/" << curr_data.getAno() << endl;

	int operacao = -1; // Inicializar com um valor diferente de 0

	//Ciclo do menu principal

	while (operacao != 0)
	{

		cout << endl << "O que quer fazer? " << endl << endl << "0. Sair" << endl << "1. Ver Informacao" << endl << "2. Pesquisar Informacao" << endl << "3. Gerir Informacao" << endl << "4. Avancar data."<< endl <<  "Se inserir outro valor numerico que nao estes voltara ao menu principal." << endl << endl;

		cin >> operacao;

		while (cin.fail())
		{
			cout << "Input nao e uma opcao valida. Por favor tente de novo.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> operacao;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		int operacao_ciclo;
		int informacao, informacao2,informacao3;
		int tipo_de_praia; //para escolher que tipo de praia adicionar
		//int operacao2;

		switch (operacao)
		{
		case 1:
		{
			cout << endl << "O que quer ver?(Introduza numero correspondente)" << endl << endl << "1. Listar todas as Praias"<< endl << "2. Informacao de uma Praia" << endl << "3. Listar todos os Concelhos"<< endl << "4. Informacao de um Concelho" << endl << "5. Listar Inspecoes" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;

			cin >> operacao_ciclo;
			cin.clear();
			cin.ignore(1000, '\n');

			if (operacao_ciclo == 1)
			{
				Guia_de_Praias.show_praias();
			}

			if (operacao_ciclo == 2)
			{
				try {
					Guia_de_Praias.show_praias();
					Guia_de_Praias.show_informacao_praia();
				}
				catch (PraiaNaoExistente &e)
				{
					cout << endl << "A praia que foi inserida (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
				}
			}

			if (operacao_ciclo == 3)
			{
				Guia_de_Praias.show_concelhos();
			}
			else if (operacao_ciclo == 4)
			{
				cout << "O que quer ver?(Introduza o numero correspondente)" << endl << endl << "1. Ver Lista de Restaurantes de um Concelho" << endl << "2. Ver Lista de Alojamentos de um Concelho" << endl << "3. Ver Lista de Pontos Turisticos de um Concelho" << endl << "4. Ver Lista de Praias de um Concelho" << endl << "5. Ver toda a informacao de um Concelho" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl;
				cin >> informacao;
				cin.clear();
				cin.ignore(1000, '\n');
				if (informacao == 1)
				{
					int rest;
					cout << "O que quer ver?(introduza o numero correspondente)" << endl << endl << "1. Restaurantes atualmente abertos" << endl << "2. Restaurantes atualmente fechados" << endl << "3. Ver todos os Restaurantes" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl;
					cin >> rest;
					cin.clear();
					cin.ignore(1000,'\n');

					if(rest == 1)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_concelhos();
							Guia_de_Praias.show_informacao_concelho(6);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
						}
					}

					if(rest == 2)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_concelhos();
							Guia_de_Praias.show_informacao_concelho(7);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
						}
					}

					if(rest == 3)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_concelhos();
							Guia_de_Praias.show_informacao_concelho(1);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
						}
					}
				}

				else if (informacao == 2)
				{
					int aloj;
					cout << "O que quer ver?(introduza o numero correspondente)" << endl << endl << "1. Alojamentos atualmente abertos" << endl << "2. Alojamentos atualmente fechados" << endl << "3. Ver todos os Alojamentos" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl;
					cin >> aloj;
					cin.clear();
					cin.ignore(1000,'\n');

					if(aloj == 1)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_concelhos();
							Guia_de_Praias.show_informacao_concelho(8);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
						}
					}

					if(aloj == 2)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_concelhos();
							Guia_de_Praias.show_informacao_concelho(9);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
						}
					}

					if(aloj == 3)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_concelhos();
							Guia_de_Praias.show_informacao_concelho(2);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
						}
					}
				}
				else if (informacao == 3)
				{
					try {
						cout << endl;
						Guia_de_Praias.show_concelhos();
						Guia_de_Praias.show_informacao_concelho(3);
					}
					catch (ConcelhoNaoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
					}
				}
				else if (informacao == 4)
				{
					try {
						cout << endl;
						Guia_de_Praias.show_concelhos();
						Guia_de_Praias.show_informacao_concelho(4);
					}
					catch (ConcelhoNaoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
					}
				}

				else if (informacao == 5)
				{
					try {
						cout << endl;
						Guia_de_Praias.show_concelhos();
						Guia_de_Praias.show_informacao_concelho(5);
					}
					catch (ConcelhoNaoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados." << endl;
					}
				}
			}

			else if(operacao_ciclo == 5)
			{
				int input;
				cout << "O que quer ver?(introduza o numero correspondente)" << endl << endl << "1. Inspecoes por tipo" << endl << "2. Inspecoes por concelho" << endl << "3. Inspecoes por praia" << endl << "4. Todas as inspecoes realizadas ate ao momento" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl;
				cin >> input;
				cin.clear();
				cin.ignore(1000,'\n');

				if(input == 1)
				{
					try{
						string tipo = Guia_de_Praias.pergunta_tipo();
						Guia_de_Praias.show_inspecao_tipo(tipo);

					}catch(TipoNaoExistente &e){
						cout << endl << "O tipo de servico inserido (" << e.getNome() <<") nao possui nenhuma inspecao realizada" << endl;
					}
				}
				else if(input == 2)
				{
					try{
						Guia_de_Praias.show_concelhos();
						Guia_de_Praias.show_inspecao_concelho();
					}catch (ConcelhoNaoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") nao possui inspecoes realizdas." << endl;
					}
				}
				else if(input == 3)
				{
					try{
						Guia_de_Praias.show_praias();
						Guia_de_Praias.show_inspecao_praia();
					}catch (PraiaNaoExistente &e){
						cout << endl << "A praia que foi inserida (" << e.getNome() << ") nao possui inspecoes realizadas." << endl;
					}
				}
				else if(input == 4)
				{
					Guia_de_Praias.show_inspecao_geral();
				}
			}
		}
		break;
		case 2:
		{
			cout << endl << "O que quer pesquisar?(Introduza numero correspondente)" << endl << endl << "1. Pontos de Interesse perto de uma Praia" << endl << "2. Praia mais proxima de um local" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;
			cin >> operacao_ciclo;
			cin.clear();
			cin.ignore(1000, '\n');
			if (operacao_ciclo == 1)
			{
				cout << endl << "Qual o tipo de Ponto de Interesse a pesquisar?(Introduza numero correspondente)" << endl << endl << "1. Alojamentos" << endl << "2. Restaurantes" << endl << "3. Pontos Turisticos" << endl << "4. Praias" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;
				cin >> informacao2;
				cin.clear();
				cin.ignore(1000, '\n');
				if (informacao2 == 1) {
					cout << endl;

					try
					{
						Guia_de_Praias.search_ponto_interesse_proximos_auxiliar(1);
					}
					// se a praia n�o estiver presente em nenhum concelho lan�a uma exce��o
					catch (PraiaNaoExistente & e)
					{
						cout << endl << "A praia inserida (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
				else if (informacao2 == 2)
				{
					cout << endl;
					try {
						Guia_de_Praias.search_ponto_interesse_proximos_auxiliar(2);
					}
					// se a praia n�o estiver presente em nenhum concelho lan�a uma exce��o
					catch (PraiaNaoExistente & e)
					{
						cout << endl << "A praia inserida (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
				else if (informacao2 == 3)
				{
					cout << endl;
					try {
						Guia_de_Praias.search_ponto_interesse_proximos_auxiliar(3);
					}
					// se a praia n�o estiver presente em nenhum concelho lan�a uma exce��o
					catch (PraiaNaoExistente & e)
					{
						cout << endl << "A praia inserida (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
				else if (informacao2 == 4)
				{
					cout << endl;
					try {
						Guia_de_Praias.search_ponto_interesse_proximos_auxiliar(4);
					}
					// se a praia n�o estiver presente em nenhum concelho lan�a uma exce��o
					catch (PraiaNaoExistente & e)
					{
						cout << endl << "A praia inserida (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
			}
			//se escolher Praia mais proxima de um local
			else if (operacao_ciclo == 2) {
				cout << endl << "1. Praia mais proxima de um Alojamento" << endl << "2. Praia mais proxima de um Restaurante" << endl << "3. Praia mais proxima de um Ponto Turistico" << endl << "4. Praia mais proxima de outra Praia" << endl << "5. Praia mais proxima de um local (inserir coordenadas)" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;
				cin >> informacao2;
				cin.clear();
				cin.ignore(1000, '\n');

				if (informacao2 == 1) {
					try{
						cout << endl;
						//show todos os alojamentos
						for(unsigned int i = 0; i < Guia_de_Praias.get_concelhos().size(); i++)
						{
							cout << Guia_de_Praias.get_concelhos().at(i).get_nome() << ":" << endl;

							for(unsigned int j = 0; j < Guia_de_Praias.get_concelhos().at(i).get_alojamento().size(); j++)
							{
								cout << Guia_de_Praias.get_concelhos().at(i).get_alojamento().at(j).get_nome();
								cout << " - ";
								cout << Guia_de_Praias.get_concelhos().at(i).get_alojamento().at(j).get_coordenadas().get_latitude();
								cout << " / ";
								cout << Guia_de_Praias.get_concelhos().at(i).get_alojamento().at(j).get_coordenadas().get_longitude();
								cout << endl;
							}
							cout << endl;
						}
						Guia_de_Praias.search_praia_mais_proxima(1);
					}
					catch (PontoInteresseNaoExistente & e)
					{
						cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}

				}
				else if (informacao2 == 2) {
					try{
						cout << endl;
						//show todos os restaurantes
						for(unsigned int i = 0; i < Guia_de_Praias.get_concelhos().size(); i++)
						{
							cout << Guia_de_Praias.get_concelhos().at(i).get_nome() << ":" << endl;

							for(unsigned int j = 0; j < Guia_de_Praias.get_concelhos().at(i).get_restauracao().size(); j++)
							{
								cout << Guia_de_Praias.get_concelhos().at(i).get_restauracao().at(j).get_nome();
								cout << " - ";
								cout << Guia_de_Praias.get_concelhos().at(i).get_restauracao().at(j).get_coordenadas().get_latitude();
								cout << " / ";
								cout << Guia_de_Praias.get_concelhos().at(i).get_restauracao().at(j).get_coordenadas().get_longitude();
								cout << endl;
							}
							cout << endl;
						}
						Guia_de_Praias.search_praia_mais_proxima(2);
					}
					catch (PontoInteresseNaoExistente & e)
					{
						cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
				else if (informacao2 == 3) {
					try{
						cout << endl;
						//show todos os pontos turisticos
						for(unsigned int i = 0; i < Guia_de_Praias.get_concelhos().size(); i++)
						{
							cout << Guia_de_Praias.get_concelhos().at(i).get_nome() << ":" << endl;

							for(unsigned int j = 0; j < Guia_de_Praias.get_concelhos().at(i).get_turismo().size(); j++)
							{
								cout << Guia_de_Praias.get_concelhos().at(i).get_turismo().at(j).get_nome();
								cout << " - ";
								cout << Guia_de_Praias.get_concelhos().at(i).get_turismo().at(j).get_coordenadas().get_latitude();
								cout << " / ";
								cout << Guia_de_Praias.get_concelhos().at(i).get_turismo().at(j).get_coordenadas().get_longitude();
								cout << endl;
							}
							cout << endl;
						}
						Guia_de_Praias.search_praia_mais_proxima(3);
					}
					catch (PontoInteresseNaoExistente & e)
					{
						cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
				else if (informacao2 == 4) {
					try{
						cout << endl;
						Guia_de_Praias.show_praias();
						Guia_de_Praias.search_praia_mais_proxima(4);
					}
					catch (PontoInteresseNaoExistente & e)
					{
						cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
				else if (informacao2 == 5) {
					try{
						cout << endl;
						Guia_de_Praias.search_praia_mais_proxima(5);
					}
					catch (PontoInteresseNaoExistente & e)
					{
						cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
			}
		}
		break;
		case 3:
		{
			cout << "O que quer gerir?" << endl << endl << "1. Gerir Praias" << endl << "2. Gerir Concelhos" << endl << "3. Gerir Pontos de Interesse(Restaurantes e Alojamentos)" << endl << "4. Realizar Inspecao" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;
			cin >> operacao_ciclo;
			cin.clear();
			cin.ignore(1000, '\n');

			if (operacao_ciclo == 1)
			{
				cout << "O que deseja fazer?" << endl << endl << "1. Adicionar Praia" << endl << "2. Remover Praia" << endl << "3. Editar Praia" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;

				cin >> informacao3;
				cin.clear();
				cin.ignore(1000, '\n');

				if (informacao3 == 1)
				{
					cout << "De que tipo?" << endl << "1. Adicionar Praia baseada em Rio" << endl << "2. Adicionar Praia baseada em Albufeira" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;

					cin >> tipo_de_praia;
					cin.clear();
					cin.ignore(1000, '\n');
					//apenas entra se inserir um tipo de praia de entre os dois do menu
					if(tipo_de_praia == 1 || tipo_de_praia == 2)
					{
						try {
							Guia_de_Praias.add_praia(tipo_de_praia);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}

						catch (PraiaExistente &e) {
							cout << endl << "A praia inserida (" << e.getNome() << ") ja existe na nossa base de dados" << endl;
						}
					}
				}

				else if (informacao3 == 2)
				{
					try {
						cout << endl;
						Guia_de_Praias.show_praias();
						cout << endl;
						Guia_de_Praias.remove_praia();
					}
					catch (PraiaNaoExistente &e) {
						cout << endl << "A praia inserida (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}

				else if (informacao3 == 3)
				{
					try {
						Guia_de_Praias.editar_praia();
					}
					catch (PraiaExistente &e) {
						cout << endl << "A praia inserida (" << e.getNome() << ") ja existe na nossa base de dados" << endl;
					}
					catch (PraiaNaoExistente &e) {
						cout << endl << "A praia inserida (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
					catch (ConcelhoNaoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados. As alteracaoes feitas nao foram guardadas." << endl;
					}
				}
			}

			else if (operacao_ciclo == 2)
			{
				cout << "O que deseja fazer?" << endl << endl << "1. Adicionar Concelho" << endl << "2. Remover Concelho" << endl << "3. Editar Concelho" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;

				cin >> informacao3;
				cin.clear();
				cin.ignore(1000, '\n');

				if (informacao3 == 1)
				{
					try {
						Guia_de_Praias.add_concelho();
					}
					catch (ConcelhoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") ja existe na nossa base de dados" << endl;
					}
				}

				else if (informacao3 == 2)
				{
					try {
						cout << endl;
						Guia_de_Praias.show_concelhos();
						cout << endl;
						Guia_de_Praias.remove_concelho();
					}
					catch (ConcelhoNaoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}

				else if (informacao3 == 3)
				{
					try {
						Guia_de_Praias.editar_concelho();
					}
					catch (ConcelhoNaoExistente &e) {
						cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
					}
				}
			}


			else if (operacao_ciclo == 3)
			{
				cout << "O que deseja fazer?" << endl << endl << "1. Fechar Ponto de Interesse" << endl << "2. Reabrir Ponto de Interesse" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;

				cin >> informacao3;
				cin.clear();
				cin.ignore(1000, '\n');

				if (informacao3 == 1)
				{
					int type;
					cout << "De que tipo?" << endl << endl << "1.Restaurante" << endl << "2.Alojamento" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;
					cin >> type;
					cin.clear();
					cin.ignore(1000,'\n');

					if(type == 1)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_informacao_concelho(1);
							cout << endl;
							Guia_de_Praias.fechar_restauracao(curr_data);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
						catch(PontoInteresseNaoExistente &e){
							cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
						catch(DataInvalida &e){
							cout << endl << "A data inserida (" << e.getData().getDia() << "/" << e.getData().getMes() << "/" << e.getData().getAno() << ") nao existe." << endl;
						}
						catch(DataImpossivel &e){
							cout << endl << "A data inserida (" << e.getDataUser().getDia() << "/" << e.getDataUser().getMes() << "/" << e.getDataUser().getAno() << ") e inferior a data atual (" << e.getDataCurr().getDia() << "/" << e.getDataCurr().getMes() << "/" << e.getDataCurr().getAno() << ")." << endl;
						}
						catch(DataIncompativel &e){
							cout << endl << "A data de reabertura (" << e.getDataAbertura().getDia() << "/" << e.getDataAbertura().getMes() << "/" << e.getDataAbertura().getAno() << ") antecede a data de fecho (" << e.getDataFecho().getDia() << "/" << e.getDataFecho().getMes() << "/" << e.getDataFecho().getAno() << ")." << endl;
						}
					}

					else if (type == 2)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_informacao_concelho(2);
							cout << endl;
							Guia_de_Praias.fechar_alojamento(curr_data);
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
						catch(PontoInteresseNaoExistente &e){
							cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
						catch(DataInvalida &e){
							cout << endl << "A data inserida (" << e.getData().getDia() << "/" << e.getData().getMes() << "/" << e.getData().getAno() << ") nao existe." << endl;
						}
						catch(DataImpossivel &e){
							cout << endl << "A data inserida (" << e.getDataUser().getDia() << "/" << e.getDataUser().getMes() << "/" << e.getDataUser().getAno() << ") e inferior a data atual (" << e.getDataCurr().getDia() << "/" << e.getDataCurr().getMes() << "/" << e.getDataCurr().getAno() << ")." << endl;
						}
						catch(DataIncompativel &e){
							cout << endl << "A data de reabertura (" << e.getDataAbertura().getDia() << "/" << e.getDataAbertura().getMes() << "/" << e.getDataAbertura().getAno() << ") antecede a data de fecho (" << e.getDataFecho().getDia() << "/" << e.getDataFecho().getMes() << "/" << e.getDataFecho().getAno() << ")." << endl;
						}
					}
				}
				else if (informacao3 == 2)
				{
					int type;
					cout << "De que tipo?" << endl << endl << "1.Restaurante" << endl << "2.Alojamento" << endl << "Se introduzir um qualquer outro carater, retornara ao menu inicial" << endl << endl;
					cin >> type;
					cin.clear();
					cin.ignore(1000,'\n');

					if(type == 1)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_informacao_concelho(1);
							cout << endl;
							Guia_de_Praias.reabrir_restauracao();
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
						catch(PontoInteresseNaoExistente &e){
							cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
					}

					else if (type == 2)
					{
						try {
							cout << endl;
							Guia_de_Praias.show_informacao_concelho(2);
							cout << endl;
							Guia_de_Praias.reabrir_alojamento();
						}
						catch (ConcelhoNaoExistente &e) {
							cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
						catch(PontoInteresseNaoExistente &e){
							cout << endl << "O ponto de interesse inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
						}
					}
				}
			}

			else if(operacao_ciclo == 4)
			{
				try{
					cout << endl;
					Guia_de_Praias.add_inspecao(&curr_data);
				}
				catch (ConcelhoNaoExistente &e) {
					cout << endl << "O concelho inserido (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
				}
				catch(PraiaNaoExistente &e){
					cout << endl << "A praia inserida (" << e.getNome() << ") nao existe na nossa base de dados" << endl;
				}
				catch(ServicoNaoExistente &e){
					cout << endl << "O servico inserido (" << e.getNome() << ") nao existe nesta praia" << endl;
				}
				catch(DataInvalida &e){
					cout << endl << "A data inserida (" << e.getData().getDia() << "/" << e.getData().getMes() << "/" << e.getData().getAno() << ") nao existe." << endl;
				}
				catch(DataImpossivel &e){
					cout << endl << "A data inserida (" << e.getDataUser().getDia() << "/" << e.getDataUser().getMes() << "/" << e.getDataUser().getAno() << ") e inferior a data atual (" << e.getDataCurr().getDia() << "/" << e.getDataCurr().getMes() << "/" << e.getDataCurr().getAno() << ")." << endl;
				}
				catch(DataIncompativel &e){
					cout << endl << "A data de reabertura (" << e.getDataAbertura().getDia() << "/" << e.getDataAbertura().getMes() << "/" << e.getDataAbertura().getAno() << ") antecede a data de fecho (" << e.getDataFecho().getDia() << "/" << e.getDataFecho().getMes() << "/" << e.getDataFecho().getAno() << ")." << endl;
				}
			}
		}
		break;
		case 4:
		{
			try{
				Guia_de_Praias.avanca_data(&curr_data);
			}
			catch(DataInvalida &e){
				cout << endl << "A data inserida (" << e.getData().getDia() << "/" << e.getData().getMes() << "/" << e.getData().getAno() << ") nao existe." << endl;
			}
			catch(DataImpossivel &e){
				cout << endl << "A data inserida (" << e.getDataUser().getDia() << "/" << e.getDataUser().getMes() << "/" << e.getDataUser().getAno() << ") e inferior a data atual (" << e.getDataCurr().getDia() << "/" << e.getDataCurr().getMes() << "/" << e.getDataCurr().getAno() << ")." << endl;
			}
		}
		cout << endl;
		}
	}

	string guardar;

	//Pergunta ao utilizador se quer guardar, se sim guarda e depois fecha

	cout << "Deseja guardar as alteracoes(Y/N)? ";

	getline(cin, guardar);

	while (guardar != "Y" && guardar != "y" && guardar != "N" && guardar != "n")
	{
		cout << "Conteudo introduzido incorretamente. Tente novamente: ";
		getline(cin, guardar);
	}

	if (guardar == "Y" || guardar == "y")
	{
		Guia_de_Praias.guardar_ficheiros(nome_ficheiro_concelhos, nome_ficheiro_praias, nome_ficheiro_hash,curr_data);
	}

	cout << endl << endl;

	//system("pause");
}

