import matplotlib.pyplot as plt
from math import *
import numpy as np
import random

def percents(a, b):
	if a > b:
		a, b = b, a
	return (b - a) / b * 100
	# < h d
def graph():
	# Первый график
	plt.figure()
	plt.title('Редакционные расстояния')
	plt.xlabel('Длина строк')
	plt.ylabel('Время, мкс')

	x1 = [25, 50, 75, 100]
	y1 = [x / 1000 for x in [6819, 24423, 45244, 81715]]

	x2 = [25, 50, 75, 100]
	y2 = [x / 1000 for x in [8387, 27310, 53815, 89166]]

	#y3 = [x / 1000 for x in [28041, 98589, 234367, 418015]]

	plt.plot(x1, y1, '-p', color='red', label='Левенштейн матричный')
	plt.plot(x2, y2, ':p', color='blue', label='Д.-Левенштейн матричный')

	plt.legend(loc='upper left') 
	plt.grid(True)

	# Второй график
	plt.figure()
	plt.title('Редакционные расстояния')
	plt.xlabel('Длина строк')
	plt.ylabel('Время, мкс')

	x1 = [4, 7, 10, 12]
	y1 = [x / 1000 for x in [1412304, 243515, 42562079, 1299961686]]

	x2 = [4, 7, 10, 12]
	y2 = [x / 1000 for x in [3525, 2795, 4887, 7208]]

	plt.plot(x1, y1, '-p', color='red', label='Д.-Левенштейн рекурсивный')
	plt.plot(x2, y2, '--D', color='blue', label='Д.-Левенштейн рекурсивный с кешем')

	plt.legend(loc='upper left') 
	plt.grid(True)
	plt.show()
	
#graph()
print(percents(43397, 58495))
#print(42567 / 5)




