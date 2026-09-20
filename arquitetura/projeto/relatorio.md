````md
# Relatório — RPyC + Mininet: Rede Distribuída Controlada

## 1. Objetivo

O objetivo deste experimento foi construir uma rede virtual distribuída utilizando o Mininet e o RPyC, permitindo executar agentes distribuídos nos hosts virtuais e controlar/consultar esses agentes remotamente.

A rede foi configurada com diferentes valores de:

- Latência;
- Largura de banda;
- Perda de pacotes.

O RPyC foi utilizado para estabelecer a comunicação entre um controlador e os agentes executados nos hosts virtuais.

---

## 2. Ambiente utilizado

O experimento foi realizado em uma VM SDNHub Mininet com:

- Ubuntu 14.04.3 LTS;
- Python 3.4.3;
- Mininet;
- RPyC 3.3.0;
- TCLink.

A versão do RPyC utilizada foi:

```text
(3, 3, 0)
````

O sistema não foi atualizado para uma versão mais recente do Ubuntu, mantendo o ambiente original da VM.

---

## 3. Arquitetura

A topologia utilizada possui três hosts e um switch:

```text
             +-------+
             |  s1   |
             +-------+
              /  |  \
             /   |   \
            /    |    \
           h1    h2    h3

        10.0.0.1  10.0.0.2  10.0.0.3
```

Cada host executa um agente RPyC na porta `18861`.

```text
h1 -> Agent RPyC -> :18861
h2 -> Agent RPyC -> :18861
h3 -> Agent RPyC -> :18861
```

Um controller executado no `h1` realiza conexões RPyC com os agentes.

---

## 4. Configuração da rede

A rede foi criada utilizando `TCLink`:

```python
net.addLink(h1, s1, bw=10, delay='20ms', loss=1)
net.addLink(h2, s1, bw=5, delay='50ms', loss=3)
net.addLink(h3, s1, bw=2, delay='100ms', loss=5)
```

A configuração pode ser resumida como:

| Host | Banda   | Latência | Perda |
| ---- | ------- | -------- | ----- |
| h1   | 10 Mbps | 20 ms    | 1%    |
| h2   | 5 Mbps  | 50 ms    | 3%    |
| h3   | 2 Mbps  | 100 ms   | 5%    |

Cada valor representa a condição configurada no enlace entre o host e o switch.

---

## 5. Instalação do RPyC

O RPyC foi instalado utilizando Python 3:

```bash
sudo apt-get install python3-pip
sudo pip3 install 'rpyc==3.3.0'
```

A instalação foi verificada com:

```bash
python3 -c "import rpyc; print(rpyc.__version__)"
```

Resultado:

```text
(3, 3, 0)
```

---

## 6. Agente RPyC

Cada host executa um agente RPyC.

O agente disponibiliza funções remotas como:

```python
exposed_status()
exposed_hostname()
exposed_ping(target)
```

A função `exposed_ping()` permite que outro processo solicite remotamente a execução de um `ping`.

O servidor utiliza a porta:

```text
18861
```

---

## 7. Execução dos agentes

Os agentes foram iniciados nos três hosts:

```text
mininet> h1 python3 agent.py &
mininet> h2 python3 agent.py &
mininet> h3 python3 agent.py &
```

Foi importante utilizar `python3`, pois o comando `python` da VM utiliza Python 2, no qual o RPyC instalado não estava disponível.

---

## 8. Validação dos agentes

A execução dos processos foi verificada com:

```text
mininet> h1 ps aux | grep agent.py
```

Os processos:

```text
python3 agent.py
```

foram encontrados.

A comunicação RPyC também foi validada através do controller.

---

## 9. Controller

O controller realiza uma conexão RPyC com o agente do host desejado.

Exemplo:

```python
conn = rpyc.connect("10.0.0.1", 18861)
```

Depois, funções disponibilizadas pelo agente podem ser chamadas remotamente:

```python
conn.root.status()
conn.root.hostname()
conn.root.ping("10.0.0.2")
```

---

## 10. Primeiro teste RPyC

Inicialmente foi realizado um teste de comunicação com os três agentes.

O controller apresentou:

```text
========================
Host: h1
IP: 10.0.0.1
Status: OK
Hostname: sdnhubvm

========================
Host: h2
IP: 10.0.0.2
Status: OK
Hostname: sdnhubvm

