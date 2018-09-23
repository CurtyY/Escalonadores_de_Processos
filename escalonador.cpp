/*
 * Arthur Curty Vieira
 * Matrícula: 11506859
 * Disciplina: Sistemas Operacionais I
 * Engenharia de Computação - CI - UFPB
 */
#include<bits/stdc++.h>

using namespace std;

typedef struct
              {
               int ID_Processo  = 0;
               int Tempo_Duracao = 0;
               int Tempo_Exec = 0;
               int Tempo_Chegada = 0;
               int Tempo_Restante = 0;
              }Processo;

/*Vetores que armazena as entrdadas do arquivo*/
vector<int>tempo_entrada;
vector<int>tempo_duracao;

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
/*função para calcular as medias e printar na tela*/
void calcula_medias (string escalonador_tipo, float tempo_de_resposta,float tempo_de_retorno,float tempo_de_espera)
{
    int numero_de_processos = tempo_duracao.size();
    float tempo_medio_de_resposta = 0;
    float tempo_medio_de_retorno = 0;
    float tempo_medio_de_espera = 0;

      tempo_medio_de_resposta = tempo_de_resposta / numero_de_processos;
    	tempo_medio_de_retorno = tempo_de_retorno / numero_de_processos;
    	tempo_medio_de_espera = tempo_de_espera / numero_de_processos;

    cout << escalonador_tipo << " "  << tempo_medio_de_retorno << " " << tempo_medio_de_resposta << " " << tempo_medio_de_espera <<endl;

}

