import matplotlib.pyplot as plt

y1 = [1, 1, 0.6, 0, 0, 0, 0]
y2 = [0, 0, 0.4, 1, 0, 0, 0]
y3 = [0, 0, 0, 0, 1, 1, 1]

x1= [32, 34, 37, 40, 43, 46, 49]
plt.grid(True)
plt.title('')

plt.plot(x1, y1, '-p', color='red', label = "маленькие")
plt.plot(x1, y2, ':p', color='blue', label = "средние")
plt.plot(x1, y3, ':p', linestyle='dashed', color='orange', label = "большие")
plt.legend()
plt.scatter(x1, y1, color='red', s=20)
plt.scatter(x1, y2, color='blue', s=20)
plt.scatter(x1, y3, color='orange', s=20)

plt.ylabel('Принадлежность')
plt.xlabel('Размер кроссовок')
plt.savefig('graph_1.png')
plt.show()
