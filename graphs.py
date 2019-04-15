import matplotlib.pyplot as plt
import subprocess

execs = ['aging_register', 'stack', 'counter', 'clock']

for binary in execs:
        cmd = './{} {}_traces '.format(binary, binary)
        x, y = list(), list()

        for i in range(2, 7, 1):
                x.append(i)
                y.append(subprocess.check_output(['bash', '-c', cmd + str(i)]))

        x = map(int, x)
        y = map(int, y)

        plt.plot(x, y)
        plt.title(binary)
        plt.ylabel('Number of page faults')
        plt.xlabel('Number of frames')
        plt.show()
