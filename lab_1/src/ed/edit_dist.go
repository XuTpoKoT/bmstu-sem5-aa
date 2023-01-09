package ed

import (
	"math"
)

func min(nums ...int) int {
	res := math.MaxInt
	for _, num := range nums {
		if num < res {
			res = num
		}
	}
	return res
}

func swapLeft(a, b, c *[]int) {
	tmp := *a
	*a = *b
	*b = *c
	*c = tmp
}

func randomString(lenght int) string {
	return "hellooo"
}

func LevenshteinRec(str1, str2 string) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	flag := 0
	if str1[n-1] != str2[m-1] {
		flag = 1
	}

	res := min(LevenshteinRec(str1[:n-1], str2)+1,
		LevenshteinRec(str1, str2[:m-1])+1,
		LevenshteinRec(str1[:n-1], str2[:m-1])+flag)

	return res
}

func LevenshteinMatrix(str1, str2 string) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	// Инициализируем буферы
	b1 := make([]int, n+1)
	b2 := make([]int, n+1)

	// Инициализируем первую строку матрицы
	for i := 0; i < n+1; i++ {
		b2[i] = i
	}

	// Рассчёт последующих строк матрицы
	for i := 1; i < m+1; i++ {
		b1, b2 = b2, b1

		b2[0] = i
		for j := 1; j < n+1; j++ {
			flag := 1
			if str1[j-1] == str2[i-1] {
				flag = 0
			}

			res := min(b2[j-1]+1, b1[j]+1, b1[j-1]+flag)

			b2[j] = res
		}
	}

	return b2[n]
}

func DamerauLevenshteinMatrix(str1, str2 string) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	// Инициализируем буферы
	b1 := make([]int, n+1)
	b2 := make([]int, n+1)
	b3 := make([]int, n+1)

	// Инициализируем первую строку матрицы
	for i := 0; i < n+1; i++ {
		b3[i] = i
	}

	// Рассчёт последующих строк матрицы
	for i := 1; i < m+1; i++ {
		swapLeft(&b1, &b2, &b3)

		b3[0] = i
		for j := 1; j < n+1; j++ {
			flag := 1
			if str1[j-1] == str2[i-1] {
				flag = 0
			}

			res := min(b3[j-1]+1, b2[j]+1, b2[j-1]+flag)

			// Проверяем перестановку
			if i > 1 && j > 1 && str1[j-1] == str2[i-2] && str1[j-2] == str2[i-1] {
				res = min(b1[j-2]+1, res)
			}

			b3[j] = res
		}
	}

	return b3[n]
}

func DamerauLevenshteinRec(str1, str2 string) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	flag := 1
	if str1[n-1] == str2[m-1] {
		flag = 0
	}

	res := min(DamerauLevenshteinRec(str1[:n-1], str2)+1,
		DamerauLevenshteinRec(str1, str2[:m-1])+1,
		DamerauLevenshteinRec(str1[:n-1], str2[:m-1])+flag)

	// Проверяем перестановку
	if n >= 2 && m >= 2 && str1[n-1] == str2[m-2] && str1[n-2] == str2[m-1] {
		cur := DamerauLevenshteinRec(str1[:n-2], str2[:m-2]) + 1
		if cur < res {
			res = cur
		}
	}

	return res
}

func damerauLevenshteinRecCache(str1, str2 string, cache [][]int) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	if cache[n-1][m-1] != -1 {
		return cache[n-1][m-1]
	}

	res := damerauLevenshteinRecCache(str1[:n-1], str2, cache) + 1

	cur := damerauLevenshteinRecCache(str1, str2[:m-1], cache) + 1
	if cur < res {
		res = cur
	}

	flag := 1
	if str1[n-1] == str2[m-1] {
		flag = 0
	}

	cur = damerauLevenshteinRecCache(str1[:n-1], str2[:m-1], cache) + flag
	if cur < res {
		res = cur
	}

	// Проверяем перестановку
	if n >= 2 && m >= 2 && str1[n-1] == str2[m-2] && str1[n-2] == str2[m-1] {
		cur = damerauLevenshteinRecCache(str1[:n-2], str2[:m-2], cache) + 1
		if cur < res {
			res = cur
		}
	}

	cache[n-1][m-1] = res
	return res
}

func DamerauLevenshteinRecCache(str1, str2 string) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	cache := make([][]int, n)
	for i := range cache {
		cache[i] = make([]int, m)
		for j := range cache[i] {
			cache[i][j] = -1
		}
	}

	return damerauLevenshteinRecCache(str1, str2, cache)
}

