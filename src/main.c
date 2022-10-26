#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Padrinho {
    char nome[64];
    double valorDoado;
};

struct Crianca {
    char nome[64];
    double valorPresente;
    double valorPreenchido;
};

struct RelPadCri {
    int indexCrianca;
    int indexPadrinho;
};

void OrganizarStructCrianca(struct Crianca arr[]) {
    char buffer[64];

    srand(time(0));

    for(int i = 0; i < 64; i++) {
        sprintf(buffer, "%d", i);

        for(int n = 0; n < 64; n++) {
            arr[i].nome[n] = buffer[n];
        }

        arr[i].valorPresente = (rand() % 1000) + 1;
        arr[i].valorPreenchido = -1;
    }
}

void OrganizarStructRel(struct RelPadCri arr[]) {
    for(int i = 0; i < 256; i++) {
        arr[i].indexCrianca = -1;
        arr[i].indexPadrinho = -1;
    }
}

void RelacionarCriancasPadrinhos(struct RelPadCri arrRelacao[],
                                 struct Crianca arrCrianca[],
                                 struct Padrinho arrPadrinho[],
                                 int numPadrCadastrados) {
    int contPadr = 0;
    int contRela = 0;

    double jaFoiPago = 0, jaDoou = 0;
    double valorPresenteReal;
    double valorDoadoReal;

    for(int i = 0; i < 64; i++) {
        if(numPadrCadastrados <= contPadr)
            break;

        arrCrianca[i].valorPreenchido = 0;

        label1:
        if(numPadrCadastrados <= contPadr)
            break;

        valorPresenteReal = arrCrianca[i].valorPresente - jaFoiPago;
        valorDoadoReal = arrPadrinho[contPadr].valorDoado - jaDoou;    

        if(valorPresenteReal > valorDoadoReal) {
            arrCrianca[i].valorPreenchido += valorDoadoReal;
            arrRelacao[contRela].indexCrianca = i;
            arrRelacao[contRela].indexPadrinho = contPadr;
            
            contRela++;
            contPadr++;

            jaFoiPago += valorDoadoReal;
            jaDoou = 0;

            goto label1;
        }
        if(valorPresenteReal == valorDoadoReal) {
            arrCrianca[i].valorPreenchido = arrCrianca[i].valorPresente;
            arrRelacao[contRela].indexCrianca = i;
            arrRelacao[contRela].indexPadrinho = contPadr;

            jaFoiPago = 0;
            jaDoou = 0;

            contRela++;
            contPadr++;

            continue;
        }
        if(valorPresenteReal < valorDoadoReal) {
            arrCrianca[i].valorPreenchido = arrCrianca[i].valorPresente;
            arrRelacao[contRela].indexCrianca = i;
            arrRelacao[contRela].indexPadrinho = contPadr;

            contRela++;

            jaDoou += valorPresenteReal;
            jaFoiPago = 0;

            continue;
        }
    }
}

double RegistrarPadrinho(struct Padrinho arr[], int contadorPadrinho) {
    double valorDoado = 0;

    printf("Nome do Padrinho: ");
    scanf("%s", &arr[contadorPadrinho].nome);
    fflush(stdin);

    printf("Valor Doado: ");
    scanf("%lf", &arr[contadorPadrinho].valorDoado);
    fflush(stdin);

    printf("\n");

    return valorDoado;
}

int SelecionarOpcao() {
    int opcao;

    printf("Selecione a opcao desejada.\n");
    printf("1 - Cadastrar uma doacao\n");
    printf("2 - Mostrar resultado geral\n");
    printf("Opcao : ");
    scanf("%d", &opcao);
    fflush(stdin);

    printf("\n");

    return opcao;
}

void MostrarPadrinhos(struct Padrinho arr[], int contadorPadrinho) {
    for(int i = 0; i < contadorPadrinho; i++) {
        printf("Nome do Padrinho: %s\n", arr[i].nome);
        printf("Valor Doado: %g\n", arr[i].valorDoado);
        printf("\n");
    }
}

void MostrarCriancas(struct Crianca arr[]) {
    for(int i = 0; i < 64; i++) {
        printf("Nome da Crianca: %s\n", arr[i].nome);
        printf("Valor do Presente: %g\n", arr[i].valorPresente);

        printf("\n");
    }
}

void MostrarPadrCrian(struct RelPadCri arrRelacao[],
                      struct Crianca arrCrianca[],
                      struct Padrinho arrPadrinho[]) {
    int buffer = 0;

    for(int i = 0; i < 64; i++) {
        printf("Nome da Crianca: %s\n", arrCrianca[i].nome);
        printf("Padrinhos:\n");
        for(buffer; buffer < 256; buffer++) {
            if(arrRelacao[buffer].indexCrianca != i)
                break;
            printf("\t%s\n", arrPadrinho[arrRelacao[buffer].indexPadrinho].nome);
        }

        if(arrCrianca[i].valorPreenchido != arrCrianca[i].valorPresente) {
            printf("O presente da crianca acima nao foi completado.\n");
            printf("Foram completos apenas %g reais dos %g reais do presente\n",
                   arrCrianca[i].valorPreenchido, arrCrianca[i].valorPresente);
            
            break;
        }

        printf("\n");

    }
    printf("\n");
}

int main() {
    struct Padrinho padrinho[64];
    struct Crianca crianca[64];
    struct RelPadCri relPadCri[256];

    int contadorPadrinho = 0;

    double valorDoado = 0;

    OrganizarStructCrianca(crianca);

    while(1) {
        switch(SelecionarOpcao()) {
            case 1:
                valorDoado += RegistrarPadrinho(padrinho, contadorPadrinho);
                contadorPadrinho++;
                break;

            case 2:
                OrganizarStructRel(relPadCri);
                MostrarPadrinhos(padrinho, contadorPadrinho);
                MostrarCriancas(crianca);
                RelacionarCriancasPadrinhos(relPadCri, crianca, padrinho,
                                            contadorPadrinho);
                MostrarPadrCrian(relPadCri, crianca, padrinho);
        }
    }
}