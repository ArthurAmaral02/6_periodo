import rpyc


hosts = [
    ("h1", "10.0.0.1"),
    ("h2", "10.0.0.2"),
    ("h3", "10.0.0.3")
]


for name, ip in hosts:

    print("\n========================")
    print("Host:", name)
    print("IP:", ip)

    try:

        conn = rpyc.connect(
            ip,
            18861
        )

        print("Status:", conn.root.status())
        print("Hostname:", conn.root.hostname())

        conn.close()

    except Exception as e:

        print("ERRO:", e)