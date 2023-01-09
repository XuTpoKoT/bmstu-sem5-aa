package main

import (
	"fmt"
	"lab_1/ed"
	"os"
)

type Command int

const (
	EXIT Command = iota
	LEV_REC
	DAM_LEV_MATR
	DAM_LEV_REC
	DAM_LEV_REC_CASH
	ALL
	TIME
	UNKNOWN_COMMAND
)

func printMenu() {
	println("0. Выход")
	println("1. Метод Левейнштейна матричный")
	println("2. Метод Дамерау-Левейнштейна матричный")
	println("3. Метод Дамерау-Левейнштейна рекурсивный")
	println("4. Метод Дамерау-Левейнштейна рекурсивный с кэшем")
	println("5. Все")
	print("Выберите пункт: ")
}

func main() {
	cmd := UNKNOWN_COMMAND
	var str1, str2 string
	for cmd != EXIT {
		printMenu()
		_, err := fmt.Scan(&cmd)
		if err != nil {
			fmt.Fprintln(os.Stderr, "Вы ввели не число")
			continue
		}
		if cmd == EXIT {
			break
		}
		if cmd == TIME {
			err = ed.EdTimeMatr()
			if err != nil {
				println("Не удалось замерить время")
			}
			break
		}

		print("Введите 1-ю строку: ")
		fmt.Scan(&str1)
		print("Введите 2-ю строку: ")
		fmt.Scan(&str2)

		print("Редакционное расстояние: ")
		switch cmd {
		case LEV_REC:
			println(ed.LevenshteinMatrixRus([]rune(str1), []rune(str2)))
		case DAM_LEV_MATR:
			println(ed.DamerauLevenshteinMatrixRus([]rune(str1), []rune(str2)))
		case DAM_LEV_REC:
			println(ed.DamerauLevenshteinRecRus([]rune(str1), []rune(str2)))
		case DAM_LEV_REC_CASH:
			println(ed.DamerauLevenshteinRecCacheRus([]rune(str1), []rune(str2)))
		case ALL:
			println(ed.LevenshteinMatrixRus([]rune(str1), []rune(str2)))
			println(ed.DamerauLevenshteinMatrixRus([]rune(str1), []rune(str2)))
			println(ed.DamerauLevenshteinRecRus([]rune(str1), []rune(str2)))
			println(ed.DamerauLevenshteinRecCacheRus([]rune(str1), []rune(str2)))
		default:
			println("Нет такого пункта")
		}
	}

	println("End.")
}
