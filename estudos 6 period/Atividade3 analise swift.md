# Atividade 3 - Análise das Linguagens de Programação

**Universidade Católica de Pernambuco** **Escola de Tecnologia e Comunicação** **Curso de Ciência da Computação** **Disciplina de Paradigmas de Linguagem de Programação** **Prof. Ana Eliza Lopes Moura**

**Nome da linguagem:** Swift

**Componentes da dupla:** Lucas Mendes Nóbrega e Arthur Amaral de Souza

> Observação: conforme solicitado, apenas as questões de número ímpar (1, 3, 5, 7 e 9) foram respondidas.

---

## 1. Vinculação de tipos

Swift utiliza vinculação de tipos **estática**: o tipo de cada variável ou constante é determinado em tempo de compilação e permanece fixo durante toda a execução do programa, de modo que o compilador verifica a compatibilidade de tipos antes mesmo de o código rodar.

Toda variável ou constante precisa ser declarada, mas essa declaração pode ser **explícita** (com anotação de tipo, usando `:`) ou **implícita**, quando o compilador consegue inferir o tipo a partir do valor inicial atribuído. Se não houver um valor inicial no momento da declaração, a anotação de tipo torna-se obrigatória, já que o compilador não tem como inferir o tipo sem uma expressão inicializadora.

```swift
// Declaração implícita: o compilador infere o tipo a partir do valor inicial
var mensagem = "Olá, mundo" // inferido como String

// Declaração explícita: necessária quando não há valor inicial
var idade: Int
idade = 21

// Declaração explícita mesmo havendo valor inicial (opcional, mas permitida)
let pi: Double = 3.14159

var nome // A Falra de uma declaração vai dar erro
```

No primeiro caso, o tipo `String` é atribuído a `mensagem` por inferência, sem necessidade de anotação. Já `idade` precisa da anotação `: Int`, pois é declarada sem valor inicial. Em ambos os casos, uma vez fixado, o tipo não pode ser alterado — tentar atribuir um `Int` a uma variável do tipo `String`, por exemplo, gera um erro de compilação, evidenciando o caráter estático da linguagem.


# 2. Com relação à vinculação de armazenamento

 1) Sim Swift possui variáveis estaticas
```swift
 struct Pessoa {
    static var nome = "Arthur Amaral de Souza"
}

print(Pessoa.nome)

Pessoa.nome = "João da Silva"

print(Pessoa.nome)

// ================================================

var contadorGlobal = 0

func incrementar() {
    contadorGlobal += 1
}

```
 > Swift possui variáveis do tipo estática, porem só podem ser declaradas dentro de structs, class e enums. podendo ainda declarar varáveis globais.
 
 2) Possui variáveis Stack-dinâmica
```Swift
 func calcular() {
    let x = 10
    var y = 20
    
    print(x + y)
}

calcular()

// =======================================
// codigo 2
var x = 11

func oi(){
  var x = 10
  print(x)
}

oi()
// ======================================
// codigo 3
var x = 11

func oi(){
  print(x)
}

oi()
```
> as variáveis declaradas dentro de funções tem como seu escopo apenas a parte interna desta função, e portanto tendo seu tempo de vida finalizado ao final desta função. Inclusive, devido a isso, o código 2 tem saída 10 e o devido ao fato dele procurar pela variável x primeiro dentro do escopo da função e depois fora dele, por isso o código 3 tem saída 11

3) Sim swift também possui variáveis tipo heap-dinâmico
```Swift
class Pessoa {
    var nome: String
    
    init(nome: String) {
        self.nome = nome
    }
}

let pessoa1 = Pessoa(nome: "João")
let pessoa2 = pessoa1

pessoa2.nome = "Carlos"

print(pessoa1.nome)
```
> uma nova instância de `Pessoa` é criada dinamicamente. O objeto possui armazenamento próprio e a variável `pessoa` mantém uma referência para ele.
> neste caso a saída do código seria Carlos, e como da para ver é possível criar varias referencias para o mesmo objeto

4) já em relação ao tipo de alocação das heaps-dinâmicas, se são explícitos ou implícitos
```Swift
class Pessoa {
    var nome: Stringm
}

let pessoa = Pessoa()

// =========================================

let ponteiro = UnsafeMutablePointer<Int>.allocate(capacity: 1)

ponteiro.initialize(to: 42)

print(ponteiro.pointee) // 42

ponteiro.deinitialize(count: 1)
ponteiro.deallocate()
```
> geralmente em Swift é utilizado a maneira implícita, porém ele permite fazer de maneira explícita, por mais que menos utilizado

5) Em relação a desalocação do heap-danamico
```Swift
class Pessoa {
    var nome: String

    init(nome: String) {
        self.nome = nome
        print("\(nome) foi criada")
    }

    deinit {
        print("\(nome) foi desalocada")
    }
}

var pessoa: Pessoa? = Pessoa(nome: "João")

pessoa = nil

```
> O Swift utiliza o **ARC (Automatic Reference Counting)** que basicamente verifica enquanto uma heap-dinâmico esta sendo referenciado, e quando ele perde referencia ele é retirado da memoria
---
## 3. Atualização de variáveis compostas

A forma como a atualização ocorre em Swift depende de o tipo composto ser um **tipo valor** (_value type_) ou um **tipo referência** (_reference type_). _Structs_, _enums_ e tuplas são tipos valor: ao serem atribuídos a uma nova variável ou passados como argumento, uma cópia completa da estrutura é criada. Por isso, Swift **suporta atualização total** para esses tipos — atribuir um novo valor a uma variável do tipo struct/tupla substitui integralmente o conteúdo anterior, e modificar a cópia não afeta o original.

