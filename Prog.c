#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//=================================
int i, f, n, g, poslist;
int precall;
int count = 0;
int sum = 0;
int num = 0;
//=================================
#define MAX 50
//=================================
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
struct Tanalise
{
    int analise_id;
    char nome[50];
    int benef;
    char colesterol[50];
    char glicose[50];
    char proteinas[50];
    Date data;
    float preco;
} info[MAX], temp[MAX];
FILE *fptr;
//=================================
int main()
{
    int escolha;
    printf("\n\t\t\t\t=================================\n");
    printf("\n\t\t\t\tBem vindo!");
    printf("\n\t\t\t\t=================================\n");
    do
    {
        printf("\n\t\t\t\t========================================================\n");
        printf("\n\t\t\t[1]  Inserir Informacao das Analises Clinicas  \n");
        printf("\n\t\t\t[2]  Gravar Analises Clinicas no Ficheiro\n");
        printf("\n\t\t\t[3]  Ler do Ficheiro e Mostrar\n");
        printf("\n\t\t\t[4]  Listar todas Analises Clinicas Inseridas\n");
        printf("\n\t\t\t[5]  Listar Analises Clinicas por Numero de Beneficiario\n");
        printf("\n\t\t\t[6]  Remover Analise Clinica por Numero da Analise\n");
        printf("\n\t\t\t[7]  Ler do Ficheiro, Ordenar, Gravar e Mostrar\n");
        printf("\n\t\t\t[8]  Calcular o Valor Total a Pagar por Todas as Analises\n");
        printf("\n\t\t\t[0]  Sair\n\n");
        printf("\n\t\t\t\t========================================================\n");
        printf("\n\t\t\tOpcao :  ");
        scanf("%d", &escolha);
        printf("\n\t\t\t\t========================================================\n");
        switch (escolha)
        {
        case 1:
            InsereAnalises();
            break;
        case 2:
            GravarAnalise();
            break;
        case 3:
            LerAnalises();
            break;
        case 4:
            Tamanho();
            MostrarAnalise();
            break;
        case 5:
            Tamanho();
            OrdenarBenef();
            break;
        case 6:
            Tamanho();
            EliminaAnalise();
            break;
        case 7:
            LerAnalises();
            Ordenar();
            GravarAnalise();
            ListarAnalises();
            break;
        case 8:
            Tamanho();
            PrecoTodas();
            break;
        };

    } while (escolha != 0);
}
int InsereAnalises()
{
    int i;
    float pg, pc, pp;
    printf("\n\n");
    printf("\n\t\t\tPerfis Introduzidos: %d\n", num);
    printf("\n\t\t\tQuantos Perfis Pretende Introduzir? : ");
    scanf("%d", &n);

    sum = n + num;

    for (i = num; i < sum; i++)
    {

        printf("\n\t\t\tAnalise N.           : ");
        scanf("%d", &info[i].analise_id);
        while (info[i].analise_id < 0)
        {
            printf("\n\t\t\tValor invalido introduza um numero positivo: ");
            scanf("%d", &info[i].analise_id);
        }

        printf("\n\t\t\tInsira Nome          : ");
        scanf("%s", info[i].nome);

        printf("\n\t\t\tInsira Beneficiario  : ");
        scanf("%d", &info[i].benef);
        while (info[i].benef < 1 || info[i].benef > 99999)
        {
            printf("\n\t\t\tInsira um N. Beneficiario valido entre 1 - 99999! : ");
            scanf("%d", &info[i].benef);
        };

        printf("\n\t\t\tTipo de Analise (S -> Sim, N -> Nao)\n");

        printf("\n\t\t\tColesterol           : ");
        scanf(" %s", &info[i].colesterol);
        while (strcmp(info[i].colesterol, "N") != 0 && strcmp(info[i].colesterol, "S") != 0)
        {
            printf("\n\t\t\tCarater Invalido, insira S -> Sim, N -> Nao: ");
            scanf(" %s", &info[i].colesterol);
        }

        printf("\n\t\t\tGlicose              : ");
        scanf(" %s", &info[i].glicose);
        while (strcmp(info[i].glicose, "N") != 0 && strcmp(info[i].glicose, "S") != 0)
        {
            printf("\n\t\t\tCarater Invalido, insira S -> Sim, N -> Nao: ");
            scanf(" %s", &info[i].glicose);
        }

        printf("\n\t\t\tProteinas            : ");
        scanf(" %s", &info[i].proteinas);
        while (strcmp(info[i].proteinas, "N") != 0 && strcmp(info[i].proteinas, "S") != 0)
        {
            printf("\n\t\t\tCarater Invalido, insira S -> Sim, N -> Nao: ");
            scanf(" %s", &info[i].proteinas);
        }

        printf("\n\t\t\tData de recolha (dia/mes/ano): ");
        scanf("%d/%d/%d", &info[i].data.dd, &info[i].data.mm, &info[i].data.yyyy);
        while (datevalid() == 0)
        {
            printf("\n\t\t\tData Invalida, insira novamente: ");
            scanf("%d/%d/%d", &info[i].data.dd, &info[i].data.mm, &info[i].data.yyyy);
        }

        if (strcmp("S", info[i].colesterol) == 0)
        {
            pc = 2.10;
        }
        else
        {
            pc = 0.0;
        }
        if (strcmp("S", info[i].glicose) == 0)
        {
            pg = 5.50;
        }
        else
        {
            pg = 0.0;
        }
        if (strcmp("S", info[i].proteinas) == 0)
        {
            pp = 2.63;
        }
        else
        {
            pp = 0.0;
        }
        info[i].preco = pc + pg + pp;
        printf("\n\t\t\tPreco Final : %.2f[eur]\n", info[i].preco);
        num++;
    }
}
int GravarAnalise()
{
    FILE *fp = NULL;
    fp = fopen("analises.dat", "wb");

    if (!fp)
    {
        printf("Error!");
        return 1;
    }
    for (i = 0; i < sum; i++)
    {
        fwrite(&info[i], sizeof(info[i]), 1, fp);
        g++;
    }
    printf("\n\t\t\t\t=================================\n");
    printf("\n\t\t\tGuardado com sucesso \n");
    printf("\n\t\t\t\t=================================");
    fclose(fp);
}
int LerAnalises()
{
    int j, leng, pos;
    FILE *fp = NULL;
    struct Tanalise ler = {0};

    fp = fopen("analises.dat", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\tErro!\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    leng = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    pos = leng / sizeof(info[0]);

    printf("\n\t\t\tDados do ficheiro\n");
    for (i = 0; i < pos; i++)
    {
        fread(&ler, sizeof(info[i]), 1, fp);
        printf("\n\t\t\t==================================================");
        printf("\n\t\t\tPaciente N. : %d", j + 1);
        printf("\n\t\t\t==================================================");
        printf("\n\t\t\tAnalise : %d \n", ler.analise_id);
        printf("\n\t\t\tNome: %s Beneficiario: %d\n", ler.nome, ler.benef);
        printf("\n\t\t\tTipo de Analise\n");
        printf("\n\t\t\tColesterol: %s Glicose: %s Proteinas: %s \n", ler.colesterol, ler.glicose, ler.proteinas);
        printf("\n\t\t\tData de Recolha : %d/%d/%d\n", ler.data.dd, ler.data.mm, ler.data.yyyy);
        printf("\n\t\t\tPreco final : %.2f [eur]\n", ler.preco);
        printf("\n\t\t\t==================================================");
        j++;
    };
    fclose(fp);
    return 0;
}
int MostrarAnalise()
{
    int i;
    printf("\n\t\t\tDados:\n");
    for (i = 0; i < poslist; i++)
    {
        printf("\n\t\t\tPaciente : %d\n", i + 1);
        printf("\n\t\t\tAnalise N.       : %d\n", info[i].analise_id);
        printf("\n\t\t\tNome             : %s\n", info[i].nome);
        printf("\n\t\t\tN. Beneficiario  : %d\n", info[i].benef);
        printf("\n\t\t\tTipo de Analise\n");
        printf("\n\t\t\tColesterol       : [%s]\n", info[i].colesterol);
        printf("\n\t\t\tGlicose          : [%s]\n", info[i].glicose);
        printf("\n\t\t\tProteinas        : [%s]\n", info[i].proteinas);
        printf("\n\t\t\tData de recolha (dia/mes/ano): %d/%d/%d\n", info[i].data.dd, info[i].data.mm, info[i].data.yyyy);
        printf("\n\t\t\tPreco final : %.2f [eur]\n", info[i].preco);
    }
}
int Ordenar()
{
    int j;

    for (i = 0; i < sum; i++)
    {
        for (j = 0; j < sum - 1; j++)
        {
            if (info[j].preco > info[j + 1].preco)
            {
                temp[j] = info[j];
                info[j] = info[j + 1];
                info[j + 1] = temp[j];
            }
        }
    }

    for (i = 0; i < sum; i++)
    {
        printf("\n\t\t\t==================================================");
        printf("\n\t\t\tN. Beneficiario : %d", info[i].benef);
        printf("\n\t\t\t==================================================");
        printf("\n\t\t\tAnalise : %d \n", info[i].analise_id);
        printf("\n\t\t\tNome: %s|\n", info[i].nome);
        printf("\n\t\t\t|Tipo de Analise|\n");
        printf("\n\t\t\tColesterol: %s | Glicose: %s | Proteinas: %s \n", info[i].colesterol, info[i].glicose, info[i].proteinas);
        printf("\n\t\t\tData de Recolha : %d/%d/%d\n", info[i].data.dd, info[i].data.mm, info[i].data.yyyy);
        printf("\n\t\t\tPreco final : %.2f\n", info[i].preco);
        printf("\n\t\t\t==================================================");
    }
}
int OrdenarBenef()
{
    int d, f;
    int posi;
    printf("\n\t\t\t| Procurar |\n");
    printf("\n\t\t\tInsira o Numero de Beneficiario do paciente : ");
    scanf("%d", &d);

    for (f = 0; f < poslist; f++)
    {
        if (info[f].benef == d)
        {
            posi = f;
        }
    }
    printf("\n\t\t\t==================================================");
    printf("\n\t\t\tN. Beneficiario : %d", info[posi].benef);
    printf("\n\t\t\t==================================================");
    printf("\n\t\t\tAnalise : %d \n", info[posi].analise_id);
    printf("\n\t\t\tNome: %s\n", info[posi].nome);
    printf("\n\t\t\t|Tipo de Analise|\n");
    printf("\n\t\t\tColesterol: %s | Glicose: %s | Proteinas: %s | \n", info[posi].colesterol, info[posi].glicose, info[posi].proteinas);
    printf("\n\t\t\tData de Recolha : %d/%d/%d\n", info[posi].data.dd, info[posi].data.mm, info[posi].data.yyyy);
    printf("\n\t\t\tPreco final : %.2f\n", info[posi].preco);
    printf("\n\t\t\t==================================================");
}
int EliminaAnalise()
{
    int d, f;
    int posi;
    printf("\n\t\t\t| Eliminar |\n");
    printf("\n\t\t\tInsira o Numero da Analise do paciente que vai eliminar : ");
    scanf("%d", &d);

    for (f = 0; f < poslist; f++)
    {
        if (info[f].analise_id == d)
        {
            posi = f;
        }
    }
    for (i = posi; i < sum; i++)
    {
        info[i] = info[i + 1];
    }
    poslist - 1;
}
int Tamanho()
{
    int f, a;
    poslist = 0;
    for (i = 0; i < MAX; i++)
    {
        if (info[i].analise_id != 0)
        {
            poslist++;
        }
    }
}
int ListarAnalises()
{
    int j, leng, pos;
    FILE *fp = NULL;
    struct Tanalise ler = {0};

    fp = fopen("analises.dat", "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\tErro!\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    leng = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    pos = leng / sizeof(info[0]);

    printf("\n\t\t\tDados do ficheiro\n");
    for (i = 0; i < pos; i++)
    {
        fread(&ler, sizeof(info[i]), 1, fp);
        printf("\n\t\t\t==================================================");
        printf("\n\t\t\tPreço final : %.2f\n", ler.preco);
        printf("\n\t\t\t==================================================");
        printf("\n\t\t\tAnalise : %d \n", ler.analise_id);
        printf("\n\t\t\tNome: %s Beneficiario: %d\n", ler.nome, ler.benef);
        printf("\n\t\t\tTipo de Analise\n");
        printf("\n\t\t\tColesterol: %s Glicose: %s Proteinas: %s \n", ler.colesterol, ler.glicose, ler.proteinas);
        printf("\n\t\t\tData de Recolha : %d/%d/%d\n", ler.data.dd, ler.data.mm, ler.data.yyyy);
        printf("\n\t\t\t==================================================");
        j++;
    };
    fclose(fp);
    return 0;
}
int PrecoTodas()
{
    float suma = 0.0;
    for (i = 0; i < sum; i++)
    {
        suma += info[i].preco;
    }
    printf("\n\t\t\tO preco total de todas as analises e: %.2f [eur]\n", suma);
}
//========================================================================
int AnoBis()
{
    if ((info[i].data.yyyy % 4 == 0) && (info[i].data.yyyy % 100 != 0) && (info[i].data.yyyy % 400 == 0))
        return 0;
    else
        return 1;
}
int datevalid()
{
    if (info[i].data.yyyy < 2020 || info[i].data.yyyy > 2050)
        return 0;
    if (info[i].data.mm < 1 || info[i].data.mm > 12)
        return 0;
    if (info[i].data.dd < 1 || info[i].data.dd > 31)
        return 0;
    if (info[i].data.mm == 2)
    {
        if (AnoBis(info[i].data.yyyy))
        {
            if (info[i].data.dd <= 29)
                return 1;
            else
                return 0;
        }
    }
    if (info[i].data.mm == 4 || info[i].data.mm == 6 || info[i].data.mm == 9 || info[i].data.mm == 11)
    {
        if (info[i].data.dd <= 30)
            return 1;
        else
            return 0;
    }
}
