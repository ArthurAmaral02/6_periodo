# Atividade 4 - Análise das Linguagens de Programação

**Universidade Católica de Pernambuco**
**Escola de Tecnologia e Comunicação**
**Curso de Ciência da Computação**
**Disciplina de Paradigmas de Linguagem de Programação**
**Prof. Ana Eliza Lopes Moura**

**Nome da linguagem:** Swift

**Componentes da dupla:** Lucas Mendes Nóbrega e Arthur Amaral de Souza

> Observação: conforme solicitado, apenas as questões 1.1, 1.3 e 1.5 foram respondidas.

---

## 1. Sistema de tipos da linguagem

### 1.1 Checagem de tipos estática

Sim, Swift realiza checagem de tipos **estática**: o tipo de cada variável, constante, parâmetro e retorno de função é verificado pelo compilador antes da execução do programa. Se houver uma incompatibilidade — como tentar atribuir um valor de um tipo a uma variável de outro tipo — o código sequer chega a compilar, sendo o erro reportado já em tempo de compilação.

```swift
var idade: Int = 25
idade = "vinte e cinco" // erro de compilação: 'String' não pode ser convertido para 'Int'

func dobro(de numero: Int) -> Int {
    return numero * 2
}

dobro(de: 10)      // ok
dobro(de: "dez")   // erro de compilação: o argumento não é do tipo Int esperado
```

Nos dois exemplos, o compilador identifica a inconsistência de tipos antes mesmo de o programa rodar, o que caracteriza a checagem estática.
### 1.2 checagem de tipos
Swift possui uma checagem de tipos estática, sendo feita toda em tempo de compilação, porém tem algumas ferramentas que permitem criar variáveis sem um tipo especifico, como por exemplo o any e só durante o código converter ela para algum tipo. 
``` swift
let numero: Int = 10
let texto: String = "5"

let resultado = numero + texto // Erro de compilação

// segundo codigo
var idade = 20
var nome = "João"
var altura = 1.75

```
Como da para ver acima, esta linguagem também permite a atribuição de tipos implícita, assim como Python  
```swift
let a: Any = 10
let b: Any = 20

if let a = a as? Int, let b = b as? Int {
    let resultado = a + b
}

```
A questão do any e como ela funciona.
### 1.3 Fortemente ou fracamente tipada

Swift é considerada uma linguagem **fortemente tipada**. Isso significa que a linguagem não realiza conversões automáticas (implícitas) entre tipos diferentes, mesmo quando essa conversão pareceria "segura" em outras linguagens — cada operação exige que os operandos sejam exatamente do mesmo tipo, ou que a conversão seja feita manualmente pelo programador.

```swift
let inteiro = 10
let texto = "10"

// print(inteiro == texto) // erro de compilação: 'Int' e 'String' não podem ser comparados diretamente

let hoursWorked: Int = 10
let hourlyRate: Double = 19.5

// let total = hourlyRate * hoursWorked
// erro de compilação: o operador '*' não pode ser aplicado a operandos de tipos 'Double' e 'Int'

let total = hourlyRate * Double(hoursWorked) // correto: conversão explícita antes da operação
```

Diferentemente de linguagens fracamente tipadas — em que, por exemplo, um número poderia ser comparado ou combinado automaticamente com uma string — Swift exige que o próprio desenvolvedor resolva essa incompatibilidade de forma explícita, o que reduz erros causados por conversões implícitas indesejadas.
### 1.4 equivalência de tipos
Sim, esta linguagem faz equivalência de tipos, ela faz equivalência por nomes e por isso o trecho de código abaixo, mesmo as duas structs tendo a mesma estrutura não é possível atribuir uma dessas estrutura a uma stack dinâmica, da outra estrutura.

```swift
struct Pessoa {
    var nome: String
    var idade: Int
}

struct Usuario {
    var nome: String
    var idade: Int
}

let pessoa = Pessoa(nome: "João", idade: 20)
let usuario: Usuario = pessoa // ❌ 

```
Nesse código, a constante usuario é declarada explicitamente como sendo do tipo Usuario. Em seguida, tentamos atribuir a ela um valor do tipo Pessoa. Embora Pessoa e Usuario possuam exatamente a mesma estrutura, o Swift considera esses dois tipos diferentes, pois utiliza equivalência nominal. Dessa forma, o compilador verifica que um valor do tipo Pessoa não pode ser atribuído a uma variável do tipo Usuario e gera um erro em tempo de compilação. Como são struckts, elas são tipos por valor e não referências para objetos de uma classe.

Ponto interessante Swift vê os structs como sendo tipo por valor e portanto as constantes pessoa e usuario não são variáveis de referencia, além disso este codigo daria erro de compilação justamente devido a checagem de tipos estática.
### 1.5 Conversão de tipos

Swift realiza conversão de tipos, mas apenas de forma **explícita**; a linguagem praticamente não possui conversão implícita entre tipos diferentes (com exceção de literais, cujo tipo é inferido diretamente a partir do contexto, o que não é tecnicamente uma conversão, e sim uma construção do valor já no tipo esperado). Para converter um valor de um tipo para outro, é necessário utilizar o inicializador do tipo de destino, como em `Double(x)` ou `Int(y)`.

```swift
let inteiro: Int = 42
let comoDouble: Double = Double(inteiro) // conversão explícita de Int para Double

let decimal: Double = 9.8
let comoInteiro: Int = Int(decimal) // conversão explícita de Double para Int (trunca para 9)

let numeroTexto: String = "123"
let comoInt: Int? = Int(numeroTexto) // conversão explícita de String para Int (retorna um Optional)
```

Note que, no último exemplo, a conversão de `String` para `Int` retorna um valor opcional (`Int?`), já que nem todo texto pode ser convertido para um número válido; essa exigência de tratamento explícito reforça o caráter fortemente tipado da linguagem, evitando conversões silenciosas que poderiam mascarar erros.

---

## 2. Referências

- REINTECH. **How to use Swift's type checking and casting**. Disponível em: https://reintech.io/blog/understanding-swift-type-checking-casting
- SWIFT BY SUNDELL. **Type inference**. Disponível em: https://www.swiftbysundell.com/basics/type-inference/
- HESS, Ethan. **Static vs Dynamic and Weak vs Strong typing**. Medium, 2026. Disponível em: https://medium.com/@ech1988/static-vs-dynamic-and-weak-vs-strong-typing-9278457028ef
- DHIWISE. **Understanding Swift Type Inference in iOS Development**. Disponível em: https://www.dhiwise.com/post/understanding-swift-type-inference-in-ios-development
- RAYWENDERLICH. **Swift Tutorial Part 2: Types and Operations**. Disponível em: https://www.raywenderlich.com/?p=199360
- SWIFT FORUMS. **Generic, Numeric addition with Double**. Disponível em: https://forums.swift.org/t/generic-numeric-addition-with-double/23234
