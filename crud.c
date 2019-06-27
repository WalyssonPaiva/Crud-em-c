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
    system("clear");
    FILE * dataBase;
    char name[200];
    int op = 0;
    while(op!=5){
        puts("\nDigite o nome (ex: home/user/documents/nomeDoArquivo) de um arquivo de turma: ");
        scanf("%s", name);//digita certo pfv
        if(name[0]=='f' && name[1]=='i' && name[2]=='m'){ //se o usuário digitar "fim", voltamos para o menu principal
            break;
        }
        op = 0;
        char *FileName = name;
        int contador = verificarTamanho(FileName);
        dataBase = fopen( FileName, "rb");  
        struct student estudantes[contador];
        int final = contador;
        contador = 0;
        while(feof(dataBase)==0){
            fread( &defaultStudent, sizeof(defaultStudent), 1, dataBase);
             if(contador!=final-1){
                estudantes[contador].matricula= defaultStudent.matricula;
                strcpy(estudantes[contador].nome, defaultStudent.nome );
                strcpy(estudantes[contador].situacao, defaultStudent.situacao );
                estudantes[contador].nota_de_trabalho = defaultStudent.nota_de_trabalho;
                estudantes[contador].nota_final = defaultStudent.nota_final;
                estudantes[contador].numero_ausencias = defaultStudent.numero_ausencias;
                for(int i = 0; i<6;i++){
                    estudantes[contador].notas_de_prova[i] = defaultStudent.notas_de_prova[i];
                    estudantes[contador].notas_de_listas[i] = defaultStudent.notas_de_listas[i]; 
                }
                contador++;
             }
        }
        //for(int i = 0; i<contador-1;i++){
            //printf("%s\n", estudantes[i].nome);
            //printf("se ta vazio deu erro");
        //}
        int matricula, ausencias;
        char nome[100], situacao[50];
        double notasProva[6], notasListas[6], notaTrabalho, notaFinal;
        //system("clear");
        while(op!=4 && op!=5){
            puts("1 - listar alunos por ordem crescente de matrícula");
            puts("2 - listar alunos por ordem alfabética");
            puts("3 - listar alunos por ordem crescente de nota final");
            puts("4 - terminar e voltar para processar nova turma");
            puts("5 - terminar execução do módulo");
            puts("===========================================");
            scanf("%d", &op);
            system("clear");
            if(op == 1){//o código aqui está muito repetitivo, vou arrumar só quando tiver tempo, boa sorte pra quem quiser entender
                for(int i = 0; i<contador-1;i++){
                    if(estudantes[i].matricula > estudantes[i+1].matricula){
                        //definindo valores de variáveis auxiliares
                        matricula = estudantes[i].matricula;
                        strcpy(nome, estudantes[i].nome);
                        strcpy(situacao, estudantes[i].situacao );
                        notaTrabalho= estudantes[i].nota_de_trabalho;
                        notaFinal = estudantes[i].nota_final;
                        ausencias = estudantes[i].numero_ausencias;
                        for(int j = 0; j<6;j++){
                            notasProva[j] = estudantes[i].notas_de_prova[j];
                            notasListas[j] = estudantes[i].notas_de_listas[j]; 
                        }
                        //beleza, agr vamos fazer a inversão de ordem
                        estudantes[i].matricula = estudantes[i+1].matricula;
                        strcpy(estudantes[i].nome, estudantes[i+1].nome);
                        strcpy(estudantes[i].situacao, estudantes[i+1].situacao );
                        estudantes[i].nota_de_trabalho = estudantes[i+1].nota_de_trabalho;
                        estudantes[i].nota_final = estudantes[i+1].nota_final;
                        estudantes[i].numero_ausencias = estudantes[i+1].numero_ausencias;
                        for(int j = 0; j<6;j++){
                            estudantes[i].notas_de_prova[j] = estudantes[i+1].notas_de_prova[j];
                            estudantes[i].notas_de_listas[j] = estudantes[i+1].notas_de_listas[j]; 
                        }
                        //agr o i+1 vai receber os valores das variáveis auxliares
                        estudantes[i+1].matricula = matricula;
                        strcpy(estudantes[i+1].nome, nome);
                        strcpy(estudantes[i+1].situacao, situacao );
                        estudantes[i+1].nota_de_trabalho = notaTrabalho;
                        estudantes[i+1].nota_final = notaFinal;
                        estudantes[i+1].numero_ausencias =  ausencias;
                        for(int j = 0; j<6;j++){
                            estudantes[i+1].notas_de_prova[j] = notasProva[j];
                            estudantes[i+1].notas_de_listas[j] = notasListas[j]; 
                        }
                            i= -1;
                    }
                }
                //finalmente vamos printar na tela
                for(int i = 0; i<contador;i++){
                puts("||======================================");
                puts("||======================================");
                printf( "||Matrícula: %d                       \n", estudantes[i].matricula ); //preenchendo os dados na tela, todos bonitinhos
                printf( "||Nome: %s                            \n", estudantes[i].nome );
                for(int j = 0; j<6;j++){
                    printf( "||Nota da prova %d: %lf           \n",i+1, estudantes[i].notas_de_prova[j]);       
                }
                for(int j = 0; j<6;j++){
                    printf( "||Nota da lista %d: %lf           \n",i+1, estudantes[i].notas_de_listas[j]);
                }
                printf( "||Nota do trabalho: %lf               \n", estudantes[i].nota_de_trabalho);
                printf( "||Nota final: %lf                     \n", estudantes[i].nota_final);
                printf( "||Noumero de ausências: %d            \n", estudantes[i].numero_ausencias);
                printf( "||Situacao: %s                        \n", estudantes[i].situacao);
                puts("||======================================");
                printf( "\n\n" );
                }
            }else if(op ==2){
                for(int i = 0; i<contador-1;i++){
                    if(strcmp(estudantes[i].nome, estudantes[i+1].nome) > 0){
                        //definindo valores de variáveis auxiliares
                        matricula = estudantes[i].matricula;
                        strcpy(nome, estudantes[i].nome);
                        strcpy(situacao, estudantes[i].situacao );
                        notaTrabalho= estudantes[i].nota_de_trabalho;
                        notaFinal = estudantes[i].nota_final;
                        ausencias = estudantes[i].numero_ausencias;
                        for(int j = 0; j<6;j++){
                            notasProva[j] = estudantes[i].notas_de_prova[j];
                            notasListas[j] = estudantes[i].notas_de_listas[j]; 
                        }
                        //beleza, agr vamos fazer a inversão de ordem
                        estudantes[i].matricula = estudantes[i+1].matricula;
                        strcpy(estudantes[i].nome, estudantes[i+1].nome);
                        strcpy(estudantes[i].situacao, estudantes[i+1].situacao );
                        estudantes[i].nota_de_trabalho = estudantes[i+1].nota_de_trabalho;
                        estudantes[i].nota_final = estudantes[i+1].nota_final;
                        estudantes[i].numero_ausencias = estudantes[i+1].numero_ausencias;
                        for(int j = 0; j<6;j++){
                            estudantes[i].notas_de_prova[j] = estudantes[i+1].notas_de_prova[j];
                            estudantes[i].notas_de_listas[j] = estudantes[i+1].notas_de_listas[j]; 
                        }
                        //agr o i+1 vai receber os valores das variáveis auxliares
                        estudantes[i+1].matricula = matricula;
                        strcpy(estudantes[i+1].nome, nome);
                        strcpy(estudantes[i+1].situacao, situacao );
                        estudantes[i+1].nota_de_trabalho = notaTrabalho;
                        estudantes[i+1].nota_final = notaFinal;
                        estudantes[i+1].numero_ausencias =  ausencias;
                        for(int j = 0; j<6;j++){
                            estudantes[i+1].notas_de_prova[j] = notasProva[j];
                            estudantes[i+1].notas_de_listas[j] = notasListas[j]; 
                        }
                            i= -1;
                    }
                }
                //finalmente vamos printar na tela
                for(int i = 0; i<contador;i++){
                puts("||======================================");
                puts("||======================================");
                printf( "||Matrícula: %d                       \n", estudantes[i].matricula ); //preenchendo os dados na tela, todos bonitinhos
                printf( "||Nome: %s                            \n", estudantes[i].nome );
                for(int j = 0; j<6;j++){
                    printf( "||Nota da prova %d: %lf           \n",i+1, estudantes[i].notas_de_prova[j]);       
                }
                for(int j = 0; j<6;j++){
                    printf( "||Nota da lista %d: %lf           \n",i+1, estudantes[i].notas_de_listas[j]);
                }
                printf( "||Nota do trabalho: %lf               \n", estudantes[i].nota_de_trabalho);
                printf( "||Nota final: %lf                     \n", estudantes[i].nota_final);
                printf( "||Noumero de ausências: %d            \n", estudantes[i].numero_ausencias);
                printf( "||Situacao: %s                        \n", estudantes[i].situacao);
                puts("||======================================");
                printf( "\n\n" );
                }
            }else if(op ==3){
                for(int i = 0; i<contador-1;i++){
                    if(estudantes[i].nota_final < estudantes[i+1].nota_final){
                        //definindo valores de variáveis auxiliares
                        matricula = estudantes[i].matricula;
                        strcpy(nome, estudantes[i].nome);
                        strcpy(situacao, estudantes[i].situacao );
                        notaTrabalho= estudantes[i].nota_de_trabalho;
                        notaFinal = estudantes[i].nota_final;
                        ausencias = estudantes[i].numero_ausencias;
                        for(int j = 0; j<6;j++){
                            notasProva[j] = estudantes[i].notas_de_prova[j];
                            notasListas[j] = estudantes[i].notas_de_listas[j]; 
                        }
                        //beleza, agr vamos fazer a inversão de ordem
                        estudantes[i].matricula = estudantes[i+1].matricula;
                        strcpy(estudantes[i].nome, estudantes[i+1].nome);
                        strcpy(estudantes[i].situacao, estudantes[i+1].situacao );
                        estudantes[i].nota_de_trabalho = estudantes[i+1].nota_de_trabalho;
                        estudantes[i].nota_final = estudantes[i+1].nota_final;
                        estudantes[i].numero_ausencias = estudantes[i+1].numero_ausencias;
                        for(int j = 0; j<6;j++){
                            estudantes[i].notas_de_prova[j] = estudantes[i+1].notas_de_prova[j];
                            estudantes[i].notas_de_listas[j] = estudantes[i+1].notas_de_listas[j]; 
                        }
                        //agr o i+1 vai receber os valores das variáveis auxliares
                        estudantes[i+1].matricula = matricula;
                        strcpy(estudantes[i+1].nome, nome);
                        strcpy(estudantes[i+1].situacao, situacao );
                        estudantes[i+1].nota_de_trabalho = notaTrabalho;
                        estudantes[i+1].nota_final = notaFinal;
                        estudantes[i+1].numero_ausencias =  ausencias;
                        for(int j = 0; j<6;j++){
                            estudantes[i+1].notas_de_prova[j] = notasProva[j];
                            estudantes[i+1].notas_de_listas[j] = notasListas[j]; 
                        }
                            i= -1;
                    }
                }
                //finalmente vamos printar na tela
                for(int i = 0; i<contador;i++){
                puts("||======================================");
                puts("||======================================");
                printf( "||Matrícula: %d                       \n", estudantes[i].matricula ); //preenchendo os dados na tela, todos bonitinhos
                printf( "||Nome: %s                            \n", estudantes[i].nome );
                for(int j = 0; j<6;j++){
                    printf( "||Nota da prova %d: %lf           \n",i+1, estudantes[i].notas_de_prova[j]);       
                }
                for(int j = 0; j<6;j++){
                    printf( "||Nota da lista %d: %lf           \n",i+1, estudantes[i].notas_de_listas[j]);
                }
                printf( "||Nota do trabalho: %lf               \n", estudantes[i].nota_de_trabalho);
                printf( "||Nota final: %lf                     \n", estudantes[i].nota_final);
                printf( "||Noumero de ausências: %d            \n", estudantes[i].numero_ausencias);
                printf( "||Situacao: %s                        \n", estudantes[i].situacao);
                puts("||======================================");
                printf( "\n\n" );
                }
            }
                
        }      
    //fclose(dataBase);
    }
}
verificarTamanho(char *FileName){
    FILE * dataBase;
    int contador = 0;
    dataBase = fopen( FileName, "rb");
        while(feof(dataBase)==0){
            fread( &defaultStudent, sizeof(defaultStudent), 1, dataBase);
            contador++;
        }
    fclose(dataBase);
    return contador;
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
                puts("digite os novos dados do aluno:");
                archiveData();
                fseek(dataBase, (-1)*sizeof(defaultStudent), SEEK_CUR);//volta o "leitor do arquivo para a posição do registro a ser alterado"
                fwrite( &defaultStudent, sizeof(defaultStudent), 1, dataBase);//finalmente altera o registro 
            }
            
        }
    fclose(dataBase);
    }       
   
}
readData(int choice){
    system("clear");//limpando terminal
    FILE * dataBase;
    char name[200];
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



    
