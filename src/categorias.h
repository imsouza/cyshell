#ifndef EP2_CATEGORIAS_H
#define EP2_CATEGORIAS_H
       
#define MAX_OPERADORES 7

#define MAX_CATEGORIAS  14

typedef enum listaCategorias {
  /* 7 operadores aritmeticos */
  OPER_EXPONENCIACAO   /* "^",   0 */
  ,OPER_RESTO_DIVISAO  /* "%",   1 */
  ,OPER_MULTIPLICACAO  /* "*",   2 */
  ,OPER_DIVISAO        /* "/",   3 */
  ,OPER_ADICAO         /* "+",   4 */
  ,OPER_SUBTRACAO      /* "-",   5 */ 
  ,OPER_MENOS_UNARIO   /* "_",   6 */  

  /* parenteses para expressoes infixas */
  ,ABRE_PARENTESES     /* "(" ,  7 */
  ,FECHA_PARENTESES    /* ")" ,  8 */

  /* categorias dos valores numéricos no formato de string */
  ,FLOAT_STR          /*         9 */
  ,INT_STR            /*        10 */

  /* categorias dos valores numéricos */
  ,FLOAT              /*        11 */
  ,INT                /*        12 */

  /* categoria indefinida */
  ,INDEFINIDA         /*        13 */
} Categoria;

void imprimeNomeCategoria(int );

char *getNomeCategoria(int);

#endif /* _CATEGORIAS_H */