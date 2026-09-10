import time
import rpyc

HOST = "localhost"
PORT = 18861

def preencher_vetor():
    vetor = []

    tamanho = int(input("Digite o tamanho do vetor: "))

    for i in range(tamanho):
        numero = int(input(f"Digite o {i + 1}º número: "))
        vetor.append(numero)

    return vetor


def menu():
    print("\n=== CLIENTE RPC ===")
    print("1 - Somar dois números")
    print("2 - Converter texto para maiúsculas")
    print("3 - Adicionar item na lista remota")
    print("4 - Listar itens da lista remota")
    print("5 - Limpar lista remota")
    print("6 - Chamada lenta (RPC síncrono)")
    print("7 - ordenar vetor int")
    print("8 - criando anagrama")
    print("0 - Sair")

def conectado(conn):
    try:
        conn.root.get_service_name()
        return True

    except Exception:
        print("Servidor não está conectado.")
        return False

def main():
    try:
        conn = rpyc.connect(HOST, PORT)
        print(f"Conectado ao servidor {HOST}:{PORT}")
    except Exception as e:
        print("Não foi possível conectar ao servidor.")
        print(f"Erro: {e}")
        return

    while True:
        
        menu()
        opcao = input("Escolha uma opção: ").strip()

        try:
            if opcao == "1":
                if not conectado(conn):
                    continue
                a = int(input("Digite o primeiro número: "))
                b = int(input("Digite o segundo número: "))
                resultado = conn.root.somar(a, b)
                print(f"Resultado remoto: {resultado}")

            elif opcao == "2":
                if not conectado(conn):
                    continue
                texto = input("Digite um texto: ")
                resultado = conn.root.maiusculas(texto)
                print(f"Resultado remoto: {resultado}")

            elif opcao == "3":
                if not conectado(conn):
                    continue
                item = input("Digite o item a adicionar: ")
                resultado = conn.root.adicionar_item(item)
                print(f"Lista remota atual: {resultado}")

            elif opcao == "4":
                if not conectado(conn):
                    continue
                resultado = conn.root.listar_itens()
                print(f"Lista remota atual: {resultado}")

            elif opcao == "5":
                if not conectado(conn):
                    continue
                resultado = conn.root.limpar_itens()
                print(f"Lista remota após limpeza: {resultado}")

            elif opcao == "6":
                if not conectado(conn):
                    continue
                segundos = int(input("Quantos segundos o servidor deve demorar? "))
                inicio = time.time()
                resultado = conn.root.demorar(segundos)
                fim = time.time()

                print(resultado)
                print(f"Tempo total de espera no cliente: {fim - inicio:.2f} s")

            elif opcao == "7":
                if not conectado(conn):
                    continue
                vetor = preencher_vetor()
                print("Vetor original:", vetor)
                vetor_ordenado = conn.root.ordenar_int(vetor)
                print("Vetor ordenado:", vetor_ordenado)
            
            elif opcao == "8":
                if not conectado(conn):
                    continue
                palavra = input("Digite uma palavra: ")
                anagrama_p = conn.root.anagrama(palavra)
                print(f"O anagrama da palavra {palavra} é {anagrama_p}")
            elif opcao == "0":
                print("Encerrando cliente.")
                conn.close()
                continue
            

            else:
                print("Opção inválida.")

        except EOFError:
            print("\nConexão encerrada.")
            break
        except Exception as e:
            print(f"Erro durante a chamada remota: {e}")


if __name__ == "__main__":
    main()