import csv
# Выведи кроссовки маленького размера
# Покажи кроссовки, имеющие средний размер
# Какие крассвки большин
# Выведи кротов маленького размера

data = {}
attributes = ['маленькие', 'средние', 'большие']
categories = {'маленькие': (32, 37), 'средние':(38, 41), 'большие': (42, 50)}

def readData():
	with open('data.csv', newline='') as File:
		reader = csv.reader(File)
		for row in reader:
			i = row[0].find(';')
			data[row[0][:i]] = int(row[0][i+1:])

def damLev(str1, str2):
    n = len(str1)
    m = len(str2)

    if n == 0 or m == 0:
        if n != 0:
            return n
        if m != 0:
            return m
        return 0

    change = 0
    if str1[-1] != str2[-1]:
        change += 1

    if n > 1 and m > 1 and str1[-1] == str2[-2] and str1[-2] == str2[-1]:
        res = min(damLev(str1[:n - 1], str2) + 1,
                      damLev(str1, str2[:m - 1]) + 1,
                      damLev(str1[:n - 1], str2[:m - 1]) + change,
                      damLev(str1[:n - 2], str2[:m - 2]) + 1)
    else:
        res = min(damLev(str1[:n - 1], str2) + 1,
                      damLev(str1, str2[:m - 1]) + 1,
                      damLev(str1[:n - 1], str2[:m - 1]) + change)
    return res

def readRequest():
	reqIsValid = False
	sizeBordersArr = []
	reqWords = input("Введите запрос: ").lower().split()
	for word in reqWords:
		if damLev(word, "кроссовки") < 3:
			break
	else:
		return reqIsValid, sizeBordersArr
	
	for word in reqWords:
		for attr in attributes:
			if damLev(word, attr) <= 3:
				sizeBordersArr.append(categories[attr])
	
	if len(sizeBordersArr) > 0:
		reqIsValid = True

	return reqIsValid, sizeBordersArr

def findData(sizeBordersArr):
	res = {}
	for key in data.keys():
		for sizeBorder in sizeBordersArr:
			if data[key] >= sizeBorder[0] and data[key] <= sizeBorder[1]:
				res[key] = data[key]
	return res

def printRes(answer):
	print("Результаты поиска:")
	for key in answer.keys():
		print(key, " с размером ", answer[key])

if __name__ == "__main__":
	readData()
	reqIsValid, sizeBordersArr = readRequest()
	if not reqIsValid:
		print('Не корректный запрос')
		exit(1)

	res = findData(sizeBordersArr)
	printRes(res)

	