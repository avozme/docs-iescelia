---
layout: page
title: Apéndice III. Vue js
permalink: /vue-js/
nav_order: 11
has_children: false
parent: Desarrollo Web en Entorno Servidor
---
# Apéndice 3. Vue.js
{: .no_toc }

- TOC
{:toc}


## A3.1. ¿Qué es Vue.js?

Vue.js es un **framework para Javascript** orientado al **diseño de interfaces de usuario** para aplicaciones web y a la **creación de aplicaciones OVA** (One View Application) o SPA (Single Page Application).

Es similar a otros frameworks como **Angular** o **React**, aunque más fácil de aprender (o, al menos, un poco más fácil). Al igual que estos dos, tiene licencia de software libre.

Para usar Vue.js en un proyecto se puede optar, al menos, por tres vías diferentes:

1. **Incluirlo como una librería Javascript más** (mejor desde un CDN). Por ejemplo:

   ```html
   <script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>
   ```

2. **Usarlo en combinación con un servidor Node**. Hay que instalar Node.js y npm en el lado del servidor. Esto permite desarrollar toda la aplicación web con Javascript, de modo que el código sea, al menos en teoría, más fácil de desarrollar y mantener, además de más eficiente.

3. **Usarlo en combinación con Laravel**. En este caso, como es lógico, hay que tener Laravel corriendo en el servidor. Laravel proporciona su propio servidor Node. De este modo, conseguimos combinar la facilidad para la construcción de interfaces de usuario que proporciona Vue con la potencia de PHP y Laravel.

## A3.2. Algunos ejemplos sencillos

Antes de explicar cuál es la estructura típica de una aplicación echa con Vue, vamos a ver algunos ejemplos sencillos de entender. Así quedará luego mucho más claro cómo se escriben este tipo de aplicaciones.

### Ejemplo 1: hola, mundo

Por supuesto, tenemos que empezar por *Hola mundo*. Observa detenidamente este código:

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        {% raw %}{{ message }}{% endraw %}
    </div>
    
    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0/dist/vue.global.prod.js"></script>
    <script>
        const app = Vue.createApp({
            data() {
                return {
                    message: '¡Hola mundo!'
                }
            }
        }).mount('#app')
    </script>

</body>

</html>
```

Observa cómo la página consta únicamente de un <div> con el id "app", y dentro solo aparece el contenido ```{{message}}```. Se parece a Blade, pero no lo es: se trata de un dato de Vue.js.

Más abajo, después de incluir Vue 3 a través de un CDN, creamos una instancia de un objeto Vue con el método estático ***createApp()***, al que le definimos un método ***data()*** que contiene los datos de Vue.js. 

En este ejemplo, el único dato es *message*. Al establecer el valor de *message* como "Hola mundo", automáticamente aparecerá el texto "Hola mundo" en el contenido ```{% raw %}{{message}}{% endraw %}``` de nuestro <div>.

Por último, mediante el método ***mount()*** enlazamos el objeto Vue con un elemento del árbol DOM de la página, en este caso el div *#app*.

Por supuesto, un objeto Vue podría tener muchos más datos además de *message* (tantos como necesitemos), cuya procedencia puede ser una base de datos del servidor, por ejemplo.

Con este sencillo ejemplo tal vez ya puedas vislumbrar la facilidad con la que pueden construirse vistas usando Vue para crear plantillas HTML y PHP para extraer datos del servidor. Pero, si aún no lo ves, no te preocupes que vamos a poner ejemplos un poco más complejos.

### Ejemplo 2: pregunta y respuesta

En el siguiente ejemplo, puedes ver un <div> parecido al anterior pero que usa dos variables, llamadas ```{{pregunta}}``` y  ```{{respuesta}}```, cuyos valores se asignan desde Vue. Si cambiamos dinámicamente los valores de "pregunta" y "respuesta", el código HTML también cambiará.

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        <p>La pregunta es: {% raw %}{{ pregunta }}{% endraw %}</p> 
        <p>La respuesta es: {% raw %}{{ respuesta }}{% endraw %}</p> 
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0/dist/vue.global.prod.js"></script>
    <script>
        const app = Vue.createApp({
            data() {
                return {
                    pregunta: "¿Cómo te llamas?",
                    respuesta: "Pepito Pérez"
                }
            }
        }).mount('#app')
    </script>
</body>

</html>
```

### Ejemplo 3: condicional simple

Con Vue también puede hacerse una salida HTML condicional, que dependa de los valores de las variables de Vue.

Aquí puedes ver un ejemplo sencillo. Si la variable *visible* vale *true*, se verá el texto "Ahora puedes verme". En el momento en el que cambie el valor de *visible* a *false*, el texto despaparecerá. Ten en cuenta que esto sucede dinámicamente, es decir, con la página ya cargada.

```html
<!DOCTYPE html>
<html lang="es">
<head>
    <title>Pruebas Vue.js</title>
</head>
<body>
    <div id="app">
        <p v-if="visible">Ahora puedes verme</p>
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0/dist/vue.global.prod.js"></script>
    <script>
        const app = Vue.createApp({
            data() {
                return {
                    visible: true
                }
            }
        }).mount('#app')
    </script>

</body>

</html>
```

### Ejemplo 4: bucle for

Igual que puede hacerse una salida HTML condicional, también puede generarse una salida HTML a partir de un array recorrido con un bucle de tipo for.

Observa el siguiente ejemplo, donde un array con nombres de animales genera la salida HTML a partir de su contenido:

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        <p v-for="animal in arrayAnimales"> {% raw %}{{ animal }}{% endraw %} </p>
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0/dist/vue.global.prod.js"></script>
    <script>
        const app = Vue.createApp({
            data() {
                return {
                    arrayAnimales: ['Perro', 'Gato', 'Oveja', 'Caballo']
                }
            }
        }).mount('#app')
    </script>
    
</body>

