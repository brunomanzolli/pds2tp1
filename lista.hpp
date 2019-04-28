#ifndef LISTA_H
#define LISTA_H

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

//Lista de Compromissos
struct ItemCompromisso
{
	string descricao;
	int hora, minutos;	
};

struct CelulaCompromisso
{
	ItemCompromisso item;
	CelulaCompromisso *prox;
};

struct Compromisso
{
  CelulaCompromisso *primeiro;
  CelulaCompromisso *ultimo;
};

//Lista de Mes
struct Dia
{
	Compromisso compromissos;
};
struct ItemMes
{
	int numeroMes, totalDias;
	Dia *diasDoMes;
};

struct Mes
{
	ItemMes item;
	Mes *prox;
};

struct Agenda
{
  Mes *primeiro;
  Mes *ultimo;
};

// Funções do arquivo
void preencheAgendaArquivo(Agenda *lista);
void imprimeAgendaArquivo(Agenda lista);

// Funções da Lista Mes
void iniciaAgenda(Agenda *lista);
void insereMes(ItemMes item, Agenda *lista);
Mes *buscaMes(int valorBuscado, Agenda *lista);
void liberaAgenda(Agenda *lista);

//Funções da Lista Compromisso
bool listaVazia(Compromisso *lista);
void iniciaListaCompromisso(Compromisso *lista);
void insereCompromisso(ItemCompromisso item, Compromisso *lista);
void removeCompromisso(int hora, int minutos, Compromisso *lista);
void liberaListaCompromisso(Compromisso *lista);
void imprimeListaCompromisso(Compromisso *lista);
bool verificaCompromisso(int hora, int minutos, Compromisso *lista);

#endif
