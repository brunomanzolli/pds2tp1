#include <stdlib.h>
#include <stdio.h>
#include "lista.hpp"

int escolheMes()
{
  int mes;
  
  cout << "\nDigite o numero do mes ao qual sera aberta a agenda" << endl;
  cout << " 0 -> Encerrar o programa" << endl;
  cout << " 1 -> Janeiro" << endl;
  cout << " 2 -> Fevereiro" << endl;
  cout << " 3 -> Marco" << endl;
  cout << " 4 -> Abril" << endl;
  cout << " 5 -> Maio" << endl;
  cout << " 6 -> Junho" << endl;
  cout << " 7 -> Julho" << endl;
  cout << " 8 -> Agosto" << endl;
  cout << " 9 -> Setembro" << endl;
  cout << "10 -> Outubro" << endl;
  cout << "11 -> Novembro" << endl;
  cout << "12 -> Dezembro" << endl;
  cout << "--->";
  cin >> mes;
  cout << "-------------------------" << endl;

  while(mes < 0 || mes > 12)
  {
    cout << "Mes Invalido, digite novamente" << endl;
    cout << "--->";
    cin >> mes;
    cout << "-------------------------" << endl;
  }

  return mes;
}


int escolheDia(Mes *mesAtual)
{
  int dia;
  cout << "\nDigite o numero do dia ao qual sera aberta a agenda" << endl;
  cout << "--->";
  cin >> dia;
  cout << "-------------------------" << endl;
  
  while(dia < 1 || dia > mesAtual->item.totalDias)
  {
    cout << "\nDia invalido, este mes tem no maximo " << mesAtual->item.totalDias << "dias" << endl;
    cout << "--->";
    cin >> dia;
    cout << "-------------------------" << endl;
  }  

  return dia;
}

int escolheOpcao()
{
  int opcao;
  cout << "\nEscolha uma opcao" << endl;
  cout << " 0 -> Escolher outro mes" << endl;
  cout << " 1 -> Inserir Compromisso" << endl;
  cout << " 2 -> Deletar Compromisso" << endl;
  cout << " 3 -> Verificar Compromisso" << endl;
  cout << " 4 -> Listar Compromisso" << endl;
  cout << "--->";
  cin >> opcao;
  cout << "-------------------------" << endl;
  
  while(opcao < 0 || opcao > 4)
  {
    cout << "\nOpcao invalida, escolha novamente" << endl;
    cout << "--->";
    cin >> opcao;
    cout << "-------------------------" << endl;
  }  

  return opcao;
}

int main(void)
{
  Agenda listaMeses;
  iniciaAgenda(&listaMeses);
  preencheAgendaArquivo(&listaMeses);


  int mesEscolhido = escolheMes();
  int diaEscolhido;
  int opcaoEscolhida;
  
  cout << "SEJA BEM VINDO!!";
  while(mesEscolhido > 0)
  {
    Mes *atual = buscaMes(mesEscolhido, &listaMeses);
    diaEscolhido = escolheDia(atual);
    opcaoEscolhida = escolheOpcao();
    if (opcaoEscolhida == 0)
    {
      mesEscolhido = escolheMes();
    }
    else if (opcaoEscolhida == 1)
    {
      ItemCompromisso item;
      char lixo, descricao[100];
      cout << "->Hora (HH:MM) do compromisso: ";
      cin >> item.hora >> lixo >> item.minutos;
      cout << "->O que e: ";
      cin.ignore();
      cin.getline(descricao,100);
      item.descricao = descricao;
      if (!verificaCompromisso(item.hora, item.minutos, &atual->item.diasDoMes[diaEscolhido-1].compromissos) == 1)
      {
        insereCompromisso(item, &atual->item.diasDoMes[diaEscolhido-1].compromissos);
      }
      else
      {
        cout << "Não foi possivel inserir" << endl;
      }        
      
    }
    else if (opcaoEscolhida == 2)
    {
      int hora, minutos;
      char lixo;
      cout << "->Hora (HH:MM) do compromisso: ";
      cin >> hora >> lixo >> minutos;
      removeCompromisso(hora, minutos, &atual->item.diasDoMes[diaEscolhido-1].compromissos);
    }
    else if (opcaoEscolhida == 3)
    {
      int hora, minutos;
      char lixo;
      cout << "->Hora (HH:MM) do compromisso: ";
      cin >> hora >> lixo >> minutos;
      if (!verificaCompromisso(hora, minutos, &atual->item.diasDoMes[diaEscolhido-1].compromissos) == 1)
      {
        cout << "Sem compromissos neste horario" << endl;
      }
    }
    else{
      imprimeListaCompromisso(&atual->item.diasDoMes[diaEscolhido-1].compromissos);
    }
  }

  imprimeAgendaArquivo(listaMeses);
  liberaAgenda(&listaMeses);
}
