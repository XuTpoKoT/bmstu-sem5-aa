import csv
import random

with open('data.csv', 'w', newline='') as file:
	writer = csv.writer(file, delimiter=';')
	for i in range(1, 20):
		writer.writerow(["Кроссовки №" + str(i), random.randint(32, 50)])