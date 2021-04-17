//
// Created by Silvia Acosta on 31/03/2021.
//

#include "querys.h"
#include "ctype.h. "


/*query 1. Dado o caminho para os 3 ficheiros (Users, Businesses, e Reviews), ler o seu conteúdo e carregar as
           estruturas de dados correspondentes.

           SGR load_sgr(char *users, char *businesses, char *reviews);





Query 2. Determinar a lista de nomes de negócios e o número total de negócios
         cujo nome inicia por uma dada letra. Note que a procura não deverá ser case sensitive.

         TABLE businesses_started_by_letter(SGR sgr, char letter);


Query 3. Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars,
         e número total reviews.

        TABLE business_info(SGR sgr, char *business_id);


Query 4. Dado um id de utilizador, determinar a lista de negócios aos quais fez review.
         A informação associada a cada negócio deve ser o id e o nome.

         TABLE businesses_reviewed(SGR sgr, char *user_id);

Query 5. Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais stars na dada cidade.
         A informação associada a cada negócio deve ser o seu id e nome.

         TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);

Query 6. Dado um número inteiro n, determinar a lista dos top n negócios
         (tendo em conta o número médio de stars) em cada cidade. A informação
         associada a cada negócio deve ser o seu id, nome, e número de estrelas.

         TABLE top_businesses_by_city(SGR sgr, int top);

Query 7. Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado
         mais de um estado, i.e. que tenham feito reviews em negócios de diferentes estados.

         TABLE international_users(SGR sgr);

Query 8. Dado um número inteiro n e uma categoria, determinar a lista dos top n negócios
         (tendo em conta o número médio de stars) que pertencem a uma determinada categoria.
         A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.

         TABLE top_businesses_with_category(SGR sgr, int top, char *category);


Query 9. Dada uma palavra, determinar a lista de ids de reviews que a referem no campo text.
         Note que deverá ter em conta os vários possíveis símbolos de pontuação para delimitar
         cada palavra que aparece no texto. Nota: função ispunct da biblioteca ctype.h.

         TABLE reviews_with_word(SGR sgr, int top, char *word);
