
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool pertenece(nat elem, TCadena cad) {
    TLocalizador aux = inicioCadena(cad);
    while (aux != NULL && natInfo(infoCadena(aux, cad)) != elem) {
        aux = siguiente(aux, cad);
    }
    return natInfo(infoCadena(aux, cad)) == elem;
}

/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
nat longitud(TCadena cad) {
    nat contador = 0;
    TLocalizador aux = inicioCadena(cad);
    while (aux != NULL) {
        contador++;
        aux = siguiente(aux, cad);
    }
    return contador;
}

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool estaOrdenadaPorNaturales(TCadena cad) {
    bool ordenada = true;
    TLocalizador aux = inicioCadena(cad);
    while (siguiente(aux, cad) != NULL && ordenada) {
        ordenada =  natInfo(infoCadena(aux, cad)) < natInfo(infoCadena(siguiente(aux, cad), cad));
        aux = siguiente(aux, cad);
    }
    return ordenada;
}



