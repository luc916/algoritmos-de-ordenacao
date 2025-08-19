#include <stdio.h>
#include <string.h> // memcpy

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
// Funções auxiliares
// --------------------

// Troca dois inteiros
void swap_int(int *a, int *b, Metricas *m) {
    int temp = *a;
    *a = *b;
    *b = temp;
    m->trocas++;  // Conta a troca
}

// Imprime um vetor de inteiros
void imprime_int(int *v, int n, const char *nome) {
    printf("%s: ", nome);
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// --------------------
// Algoritmos de Ordenação
// --------------------

// Bubble Sort (int crescente)
void bubble_int_asc(int *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int pass = 0; pass < n - 1; pass++) {
        int mudou = 0; 
        for (int i = 0; i < n - 1 - pass; i++) {
            m->comparacoes++;
            if (v[i] > v[i + 1]) {
                swap_int(&v[i], &v[i + 1], m);
                mudou = 1;
            }
        }
        if (!mudou) break;
    }
}

// Insertion Sort (int crescente)
void insertion_int_asc(int *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            m->comparacoes++;
            if (v[j] > chave) {
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

// Selection Sort (int crescente)
void selection_int_asc(int *v, int n, Metricas *m) {
    zera_metricas(m);
    for (int i = 0; i < n - 1; i++) {
        int idx_min = i;
        for (int j = i + 1; j < n; j++) {
            m->comparacoes++;
            if (v[j] < v[idx_min]) idx_min = j;
        }
        if (idx_min != i) swap_int(&v[i], &v[idx_min], m);
    }
}

int main(void) {
    int alturas_base[] = {160, 170, 163, 174, 181, 179, 190, 155, 200, 178, 161};
    int n_alturas = (int)(sizeof(alturas_base) / sizeof(alturas_base[0]));
    int a1[11], a2[11], a3[11];
    memcpy(a1, alturas_base, sizeof(alturas_base));
    memcpy(a2, alturas_base, sizeof(alturas_base));
    memcpy(a3, alturas_base, sizeof(alturas_base));

    imprime_int(alturas_base, n_alturas, "Alturas (original)");

    Metricas mb, mi, ms;
    bubble_int_asc(a1, n_alturas, &mb);
    imprime_int(a1, n_alturas, "Bubble (asc)");
    printf("Bubble -> comparacoes=%ld, trocas=%ld\n", mb.comparacoes, mb.trocas);

    insertion_int_asc(a2, n_alturas, &mi);
    imprime_int(a2, n_alturas, "Insertion (asc)");
    printf("Insertion -> comparacoes=%ld, movimentos=%ld\n", mi.comparacoes, mi.trocas);

    selection_int_asc(a3, n_alturas, &ms);
    imprime_int(a3, n_alturas, "Selection (asc)");
    printf("Selection -> comparacoes=%ld, trocas=%ld\n\n", ms.comparacoes, ms.trocas);

    return 0;
}
