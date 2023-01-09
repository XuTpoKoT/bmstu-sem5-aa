package ed

import (
	"testing"
)

type TestPack struct {
	a, b string
	want int
}

var testsCommon = []TestPack{
	{"cat", "cute", 2},
	{"cute", "cat", 2},
	{"dog", "dog", 0},
	{"toook", "t", 4},
	{"", "", 0},
	{"", "33", 2},
	{"1234", "", 4},
	{"sample", "samlpee", 2},
	{"йцукен", "йцкеун", 2},
}

var testsLevOnly = []TestPack{
	{"abcde", "abced", 2},
	{"abcde", "baced", 4},
}

var testsDamLevOnly = []TestPack{
	{"abcde", "abced", 1},
	{"abcde", "baced", 2},
}

func TestLevDist(t *testing.T) {
	for i, test := range append(testsCommon, testsLevOnly...) {
		got := LevenshteinMatrixRus([]rune(test.a), []rune(test.b))
		if got != test.want {
			t.Fatalf("test %d: LevenshteinMatrix(%s, %s) = %d, want %d", i, test.a, test.b, got, test.want)
		}
	}
}

func TestDamLevDist(t *testing.T) {
	for i, test := range append(testsCommon, testsDamLevOnly...) {
		got := DamerauLevenshteinMatrixRus([]rune(test.a), []rune(test.b))
		if got != test.want {
			t.Fatalf("test %d: DamerauLevenshteinMatrix(%s, %s) = %d, want %d", i, test.a, test.b, got, test.want)
		}
	}
}

func TestDamLevDistRec(t *testing.T) {
	for i, test := range append(testsCommon, testsDamLevOnly...) {
		got := DamerauLevenshteinRecRus([]rune(test.a), []rune(test.b))
		if got != test.want {
			t.Fatalf("test %d: DamerauLevenshteinRec(%s, %s) = %d, want %d", i, test.a, test.b, got, test.want)
		}
	}
}

func TestDamLevDistRecCache(t *testing.T) {
	for i, test := range append(testsCommon, testsDamLevOnly...) {
		got := DamerauLevenshteinRecCacheRus([]rune(test.a), []rune(test.b))
		if got != test.want {
			t.Fatalf("test %d: DamerauLevenshteinRecCache(%s, %s) = %d, want %d", i, test.a, test.b, got, test.want)
		}
	}
}
