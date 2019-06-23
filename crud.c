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
        system("clear");
        puts("      (\"`-''-/\").___..--''\"`-._");
        puts("       `6_ 6  )   `-.  (     ).`-.__.`)");
        puts("       (_Y_.)'  ._   )  `._ `. ``-..-'");
        puts("      ..`--'_..-_/  /--'_.' ,'");
        puts("      (il),-''  (li),'  ((!.-'");
        puts("||=============================||");
        puts("||======Escolha uma opção======||");
        puts("||=============================||");
        puts("||1|| Cadastrar uma turma      || \n||2|| Consultar um aluno       ||");
        puts("||3|| Alterar dados de um aluno|| \n||4|| Listar dados de uma turma||");
        puts("||5|| Terminar a execução      ||");
        puts("||=============================||");
        scanf("%d", &choice);
        if(choice == 1)
            createData();
         else if(choice == 2)
             readData(1);
         else if(choice == 3)
            readData(0);
         else if(choice == 4)
             listData();
        else if(choice == 5)
            break; //sai do while
        else //se for diferente das opções dadas
            puts("Opção inexistente");     
    }   
}
listData(){

}
updateData(int matricula, char *FileName){
    system("clear");
    if(!(matricula == 0)){//se a matricula for 0, ele não faz nada
        FILE * dataBase;
        dataBase = fopen( FileName, "r+b");//abre o arquivo em modo aleatório para podermos sobrescrever um registro
        while (fread( &defaultStudent, sizeof(defaultStudent), 1, dataBase)){//vamos ler o arquivo XD
            if(defaultStudent.matricula == matricula){//se a matricula do arquivo for igual a digitada pelo usuário
                puts("||======================================");
                puts("||======================================");
                printf( "||Matrícula: %d                       \n", defaultStudent.matricula ); //preenchendo os dados na tela, todos bonitinhos
                printf( "||Nome: %s                            \n", defaultStudent.nome );
                for(int i = 0; i<6;i++){
                    printf( "||Nota da prova %d: %lf           \n",i+1, defaultStudent.notas_de_prova[i]);       
                }
                for(int i = 0; i<6;i++){
                    printf( "||Nota da lista %d: %lf           \n",i+1, defaultStudent.notas_de_listas[i]);
                }
                printf( "||Nota do trabalho: %lf               \n", defaultStudent.nota_de_trabalho);
                printf( "||Nota final: %lf                     \n", defaultStudent.nota_final);
                printf( "||Noumero de ausências: %d            \n", defaultStudent.numero_ausencias);
                printf( "||Situacao: %s                        \n", defaultStudent.situacao);
                puts("||======================================");
                printf( "\n\n" );
                puts("digite os novos dados do aluno");
                
            }
            archiveData();
            fseek(dataBase, (-1)*sizeof(defaultStudent), SEEK_CUR);//volta o "leitor do arquivo para a posição do registro a ser alterado"
            fwrite( &defaultStudent, sizeof(defaultStudent), 1, dataBase);//finalmente altera o registro
        }
    fclose(dataBase);
    }       
   
}
readData(int choice){
    system("clear");//limpando terminal
    FILE * dataBase;
    char name[100];
    int matricula;
    while(1){ //é só para ja entrar aqui direto, e caso a matricula seja 0, sai na hr
        puts("\nDigite o nome (ex: home/user/documents/nomeDoArquivo) de um arquivo de turma: ");
        scanf("%s", name);//digita certo pfv
        if(name[0]=='f' && name[1]=='i' && name[2]=='m'){ //se o usuário digitar "fim", voltamos para o menu principal
            break;
        }
        matricula = 1;
        char *FileName = name;
        dataBase = fopen( FileName, "rb");//abrindo apenas em modo de leitura READ BINARY
        if(!(dataBase==NULL)){//só entra aqui se o arquivo não estiver vazio, se estiver ele pede para digitar de novo
            while(matricula){//vai ficar nesse loop enquanto a matrícula não for 0
                puts("\nDigite um número de matrícula: ");
                scanf("%d",&matricula);
                if(choice)//se a requisição veio do Main, entra no método abaixo
                    lendoArquivo(matricula, FileName);//achei melhor uma função para isso, se não ficaria desorganizado        
                else
                    updateData(matricula, FileName);
            }
        
        }
        fclose(dataBase);
    }
    
}
lendoArquivo(int matricula, char *FileName){
    if(!(matricula == 0)){//se a matricula for 0, ele não faz nada
        FILE * dataBase;
        dataBase = fopen( FileName, "rb");
        while (fread( &defaultStudent, sizeof(defaultStudent), 1, dataBase)){//vamos ler o arquivo XD
            if(defaultStudent.matricula == matricula){//se a matricula do arquivo for igual a digitada pelo usuário
                puts("||======================================");
                puts("||======================================");
                printf( "||Matrícula: %d                       \n", defaultStudent.matricula ); //preenchendo os dados na tela, todos bonitinhos
                puts("||--------------------------------------");
                printf( "||Nome: %s                            \n", defaultStudent.nome );
                puts("||--------------------------------------");
                for(int i = 0; i<6;i++){
                    printf( "||Nota da prova %d: %lf           \n",i+1, defaultStudent.notas_de_prova[i]);
                    puts("||--------------------------------------");
                   
                }
                for(int i = 0; i<6;i++){
                    printf( "||Nota da lista %d: %lf           \n",i+1, defaultStudent.notas_de_listas[i]);
                    puts("||--------------------------------------");
                }
                printf( "||Nota do trabalho: %lf               \n", defaultStudent.nota_de_trabalho);
                puts("||--------------------------------------");
                printf( "||Nota final: %lf                     \n", defaultStudent.nota_final);
                puts("||--------------------------------------");
                printf( "||Noumero de ausências: %d            \n", defaultStudent.numero_ausencias);
                puts("||--------------------------------------");
                printf( "||Situacao: %s                        \n", defaultStudent.situacao);
                puts("||======================================");
                puts("||======================================");
                printf( "\n\n" );
                break;
            }
        }
    fclose(dataBase);
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
        archiveData();//função para receber os valores do usuário
        fwrite( &defaultStudent, sizeof(defaultStudent), 1, dataBase);
         //salvando tudo no arquivo finalmente
    
    } while (defaultStudent.matricula!=0);
    fclose(dataBase);
    // puts("Conteúdo atual do arquivo");
    //  dataBase = fopen( file, "rb");
    //         fread( &defaultStudent, sizeof(defaultStudent), 1, dataBase);
    //         printf( "Nome     : %s\n", defaultStudent.nome );
    //         printf( "situacao    : %s\n", defaultStudent.situacao);
    //         printf( "\n" );
    
}
archiveData(){
 puts("digite o nome: ");
        getchar();//o puts tem o /n por padrão, esse getchar serve para q o scanf nao confunda esse /n com entrada do teclado
        scanf("%[^\n]", defaultStudent.nome);//esse código [^\n] serve para ler toda a linha que o usuário digitar
        getchar();
        //o laço abaixo serve para preenchermos o vetor de notas de prova
        for(int i =0; i<6;i++){
            printf("digite a nota de prova número %d: ", i+1);
            scanf("%lf", &defaultStudent.notas_de_prova[i]);
        }
        //o laço abaixo serve para preenchermos o vetor de notas de listas
        for(int i =0; i<6;i++){
            printf("digite a nota de lista número %d: ", i+1);
            scanf("%lf", &defaultStudent.notas_de_listas[i]);
        }
        puts("digite a nota do trabalho: ");
        scanf("%lf", &defaultStudent.nota_de_trabalho);

        puts("digite o número de ausências: ");
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



    
