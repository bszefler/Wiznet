from socket import *
from threading import Thread
from matplotlib import style
from matplotlib import pyplot as plt
from matplotlib import animation
import numpy as np


class Serwer:
    def __init__(self):
        style.use('fivethirtyeight')
        self.fig = plt.figure()
        self.fig.text(0.5, 0.95, 'Wykres wiglotności i temperatury', ha='center', va='center')
        self.ax1 = self.fig.add_subplot(1, 1, 1)

        self.hs = np.zeros(100)
        self.ts = np.zeros(100)
        self.t = np.arange(100)
        self.thread = Thread(target=self.stream, args=())
        self.draw()

    def animate(self, i):
        self.ax1.clear()
        self.ax1.plot(self.t, self.hs, self.t, self.ts)

    def draw(self):
        self.thread.start()
        ani = animation.FuncAnimation(self.fig, self.animate, interval=1000)

        plt.show()

    def stream(self):
        while True:
            flaga = True
            s = socket(AF_INET, SOCK_STREAM)

            s.bind(('', 5000))

            s.listen(5)     #5 prób połączenia przed odrzuceniem

            client_socket, addr = s.accept()
            print("Połączenie z ", addr)

            while flaga:
                    try:
                        dana = client_socket.recv(1024).decode()

                        if not dana:
                            flaga = False
                            print("brak danej")
                            client_socket.close()
                        else:
                            print(dana)
                            dana = dana.split()
                            # x = dana[0]
                            # y = dana[1]
                            # print(x, y)
                            self.hs = np.roll(self.hs, -1)
                            self.ts = np.roll(self.ts, -1)
                            self.hs[99] = dana[0]
                            self.ts[99] = dana[1]

                    except OSError as e:
                        if e.errno == 10054 or e.errno == 10053:
                            client_socket.close()
                            flaga = False
                        else:
                            raise

serwer = Serwer()









