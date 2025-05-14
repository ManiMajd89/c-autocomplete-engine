#include "autocomplete.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 

typedef struct term{
    char term[200]; // assume terms are not longer than 200
    double weight;
} term;

*/

int compare_terms_lex(const void *a, const void*b ){
        
    // Use strcmp to compare the term strings
    return strcmp( ((term*)a)->term, ((term*)b)->term);
}


void read_in_terms(struct term** terms, int* pnterms, char* filename){
    
    FILE *fp = fopen(filename , "r");

    fscanf(fp, "%d", pnterms);

    (*terms) = (term*) malloc((*pnterms) * sizeof(term));
    
    for (int i = 0 ; i < *pnterms ; i++){
        fscanf(fp, "%lf %[^\n]", &(*terms)[i].weight, (*terms)[i].term);
    }

    qsort( *terms, *pnterms, sizeof(term) , compare_terms_lex );

\
}


// terms are sorted in ascending order
int lowest_match(struct term *terms, int nterms, char *substr){
    int right = nterms -1;
    int left = 0;
    int len_substr = strlen(substr);

    while(left <= right){
        int mid = (right + left) / 2;

        if (strncmp( (terms[mid].term) , substr, len_substr ) >= 0){
            right = mid - 1;
        }

        else {
            left = mid + 1;
        }

    }
    return left;

}

int highest_match(struct term *terms, int nterms, char *substr){

    int right = nterms -1;
    int left = 0;
    int len_substr = strlen(substr);

    while(left <= right){
        int mid = (right + left) / 2;

        if (strncmp( (terms[mid].term) , substr, len_substr ) > 0){
            right = mid - 1;
        }

        else{
            left = mid +1;
        }

    }
    return right;

}

int compare_weight(const void *a, const void*b ){
        
    term* A = (term*)a;
    term* B = (term*)b;
    
    if (A->weight > B->weight){
        return -1;
    }
    else if (B->weight > A->weight){
        return 1;
    }
    else{
        return 0;
    }
}


void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){

    int low = lowest_match(terms, nterms, substr);
    int high = highest_match(terms, nterms, substr);
    *n_answer = high - low +1;

    *answer = (term*) malloc(*n_answer * sizeof(term));

    for (int i = 0 ; i<*n_answer; i++){
        strcpy((*answer)[i].term , terms[i+low].term);
        (*answer)[i].weight = terms[i+low].weight;

    }

    qsort(*answer, *n_answer, sizeof(term), compare_weight);

}

