
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de
  elementos de 'cad' son iguales.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool hayNatsRepetidos(TCadena cad) {
  bool repetidos = false;
  TLocalizador aux = inicioCadena(cad);
  while (aux != NULL && !repetidos) {
    TLocalizador target = siguiente(aux, cad);
    while (target != NULL && !repetidos) {
      repetidos = natInfo(infoCadena(aux, cad)) == natInfo(infoCadena(target, cad));
      target = siguiente(target, cad);
    }
    aux = siguiente(aux, cad);
  }
  return repetidos;
}
/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
bool sonIgualesCadena(TCadena c1, TCadena c2) {
  TLocalizador aux1 = inicioCadena(c1);
  TLocalizador aux2 = inicioCadena(c2);
  bool iguales = true;
  while ( aux1 != NULL && aux2 != NULL && iguales ) {
    iguales = sonIgualesInfo(infoCadena(aux1, c1), infoCadena(aux2, c2));
    aux1 = siguiente(aux1, c1);
    aux2 = siguiente(aux2, c2);
  }
  return iguales && aux1 == NULL && aux2 == NULL;
}
/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
TCadena concatenar(TCadena c1, TCadena c2) {
  TCadena c1copia = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
  TCadena c2copia = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
  return insertarSegmentoDespues(c2copia, finalCadena(c1copia), c1copia);
}

/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena ordenar(TCadena cad) {
  TLocalizador aux = inicioCadena(cad);
  while (aux) {
    TLocalizador menor = menorEnCadena(aux, cad);
    intercambiar(aux, menor, cad); // ver si es necesario igualar a CAD
    aux = siguiente(aux, cad);
  }

  return cad;
}

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
  TLocalizador aux = siguienteClave(original, inicioCadena(cad), cad);
  
  while(aux) {
    TInfo info = crearInfo(nuevo, realInfo(infoCadena(aux, cad)));
    cambiarEnCadena(info, aux, cad); // same above
    if(siguiente(aux, cad)) {
      aux = siguienteClave(original, siguiente(aux, cad), cad);
    } else {
      aux = NULL;
    }
  }

  return cad;
}

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena subCadena(nat menor, nat mayor, TCadena cad) {
  TLocalizador aux = inicioCadena(cad);
  TCadena nuevaCad = crearCadena();
  
  while(aux && menor <= natInfo(infoCadena(aux, cad)) && natInfo(infoCadena(aux, cad)) <= mayor) {
    TInfo info = copiaInfo(infoCadena(aux, cad));
    nuevaCad = insertarAlFinal(info, nuevaCad);
    aux = siguiente(aux, cad);
  }

  return nuevaCad;
}