</html>
```

### Ejemplo 5: formularios

Con Vue.js se pueden asociar campos de formulario a variables de Vue, de modo que si cambia una, cambiará también la otra dinámicamente.

En el siguiente ejemplo hemos asociado un campo de un formulario ("nombre") con un atributo del objeto Vue llamado también "nombre".

Observa que, para hacer ese enlace efectivo, hay que definir una propiedad HTML llamada *v-model* con el mismo identificador que el dato de Vue.

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        <p>Nombre: <input type="text" v-model="nombre"></p>
        <p>Tu nombre es: {% raw %}{{ nombre }}{% endraw %}</p>
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0/dist/vue.global.prod.js"></script>
    <script>
        const app = Vue.createApp({
            data() {
                return {
                    nombre: 'Pepito'
                }
            }
        }).mount('#app');
    </script>
</body>

</html>
```

A partir de este momento, si cambiamos dinámicamente el valor de *data.nombre*, el campo del formulario también cambiará, así como el texto "Tu nombre es: ...". Y, al contrario, si escribimos algo en el campo del formulario, cambiará el valor de la variable *data.nombre* y, en consecuencia, el texto "Tu nombre es: ..."

### Ejemplo 6: evento click

Otra cosa que puede hacerse con Vue, como es lógico, es capturar los eventos y asociarlos a métodos.

Vue tiene abreviaturas para todos los eventos HTML, de modo que resulta fácil asocialos a método de nuestro objeto Vue.

Observa cómo en el siguiente ejemplo se asocia el evento "click" de un botón al método *saludar()* del objeto Vue:

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        <p>Nombre: <input type="text" v-model="nombre"></p>
        <p><button @click="saludar">Púlsame</button></p>
        <!-- Sintaxis alternativa para el evento:
            <button v-on:click="saludar">Púlsame</button>
        -->
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0/dist/vue.global.prod.js"></script>
    <script>
        const app = Vue.createApp({
            data() {
                return {
                    nombre: ''
                }
            },
            methods: {
                saludar() {
                    alert('Hola, ' + this.nombre);
                }
            }
        }).mount('#app')
    </script>    
</body>

</html>
```

### Ejemplo 7: evento key

Otro evento habitual que conviene capturar es el de pulsación de una tecla concreta sobre un elemento HTML. 

En el siguiente ejemplo, capturaremos la pulsación de la tecla *Enter* en el campo "nombre" del formulario. Al hacerlo, se ejecutará el método *saludar()*.

Fíjate en que el evento "pulsar la tecla *Enter*" se abrevia, en Vue, *@keyup.enter*, y mira lo fácil que resulta asociarlo a un método el objeto Vue:

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        <p>Nombre: <input type="text" @keyup.enter="saludar" v-model="nombre"></p>
        <p><button @click="saludar">Púlsame</button></p>
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0/dist/vue.global.prod.js"></script>
    <script>
        const app = Vue.createApp({
            data() {
                return {
                    nombre: ''
                }
            },
            methods: {
                saludar() {
                    alert('Hola, ' + this.nombre);
                }
            }
        }).mount('#app')
    </script>    
</body>

</html>
```

### Ejemplo 8: componente "Hola mundo"

Algo fundamental en los frameworks como Vue son los **componentes**.

Un **componente** es un trozo de código HTML asociado a un objeto Vue y, por tanto, con sus propios datos y métodos que pueden actuar sobre el HTML. 

Los componentes pueden reutilizarse cuantas veces sea necesario. Son como las piezas que componente una web.

Más adelante hablaremos más despacio de los componentes. Por ahora, te presento el ejemplo más sencillo posible. Se trata de un <div> con el típico texto "Hola mundo" en su interior. Observa cómo se registra el componente usando la expresión **Vue.createApp().component**. Durante ese registro se le asocia un nombre ('hola-mundo') y un código HTML (declarado previamente como ```const holaMundo```).

Ese componente puede usarse todas las veces que haga falta. En este ejemplo lo usamos tres veces, por lo que el texto "Hola mundo" aparecerá tres veces en la ventana del navegador.

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        <hola-mundo></hola-mundo>
        <hola-mundo></hola-mundo>
        <hola-mundo></hola-mundo>
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0"></script>
    <script>
        const holaMundo = {
            template: `<div>¡Hola, mundo!</div>`
        }
        const app = Vue.createApp({}).component('hola-mundo', holaMundo).mount('#app');
    </script>

</body>

</html>

```

### Ejemplo 9: componente "Lista de tareas"

Vamos a crear un componente un poco más complejo, que contenga datos y métodos.

Se trata de un componente llamado "mis-tareas", que servirá para añadir una lista de tareas a una persona.

El componente dispondrá de un dato, llamado *tareas*, que será un array de strings. También tendrá un método, que llamaremos *crearTarea()*, cuyo cometido será agregar al array de tareas una tarea nueva.

Esa tarea nueva la tomaremos de un *input* de texto de un formulario, cuyo evento *keyup.enter* asociaremos al método *crearTarea()*. También añadiremos un botón "Añadir tarea" con su evento *click* asociado al mismo método.

En este código puedes ver cómo se haría todo esto con Vue:

* Primero se declara el **template HTML** con y se asocia a una constante (```const misTareas```).
* Después se declaran los **datos** del objeto Vue: *tareas*, que es un array vacío al principio, y *nuevaTarea*, que quedará enlazada con el campo de texto del formulario.
* Por último se declara el **método** *crearTarea()*, que añade el contenido de *nuevaTarea* al array *tareas*.

Observa cómo, al final del código, se registra el componente "mis-tareas" de forma muy parecida a la que usamos con "hola-mundo".

```html
<!DOCTYPE html>
<html lang="es">

<head>
    <title>Pruebas Vue.js</title>
</head>

