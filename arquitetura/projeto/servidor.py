import rpyc
from rpyc.utils.server import ThreadedServer


class MeuServico(rpyc.Service):

    def exposed_soma(self, a, b):
        return a + b

    def exposed_mensagem(self):
        return "Ola! Mensagem enviada pelo h2"


server = ThreadedServer(MeuServico, port=18861)

print("Servidor RPyC iniciado na porta 18861")
server.start()