
![[Pasted image 20260922192220.png]]

>  Se a vinculação de tipos for dinâmica, a checagem de tipos que depende desse tipo não pode ser realizada estaticamente, pois o tipo só será conhecido em tempo de execução. Portanto, essa checagem deve ser dinâmica.
>  Por outro lado, se a vinculação de tipos for estática, a checagem pode ser estática, mas também pode haver verificações realizadas dinamicamente durante a execução. Assim, a vinculação estática permite checagem estática, mas não impede a existência de checagens dinâmicas.

![[Pasted image 20260922194207.png]]


Isso vira algo como:

```
Início do programa
        ↓
        ├── início int exp
        ├── início float base
        ↓
----------->Início main()
        ↓
        ↓
  base = 2
  exp = 3
        ↓
        ↓
----------> potencia(base, exp)
        ↓
        ├── início float b = base → 2
        ├── início int e = exp   → 3
        ├── início int i
        ├── início float pot = 1
        ↓
        ├── i = 3
        │   pot = 1 × 2 = 2
        │
        ├── i = 2
        │   pot = 2 × 2 = 4
        │
        ├── i = 1
        │   pot = 4 × 2 = 8
        ↓
        ├── fim b
        ├── fim e
        ├── fim i
        ├── fim pot
        ↓
----------> fim potencia()
        ↓
     printf("%f", 8)
        ↓
     return 0
        ↓
---------->fim main()
        ↓
     fim exp
     fim base
        ↓
   Fim do programa

```

![[Pasted image 20260922220156.png]]


```
----------->Início main()
        ↓
        ├── início int exp
        ├── início float base
        ↓
  base = 2
  exp = 3
        ↓
        ↓
----------> inicio 1° potencia(base, exp)
        ↓
        ├── início float b = base → 2
        ├── início int e = exp   → 3
        ↓
--------------------> inicio 2°, b * potencia(b, (e-1) = 3 -1 = 2)
	        ├── início float b = base → 2
		    ├── início int e = exp → 2      
------------------------> inicio 3°, b * potencia(b, (e -1) = 2 -1 = 1) 
		        ├── início float b = base → 2
		        ├── início int e = exp → 1
----------------------------> inicio 4°,b * potencia(b, (e -1) = 1 -1 = 0)
			        ├── início float b = base → 2
			        ├── início int e = exp → 0
			        ├── return 1  <-------------------------------- RETURN 1°
			        ├── fim int e
			        ├── fim float b
----------------------------> fim 4° potencia(base, exp)
		        ├── return  (b * 1) = 2 * 1 = 2 <----------------- RETURN 2°
			    ├── fim int e
			    ├── fim float b
------------------------> fim 3° potencia(base, exp) 
		    ├── return (b * 2) = 2 * 2 = 4 <--------------------RETURN 3°
		    ├── fim int e
		    ├── fim float b
--------------------> fim 2° potencia(base, exp)
        ├── return (b * 4) = 2 * 4 = 8 <-----------------------RETURN 4°
        ├── fim int e
        ├── fim float b
----------> fim potencia()
        ↓
     printf("%f", 8)
        ↓
     return 0
        ↓
        ↓
     fim exp
     fim base
        ↓
----------->fim main()
```

![[Pasted image 20260922222351.png]]
> Uma linguagem é tida como universal quando é possível representar com ela qualquer problema computacional, exemplos de linguagem universal são Python, Java, C que conseguem estar presentes em:
>- cálculos matemáticos;
>- manipulação de arquivos;
>- estruturas de dados;
>- inteligência artificial;
>- sistemas operacionais;
>- jogos;
>- aplicações web etc.

![[Pasted image 20260922222546.png]]
> Um dos pontos positivos de checagem em tempo de execução é que ela consegue checar situações invalidas durante a execução e assim garantido segurança e confiabilidade, porém, isto deixa o programa mais lento, pois é preciso a todo momento ter uma especie de deamon rodando de fundo procurando e fazendo essas checagens ao longo do programa.


![[Pasted image 20260922222821.png]]
> Nem todas linguagens implementam variáveis de tipo stack dinâmica com vinculação de tipos estática,
``` C
void teste(){
	int x
}

```
> como no exemplo acima, x é estack dinâmica pois seu espaço de memoria é criado quando a função é chamada e é liberado quando a função termina
```python
func teste():
	x = 10
	
	# code ......
	
	x = "art"

```
> neste exemplo em Python mesmo x é stack dinâmico, porem não tem sua vinculação de tipo sendo estática

