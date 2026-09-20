import rpyc

print("Conectando ao agente do h2...")

try:
    conn = rpyc.connect("10.0.0.2", 18861)

    print("Conectado!")
    print("Status:", conn.root.status())

    print("\nExecutando ping de h1 para h2...")
    resultado = conn.root.ping("10.0.0.2")

    print("\n========== RESULTADO ==========")
    print(resultado)

    conn.close()

except Exception as e:
    print("ERRO:", e)

