#include <stdio.h>
#include <string.h>

// --------------------
// Métricas de execução
// --------------------

typedef struct {
    long comparacoes;
    long trocas;
} Metricas;

void zera_metricas(Metricas *m) { 
    m->comparacoes = 0; 
    m->trocas = 0; 
}

// --------------------
// Utilidades
// --------------------

void swap_float(float *a, float *b, Metricas *m) {
    float temp = *a;
    *a = *b;
    *b = temp;
    m->trocas++; 
}

void imprime_float(float *v, int n, const char *nome) {
    printf("%s: ", nome);
    for (int i = 0; i < n; i++) {
        printf("%.2f ", v[i]);
    }
    printf("\n");
}

// --------------------
// Algoritmos de ordenação (para números decrescentes)
// --------------------

// Algoritmo Bubble Sort (float decrescente)
// O algoritmo percorre o vetor repetidamente e troca elementos adjacentes se estiverem fora de ordem (do maior para o menor).
void bubble_float_desc(float *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int pass = 0; pass < n - 1; pass++) {
        int mudou = 0;
        for (int i = 0; i < n - 1 - pass; i++) {
            m->comparacoes++; 
            if (v[i] < v[i + 1]) {  // Compara e troca se necessário
                swap_float(&v[i], &v[i + 1], m);
                mudou = 1;
            }
        }
        if (!mudou) break;  // Se não houve trocas, o vetor já está ordenado
    }
}

// Algoritmo Insertion Sort (float decrescente)
// A cada iteração, o algoritmo insere um elemento na posição correta dentro da parte já ordenada do vetor.
void insertion_float_desc(float *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int i = 1; i < n; i++) {
        float chave = v[i]; 
        int j = i - 1;
        while (j >= 0) {
            m->comparacoes++;
            if (v[j] < chave) { // Move os elementos para a direita se necessário
                v[j + 1] = v[j];
                m->trocas++;
                j--;
            } else {
                break; // Se o elemento estiver na posição correta, sai do loop
            }
        }
        v[j + 1] = chave; // Coloca o elemento na posição correta
    }
}

// Algoritmo Selection Sort (float decrescente)
// O algoritmo encontra o maior elemento restante e o coloca na posição correta do vetor.
void selection_float_desc(float *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int i = 0; i < n - 1; i++) {
        int idx_max = i;
        for (int j = i + 1; j < n; j++) {
            m->comparacoes++; 
            if (v[j] > v[idx_max]) idx_max = j; // Encontra o maior valor
        }
        if (idx_max != i) swap_float(&v[i], &v[idx_max], m); // Troca com o maior encontrado
    }
}

int main(void) {
    // -------------------------
    // Exemplo 1: Pontos (float)
    // -------------------------
    float pontos_base[] = {5.4, 6.0, 10.0, 7.5, 4.0, 7.0, 9.3, 6.6, 8.0, 5.5, 7.8, 3.7};
    int n_pontos = (int)(sizeof(pontos_base) / sizeof(pontos_base[0])); 
    float a1[12], a2[12], a3[12];  
    memcpy(a1, pontos_base, sizeof(pontos_base)); // Cópia para Bubble Sort
    memcpy(a2, pontos_base, sizeof(pontos_base)); // Cópia para Insertion Sort
    memcpy(a3, pontos_base, sizeof(pontos_base)); // Cópia para Selection Sort
    
    int indice_maior_pontuacao = 0;
    // Encontrar o índice do aluno com maior pontuação antes da ordenação
    for (int i = 1; i < n_pontos; i++) {
        if (pontos_base[i] > pontos_base[indice_maior_pontuacao]) {
            indice_maior_pontuacao = i;
        }
    }

    printf("Aluno com a maior pontuação antes da ordenação: Índice %d, Pontuação %.2f\n", indice_maior_pontuacao, pontos_base[indice_maior_pontuacao]);

    // Imprime o vetor original
    imprime_float(pontos_base, n_pontos, "Pontos (original)");

    Metricas mb, mi, ms; // Variáveis para armazenar as métricas de cada algoritmo
    bubble_float_desc(a1, n_pontos, &mb);  // Executa o Bubble Sort
    imprime_float(a1, n_pontos, "Bubble (desc)"); 
    printf("Bubble -> comparacoes=%ld, trocas=%ld\n", mb.comparacoes, mb.trocas);

    insertion_float_desc(a2, n_pontos, &mi);  // Executa o Insertion Sort
    imprime_float(a2, n_pontos, "Insertion (desc)");
    printf("Insertion -> comparacoes=%ld, movimentos=%ld\n", mi.comparacoes, mi.trocas);

    selection_float_desc(a3, n_pontos, &ms); // Executa o Selection Sort
    imprime_float(a3, n_pontos, "Selection (desc)");
    printf("Selection -> comparacoes=%ld, trocas=%ld\n\n", ms.comparacoes, ms.trocas);
    
    // Após a ordenação, encontra a nova posição do aluno com a maior pontuação
    int nova_posicao = -1;
    for (int i = 0; i < n_pontos; i++) {
        if (a1[i] == pontos_base[indice_maior_pontuacao]) {
            nova_posicao = i;
            break;
        }
    }
    
    // Imprime a nova posição do aluno com a maior pontuação
    printf("Após a ordenação, o aluno com a maior pontuação ficou na posição: %d\n", nova_posicao);

    return 0;
}
