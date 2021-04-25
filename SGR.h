#ifndef GRUPO66_SGR_H
#define GRUPO66_SGR_H

#include "leitura.h"


/** ---------------- Estruturas ---------------**/

typedef struct sgr * SGR;


SGR init_SGR();
void free_sgr(SGR sgr);
int query1();
int query2();
int query3();
SGR load_sgr(char *users, char *businesses, char *reviews);
TABLE businesses_started_by_letter(SGR sgr, char letter);
/**
TABLE business_info(SGR sgr, char *business_id);
TABLE businesses_reviewed(SGR sgr, char *user_id);
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);
TABLE top_businesses_by_city(SGR sgr, int top);
TABLE international_users(SGR sgr);
TABLE top_businesses_with_category(SGR sgr, int top, char *category);
TABLE reviews_with_word(SGR sgr, int top, char *word);
int findPalavra(char* text, char * word);


*/

#endif //GRUPO66_SGR_H
