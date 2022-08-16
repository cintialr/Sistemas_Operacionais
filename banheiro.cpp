

#define CABINE 6

/**
 * Declaracao das funcoes 
 */
void entraNoBanheiro(void * arg);
void pessoa();

    
/**
 * Declaracao das threads
 * uma pessoa so pode estar usando uma cabine ou 
 * esperando para usar o banheiro
 */
pthread_t Espera
pthread_t Adquire_cabine
pthread_t Usa_banheiro
pthread_t Libera_cabine

/**
 * Declaracao dos semaforos
 */
sem_t fluxo;