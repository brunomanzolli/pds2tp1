#ifndef LISTA_C
#define LISTA_C
#include "lista.hpp"

//Funções do arquivo
void preencheAgendaArquivo(Agenda *lista)
{
  int dia;
  string linha;
  
  Mes *aux;
  Compromisso compAux;
  ItemMes itemMesAux;
  ItemCompromisso itemCompAux; 
  
  ifstream entrada("agenda.txt");
  
  if(entrada.is_open()){
    while ( getline (entrada,linha) ) {
      if(linha.front() == '>'){ // Encontrou um mes
        linha.erase (linha.begin());
        aux = buscaMes(atoi(linha.c_str()), lista); //Acha o mes da lista
        
      }
      else if (linha.substr(0,3) == "Dia") // Encontrou um dia
      {
        dia = atoi(linha.substr(5,2).c_str());
      }
      else // encontrou um comprommisso
      {
        itemCompAux.hora = atoi(linha.substr(0,2).c_str());
        itemCompAux.minutos = atoi(linha.substr(3,2).c_str());
        itemCompAux.descricao = linha.substr(8).c_str();
        insereCompromisso(itemCompAux, &aux->item.diasDoMes[dia-1].compromissos); //insere o compromisso na sua devida lista
      }
    }
  }
}

void imprimeAgendaArquivo(Agenda lista)
{
  ofstream saida ("agenda.txt");
  Mes *aux = lista.primeiro->prox;
  CelulaCompromisso *compAux;
  
  while(aux != NULL){ //Percorre todos os meses
    saida << ">" << aux->item.numeroMes << endl;
    for (int i = 0; i < aux->item.totalDias; i++) { //Percorre cada dia do mes
      if(!listaVazia(&aux->item.diasDoMes[i].compromissos)){ // se houver algum compromisso no dia, irá imprimir.
        compAux = aux->item.diasDoMes[i].compromissos.primeiro->prox;
        saida << "Dia: " << i+1 << endl;
        while(compAux != NULL){ //percorre os compromissos inseridos
          saida << setfill('0') << setw(2) << compAux->item.hora << ":" << setw(2) << compAux->item.minutos << " - " << compAux->item.descricao << endl;
          compAux = compAux->prox;
        }
      }
    }
    aux = aux->prox;
  }
  saida.close();
}

//Funções da Lista Mes
void iniciaAgenda(Agenda *lista)
{
  lista->primeiro = (Mes*)calloc(1, sizeof(Mes));
  lista->ultimo = lista->primeiro;
  lista->primeiro->prox = NULL;

  ItemMes m;
  
  for (int i = 1; i <= 12; ++i) //insere todos os meses na lista
  {
    m.numeroMes = i;
    if (m.numeroMes == 1 || m.numeroMes == 3 || m.numeroMes == 5 || m.numeroMes == 7 || m.numeroMes == 8 || m.numeroMes == 10 || m.numeroMes == 12)
    {
      m.totalDias = 31;
    }
    else if(m.numeroMes == 2)
    {
      m.totalDias = 28;
    }
    else
    {
      m.totalDias = 30;
    }
    m.diasDoMes = (Dia*)calloc(m.totalDias, sizeof(Dia));
    for (int j = 0; j < m.totalDias; j++) //para cada dia do mes, inicia a lista de compromissos
    {
      iniciaListaCompromisso(&m.diasDoMes[j].compromissos); 
    }
    insereMes(m, lista);
  }
}

Mes *buscaMes (int valorBuscado, Agenda *lista)
{
  Mes *aux = lista->primeiro->prox; //começa no prox pois o primeiro é vazio por ser a celula cabeça
  while(aux->item.numeroMes != valorBuscado && aux->prox != NULL)
  {
    aux = aux->prox;
  }
  if (aux->item.numeroMes != valorBuscado)
    return NULL;
  else //se encontrou o mes, irá retorna-lo.
    return aux;
}

