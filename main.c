#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHOFICHA 10
#define TAMANHOCAMPO 50

typedef struct ficha{
    char nome[TAMANHOCAMPO];
    char equipe[TAMANHOCAMPO];
    float altura;
    int colocacao;
    float tempo;
}FICHA;

//Protótipos
void Menu1(FICHA Formula[TAMANHOFICHA], FILE *Arquivo);
void Menu2(FICHA Formula[TAMANHOFICHA], int escolha);
int Menu3(FICHA Formula[TAMANHOFICHA]);
void Menu4(FICHA Formula[TAMANHOFICHA], FILE *newarchive);

int main(){
    //Dados de Entrada //
    int Opcao, escolha,Pesquisado,cont;
    FILE *Arquivo;//Variável do tipo File (arquivo)
    FILE *newarchive;
    struct ficha Formula[TAMANHOFICHA];

    do{
        printf("\t  |******************************|\n");
        printf("\t  |-------MENU DE OPCAO:---------|\n");
        printf("\t  |[1]: Carregar arquivo e exibir|\n");
        printf("\t  |[2]: Ordenar dados e exibir   |\n");
        printf("\t  |[3]: Pesquisar dados e exibir |\n");
        printf("\t  |[4]: Gravar os dados ORDENADOS|\n");
        printf("\t  |[0]: Sair do programa\t |\n");
        printf("\t  |******************************|\n");
        printf("\t  |Sua opcao:\t\t\t |\n");
        scanf("%i", &Opcao);

        /* Opcao: Carregar arquivo e exibir */
        if (Opcao == 1){
            system("cls");
            printf("Dados do arquivo: \n\n");
            Arquivo = fopen("Arquivo28.txt", "r");
            if (Arquivo == 0){
                printf("Erro na abertura do arquivo.\n\n\n");
                fclose(Arquivo);
            }
            else
                Menu1(Formula, Arquivo);
        }
        /* Opcao: Ordenar dados e exibir */
        else if(Opcao == 2){
            system("cls");
            printf("Ordenar os dados e exibir: \n\n");
            printf("Escolha o numero do campo a ser ordenado:\n");
            printf("\t |**************|\n");
            printf("\t |Nome:      [1]|\n");
            printf("\t |Equipe:    [2]|\n");
            printf("\t |Altura:    [3]|\n");
            printf("\t |Colocacao: [4]|\n");
            printf("\t |Tempo:     [5]|\n");
            printf("\t |**************|\n");
            scanf("%d",&escolha);
            Menu2(Formula, escolha);
            for (cont = 0; cont < TAMANHOFICHA; cont++){
                printf("Corredor %d:\n", cont + 1);
                printf("\t  Nome     : %s\n", Formula[cont].nome);
                printf("\t  Equipe   : %s\n", Formula[cont].equipe);
                printf("\t  Altura   : %.2f\n", Formula[cont].altura);
                printf("\t  Colocacao: %i\n", Formula[cont].colocacao);
                printf("\t  Tempo    : %.2f\n", Formula[cont].tempo);
            }
        }
        // Opcao: Pesquisa (Binária) de dados e exibir //
        else if(Opcao == 3){
            system("cls");
            printf("Pesquisar dados e exibir: \n\n");
            Pesquisado = Menu3(Formula);
            if(Pesquisado == -1)
                printf("COMPETIDOR INVALIDO!\n");
            else{
                printf("Dados do competidor: \n");
                printf("\t  Nome     : %s\n", Formula[Pesquisado].nome);
                printf("\t  Equipe   : %s\n", Formula[Pesquisado].equipe);
                printf("\t  Altura   : %.2f\n", Formula[Pesquisado].altura);
                printf("\t  Colocacao: %i\n", Formula[Pesquisado].colocacao);
                printf("\t  Tempo    : %.2f\n", Formula[Pesquisado].tempo);
                Menu2(Formula, escolha);
            }
        }
        // Opcao: Gravar os dados ORDENADOS //
        else if(Opcao == 4){
            system("cls");
            printf("Dados gravados com sucesso! \n\n");
            newarchive = fopen("newarchive.txt","r+");
            Menu4(Formula, newarchive);
            fclose(newarchive);
        }
        // Opcao: Sair do Programa //
        else if(Opcao == 0){
            system("cls");
            printf("FIM DO PROGRAMA.\n\n\n");
        }
    }while(Opcao);
    return 0;
}
void Menu1(struct ficha Formula[TAMANHOFICHA], FILE *Arquivo)
{
    int i = 0;     //Indice de contagem do vetor Auxiliar.
    char C;        //Caractere Auxiliar: Ler um a um do arquivo.
    int Quant = 0; //Conta a quantidade de Registros no arquivo.
    int Campo = 1; //Acessa os Campos dos Registros: Vetor Ficha.
    char Auxiliar[TAMANHOCAMPO]; //Monta a linha do arquivo.
    do{
        // Ler caractere por caractere do arquivo //
        C = getc(Arquivo);
        if (C != '\n' && C != EOF){
            /* Monta um vetor (Auxiliar) com os caracteres da linha */
            /* Monta linha por linha do arquivo */
            Auxiliar[i] = C;
            i++;
        }
        else
        {
            /* Monta o vetor Ficha: Campo por Campo */
            Auxiliar[i] = '\0'; //Finaliza a linha (String)
            /* Salva a linha no Registro no seu Respectivo Campo */
            switch (Campo){
                case 1:
                    strcpy(Formula[Quant].nome, Auxiliar);
                    break;
                case 2:
                    strcpy(Formula[Quant].equipe, Auxiliar);
                    break;
                case 3:
                    Formula[Quant].altura = atof(Auxiliar);
                    break;
                case 4:
                    Formula[Quant].colocacao = atoi(Auxiliar);
                    break;
                case 5:
                    Formula[Quant].tempo = atof(Auxiliar);
                    Campo = 0; //Reinicia para o próximo registro
                    Quant++;   //Incrementa 1 para o próximo registro
            }
            Campo++; //Próximo Campo
            i = 0;   //Reinicia o Indice do vetor Auxiliar.
        }
    /* Enquanto: Caractere (C) for diferente do 'End Of File' (EOF)*/
    }while (C != EOF);
    /* Fechar o arquivo (FILE) */
    fclose(Arquivo);
    /* Exibe os dados do Arquivo (Registros: Ficha) */
    for (i = 0; i < Quant; i++){
        printf("Corredor %i:\n", i + 1);
        printf("\t  Nome     : %s\n", Formula[i].nome);
        printf("\t  Equipe   : %s\n", Formula[i].equipe);
        printf("\t  Altura   : %.2f\n", Formula[i].altura);
        printf("\t  Colocacao: %i\n", Formula[i].colocacao);
        printf("\t  Tempo    : %.2f\n", Formula[i].tempo);
    }
}
void Menu2(FICHA Formula[TAMANHOFICHA], int escolha){
    int cont, sentinela, repeticao;
    FICHA auxiliar;

    repeticao = TAMANHOFICHA - 1;
    if(escolha == 1){
        do{
            sentinela = 0;
            for(cont=0;cont<repeticao;cont++){
                if(strcmp(Formula[cont].nome,Formula[cont+1].nome)== 1){
                    auxiliar = Formula[cont];
                    Formula[cont] =  Formula[cont+1];
                    Formula[cont+1] = auxiliar;
                    sentinela = 1;
                }
            }
            repeticao-= 1;
        }while(sentinela);
    }
    if(escolha == 2){
        do{
            sentinela = 0;
            for(cont=0;cont<repeticao;cont++){
                if(strcmp(Formula[cont].equipe,Formula[cont+1].equipe)== 1){
                    auxiliar = Formula[cont];
                    Formula[cont] =  Formula[cont+1];
                    Formula[cont+1] = auxiliar;
                    sentinela = 1;
                }
            }
            repeticao-= 1;
        }while(sentinela);
    }
    if(escolha == 3){
        do{
            sentinela = 0;
            for(cont=0;cont<repeticao;cont++){
                if(Formula[cont].altura>Formula[cont+1].altura){
                    auxiliar = Formula[cont];
                    Formula[cont] =  Formula[cont+1];
                    Formula[cont+1] = auxiliar;
                    sentinela = 1;
                }
            }
            repeticao-= 1;
        }while(sentinela);
    }
    if(escolha == 4){
        do{
            sentinela = 0;
            for(cont=0;cont<repeticao;cont++){
                if(Formula[cont].colocacao>Formula[cont+1].colocacao){
                    auxiliar = Formula[cont];
                    Formula[cont] =  Formula[cont+1];
                    Formula[cont+1] = auxiliar;
                    sentinela = 1;
                }
            }
            repeticao-= 1;
        }while(sentinela);
    }
    if(escolha == 5){
        do{
            sentinela = 0;
            for(cont=0;cont<repeticao;cont++){
                if(Formula[cont].tempo>Formula[cont+1].tempo){
                    auxiliar = Formula[cont];
                    Formula[cont] =  Formula[cont+1];
                    Formula[cont+1] = auxiliar;
                    sentinela = 1;
                }
            }
            repeticao-= 1;
        }while(sentinela);
    }
}
int Menu3(FICHA Formula[TAMANHOFICHA]){
   int Campo, Li = 0, Ls = TAMANHOFICHA - 1, meio, resultado = -1;
   FICHA informacao;
    printf("Escolha o campo a ser pesquisado:\n");
    printf("\t |**************|\n");
    printf("\t |Altura:    [1]|\n");
    printf("\t |Colocacao: [2]|\n");
    printf("\t |Tempo:     [3]|\n");
    printf("\t |**************|\n");
    scanf("%d",&Campo);

    if(Campo == 1){
        system("cls");
        Menu2(Formula, Campo+2);
        printf("Informe a altura:\n");
        scanf("%f",&informacao.altura);
        while(Li<=Ls && resultado == -1){
            meio = (Li + Ls)/2;
            if(Formula[meio].altura == informacao.altura)
                resultado = meio;
            else if(Formula[meio].altura>informacao.altura)
                Ls = meio - 1;
            else
                Li = meio + 1;
        }
        return resultado;
    }
    if(Campo == 2){
        system("cls");
        Menu2(Formula, Campo+2);
        printf("Informe a colocacao:\n");
        scanf("%d",&informacao.colocacao);
        while(Li<=Ls && resultado == -1){
            meio = (Li + Ls)/2;
            if(Formula[meio].colocacao == informacao.colocacao)
                resultado = meio;
            else if(Formula[meio].colocacao>informacao.colocacao)
                Ls = meio - 1;
            else
                Li = meio + 1;
        }
        return resultado;
    }
    if(Campo == 3){
        system("cls");
        Menu2(Formula, Campo+2);
        printf("Informe o tempo:\n");
        scanf("%f",&informacao.tempo);
        while(Li<=Ls && resultado == -1){
            meio = (Li + Ls)/2;
            if(Formula[meio].tempo == informacao.tempo)
                resultado = meio;
            else if(Formula[meio].tempo>informacao.tempo)
                Ls = meio - 1;
            else
                Li = meio + 1;
        }
        return resultado;
    }
}
void Menu4(FICHA Formula[TAMANHOFICHA], FILE *newarchive){
    int cont = 0;
    while(cont<TAMANHOFICHA){
        fprintf(newarchive,"%s", Formula[cont].nome);
        fprintf(newarchive,"\n%s ", Formula[cont].equipe);
        fprintf(newarchive,"\n%.2f \n", Formula[cont].altura);
        fprintf(newarchive,"%d \n", Formula[cont].colocacao);
        fprintf(newarchive,"%.3f \n", Formula[cont].tempo);
        cont++;
    }
}
