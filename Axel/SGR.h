#ifndef GRUPO66_SGR_H
#define GRUPO66_SGR_H

#include "leitura.h"


/** ---------------- Estruturas ---------------**/

typedef struct sgr * SGR;
typedef struct valor *VALOR;


SGR init_SGR();
void free_sgr(SGR sgr);
int query1();
SGR load_sgr(char *users, char *businesses, char *reviews);
int query2();
TABLE businesses_started_by_letter(SGR sgr, char letter);
int query3();
TABLE business_info(SGR sgr, char *business_id);
int query4();
TABLE businesses_reviewed(SGR sgr, char *user_id);
int query5();
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);
int query7();
TABLE international_users(SGR sgr);
int query8();
TABLE top_businesses_with_category(SGR sgr, int top, char *category);
int query9();


/**
TABLE top_businesses_by_city(SGR sgr, int top);
TABLE top_businesses_with_category(SGR sgr, int top, char *category);
TABLE reviews_with_word(SGR sgr, int top, char *word);
int findPalavra(char* text, char * word);

*/

#endif //GRUPO66_SGR_H