```swift
struct Ponto {
    var x: Int
    var y: Int
}

var p1 = Ponto(x: 0, y: 0)
var p2 = p1        // p2 recebe uma cópia completa de p1
p2 = Ponto(x: 5, y: 5) // atualização total: todo o conteúdo de p2 é substituído

print(p1.x) // 0, p1 não foi afetado
print(p2.x) // 5
```

Já as _classes_ são tipos referência: a variável armazena apenas uma referência ao objeto na heap, então atribuir uma classe a outra variável não copia os dados, apenas o endereço de referência — modificar uma propriedade através de qualquer uma das referências afeta a mesma instância compartilhada.

```swift
class Contador {
    var valor: Int = 0
}

let c1 = Contador()
let c2 = c1        // c2 referencia o mesmo objeto que c1
c2.valor = 10

print(c1.valor) // 10, pois c1 e c2 apontam para a mesma instância
```

---
# 4 Esta linguagem faz inferência de tipos?

Sim Swift faz inferência de tipos
```Swift
let idade = 20
let nome = "João"
let altura = 1.75
let estudante = true
```
Porém também permite uma declaração mais explicita
```Swift
let idade: Int = 20
let nome: String = "João"
let altura: Double = 1.75
let estudante: Bool = true

```
## 5. Constantes nomeadas

Swift possui constantes nomeadas, declaradas com a palavra-chave `let`. Uma vez atribuído um valor a uma constante, ele **não pode ser modificado** posteriormente; qualquer tentativa de reatribuição gera um erro de compilação. É permitido declarar a constante sem valor inicial e atribuí-lo depois (inicialização adiada), mas apenas uma única atribuição é aceita ao longo de todo o seu tempo de vida.

```swift
let velocidadeLuz = 299792458 // constante inicializada na declaração

// velocidadeLuz = 300000000 // erro de compilação: não é permitido reatribuir um 'let'

let gravidade: Double // constante sem valor inicial (inicialização adiada)
gravidade = 9.8       // atribuição única, permitida apenas uma vez
```

Assim como as variáveis, as constantes têm tipo estático e podem ter esse tipo inferido ou declarado explicitamente. A diferença está exclusivamente na mutabilidade: o uso de `let` é recomendado sempre que o valor não precisar variar durante a execução, tornando o código mais seguro e expressando a intenção de que aquele valor é fixo.

---
# 6 Qual tipo de estrutura de blocos utilizada

Swift utiliza estrutura de blocos explícita/delimitada, na qual os blocos começam com e terminam com { }, esta linguagem também permite blocos aninhados

```Swift
func verificarIdade() {
    let idade = 20

    if idade >= 18 {
        print("Maior de idade")

        if idade >= 60 {
            print("Idoso")
        }
    }
}

```
## 7. Acesso a variáveis não locais ocultas

Sim, Swift apresenta um mecanismo desse tipo através das **closures**, que podem capturar e acessar variáveis e constantes do escopo em que foram definidas mesmo depois que esse escopo deixou de existir. Essa captura acontece de forma implícita — o programador não precisa declarar explicitamente quais variáveis externas serão usadas dentro do corpo da closure — e é feita por referência para variáveis (`var`), de modo que alterações posteriores à variável capturada são refletidas dentro da closure.

```swift
func criarContador() -> () -> Int {
    var contador = 0
    func incrementar() -> Int {
        contador += 1   // acessa a variável não local 'contador' de forma oculta
        return contador
    }
    return incrementar
}

let proximo = criarContador()
print(proximo()) // 1
print(proximo()) // 2
```

Mesmo após `criarContador()` retornar e seu escopo local se encerrar, a função interna `incrementar` mantém acesso oculto à variável `contador`, que permanece viva na memória enquanto a closure existir. Esse mesmo mecanismo ocorre com o `self` dentro de métodos de uma classe: propriedades da instância podem ser acessadas implicitamente sem a necessidade de declará-las como parâmetros.

---
# 8 Escopo estático ou dinâmico?

Swift tem escopo estatico
```Swift
var x = 10

func A() {
    print(x)
}

func B() {
    var x = 20
    A()
}

B()

```
> neste código em questão a saída é 10, pois A foi definida no escopo onde existe x = 10 e portanto quando ela é utilizado depois ela usa essa informação. Porém colocando o caso do stack-dinâmico e levando os blocos de codigo em consideração

```Swift
var x = 10

func A() {
  var x = 30  
  print(x)
}

func B() {
    var x = 20
    A()
}

B()

```
> se o código fosse a assim a saída seria 30
## 9. Referências

- THE SWIFT PROGRAMMING LANGUAGE. **Declarations**. Disponível em: https://the-swift-programming-language.readthedocs.io/en/latest/md/Declarations/
- SWIFT.ORG. **Types — The Swift Programming Language**. Disponível em: https://docs.swift.org/swift-book/documentation/the-swift-programming-language/types/
- SWIFT.ORG. **Value and Reference Types**. Disponível em: https://www.swift.org/documentation/articles/value-and-reference-types.html
- EXERCISM. **Value and reference types (Swift Track)**. Disponível em: https://exercism.org/tracks/swift/concepts/value-and-reference-types
- LEYAA.AI. **Let for constants (immutable) in Swift**. Disponível em: https://leyaa.ai/codefly/learn/swift/part-1/swift-let-for-constants-immutable/deep
- SWIFT BY SUNDELL. **Swift's closure capturing mechanics**. Disponível em: https://www.swiftbysundell.com/articles/swifts-closure-capturing-mechanics/
- ABDUL AHAD. **Deep Dive into Functions and Closures**. Medium, 2024. Disponível em: https://abdulahd1996.medium.com/deep-dive-into-functions-and-closures-5577fdf6e6f8