========================
Host: h3
IP: 10.0.0.3
Status: OK
Hostname: sdnhubvm
```

Isso confirmou que o controller conseguiu estabelecer conexões RPyC com os três hosts.

---

## 11. Teste de ping via RPyC

Foi realizado um teste em que o controller conectou-se ao agente do `h1` e solicitou remotamente:

```python
conn.root.ping("10.0.0.2")
```

Nesse caso, o fluxo foi:

```text
Controller
    |
    | RPyC
    v
Agent h1
    |
    | ICMP
    v
   h2
```

Portanto, o ping foi realmente executado a partir do namespace do `h1`.

---

## 12. Resultado experimental

O resultado obtido foi:

```text
10 packets transmitted, 8 received, 20% packet loss
```

Estatísticas de RTT:

```text
rtt min/avg/max/mdev =
141.166/182.961/291.685/50.599 ms
```

Os tempos individuais observados incluíram:

```text
200 ms
227 ms
145 ms
141 ms
291 ms
142 ms
166 ms
147 ms
```

Dois dos dez pacotes não receberam resposta.

---

## 13. Análise da latência

Para o caminho:

```text
h1 -> s1 -> h2
```

foram configurados:

```text
h1 -> s1 = 20 ms
h2 -> s1 = 50 ms
```

A soma do atraso em uma direção é aproximadamente:

```text
20 + 50 = 70 ms
```

Como o `ping` mede ida e volta, o RTT básico esperado é aproximadamente:

```text
70 * 2 = 140 ms
```

Os resultados apresentaram vários valores próximos desse valor:

```text
141 ms
142 ms
145 ms
147 ms
```

Portanto, o experimento demonstrou que a latência configurada nos enlaces do Mininet está influenciando o tráfego observado.

Também foram observados valores maiores, como:

```text
200 ms
227 ms
291 ms
```

Essas diferenças podem ocorrer devido ao comportamento do `netem`, filas, processamento da VM e outras características do ambiente virtualizado.

---

## 14. Análise da perda de pacotes

O resultado apresentou:

```text
20% packet loss
```

ou seja:

```text
10 pacotes enviados
8 pacotes recebidos
2 pacotes perdidos
```

Os enlaces utilizados possuem perdas configuradas de:

```text
h1 -> s1 = 1%
h2 -> s1 = 3%
```

A perda observada no caminho não deve ser interpretada simplesmente como:

```text
1% + 3% = 4%
```

Os mecanismos de perda atuam em enlaces diferentes e o experimento utilizou apenas 10 pacotes, uma amostra pequena para estimar uma taxa de perda com precisão.

---

## 15. Resultado geral

O experimento demonstrou com sucesso a integração entre:

```text
Mininet
   +
TCLink
   +
RPyC
   +
Agentes distribuídos
   +
Controller
```

Foi possível:

1. Criar uma rede virtual com três hosts;
2. Configurar largura de banda;
3. Configurar latência;
4. Configurar perda de pacotes;
5. Executar agentes RPyC nos hosts;
6. Conectar remotamente aos agentes;
7. Consultar informações dos agentes;
8. Executar comandos de rede remotamente;
9. Observar o efeito das condições configuradas no Mininet.

---

## 16. Limitações atuais

O experimento atual ainda possui algumas limitações.

A coleta de métricas é feita através da saída textual do comando `ping`.

Além disso, os testes ainda são executados individualmente.

Ainda não foi implementado:

* Coleta automática de todos os pares;
* Armazenamento dos resultados;
* Geração automática de gráficos;
* Alteração dinâmica de `delay`;
* Alteração dinâmica de `loss`;
* Alteração dinâmica de `bw`;
* Monitoramento contínuo;
* Banco de dados de métricas.

---

## 17. Próximas etapas

Como evolução do projeto, o controller pode realizar automaticamente:

```text
h1 -> h2
h1 -> h3
h2 -> h1
h2 -> h3
h3 -> h1
h3 -> h2
```

Para cada caminho podem ser coletados:

* RTT mínimo;
* RTT médio;
* RTT máximo;
* Desvio padrão;
* Percentual de perda.

Posteriormente, o controller pode ser expandido para modificar dinamicamente as condições da rede e observar como essas mudanças afetam o desempenho.

---

## 18. Conclusão

O experimento comprovou que é possível combinar Mininet e RPyC para criar uma rede virtual distribuída na qual agentes executados em diferentes hosts podem ser controlados remotamente.

As medições realizadas no caminho `h1 -> h2` apresentaram RTTs próximos do valor esperado a partir dos atrasos configurados nos enlaces e também demonstraram perda de pacotes.

Dessa forma, a infraestrutura criada fornece uma base para experimentos mais avançados de monitoramento e controle de redes distribuídas.

```
```