void insereMes(ItemMes item, Agenda *lista) //insere o mes ao final da lista
{
  lista->ultimo->prox = (Mes*)calloc(1, sizeof(Mes));
  lista->ultimo = lista->ultimo->prox;
  lista->ultimo->item = item;
  lista->ultimo->prox = NULL;
}

void liberaAgenda(Agenda *lista) //da free na estrutura inteira
{
  Mes *aux = lista->primeiro;
  Mes *auxProx;
  while(aux != NULL)
  {
    auxProx = aux->prox;
    for (int i = 0; i < aux->item.totalDias; i++) //para cada dia, libera a lista de compromissos
    {
      liberaListaCompromisso(&aux->item.diasDoMes[i].compromissos);     
    }
    free(aux->item.diasDoMes);
    free(aux);
    aux = auxProx;
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
}

//Funções da Lista Compromissos

void iniciaListaCompromisso(Compromisso *lista) 
{
  lista->primeiro = (CelulaCompromisso*)calloc(1, sizeof(CelulaCompromisso));
  lista->ultimo = lista->primeiro;
  lista->primeiro->prox = NULL;
}

bool listaVazia(Compromisso *lista)
{
  return (lista->primeiro == lista->ultimo);
}

void insereCompromisso(ItemCompromisso item, Compromisso *lista) //insere o compromisso ao fim da lista
{
  lista->ultimo->prox = (CelulaCompromisso*)calloc(1, sizeof(CelulaCompromisso));
  lista->ultimo = lista->ultimo->prox;
  lista->ultimo->item = item;
  lista->ultimo->prox = NULL;
}

void removeCompromisso(int hora, int minutos, Compromisso *lista) //percorre a lista até encontrar o compromisso e o remove
{
  if(!verificaCompromisso(hora, minutos, lista)) //Se o compromisso não existe, não será realizado nada.
  {
    cout << "Compromisso não encontrado" << endl;
    return;
  } 

  CelulaCompromisso *ant = lista->primeiro;
  while(!(ant->prox->item.hora == hora && ant->prox->item.minutos == minutos)){
    ant = ant->prox;
  }

  CelulaCompromisso *aux = ant->prox;
  if (aux->prox != NULL ) //caso nao seja o ultimo da lista, o anterior apenas aponta pro proximo
  {
    ant->prox = aux->prox;
    free(aux);
  }
  else //caso seja o ultimo elemento da lista, o pronteiro ultimo deve ser o elemento anterior
  {
    lista->ultimo = ant;
    lista->ultimo->prox = NULL;
    free(aux);
  }
  cout << "O compromisso acima foi deletado" << endl; // Essa mensagem é mostrada devido a impressao do compromisso pelo if inicial dessa função
}

void liberaListaCompromisso(Compromisso *lista) // da free na lista de compromissos
{
  CelulaCompromisso *aux = lista->primeiro;
  CelulaCompromisso *auxProx;
  while(aux != NULL)
  {
    auxProx = aux->prox;
    free(aux);
    aux = auxProx;
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
}

void imprimeListaCompromisso(Compromisso *lista) //imprime os compromissos no terminal
{
  CelulaCompromisso *aux = lista->primeiro->prox;
  while(aux != NULL)
  {
    cout << setfill('0') << setw(2) << aux->item.hora << ":" << setw(2) << aux->item.minutos << "  --  " << aux->item.descricao << endl;
    aux = aux->prox;
  }
}

bool verificaCompromisso(int hora, int minutos, Compromisso *lista) //verifica se um compromisso existe ou não na lista e o imprime na tela
{
  CelulaCompromisso *aux = lista->primeiro->prox;
  while(aux != NULL){
    if((aux->item.hora == hora && aux->item.minutos == minutos))
    {
      cout << "Compromisso neste horario" << endl;
      cout << setfill('0') << setw(2) << aux->item.hora << ":" << setw(2) << aux->item.minutos << "  --  " << aux->item.descricao << endl;
      return true;
    }
    aux = aux->prox;
  }
  return false;

}
#endif