<body>
    <div id="app">
        <h1>Tareas del equipo de trabajo</h1>
        <h2>Pepito Pérez</h2>
        <mis-tareas></mis-tareas>
        <h2>Susana Sánchez</h2>
        <mis-tareas></mis-tareas>
    </div>

    <!-- Scripts -->
    <script src="https://cdn.jsdelivr.net/npm/vue@3.0.0"></script>
    <script>
        const misTareas = {
            template: `<div>
                            <ul>
                                <li v-for="tarea in tareas"> {% raw %}{{ tarea }}{% endraw %} </li>
                            </ul>
                            Nueva tarea: <input type="text" v-model="nuevaTarea" @keyup.enter="crearTarea">
                            <button @click="crearTarea">Añadir tarea</button>
                      </div>`,
            data() {
                return {
                    nuevaTarea: '',
                    tareas: []
                }
            },
            methods: {
                crearTarea() {
                    this.tareas.push(this.nuevaTarea);
                    this.nuevaTarea = '';
                }
            }                      
        }
        const app = Vue.createApp({}).component('mis-tareas', misTareas).mount('#app');
    </script>

</body>

</html>
```

El componente "mis-tareas" puede **reutilizarse** cuantas veces sean necesarias, y cada componente tendrá sus propios datos. Por ejemplo, podemos crear dos listas de tareas independientes, una para Juan Pérez y otra para Susana Sánchez, así:

```html
    <div id="app">
        <h1>Tareas del equipo de trabajo</h1>
        <h2>Juan Pérez</h2>
        <mis-tareas></mis-tareas>
        <h2>Susana Sánchez</h2>
        <mis-tareas></mis-tareas>
    </div>
```

## A3.3. Estructurando una aplicación hecha con Vue: los componentes

Ahora que hemos visto y comprendido algunos ejemplos, estamos en mejores condiciones para hablar de cuál es la estructura típica de una página hecha con Vue.js y cómo se crea una jerarquía de componentes.

Los **componentes** de Vue, como la lista de tareas de los últimos ejemplos, se usan típicamente para construir elementos del interfaz que sean como **piezas reutilizables**.

Es decir, cada componente es una pieza del interfaz que cumple que:

* Tiene sus propios datos y lógica interna
* Puede manipularse independientemente del resto de piezas.
* Puede contener otras piezas más pequeñas.

¿Qué significa todo esto? Sigue leyendo y lo comprenderás.

### A3.3.1. ¿Qué componentes debería tener mi aplicación?

Debes tener muy claro el **interfaz de usuario** de tu aplicación para poder descomponerlo en componentes. Esto es fundamental, así que saca papel y lápiz y diseña el interfaz con detalle.

Por ejemplo, imagina que estás diseñando una web sencillita (y bastante típica) con esta distribución de elementos:

![Diseño típico de una web](/docs/dwes/_site/assets/images/a3-vue-01.png)

Arriba tenemos un encabezado (*Header*), en el centro el área principal (*Main*) que contiene dos elementos (que llamaremos *Articles*), y a la derecha hay un panel lateral (lo llamaremos *Aside*) con tres elementos (*Items*).

Pues bien; para este diseño de interfaz tendríamos que crear estos componentes:

![Componentes típicos de una web](/docs/dwes/_site/assets/images/a3-vue-02.png)

Como ves, diseñar y relacionar los componentes Vue entre sí se parece bastante a diseñar y relacionar los elementos HTML de una web tradicional: 

* En HTML, hay un **componente raíz** que llamado ```<body>``` que contiene a todos los demás elementos HTML. Con Vue, puedes tener un componente "Root" o "App" que contenga a los demás.
* En HTML, puedes tener **dentro del componente raíz** ```<body>``` varias capas hechas con ```<div>```, tales como ```<div class='header'>``` para el encabezado, ```<div class='main'>``` para el contenido principal y ```<div class='aside'>``` para la barra lateral. En Vue, puedes tener tres componentes dentro de "Root" llamados "Header", "Main" y "Aside"
* En HTML, **algunos elementos pueden tener dentro otros elementos**. Es decir, algunos ```<div>``` pueden tener dentro otros ```<div>``` o cualquier otra cosa. Por ejemplo, el ```<div class='main'>``` puede tener dentro dos ```<div class='article'>```. En Vue ocurre lo mismo: el componente "Main" puede tener dentro dos componentes "Article". Y así sucesivamente.

En Vue, **cada componente se guarda en un archivo .vue** independiente con una estructura como esta:

```html
<template>
  <button @click="count++">Has hecho click {% raw %}{{ count }}{% endraw %} veces.</button>
</template>

<script>
export default {
  name: 'nombre del componente',
  data() {
    return {
      dato1: 'valor-1',
      dato2: 'valor-2',
      ...
      datoN: 'valor-n'
    }
  },
  methods: {
    metodo1() {
      // Código del método
    }
    metodo2() {
      // Código del método
    }
    ...
    metodoN() {
      // Código del método
    }
  }
}
</script>
```

Fíjate que **el *template* con el código HTML del componente se coloca entre los tags** ```<template>``` **y** ```</template>```, a diferencia de los ejemplos sencillitos del principio del tema, donde lo insertábamos como parte del objeto Vue. Eso solo se hace cuando el componente Vue no se escribe en un archivo independiente.

Ni que decir tiene que lo más habitual es que sí se escriba en un archivo independiente, es decir, con el formato que te acabo de mostrar.

### A3.3.2. Estructura típica de una aplicación Vue

Aunque, como acabamos de decir, una aplicación Vue se debe organizar en función del interfaz de usuario que hayas diseñado, generalmente constará de los siguientes elementos:

* **Un archivo HTML** que contiene la estructura básica de la página y un contenedor (```<div id="app">```) para la aplicación Vue. Este archivo, por supuesto, se puede generar en un servidor web como una aplicación PHP.

* **Un archivo JavaScript** que contiene la lógica de la aplicación Vue, incluyendo la configuración, los componentes y los métodos. Aunque en los ejemplos hemos incluido esto en el mismo archivo que el HTML, lo normal es sacarlo a un archivo JS.

* **Un archivo .vue** con la estructura base de la aplicación Vue, donde se importen y registros otros componentes. Este sería nuestro componente "Root" o "App".

* **Archivos .vue** independientes para cada uno de los componentes. Si tenemos muchos, podemos distribuirlos en directorios y subdirectorios.

* Además, tendremos los archivos .css con los estilos para la página, como en cualquier web, y, opcionalmente, pueden usarse archivos vue adicionales para manejar rutas, para el almacenamiento de datos y o para otras funcionalidades. Veremos el enrutador de Vue al final de este apéndice.

Por lo tanto, la estructura de archivos de una aplicación Vue puede ser más o menos así:

```
-index.html
-main.js
-App.vue
-components/
    -header.vue
    -example.vue
    -footer.vue
