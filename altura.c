#include <stdio.h>
#include <string.h> 

// --------------------
// Métricas de execução
// --------------------

typedef struct {
    long comparacoes; // Conta o número de comparações realizadas
    long trocas; // Conta o número de trocas realizadas
} Metricas;

// Função para resetar as métricas de comparações e trocas
void zera_metricas(Metricas *m) { 
    m->comparacoes = 0; 
    m->trocas = 0; 
}

// --------------------
// Utilidades
// --------------------

// Troca os valores de dois inteiros e atualiza as métricas de trocas
void swap_int(int *a, int *b, Metricas *m) {
    int temp = *a;
    *a = *b;
    *b = temp;
    m->trocas++; 
}


// Função para imprimir um vetor de inteiros
void imprime_int(int *v, int n, const char *nome) {
    printf("%s: ", nome);
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// --------------------
// Algoritmos de ordenação
// --------------------

// Bubble Sort (int crescente)
// Percorre o vetor várias vezes, comparando elementos adjacentes e trocando-os se necessário.
// Se em uma passada inteira não houver trocas, o vetor já está ordenado e o algoritmo termina.
void bubble_int_asc(int *v, int n, Metricas *m) {
    zera_metricas(m); // Reseta as métricas
    for (int pass = 0; pass < n - 1; pass++) { // Passa por todo o vetor, n-1 vezes
        int mudou = 0;  
        for (int i = 0; i < n - 1 - pass; i++) { // Comparação entre elementos adjacentes
            m->comparacoes++; // Contabiliza a comparação
            if (v[i] > v[i + 1]) { // Se estiver fora de ordem, troca
                swap_int(&v[i], &v[i + 1], m); // Realiza a troca e conta
                mudou = 1;
            }
        }
        if (!mudou) break; // Se não houve trocas, o vetor já está ordenado
    }
}

// Insertion Sort (int crescente)
// Ordena inserindo um elemento de cada vez em sua posição correta na parte já ordenada do vetor.
void insertion_int_asc(int *v, int n, Metricas *m) {
    zera_metricas(m); // Reseta as métricas
    for (int i = 1; i < n; i++) { // Percorre do segundo elemento até o último
        int chave = v[i]; // Elemento a ser inserido
        int j = i - 1;
        while (j >= 0) { // Move os elementos maiores para a direita
            m->comparacoes++; // Contabiliza a comparação
            if (v[j] > chave) { // Se o elemento for maior que a chave
                v[j + 1] = v[j]; // Move o elemento para a posição seguinte
                m->trocas++;     // Conta a movimentação
                j--;
            } else {
                break; // Se encontrar o local correto para a chave, sai do loop
            }
        }
        v[j + 1] = chave; // Coloca a chave na posição correta
    }
}

// Selection Sort (int crescente)
// Encontra o menor elemento em cada iteração e coloca-o na posição correta do vetor.
void selection_int_asc(int *v, int n, Metricas *m) {
    zera_metricas(m); // Reseta as métricas
    for (int i = 0; i < n - 1; i++) { // Percorre o vetor
        int idx_min = i; // Índice do menor elemento encontrado
        for (int j = i + 1; j < n; j++) { // Busca o menor elemento à direita
            m->comparacoes++; // Contabiliza a comparação
            if (v[j] < v[idx_min]) idx_min = j; // Atualiza o índice do menor elemento
        }
        if (idx_min != i) swap_int(&v[i], &v[idx_min], m); // Troca o elemento na posição i com o menor encontrado
    }
}

int main(void) {
    // Vetor de alturas a ser ordenado
    int alturas_base[] = {160, 170, 163, 174, 181, 179, 190, 155, 200, 178};
    int n_alturas = (int)(sizeof(alturas_base) / sizeof(alturas_base[0])); // Tamanho do vetor
    int a1[11], a2[11], a3[11];
    memcpy(a1, alturas_base, sizeof(alturas_base)); // Cópia dos dados para cada algoritmo
    memcpy(a2, alturas_base, sizeof(alturas_base));
    memcpy(a3, alturas_base, sizeof(alturas_base));

    imprime_int(alturas_base, n_alturas, "Alturas (original)"); // Imprime o vetor original

    Metricas mb, mi, ms; // Variáveis para armazenar as métricas de cada algoritmo
    bubble_int_asc(a1, n_alturas, &mb); // Executa Bubble Sort
    imprime_int(a1, n_alturas, "Bubble (asc)"); // Imprime o vetor ordenado
    printf("Bubble -> comparacoes=%ld, trocas=%ld\n", mb.comparacoes, mb.trocas); // Exibe as métricas

    insertion_int_asc(a2, n_alturas, &mi); // Executa Insertion Sort
    imprime_int(a2, n_alturas, "Insertion (asc)");
    printf("Insertion -> comparacoes=%ld, movimentos=%ld\n", mi.comparacoes, mi.trocas); // Exibe as métricas

    selection_int_asc(a3, n_alturas, &ms); // Executa Selection Sort
    imprime_int(a3, n_alturas, "Selection (asc)");
    printf("Selection -> comparacoes=%ld, trocas=%ld\n\n", ms.comparacoes, ms.trocas); // Exibe as métricas

    return 0;
}