![[Pasted image 20260922223935.png]]
> A vantagem é que ela não é desalocada ate que o código termine e portanto caso declarada em uma função pode ser usada por exemplo como contador desta função e contar todas as vezes que essa função é chamada, sem nunca ser desalocada e perdendo esses dados, ate o fim do programa.
> Desvantagem: Ocupa memoria durante toda a execução do programa, mesmo quando não esta sendo usada, pode tornar o comportamento de algumas função imprevisíveis como por exemplo funções recursivas.

![[Pasted image 20260922224329.png]]
> existem alguns casos a serem estudados
> caso 1: tem duas variáveis apontando por mesmo heap, uma é desalocada outra ainda aponta, todo OK
> caso 2: um unica variável está apontando, é desalocada, em linguagens como C perdemos esse endereço de memoria e vira lixo na memoria, ocupando espaço, "vazando memoria"
> caso 3: igual ao caso 2 porem em linguagem como java, ele tem um garbage colector que limpa a memoria caso tenha alguma heap sem ser endereçada em momento no código, porem isso pesa mais para a linguagem, já que ela precisa desse deamom rodando procurando pelas heaps que não tem mais endereçamento

![[Pasted image 20260923060411.png]]

```
Início do programa
        ↓
        ├── início int n 
        ↓
---------->Início main()
        ↓
        ↓
        ├── início int n = 5 <-------------------------------------------|
        ↓                                                                |
        ↓                                                                |
----------> inicio inc(d) // no codigo ele passa n = 5                   |
	        ↓                                                            |
	        ├── incio d = 5                                              |
	        ├── início int n // sem valor atribuido <-----------| <----| |
----------------------> inicio zero()                           |      | |
	        ├── n = 0                        <------------------|      | |
----------------------> fim zero()                                     | |
	        ├── (n = n + d) = n = 0 +5 = 5 <---------------------------| |
	        ├── fim n <------------------------------------------------| |
----------> fim inc(d)                                                   |
	        ↓                                                            |
	        ↓                                                            |
		├── print n = 5 // n da main n = 5 |
		├── return 0                                                     |
		├── fim n  <-----------------------------------------------------|
----------->fim main()
        ↓
     fim n
        ↓
   Fim do programa

```
> explicando alguns pontos melhor, o primeiro n, o n global não é utilizado pois ele sempre é sombreado pela definição de outros n's dentro das funções, e portanto se torna invisível para as funções 
> Além disso o print na main print 5 pois o n criado nela tem valor atribuido como sendo 5, e e mesmo a main chamando outras funções, zero e inc, essas funções nunca retornam nd usam apenas o n dentro delas, e no final delas esse n acaba pois se trata de um stack dinamico.

![[Pasted image 20260923063831.png]]
```
Início do programa
        ↓
        ↓
---------->Início main()
        ↓
        ├──
--------------------->Início p()
	        ├── inicio const int d = 1 <-----------------------|
--------------------------->Início add(i) // valor passado 20  |
				├── inicio i                                   |
				├── return (i + d) = 1 + 20 = 21 <-------------|
				├── fim i
--------------------------->fim add()
			├── print // 21
			├── fim d
--------------------->fim p()
        ↓
        ↓
        ↓
        ↓ // (code ...)
        ↓
        ↓
        ↓
--------------------->Início q()
	        ├── inicio const int d = w <-----------------------|
--------------------------->Início add(i) // valor passado 20  |
				├── inicio i                                   |
				├── return (i + d) = 2 + 20 = 22 <-------------|
				├── fim i
--------------------------->fim add()
			├── print // 22
			├── fim d
--------------------->fim q()
----------->fim main()
        ↓
   Fim do programa

```
> as saídas dos dois programas são bem parecida, sendo a unica diferença que em q ele starta d como 2 e em p d como 1, mas os dois usam a função add(20) passando 20 como parâmetro para i.
> A saídas são assim pois tanto o d de q quanto o d de p são declarado em bloco de códigos diferentes e portanto n se sobre escrevem nem se sombream, ja que ao final do bloco elas são desalocadas, já que não são declaradas como static

![[Pasted image 20260923092738.png]]

Variaveis heap 