-assets/
    -css/
        -main.css
    -img/
```

* El archivo *index.html* contiene la estructura básica de la página y un contenedor para la aplicación Vue (```<div id="app">```).

* El archivo *main.js* contiene la configuración de la aplicación y las funciones Javascript. Aquí se importa el archivo *App.vue*, donde estarán registrados los componentes Vue.

* El archivo *App.vue* contiene la estructura base de la aplicación Vue. Aquí se importan los demás componentes, que se colocan en archivos individuales.

* En la carpeta *components* se tienen todos los componentes de Vue que se usan en la aplicación (un componente por archivo, todo con extensión .vue).

* En la carpeta *assets*, como es habitual, están todos los demás recursos necesarios para la aplicación, como css adicional, imágenes, audios, etc.

### A3.3.3. Componente principal: el archivo App.vue

El archivo ***App.vue*** o ***Root.vue*** del ejemplo anterior (ten en cuenta que, por convenio, suele usarse más el nombre *App.vue*) debería ser el componente que contenga la **estructura base** de la aplicación Vue en forma de **plantilla**, además de importar todos los componentes Vue que estarán almacenados en archivos independientes.

Es decir, es el "Root" de nuestra aplicación.

Podría ser algo como esto:

```html
<template>
  <div id="app">
    <header-component />
    <example-component /> 
    <footer-component />
  </div>
</template>

<script>
import HeaderComponent from './components/header.vue'
import ExampleComponent from './components/example.vue'
import FooterComponent from './components/footer.vue'

export default {
  name: 'app',
  components: {
    'header-component': HeaderComponent,
    'example-component': ExampleComponent,
    'footer-component': FooterComponent
  }
}
</script>
```

Observa como, en el ***template* o plantilla**, se indica la estructura base de la aplicación, donde se usan los componentes ```<header-component>```, ```<example-component>``` y ```<footer-component>```. Por supuesto, podría haber más componentes, o alguno de estos podría usarse varias veces.

Inmediatamente después, en el script, se **importan** los archivos que contienen esos componentes (*header.vue*, *example.vue* y *footer.vue*). Después, los componentes se **registran** como parte de la aplicación Vue. Esto es necesario para poder usarlos.

En este archivo también podría incluirse el **CSS** u otros archivos de configuración necesarios para la aplicación. No lo hemos hecho en este ejemplo para simplificarlo.

### A3.3.4. Componentes de Vue

Por último, necesitaríamos escribir el código Vue de los **componentes**. 

Mostramos a modo de ejemplo cómo podría ser el código de ***example-component***, donde usaremos la estructura típica de un componente que vimos más arriba:

```html
<template>
  <div>
    <h1>{% raw %}{{ title }}{% endraw %}</h1>
    <p>{% raw %}{{ message }}{% endraw %}</p>
    <button @click="changeMessage">Cambiar mensaje</button>
  </div>
</template>

<script>
export default {
  name: 'example-component',
  data() {
    return {
      title: 'Example Component',
      message: '¡Hola, mundo! Soy example component'
    }
  },
  methods: {
    changeMessage() {
      this.message = 'El mensaje ha cambiado'
    }
  }
}
</script>
```

En el ***template*** se tiene una estructura HTML del componente, con su título, un párrafo y un botón, los cuales están ligados a las propiedades del componente *title* y *message* que aparecen más abajo. El botón se asocia al evento *click*, de manera que, cuando ocurra ese evento, se lanzará el método *changeMessage()*.

En el ***script*** se configura todo el componente: se le asigna un **nombre** (*example-component*), un objeto ***data*** con las propiedades *title* y *message* y un objeto ***methods*** con el método *changeMessage()*.

Este componente se usa en la plantilla de la aplicación (*App.vue*) pero también podría usarse como parte de otro componente más complejo.

Y, de este modo, montando componentes, se construyen los interfaces de usuario con Vue.

### A3.3.5. Manejo de eventos con Vue

En todos los ejemplos anteriores hemos utilizado eventos como *@click* o *@keyup* para enlazar métodos de Vue con eventos de usuario.

Vue dispone de muchos otros eventos que podemos usar en nuestros interfaces de usuario. En realidad, son **eventos nativos del navegador** manejados al "estilo Vue". Aunque esto no pretende ser una lista exhaustiva, te pongo aquí los más habituales:

* **click**: Se activa cuando se hace clic en un elemento.
* **input**: Se activa cuando el valor de un elemento de entrada (input, select, textarea) cambia.
* **submit**: Se activa cuando se envía un formulario.
* **keydown**: Se activa cuando se presiona una tecla en un elemento.
* **keyup**: Se activa cuando se suelta una tecla en un elemento.
* **mouseenter**: Se activa cuando el cursor entra en un elemento.
* **mouseleave**: Se activa cuando el cursor sale de un elemento.
* **focus**: Se activa cuando un elemento obtiene el foco.
* **blur**: Se activa cuando un elemento pierde el foco.

Todos ellos se pueden manejar con Vue utilizando la directiva ***v-on*** o el atajo ***@***:

```html
<!-- EVENTO CAPTURADO MEDIANTE LA DIRECTIVA v-on -->
<template>
  <button v-on:click="myMethod">Click me</button>