func LevenshteinRecRus(str1 []rune, str2 []rune) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	flag := 0
	if str1[n-1] != str2[m-1] {
		flag = 1
	}

	res := min(LevenshteinRecRus(str1[:n-1], str2)+1,
		LevenshteinRecRus(str1, str2[:m-1])+1,
		LevenshteinRecRus(str1[:n-1], str2[:m-1])+flag)

	return res
}

func LevenshteinMatrixRus(str1 []rune, str2 []rune) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	// Инициализируем буферы
	b1 := make([]int, n+1)
	b2 := make([]int, n+1)

	// Инициализируем первую строку матрицы
	for i := 0; i < n+1; i++ {
		b2[i] = i
	}

	// Рассчёт последующих строк матрицы
	for i := 1; i < m+1; i++ {
		b1, b2 = b2, b1

		b2[0] = i
		for j := 1; j < n+1; j++ {
			flag := 1
			if str1[j-1] == str2[i-1] {
				flag = 0
			}

			res := min(b2[j-1]+1, b1[j]+1, b1[j-1]+flag)

			b2[j] = res
		}
	}

	return b2[n]
}

func DamerauLevenshteinMatrixRus(str1 []rune, str2 []rune) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	// Инициализируем буферы
	b1 := make([]int, n+1)
	b2 := make([]int, n+1)
	b3 := make([]int, n+1)

	// Инициализируем первую строку матрицы
	for i := 0; i < n+1; i++ {
		b3[i] = i
	}

	// Рассчёт последующих строк матрицы
	for i := 1; i < m+1; i++ {
		swapLeft(&b1, &b2, &b3)

		b3[0] = i
		for j := 1; j < n+1; j++ {
			flag := 1
			if str1[j-1] == str2[i-1] {
				flag = 0
			}

			res := min(b3[j-1]+1, b2[j]+1, b2[j-1]+flag)

			// Проверяем перестановку
			if i > 1 && j > 1 && str1[j-1] == str2[i-2] && str1[j-2] == str2[i-1] {
				res = min(b1[j-2]+1, res)
			}

			b3[j] = res
		}
	}

	return b3[n]
}

func DamerauLevenshteinRecRus(str1 []rune, str2 []rune) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	flag := 1
	if str1[n-1] == str2[m-1] {
		flag = 0
	}

	res := min(DamerauLevenshteinRecRus(str1[:n-1], str2)+1,
		DamerauLevenshteinRecRus(str1, str2[:m-1])+1,
		DamerauLevenshteinRecRus(str1[:n-1], str2[:m-1])+flag)

	// Проверяем перестановку
	if n >= 2 && m >= 2 && str1[n-1] == str2[m-2] && str1[n-2] == str2[m-1] {
		cur := DamerauLevenshteinRecRus(str1[:n-2], str2[:m-2]) + 1
		if cur < res {
			res = cur
		}
	}

	return res
}

func damerauLevenshteinRecCacheRus(str1 []rune, str2 []rune, cache [][]int) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	if cache[n-1][m-1] != -1 {
		return cache[n-1][m-1]
	}

	res := damerauLevenshteinRecCacheRus(str1[:n-1], str2, cache) + 1

	cur := damerauLevenshteinRecCacheRus(str1, str2[:m-1], cache) + 1
	if cur < res {
		res = cur
	}

	flag := 1
	if str1[n-1] == str2[m-1] {
		flag = 0
	}

	cur = damerauLevenshteinRecCacheRus(str1[:n-1], str2[:m-1], cache) + flag
	if cur < res {
		res = cur
	}

	// Проверяем перестановку
	if n >= 2 && m >= 2 && str1[n-1] == str2[m-2] && str1[n-2] == str2[m-1] {
		cur = damerauLevenshteinRecCacheRus(str1[:n-2], str2[:m-2], cache) + 1
		if cur < res {
			res = cur
		}
	}

	cache[n-1][m-1] = res
	return res
}

func DamerauLevenshteinRecCacheRus(str1 []rune, str2 []rune) int {
	n := len(str1)
	m := len(str2)

	if n == 0 {
		return m
	} else if m == 0 {
		return n
	}

	cache := make([][]int, n)
	for i := range cache {
		cache[i] = make([]int, m)
		for j := range cache[i] {
			cache[i][j] = -1
		}
	}

	return damerauLevenshteinRecCacheRus(str1, str2, cache)
}
