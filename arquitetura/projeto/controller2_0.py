import rpyc

print("Conectando ao agente do h1...")

try:
    # Conecta ao agente que está rodando no h1
    conn = rpyc.connect("10.0.0.1", 18861)

    print("Conectado!")
    print("Status:", conn.root.status())

    print("\nExecutando ping de h1 para h2...")

    # O agente do h1 executará o ping
    resultado = conn.root.ping("10.0.0.2")

    print("\n========== RESULTADO ==========")
    print(resultado)

    conn.close()

except Exception as e:
    print("ERRO:", e)