</template>

<!-- EVENTO CAPTURADO MEDIANTE EL ATAJO @ -->
<template>
  <button @click="myMethod">Click me</button>
</template>
```

## A3.4. ¿Y si quiero que el componente Vue tome sus datos del servidor?

La verdadera potencia de Vue.js para crear aplicaciones web de una sola vista comienza a verse si logramos **alimentar los componentes con datos procedentes del servidor**. Entonces estaremos cerca de lograr una OVA con una sola vista que pueda ir actualizándose de forma dinámica según los datos que se reciban de un servidor web.

La situación habitual en este caso es tener ya una vista cargada (creada con componentes de Vue) que tenemos que actualizar con datos procedentes del servidor. Por lo tanto, **todas las peticiones al servidor deben ser asíncronas**.

Como vimos en el [tema 7](/docs/dwes/_site/ajax/), para hacer peticiones asíncronas puedes utilizar **Ajax** de dos maneras diferentes:

1. En su forma tradicional, es decir, con el objeto ***XMLHttpResponse***.
2. O bien mediante alguna libería moderna como ***fetch*** o ***axios***.

Como siempre, vamos a ver cómo se actualiza un componente Vue con datos del servidor mediante un ejemplo sencillo que puedas usar como base para tus propios desarrollos. Después veremos un ejemplo un poco más completo: un CRUD hecho con Vue.

### A3.4.1. Un ejemplo sencillo

En el siguiente ejemplo, tendremos un *input* de tipo *text* para teclear un DNI. Cuando se introduzca algo en ese *input*, se cargará el nombre y apellidos de la persona desde el servidor, es decir, mediante una consulta a una base de datos remota, y se mostrarán en la pantalla.

```html
<template>
  <div>
    <input type="text" v-model="dni" @input="getNameAndLastname" placeholder="Ingresa el DNI">
    <p>Nombre: {% raw %}{{ name }}{% endraw %}</p>
    <p>Apellido: {% raw %}{{ lastname }}{% endraw %}</p>
  </div>
</template>

<script>
export default {
  data() {
    return {
      dni: '',
      name: '',
      lastname: ''
    }
  },
  methods: {
    async getNameAndLastname() {
      try {
        const response = await fetch(`http://mi-servidor.com/person/${this.dni}`);
        const data = await response.json();
        this.name = data.name;
        this.lastname = data.lastname;
      } catch (error) {
        console.error(error);
      }
    }
  }
}
</script>
```

Si observas el código con detenimiento, verás que el método *getNameAndLastName()* se ejecuta al introducir cualquier cosa en el campo de texto. La abreviatura para ese evento en Vue es ***@input***, aunque un evento tradicional de Javascript también funcionaría.

El método *getNameAndLastName()* está declarado como ***async***, lo que significa que contiene una operación asíncrona en su interior. Un método declarado así permite utilizar el controlador *await* para esperar a que una promesa se resuelva antes de continuar la ejecución del código.

La función *fetch()* devuelve una promesa que se resuelve cuando el servidor responde. Al usar *await*, se espera a que la promesa se resuelva antes de continuar la ejecución del código, lo que nos permite escribir el código de la función **como si fuera síncrono**. Esto hace que el código sea más fácil de entender y mantener. 

Si no utilizásemos la palabra *async* delante del nombre del método, el *await* se ejecutaría de forma asíncrona y tendríamos que trabajar con *callbacks* o encadenando promesas para acceder a los datos, como hicimos en los [ejemplos con *fetch* del tema 7](http://localhost:4000/docs/dwes/_site/ajax/#75-ajax-y-la-api-fetch).

Una vez que se recibe la respuesta del servidor (un JSON con el nombre y el apellido de la persona a la que corresponde ese DNI), se coloca en los dos elementos <p> reservados para ello dentro de la plantilla.

### A3.4.2. Un ejemplo completo: CRUD con Vue y un servidor RESTful

Vamos a mostrar ahora un ejemplo más completo. Supongamos ahora que tenemos una base de datos con una tabla llamada *Libros* cuyos campos son *id, título, autor* y *editorial*. Supongamos también que tenemos un **servidor REST** programado con PHP (o con lo que sea, porque en realidad no importa) que trabaja con esa tabla.

No es un ejemplo realista, desde luego (la tabla está horrorosamente diseñada), pero sí que nos servirá para ilustrar cómo puede interactuar Vue con un servidor RESTful.

En el siguiente código, vamos a usar ***axios*** en lugar de *fetch*. Se trata de otra librería Javascript para hacer peticiones asíncronas al servidor. Es muy similar a *fetch* o al método *ajax* de jQuery. Como se utiliza mucho, te la muestro en este ejemplo para que veas qué aspecto tiene. Compárala con el ejemplo anterior, en el que utilizamos *fetch*, y verás que hay muy pocas diferencias prácticas.

```html
<template>
  <div>
    <table>
      <tr>
        <th>ID</th>
        <th>Título</th>
        <th>Autor</th>
        <th>Editorial</th>
      </tr>
      <tr v-for="libro in libros" :key="libro.idLibro">
        <td>{% raw %}{{ libro.idLibro }}{% endraw %}</td>
        <td>{% raw %}{{ libro.titulo }}{% endraw %}</td>
        <td>{% raw %}{{ libro.autor }}{% endraw %}</td>
        <td>{% raw %}{{ libro.editorial }}{% endraw %}</td>
      </tr>
    </table>
  </div>
</template>

