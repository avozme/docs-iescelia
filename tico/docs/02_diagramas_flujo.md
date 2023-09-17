---
layout: page
title: 2. Programación con diagramas de flujo
permalink: /diagramas-de-flujo/
nav_order: 2
has_children: true
parent: Tecnologías de la Información y la Comunicación 2º BACHILLERATO
---

# 2. Programación con diagramas de flujo
{: .no_toc }


- TOC
{:toc}

El diagrama de flujo es una de las herramientas más poderosas para describir algoritmos y, sin embargo, poco utilizado porque da algo más de trabajo y ocupa mucho espacio.

El diagrama de flujo permite **describir gráficamente un algoritmo**, de manera que podemos comprobar de un golpe de vista si hemos cubierto todos los caminos que ese algoritmo puede tomar.

Una vez descrito el diagrama de flujo, es muy fácil transformar el algoritmo a cualquier lenguaje de programación.

Los diagramas de flujo son herramientas descriptivas tan potentes que se utilizan con asiduidad en la vida diaria para entender mejor la lógica de un problema o su solución. Por ejemplo, en este diagrama de flujo se propone gráficamente un proceso de toma de decisiones para determinar si se realiza o no una intervención quirúrjica a un paciente en el contexto de la pandemia del COVID-19 (fuente: [Patient Safety in Surgery Journal](https://pssjournal.biomedcentral.com/articles/10.1186/s13037-020-00235-9)):

![Diagrama de flujo COVID-19](/docs/prog-y-3d/_site/assets/images/03-diagrama-de-flujo-covid-19.png)

## 2.1. Simbología de los diagramas de flujo

En los diagramas de flujo, cada **símbolo** representa una operación específica. Las operaciones se conectan entre ellas con **flechas**, que indican el orden de ejecución.

Los símbolos de los diagramas de flujo orientados a programación están estandarizados, aunque puedes encontrar pequeñas diferencias según qué fuente consultes. Nosotros vamos a usar los de PSeInt, igual que hicimos con el pseudocódigo, para luego no tener problemas cuando usemos esa herramienta para resolver nuestros ejercicios prácticos.

Los símbolos más importantes de un diagrama de flujo, junto con su equivalencia en pseudocódigo, son estos:

<table>
<tr>
  <td style='background-color: lightgrey' width='30%'><strong>Símbolo</strong></td>
  <td style='background-color: lightgrey'><strong>Equivalencia en pseudocódigo</strong></td>
  <td style='background-color: lightgrey'><strong>Significado</strong></td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-algoritmo.png'></td>
  <td><strong>Algoritmo</strong> nombre</td>
  <td>Marca el comienzo de un algoritmo y le adjudica un nombre</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-fin-algoritmo.png'></td>
  <td><strong>FinAlgoritmo</strong></td>
  <td>Marca el final del algoritmo</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-definir.png'></td>
  <td><strong>Definir</strong> variable <strong>Como</strong> tipo</td>
  <td>Declara una variable y le asigna un tipo.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-leer.png'></td>
  <td><strong>Leer</strong> variable</td>
  <td>Entrada de datos.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-escribir.png'></td>
  <td><strong>Escribir</strong> expresión</td>
  <td>Salida de datos.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-asignacion.png'></td>
  <td>variable <- expresion</td>
  <td>Asignación.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-condicion.png'></td>
  <td><strong>Si</strong> condición <strong>Entonces</strong>
	&nbsp;&nbsp;&nbsp;&nbsp;acciones-1<br>
	<strong>SiNo</strong><br>
	&nbsp;&nbsp;&nbsp;&nbsp;acciones-2<br>
	<strong>FinSi</strong></td>
  <td>Estructura condicional.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-condicion-multiple.png'></td>
  <td><strong>Segun</strong> expresion <strong>hacer</strong><br>
  &nbsp;&nbsp;&nbsp;&nbsp;valor-1: acciones-1;<br>
  &nbsp;&nbsp;&nbsp;&nbsp;valor-2: acciones-2;<br>
  &nbsp;&nbsp;&nbsp;&nbsp;...<br>
  &nbsp;&nbsp;&nbsp;&nbsp;valor-n: acciones-N;<br>
  &nbsp;&nbsp;&nbsp;&nbsp;<strong>De otro modo</strong>: acciones-por-defecto;<br>
  <strong>FinSegun</strong></td>
  <td> Condicional múltiple.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-mientras.png'></td>
  <td><strong>Mientras</strong> Condición<br>
   &nbsp;&nbsp;&nbsp;&nbsp;acciones<br>
  <strong>FinMientras</strong></td>
  <td>Bucle con condición al princio.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-repetir.png'></td>
  <td><strong>Repetir<br></strong>
   &nbsp;&nbsp;&nbsp;&nbsp;acciones<br>
  <strong>Hasta Que</strong> Condición</td>
  <td>Bucle con condición al final.</td>
</tr>
<tr>
  <td><img src='/docs/prog-y-3d/_site/assets/images/simbolos-diagrama-flujo/03-simbolo-para.png'></td>
  <td><strong>Para</strong> variable <strong><-</strong> valor_inicial <strong>Hasta</strong> valor_final <strong>Hacer</strong><br>
   &nbsp;&nbsp;&nbsp;&nbsp;acciones<br>
  <strong>FinPara</strong></td>
  <td>Bucle con iterador.</td>
</tr>
</table>

Recuerda que también existen símbolos para definir y utilizar **subalgoritmos**, destinados a dividir el algoritmo en trozos cuando resolvemos problemas complejos. Por ahora, nuestros problemas serán simples y no usaremos subalgoritmos. Cuando llegue el momento, explicaremos cómo se utilizan.

Para terminar, te muestro el algoritmo para contar números enteros entre dos números cualesquiera, A y B, escrito como un diagrama de flujo. No dejes de comparar esta solución con la que planteamos en pseudocódigo un poco más arriba. Ambas son exactamente iguales, pero están descritas con una herramienta diferente. Es como si hubiéramos escrito la misma frase en dos idiomas distintos.

![Diagrama de flujo contar-numeros](/docs/prog-y-3d/_site/assets/images/03-contar-numeros.png)
