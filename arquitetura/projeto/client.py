import rpyc

conn = rpyc.connect("127.0.0.1", 18861)

resultado = conn.root.soma(10, 20)
print("Resultado da soma:", resultado)

mensagem = conn.root.mensagem()
print("Mensagem:", mensagem)

conn.close()