<script>
export default {
  data() {
    return {
      libros: []
    }
  },
  created() {
    this.cargarLibros();
  },
  methods: {
    async cargarLibros() {
      try {
        const response = await axios.get('https://tu-api-rest.com/libros');
        this.libros = response.data;
      } catch (error) {
        console.error(error);
      }
    }
  }
}
</script>
```

En el código anterior puedes ver cómo, usando *axios*, se puede hacer dinámicamente la carga de libros y asignarla al array *libros*, que a su vez está asociado al template HTML. El método *cargarLibros()*, como en el ejemplo anterior, se ha declarado como *async* para poder escribir el código linealmente, como si fuera síncrono, lo cual facilita mucho la labor de desarrollo.

Añadamos ahora las **funcionalidades típicas de un CRUD**, como "Editar", "Borrar", etc. De ese modo, conseguiremos un CRUD completo que trabaje con este servidor REST.

En el siguiente ejemplo puedes ver cómo construir ese CRUD con Vue. Observa bien cómo se etiquetan los campos de la tabla y de los formularios para enlazarlos con los datos de Vue, y qué fácil y limpio queda el código de los métodos usando *async* y una librería como *axios*:

```html
<template>
  <div>
    <table>
      <thead>
        <tr>
          <th>ID</th>
          <th>Título</th>
          <th>Autor</th>
          <th>Editorial</th>
          <th>Acciones</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="book in books">
          <td>{% raw %}{{ book.id }}{% endraw %}</td>
          <td>{% raw %}{{ book.title }}{% endraw %}</td>
          <td>{% raw %}{{ book.author }}{% endraw %}</td>
          <td>{% raw %}{{ book.editorial }}{% endraw %}</td>
          <td>
            <button @click="editBook(book)">Editar</button>
            <button @click="deleteBook(book.id)">Borrar</button>
          </td>
        </tr>
      </tbody>
    </table>
    <hr>
    <h3>Crear un nuevo libro</h3>
    <form @submit.prevent="createBook">
      <label>Título:</label>
      <input type="text" v-model="newBook.title">
      <label>Autor:</label>
      <input type="text" v-model="newBook.author">
      <label>Editorial:</label>
      <input type="text" v-model="newBook.editorial">
      <button type="submit">Crear</button>
    </form>
    <hr>
    <h3>Actualizar un libro existente</h3>
    <form @submit.prevent="updateBook">
      <input type="hidden" v-model="currentBook.id">
      <label>Título:</label>
      <input type="text" v-model="currentBook.title">
      <label>Autor:</label>
      <input type="text" v-model="currentBook.author">
      <label>Editorial:</label>
      <input type="text" v-model="currentBook.editorial">
      <button type="submit">Actualizar</button>
    </form>
  </div>
</template>

<script>
import axios from 'axios';

export default {
  data() {
    return {
      books: [],
      newBook: {
        id: null,
        title: '',
        author: '',
        editorial: ''
      },
      currentBook: {
        id: null,
        title: '',
        author: '',
        editorial: ''
      },
      bookIdToDelete: null
    }
  },
  created() {
    this.getBooks();
  },
  methods: {
    async getBooks() {
      try {
        const response = await axios.get('http://mi-servidor.com/books');
        this.books = response.data;
      } catch (error) {
        console.error(error);
      }
    },
    async createBook() {
      try {
        const response = await axios.post('http://mi-servidor.com/books', this.newBook);
        this.books.push(response.data);
        this.newBook = { id: null, title: '', author: '', editorial: '' };
      } catch (error) {
        console.error(error);
      }
    },
    async updateBook() {
      try {
        const response = await axios.put(`http://mi-servidor.com/books/${this.currentBook.id}`, this.currentBook);
        this.getBooks();
        this.currentBook = { id: null, title: '', author: '', editorial: '' };
      } catch (error) {
        console.error(error);
      }
    },
    async deleteBook(bookId) {
      try {
        await axios.delete(`http://mi-servidor.com/books/${bookId}`);
        this.getBooks();
      } catch (error) {
        console.error(error);
      }
    },
    editBook(book) {
      this.currentBook = Object.assign({}, book);
    }
  }
}
</script>
```

### A3.4.3. Otro ejemplo completo: un componente capaz de mostrar cualquier tabla

Otro caso típico en el que los frameworks como Vue, React o Angular demuestran lo mucho que nos pueden facilitar la vida, es en el diseño de un *template* HTML capaz de mostrar los datos de **cualquier tabla** que un servidor REST esté dispuesto a servirnos.

¿Te lo imaginas? Se acabó hacer una vista para cada una de las tablas que tu aplicación tenga que manejar. Ahora puedes hacer una plantilla que funcione con *cualquier* tabla y marcharte a tomar un café.

Te muestro un ejemplo muy sencillo. El nombre de la tabla se escribe en un campo de texto, pero bien podría seleccionarse por medio de un menú o de cualquier otra forma.

El ejemplo solo muestra el contenido de la tabla y no permite modificar, borrar ni añadir datos, pero no sería muy complicado agregarle estas funciones. Piénsalo y verás (es un excelente ejercicio). 

Ah, se supone que el servidor devuelve los datos en forma de JSON.

```html
<template>
  <div>
    <label>Nombre de la tabla:</label>
    <input v-model="tableName" type="text" />
    <button @click="fetchTableData">Consultar</button>
    <table v-if="tableData.length">
      <thead>
        <tr>
          <th v-for="key in Object.keys(tableData[0])" :key="key">{% raw %}{{ key }}{% endraw %}</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="row in tableData" :key="row.id">
          <td v-for="key in Object.keys(row)">{% raw %}{{ row[key] }}{% endraw %}</td>
        </tr>
      </tbody>
    </table>
    <div v-else>No hay datos para mostrar</div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      tableName: "",
      tableData: []
    };
  },
  methods: {
    fetchTableData() {
      let url = `http://mi-servidor.com/${this.tableName}`;
      fetch(url)
        .then(res => res.json())
        .then(data => {
          this.tableData = data;
        })
        .catch(error => {
          console.error(error);
        });
    }
  }
};
</script>
```

## A3.5. Vue.js con Laravel

Laravel dispone de un servidor Node integrado (llamado **Laravel Echo**) para poder, entre otras cosas, usar *web sockets*, unos componentes que permiten recibir y emitir eventos entre el cliente y el servidor en tiempo real.

En realidad, no nos importa demasiado por qué Laravel tiene un servidor Node integrado. El caso es que lo tiene. Y, si lo tiene, eso significa que podemos tener Vue, React, Angular o cualquier otra librería Javascript también integrada con Laravel.

Así que, sí, **se puede instalar Vue en nuestra aplicación Laravel a través de *artisan***.

También podemos usar Vue en una aplicación Laravel sin necesidad de instalarlo en el servidor, desde luego, pero si lo haces al "estilo Laravel" obtendrás ciertas **ventajas adicionales**, tales como: 

* Mayor control sobre la versión de Vue que estamos usando.
* Mejor rendimiento.
* Mayor flexibilidad de desarrollo (investiga qué es *vue-cli* para saber por qué).
* Mayor seguridad (al no depender de elementos externos).
* Mayores posibilidades de personalización.

### A3.5.1. Instalar Vue en Laravel

El modo más sencillo de tener Vue en Laravel es instalar ***laravel/ui*** (aunque existen otras maneras). Este paquete sirve para hacer autenticación de usuarios (como Breeze o Jetstream).

```
$ composer require laravel/ui
```

A continuación lanzamos *artisan*, instalamos las dependencias de Node y recompilamos todo:

```
$ php artisan ui vue
$ npm install
$ npm run dev
```

Una vez hecho esto, el archivo *public/js/app.js* contendrá los contenedores de Vue. Por lo tanto, debes incluirlo en tus vistas:

```html
<script src="{% raw %}{{ mix('/js/app.js') }}{% endraw %}"></script>
```

Ya puedes usar Vue en esa vista (asegúrate de utilizar el id “app”):

```html
<div id="app">
   <example-component></example-component>
