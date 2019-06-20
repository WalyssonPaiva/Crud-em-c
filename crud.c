#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{ //struct padrão de alunos
    int matricula;
    char nome[100];
    double notas_de_prova[6];
    double notas_de_listas[6];
    double nota_de_trabalho;
    double nota_final;
    int numero_ausencias;
    char situacao[50];
} defaultStudent;

main(){
    int choice;
    while(1){ //lista de opções do programa
        puts("1 - Cadastrar uma turma \n2 - Consultar um aluno");
        puts("3 - Alterar dados de um aluno \n4 - Listar dados de uma turma");
        puts("5 - Terminar a execução\n");
        scanf("%d", &choice);
        if(choice == 1)
            createData();
        // else if(choice == 2)
        //     readData();
        // else if(choice == 3)
        //     updateData();
        // else if(choice == 4)
        //     listData();
        else if(choice == 5)
            break; //sai do while
        else //se for diferente das opções dadas
            puts("Opção inexistente");     
    }   
}
createData(){
    char name[100], directory[100];
    system("clear"); //limpar o Terminal

    puts("Digite o nome do arquivo: ");
    scanf("%s", name); //lendo nome do arquivo
    puts("\nDigite o caminho do arquivo: ");
    scanf("%s", directory);//lendo diretório do arquivo

    //adicionando uma "/" no final do diretorio, para conseguirmos concatenar com o arquivo
    char *Finaldirectory = strcat(directory,"/"); 
    //salvando corretamente nome do diretório + nome do arquivo
    const char *file = strcat(Finaldirectory,name);
    //finalmente criando o arquivo 
    FILE * dataBase = fopen(file,"wb");//criando o arquivo. file = diretorio+/+nomeDoArquivo
    //"wb" => w=> para criar um arquivo e sobrescrever caso ja exista, b => arquivo binário

    do{
        puts("\ndigite a matricula: ");
        scanf("%d", &defaultStudent.matricula);
        if(defaultStudent.matricula == 0)
            break;

        puts("\ndigite o nome: ");
        scanf("%s", defaultStudent.nome);
        //o laço abaixo serve para preenchermos o vetor de notas de prova
        for(int i =0; i<6;i++){
            printf("\ndigite a nota de prova número %d: ", i+1);
            scanf("%lf", &defaultStudent.notas_de_prova[i]);
        }
        //o laço abaixo serve para preenchermos o vetor de notas de listas
        for(int i =0; i<6;i++){
            printf("\ndigite a nota de lista número %d: ", i+1);
            scanf("%lf", &defaultStudent.notas_de_listas[i]);
        }
        puts("\ndigite a nota do trabalho: ");
        scanf("%lf", &defaultStudent.nota_de_trabalho);

        puts("\ndigite o número de ausências: ");
        scanf("%d", &defaultStudent.numero_ausencias);
        
        //setando ponteiros para jogar os vetores em outra função
        double *notasProvas = defaultStudent.notas_de_prova, *notasListas = defaultStudent.notas_de_listas;
        defaultStudent.nota_final = finalMedia(notasProvas,notasListas, defaultStudent.nota_de_trabalho);

        //verificar situação
        int situation = checkSituation( defaultStudent.nota_final, defaultStudent.numero_ausencias);
        if(situation == 0)
            strcpy(defaultStudent.situacao, "Reprovado por ausência e por nota");
        else if(situation == 1)
            strcpy(defaultStudent.situacao, "Reprovado por ausência");
        else if(situation == 2)
            strcpy(defaultStudent.situacao, "Reprovado por nota");
        else if(situation == 3)
            strcpy(defaultStudent.situacao, "Aprovado");

        fwrite( &defaultStudent, sizeof(defaultStudent), 1, dataBase);
        // //salvando tudo no arquivo finalmente
        // fscanf(stdin, "%d", &defaultStudent.matricula);
        // fscanf(stdin, "%s", &defaultStudent.nome);
        // //salvando trabalhos e provas
        // for(int i = 0; i<6;i++){
        //     fscanf(stdin, "%lf", &defaultStudent.notas_de_prova[i]);
        //     fscanf(stdin, "%lf", &defaultStudent.notas_de_listas[i]);
        // }
        // fscanf(stdin, "%lf", &defaultStudent.nota_de_trabalho);
        // fscanf(stdin, "%lf", &defaultStudent.nota_final);
        // fscanf(stdin, "%d", &defaultStudent.numero_ausencias);
        // fscanf(stdin, "%s", &defaultStudent.situacao);
    
    } while (defaultStudent.matricula!=0);
    fclose(dataBase);
    // puts("Conteúdo atual do arquivo");
    //  dataBase = fopen( file, "rb");
    //         fread( &defaultStudent, sizeof(defaultStudent), 1, dataBase);
    //         printf( "Nome     : %s\n", defaultStudent.nome );
    //         printf( "situacao    : %s\n", defaultStudent.situacao);
    //         printf( "\n" );
    
}
checkSituation(double notaFinal, int faltas){
    int s;
    if(notaFinal >= 6 && faltas < 0.25 * 128)
        return 3;
    else if(notaFinal <6 && faltas < 0.25*128)
        return 2;
    else if(notaFinal >=6 && faltas >= 0.25*128)
        return 1;
    else
        return 0;
}

finalMedia(double *notasProvas, double *notasListas, double notaTrabalho){
    //calculando média das provas e listas
    double mp = 0, ml = 0, mf;
    for(int i = 0; i<6;i++){
        mp += notasProvas[i];
        ml += notasListas[i];
    }
    mp = mp/6;
    ml = ml/6;
    //calculando média final
    mf = (mp * 0.8) + (ml * 0.1)+ (notaTrabalho * 0.1);

    return mf; //retornando a média final
}



    
