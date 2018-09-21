/*
 * Arthur Curty Vieira
 * Matrícula: 11506859
 * Disciplina: Sistemas Operacionais
 * Engenharia de Computação - CI - UFPB
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <deque>

using namespace std;

typedef struct {
 int ID_Processo  = 0;
 int Tempo_Duracao = 0;
 int Tempo_Exec = 0;
 int Tempo_Chegada = 0;
 int Tempo_Restante = 0;
}Processo;

/*Vetores que armazena as entrdadas do arquivo*/
vector<int>tempo_entrada;
vector<int>tempo_duracao;

/* Abre o arquivo, e armazena os dados nos lugares corretos */
void recebendo_arquivo()
{
            /* Lendo arquivo e armazenando dados de cada linha nos vetores globais */
            ifstream file;

            file.open("testes.txt");
            int novo_T_entrada, novo_T_duracao;

            if (file.is_open())
            {
                while (file >> novo_T_entrada >> novo_T_duracao)
                 {
                    tempo_entrada.push_back(novo_T_entrada);
                    tempo_duracao.push_back(novo_T_duracao);
                 }
            }
            file.close();
}

void FCFS(const Processo *processos)
{
        int num_de_processos = tempo_entrada.size();
        float tempo_inicio[num_de_processos];
        float tempo_retorno[num_de_processos];
        float tempo_espera[num_de_processos];
        float tempo_resposta[num_de_processos];
        float tempo_medio_espera,
              tempo_medio_resposta,
              tempo_medio_retorno,
              tempo_retorno_total,
              tempo_resposta_total,
              tempo_espera_total = 0;

            /*  Inicio do primeiro processo = tempo de chegada */
        tempo_inicio[0] = processos[0].Tempo_Chegada;
        for(int i=0;i<num_de_processos;i++)
        {   /* Tempo de inicio, como o primeiro que entra e o pripeiro que sai, o proximo so começa quando o anterior termina
             */
            tempo_inicio[i+1] = tempo_inicio[i] + processos[i].Tempo_Duracao;

            tempo_resposta [i] = tempo_inicio[i] - processos[i].Tempo_Chegada;
            tempo_resposta_total = tempo_resposta_total + tempo_resposta[i];

             /* tempo de espera , que é o tempo de chegada - o tempo de inicio */
            tempo_espera[i] = tempo_inicio[i] - processos[i].Tempo_Chegada;
            tempo_espera_total = tempo_espera_total + tempo_espera[i];
             /* tempo de retorno , que é o tempo de inicio do proximo - o tempo de chegada do atual */
            tempo_retorno[i] = tempo_inicio[i+1] - processos[i].Tempo_Chegada;
            tempo_retorno_total = tempo_retorno_total + tempo_retorno[i];

        }
            /* Tempos medios */
            tempo_medio_espera = tempo_espera_total / num_de_processos;
            tempo_medio_retorno = tempo_retorno_total / num_de_processos;
            tempo_medio_resposta = tempo_resposta_total / num_de_processos;
            cout<<"FCFS: "<<tempo_medio_retorno<<" "<<tempo_medio_resposta<<" "<<tempo_medio_espera<<endl;

}

void SJF (const Processo *processos){
/*
  SJF

*/
        int num_de_processos = tempo_entrada.size();
        float tempo_inicio[num_de_processos];
        float tempo_retorno[num_de_processos];
        float tempo_espera[num_de_processos];
        float tempo_resposta[num_de_processos];
        float tempo_medio_espera,
              tempo_medio_resposta,
              tempo_medio_retorno,
              tempo_retorno_total,
              tempo_resposta_total,
              tempo_espera_total = 0;


}
void RR(const Processo *processos)
{
/*
  Round Robin

*/
        int num_de_processos = tempo_entrada.size();
        float tempo_inicio[num_de_processos];
        float tempo_retorno[num_de_processos];
        float tempo_espera[num_de_processos];
        float tempo_resposta[num_de_processos];
        float tempo_medio_espera,
              tempo_medio_resposta,
              tempo_medio_retorno,
              tempo_retorno_total,
              tempo_resposta_total,
              tempo_espera_total = 0;


}

/* Ordena os processos caso o tempo de chegada esteja fora de ordem */
void Ordena_chegada(Processo *Ordena)
{
  Processo aux;

   for(int j=tempo_entrada.size()-1; j>0; j--){
        for ( int i=0; i<j; i++){
            if (Ordena[i].Tempo_Chegada > Ordena[i+1].Tempo_Chegada){
                aux = Ordena[i];
                Ordena[i] = Ordena[i+1];
                Ordena[i+1] = aux;
            }
        }
    }

}

int main ()
{
    /*chamada da função*/
    recebendo_arquivo();

    /* como cada linha é um processo, podemos obter a quantidade de processos pelo tamanho de um dos vetores de entrada*/
    int numero_de_processos = tempo_entrada.size();

    /*objeto da struct */
    Processo *processos = new Processo[numero_de_processos];


    /* armazenando os dados de entrada do arquivo na struct */
    for(int i = 0; i < numero_de_processos; i++)
    {
        processos[i].ID_Processo = i;
        processos[i].Tempo_Chegada = tempo_entrada[i];
        processos[i].Tempo_Duracao = tempo_duracao[i];
        processos[i].Tempo_Restante = processos[i].Tempo_Duracao;

        if(processos[i].Tempo_Duracao == 0)
            {
              numero_de_processos = numero_de_processos - 1;
            }
    }
    /*Chamada da função de ordenação de processos*/
    Ordena_chegada(processos);

    /* Printando os dados armazenados nos de cada processo */
    for(int i =0;i<numero_de_processos;i++)
    {
        cout<<"ID do processo: "<<processos[i].ID_Processo<<" Tempo de entrada: "<<processos[i].Tempo_Chegada<<" Tempo de duracao: "<<processos[i].Tempo_Duracao<<endl;

    }
    /*Chamadas dos escalonadores*/
    FCFS(processos);
    SJF(processos);
    RR(processos);

  return 0;
}