</div>
```

El componente "example-component" viene creado por defecto pero, por supuesto, puedes crear tus propios componentes. Vamos a ver cómo.

### A3.5.2. Crear componentes Vue con Laravel

Para **crear un componente**, solo tienes que crear un archivo .vue en el directorio *resources/js/components*. Allí ya encontrarás un archivo llamado *example-component.vue*. Puedes usarlo como plantilla para crear componentes adicionales.

Después de crearlo, debes **registrar el componente** en *resources/js/app.js*. Nuevamente, encontrarás que ya está registrado el componente "example-component", así que puedes usar ese registro como plantilla para los tuyos.

Una vez creados y registrados, los componentes estarán disponibles para usarlos en cualquier vista.

### A3.5.3. Un ejemplo completo: CRUD con Laravel y Vue

En este ejemplo vamos a seguir todos los pasos necesarios para crear un CRUD sencillo con Laravel y Vue. Lo vamos a hacer con el Vue integrado en Laravel, pero ten en cuenta que también funcionaría si cargamos la versión de Vue que queramos desde un CDN o desde nuestros propios archivos Javascript.

Los pasos que vamos a describir para crear el CRUD son:

1. Crear proyecto Laravel
2. Configurar conexión con base de datos
3. Crear modelos y lanzar las migraciones
4. Crear al menos un controlador
5. Añadir las rutas
6. Instalar Laravel Vue UI
7. Iniciar Vue en Laravel
8. Construir los componentes Vue
9. Enrutamiento con Vue

#### PASO 1. Crear proyecto Laravel

```
$ composer create-project laravel/laravel laravel-vue-crud --prefer-dist
```

#### PASO 2. Configurar conexión con BD

Editamos el archivo .env:

```
DB_CONNECTION=mysql
DB_HOST=127.0.0.1
DB_PORT=3306
DB_DATABASE=???
DB_USERNAME=???
DB_PASSWORD=???
```

#### PASO 3. Crear modelos / Lanzar migraciones

Por ejemplo, vamos a centrarnos en una tabla llamada *products*:

```
$ php artisan make:model Product -m
$ php artisan migrate
```

(lógicamente, hay que escribir la migración antes de lanzarla)

#### PASO 4. Crear controlador

Seguimos trabajando con la tabla *products*, ahora creando su controlador:

```
$ php artisan make:controller ProductController
```

Los métodos del controlador devolverán solo datos, no vistas, puesto que van a trabajar con Vue en el lado del cliente. 

Por ejemplo, podrían ser algo así:

```php
    public function index()
    {
        $products = Product::all()->toArray();
        return response()->json($products);      
    }
    public function store(Request $request)
    {
        $product = new Product([
            'name' => $request->input('name'),
            'detail' => $request->input('detail')
        ]);
        $product->save();
        return response()->json('Product created!');
    }

    public function show($id)
    {
        $product = Product::find($id);
        return response()->json($product);
    }

    public function update($id, Request $request)
    {
        $product = Product::find($id);
        $product->update($request->all());
        return response()->json('Product updated!');
    }

    public function destroy($id)
    {
        $product = Product::find($id);
        $product->delete();
        return response()->json('Product deleted!');
    }
```

Observa que no hemos escrito los método *create()* ni *edit()*, puesto que no tienen sentido en una API REST controlada desde el cliente: esos formularios de creación y edición los construirá el cliente, no el servidor.

#### PASO 5. Añadir rutas

Editamos nuestro archivo *routes/web.php*. Podría quedar como esto:

```php
Route::post('/producto',
       [App\Http\Controllers\ProductController::class, 'store']);
Route::get('/producto/{product_id}',
       [App\Http\Controllers\ProductController::class, 'show']);
Route::delete('/eliminar-producto/{product_id}',
       [App\Http\Controllers\ProductController::class, 'delete']);
Route::get('/todos-productos',
       [App\Http\Controllers\ProductController::class, 'all']));
