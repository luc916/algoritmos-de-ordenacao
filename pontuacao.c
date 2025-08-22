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

// Bubble Sort (float decrescente)
void bubble_float_desc(float *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int pass = 0; pass < n - 1; pass++) {
        int mudou = 0;
        for (int i = 0; i < n - 1 - pass; i++) {
            m->comparacoes++;
            if (v[i] < v[i + 1]) { 
                swap_float(&v[i], &v[i + 1], m);
                mudou = 1;
            }
        }
        if (!mudou) break;
    }
}

// Insertion Sort (float decrescente)
void insertion_float_desc(float *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int i = 1; i < n; i++) {
        float chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            m->comparacoes++;
            if (v[j] < chave) { 
                v[j + 1] = v[j];
                m->trocas++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

// Selection Sort (float decrescente)
void selection_float_desc(float *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int i = 0; i < n - 1; i++) {
        int idx_max = i;
        for (int j = i + 1; j < n; j++) {
            m->comparacoes++;
            if (v[j] > v[idx_max]) idx_max = j; 
        }
        if (idx_max != i) swap_float(&v[i], &v[idx_max], m);
    }
}

int main(void) {
    // -------------------------
    // Exemplo 1: Pontos (float)
    // -------------------------
    float pontos_base[] = {5.4, 6.0, 10.0, 7.5, 4.0, 7.0, 9.3, 6.6, 8.0, 5.5, 7.8, 3.7};
    int n_pontos = (int)(sizeof(pontos_base) / sizeof(pontos_base[0])); 
    float a1[12], a2[12], a3[12];  
    memcpy(a1, pontos_base, sizeof(pontos_base));
    memcpy(a2, pontos_base, sizeof(pontos_base));
    memcpy(a3, pontos_base, sizeof(pontos_base));
    
    int indice_maior_pontuacao = 0;
    for (int i = 1; i < n_pontos; i++) {
        if (pontos_base[i] > pontos_base[indice_maior_pontuacao]) {
            indice_maior_pontuacao = i;
        }
    }

    printf("Aluno com a maior pontuação antes da ordenação: Índice %d, Pontuação %.2f\n", indice_maior_pontuacao, pontos_base[indice_maior_pontuacao]);

    imprime_float(pontos_base, n_pontos, "Pontos (original)");

    Metricas mb, mi, ms;
    bubble_float_desc(a1, n_pontos, &mb);  
    imprime_float(a1, n_pontos, "Bubble (desc)");
    printf("Bubble -> comparacoes=%ld, trocas=%ld\n", mb.comparacoes, mb.trocas);

    insertion_float_desc(a2, n_pontos, &mi);  
    imprime_float(a2, n_pontos, "Insertion (desc)");
    printf("Insertion -> comparacoes=%ld, movimentos=%ld\n", mi.comparacoes, mi.trocas);

    selection_float_desc(a3, n_pontos, &ms); 
    imprime_float(a3, n_pontos, "Selection (desc)");
    printf("Selection -> comparacoes=%ld, trocas=%ld\n\n", ms.comparacoes, ms.trocas);

    int nova_posicao = -1;
    for (int i = 0; i < n_pontos; i++) {
        if (a1[i] == pontos_base[indice_maior_pontuacao]) {
            nova_posicao = i;
            break;
        }
    }

    printf("Após a ordenação, o aluno com a maior pontuação ficou na posição: %d\n", nova_posicao);

    return 0;
}
