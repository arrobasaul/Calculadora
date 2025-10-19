# Calculadora
## Shunting-Yard
Implementación básica del algoritmo “Shunting-Yard” que produce notación polaca reversa (RPN).

## funcionalidad
Ingresar expresiones que pueden o no retornar valores o guardar en variables, para salir se ingresa una expresión vacía. Ejemplos:
```
6/2(1+2)
algo = pi *$?
_Algo2 = (10* 15)^ 2
_Algo2/ algo
```

Especificaciones
Implementa las operaciones esenciales para realizar cálculos matemáticos
* Suma
* Resta
* Multiplicación
* División
* Exponencial
* Residuo
## Buid
```
git clone https://github.com/arrobasaul/Calculadora.git
cd Calculadora
mkdir build
cmake -S . -B build
cd build
cmake --build .
```

## Variables internas
```
std::unordered_map<std::string, Token> Vars;
Token pi{};
pi.type = Token::Type::Number;
pi.precedence = -1;
pi.elementStr = "3.14159265358979323846";

Parser parser;
Vars["pi"] =  pi;
```
## Crear variables
```
algo = pi *10
```
Aqui se crea una variable, "algo" que puede ser usada en los cálculos.
```
25 *algo
```
La variable puede iniciar con “_” así como contener números.

```
_Algo2 = algo /2
```
La variable “_Algo2” es correcta.
## Utilizar la última salida
```
_Algo2 = 6 /2
$? + 10
```
El resultado de la ultima expresión es de 13, es decir que “$?” contiene el resultado de la última expresión.