/* Abre o arquivo, e armazena os dados nos lugares corretos */
void recebendo_arquivo(string nome)
{
            /* Lendo arquivo e armazenando dados de cada linha nos vetores globais */
            ifstream file;

            file.open(nome);
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
/* compara tempo de duração de processos */
bool comparar(const Processo& p1, const Processo& p2){

	return (p1.Tempo_Duracao <= p2.Tempo_Duracao);

}

/* FCFS */
void FCFS(const Processo *processos)
{
        int num_de_processos = tempo_entrada.size();
        float tempo_inicio[num_de_processos];
        float tempo_retorno[num_de_processos];
        float tempo_espera[num_de_processos];
        float tempo_resposta[num_de_processos];
        float tempo_medio_espera = 0;
        float tempo_medio_resposta = 0;
        float tempo_medio_retorno = 0;
        float tempo_retorno_total = 0;
        float tempo_resposta_total = 0;
        float tempo_espera_total = 0;

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

        calcula_medias("FCFS ",tempo_resposta_total,tempo_retorno_total,tempo_espera_total);


}

/* SJF */
void SJF (const Processo *processos)
{
    int numero_de_processos = tempo_entrada.size();
	float tempo_de_resposta = 0;
	float tempo_de_retorno = 0;
	float tempo_de_espera = 0;
	float tempo_medio_de_resposta = 0;
	float tempo_medio_de_retorno = 0;
	float tempo_medio_de_espera = 0;
	int   retorno = numero_de_processos;
	int   ciclo= 0;

	vector<Processo> prontos;
	vector<Processo> novos;

      	for (int i= 0; i < numero_de_processos; i++)
        {
         novos.push_back(processos[i]);
      	}

      	while(retorno != 0){

      		for (int i = 0; i < novos.size(); i++)
              {

      			if( novos[i].Tempo_Chegada <= ciclo)
      			{
      				prontos.push_back(novos[i]);
      				novos.erase (novos.begin()+i);
      				i--;
      			}

      		}
      		sort(prontos.begin(),prontos.end(),comparar);

      		Processo inicio = prontos[0];
      		retorno--;
      		prontos.erase(prontos.begin());

      		tempo_de_espera   = tempo_de_espera + ciclo - inicio.Tempo_Chegada;
      		tempo_de_resposta = tempo_de_resposta + ciclo - inicio.Tempo_Chegada;
      		ciclo = ciclo + inicio.Tempo_Duracao;
      		tempo_de_retorno  = tempo_de_retorno + ciclo - inicio.Tempo_Chegada;

      	}
      	    calcula_medias("SJF ",tempo_de_resposta,tempo_de_retorno,tempo_de_espera);
}

/* Round Robin */
void RR(const Processo *processos)
{
    int numero_de_processos = tempo_entrada.size();
  	float tempo_de_resposta = 0;
  	float tempo_de_retorno = 0;
  	float tempo_de_espera = 0;
  	float tempo_medio_de_resposta = 0;
  	float tempo_medio_de_retorno = 0;
  	float tempo_medio_de_espera = 0;
  	int   retorno = numero_de_processos;
  	int   ciclo = 0;
  	int   quantum = 2;
  	bool  volta_para_pronto = false;

    /* fila de prontos e novos processos */
	vector<Processo> prontos;
	vector<Processo> novos;

	Processo inicio;

        /* coloca todos os processo na fila de novos */
    	for (int i= 0; i < numero_de_processos; i++)
      {
    		novos.push_back(processos[i]);
    	}

    	while(retorno != 0)
        {

    		for (int i = 0; i < novos.size(); i++)
            {

    			if( novos[i].Tempo_Chegada == ciclo)
                {

    				prontos.push_back(novos[i]);
    				novos.erase (novos.begin()+i);
    				i--;

    			}else if( novos[i].Tempo_Chegada < ciclo)
    			{

    				tempo_de_espera += ciclo - novos[i].Tempo_Chegada;
    				prontos.push_back(novos[i]);
    				novos.erase (novos.begin()+i);
    				i--;

    			}
    		}

                if(volta_para_pronto)
                {
                    prontos.push_back(inicio);
                    volta_para_pronto = false;
                }

    		inicio = prontos[0];
    		prontos.erase(prontos.begin());

                if(inicio.Tempo_Restante == inicio.Tempo_Duracao)
                {
                    tempo_de_resposta += ciclo - inicio.Tempo_Chegada;
                }

    		ciclo = ciclo + quantum;
    		inicio.Tempo_Restante = inicio.Tempo_Restante -quantum;
    		tempo_de_espera   = tempo_de_espera + quantum * prontos.size();

                if(inicio.Tempo_Restante > 0)
                {
                    volta_para_pronto = true;
                }

                if(inicio.Tempo_Restante <= 0)
                {
                    retorno--;
                    int num_prontos = prontos.size();

                    ciclo = ciclo + inicio.Tempo_Restante;
                    tempo_de_espera = tempo_de_espera + (inicio.Tempo_Restante * num_prontos);
                    tempo_de_retorno  = tempo_de_retorno + ciclo - inicio.Tempo_Chegada;
                }

    	}
        calcula_medias("RR ",tempo_de_resposta,tempo_de_retorno,tempo_de_espera);

}

/* Printa na tela os processos junto com os tempos de entrada e duração*/
void print (const Processo *processos, int numero_de_processos)
{

    for(int i =0;i<numero_de_processos;i++)
    {
      cout<<"ID do processo: "<<processos[i].ID_Processo<<" Tempo de entrada: "<<processos[i].Tempo_Chegada<<" Tempo de duracao: "<<processos[i].Tempo_Duracao<<endl;
    }

}

/* armazenando os dados de entrada do arquivo na struct */
void armazena_no_struct(Processo *processos,int numero_de_processos)
{

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
}


int main ()
{
    /*chamada da função*/
    recebendo_arquivo("testes.txt");

    /* como cada linha é um processo, podemos obter a quantidade de processos pelo tamanho de um dos vetores de entrada*/
    int numero_de_processos = tempo_entrada.size();

    /*objeto da struct */
    Processo *processos = new Processo[numero_de_processos]; /*nova struct do tipo processos para FCFS e RR */

    /* armazenando os dados de entrada do arquivo na struct */
    armazena_no_struct(processos,numero_de_processos);

    Ordena_chegada(processos);/*Chamada da função de ordenação de processos*/
    print(processos,numero_de_processos);/*Chama a função que printa a lista de processos*/
    cout<<endl;

    /*Chamadas dos escalonadores*/
    FCFS(processos);
    SJF(processos);
    RR(processos);

  return 0;
}