Route::put('/actualizar-producto/{product_id}',
       [App\Http\Controllers\ProductController::class, 'update']);
```

#### PASO 6. Instalar Laravel Vue UI

***laravel/ui*** es un componente de Laravel que incluye varios paquetes orientados a la creación del interfaz de usuario, entre ellos Vue.

Si instalas *laravel/ui*, se creará la carpeta *resources/js/components* para colocar ahí los componentes de Vue.

```
$ composer require laravel/ui
$ php artisan ui vue
$ npm run dev
```

Además de *laravel/ui*, en muchos casos se instala también:

* **Vue-router**: un enrutador para Vue. Facilita la selección de los componentes que hay que cargar en cada ruta.
* **Vue-axios**: un cliente HTTP para lanzar peticiones asíncronas al servidor, es decir, peticiones por Ajax. Es parecido a *fetch* y hay quien lo prefiere usar en su lugar.

Para instalar estos dos componentes tendremos que recurrir a *npm*, el gestor de paquetes de Node, puesto que trabajan en el lado del cliente:

```
$ npm install vue-router vue-axios
```

#### PASO 7. Iniciar Vue en Laravel

Tenemos que crear un layout para nuestra aplicación en *resources/views/layout/app.blade.php*. 

Ese layout debe incluir el archivo ***js/app.js***, que es donde estará la librería Vue.

Un layout muy sencillito podría ser algo como esto:

```html
<head>
    <meta name="csrf-token" value="{% raw %}{{ csrf_token() }}{% endraw %}" />
    <title>Ejemplo de CRUD con Vue y Laravel</title>
    <link href="{% raw %}{{ mix('css/app.css') }}{% endraw %}" type="text/css" 
          rel="stylesheet" />
</head>
<body>
    <div id="app"></div>
    <script src="{% raw %}{{ mix('js/app.js') }}{% endraw %}" type="text/javascript">
    </script>
</body>
```

#### PASO 8. Construir componentes Vue

Este es el paso más largo. 

Los componentes que necesitemos se crean en archivos individuales en el directorio *resources/js/components*. Por ejemplo, vamos a crear componentes como:

* *AllProduct.vue*: para mostrar todos los productos.
* *CreateProduct.vue*: formulario para creación de un nuevo producto.
* *EditProduct.vue*: formulario para edición de productos existentes.

Una vez creados, se pueden reutilizar en cualquier punto de la aplicación.

Cada componente de Vue en Laravel tiene esta estructura:

```html
<template>
    <!-- HTML del componente -->
</template>
<script>
    // Código del componente
</script>
<style>
    // Estilos del componente
</style>
```

Por ejemplo, el componente *CreateProduct.vue* podría ser así: 

```html
<template>
   <div class="panel panel-default" >
      <div class="panel-heading">Nuevo producto</div>
      <div class="panel-body">
         <form action="" v-on:submit.prevent="newProduct()">                
             <div class="form-group">
                 Referencia: <input type="text" class="form-control" name="reference" v-model="reference">
             </div>
             <div class="form-group">
                 Categoría: <input type="text" class="form-control" name="category" v-model="category">
             </div>
             <div class="form-group">
                 Precio: <input type="text" class="form-control" name="cost" v-model="cost">
             </div>
             <div class="form-group">
                 Cantidad: <input type="text" class="form-control" name="quantity" v-model="quantity">
             </div>
             <button type="submit" class="btn btn-primary">
                 Enviar Producto
             </button>
         </form>
      </div>
   </div>
</template>
<script>
    export default {
        data() {   // Datos que recogemos del componente
            return {
                reference: '',
                category: '',
                cost: '',
                quantity: ''
            }
        },
        methods: {
            newProduct() {
                const params = {
                    reference: this.reference,
                    category: this.category,
                    cost: this.cost,
                    quantity: this.quantity
                };
                this.reference = '';  //eliminamos los valores para que los campos del formulario se vacien
                this.category = '';
                this.cost = '';
                this.quantity = '';
                axios.post('/producto', params)
                    .then((response) => {
                        const product = response.data;
                        this.$emit('new', product);
                    });
            }
        }
    }
</script>
```

Observa que hemos asociado el método *newProduct()* con el evento *v-on:submit.prevent*. Esto hace que el evento *submit* del formulario se redirija al método que nos interesa. La palabra *prevent* se refiere a que queremos prevenir (evitar) su comportamiento por defecto, es decir, evitar que el navegador envíe directamente el formulario al servidor.

Por lo tanto, al pulsar "submit", se pasará el control al método *newProduct()*, que será quien se encargue de enviar el formulario al servidor de forma asíncrona mediante *axios*.

#### PASO 9: enrutamiento con Vue

Vue dispone en Laravel de su propio enrutador en un paquete llamado ***vue-router***. Como dijimos antes, si lo instalas puedes enrutar también en el lado del cliente.

El enrutador de Vue con Laravel está ubicado en el archivo *resources/js/routes.js*.

El enrutamiento con Vue permite seleccionar los componentes cuyos datos se deben cargar en cada ruta. Esto facilita mucho el trabajo en las aplicaciones OVA (*one view application*).

El enrutador de Vue está escrito en Javascript, claro, no en PHP, y tiene un aspecto como este:

```javascript
export const routes = [
    {
        name: 'home',
        path: '/',
        component: AllProduct
    },
    {
        name: 'create',
        path: '/create',
        component: CreateProduct
    },
    {
        name: 'edit',
        path: '/edit/:id',
        component: EditProduct
    }
];
```

Observa cómo, para cada ruta, se indica un nombre (de uso interno para la aplicación), una URL y el componente (o componentes) que se cargarán en el *layout* en caso de solicitar esa ruta.

Cada componente, a su vez, se encargará de pedir los datos al servidor mediante alguna de las rutas definidas en el enrutador de Laravel (*web.php*), por lo que el uso del enrutador de Vue no implica que dejemos de usar el enrutamiento en el servidor.



