from matplotlib import pyplot as plt
from subprocess import check_output
from sys import argv, stderr
from time import time

execs = ['aging_register', 'stack', 'counter', 'clock']

def faults_graphs():
        for binary in execs:
                cmd = '../{} {}_traces '.format(binary, binary)
                x, y = list(), list()

                for i in range(2, 7, 1):
                        x.append(i)
                        y.append(check_output(['bash', '-c', cmd + str(i)]))

                x = map(int, x)
                y = map(int, y)

                plt.plot(x, y)
                plt.title(binary)
                plt.ylabel('Number of page faults')
                plt.xlabel('Number of frames')
                plt.show()

def exec_time_graph():
        x_pos = [0, 1, 2, 3]
        y = list()

        print('generating random pages...')
        check_output(['bash', '-c', 'python2 rand_int_gen.py traces 10000000'])
        print('done')

        for binary in execs:
                cmd = '../{} traces '.format(binary)
                all_time = list()

                for i in range(2, 7, 1):
                        time_s = time()
                        check_output(['bash', '-c', cmd + str(i)])
                        time_e = time()
                        all_time.append(time_e - time_s)

                all_time = map(float, all_time)
                y.append(sum(all_time) / len(all_time))

        print('showing graph')
        plt.bar(x_pos, y, align='center', alpha=0.5)
        plt.xticks(x_pos, execs)
        plt.title('Execution Statistics')
        plt.ylabel('Execution Time (in secs)')
        plt.show()

def main():
        if len(argv) < 2:
                stderr.write('usage: python2 graphs.py [faults | time]\n')
                exit(-1)
        if argv[1] == 'faults':
                faults_graphs()
        elif argv[1] == 'time':
                exec_time_graph()
        else:
                stderr.write('usage: python2 graphs.py [faults | time]\n')
                exit(-1)

if __name__ == '__main__':
        main()
