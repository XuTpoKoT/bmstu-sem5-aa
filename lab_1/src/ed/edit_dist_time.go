package ed

import (
	"encoding/csv"
	"os"
	sc "strconv"
)

/*
#include <pthread.h>
#include <time.h>
#include <stdio.h>

static long long getThreadCpuTimeNs() {
    struct timespec t;
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
        perror("clock_gettime");
        return 0;
    }
    return t.tv_sec * 1000000000LL + t.tv_nsec;
}
*/
import "C"

var strings1 = map[int]string{
	4:   "акеп",
	7:   "frrtged",
	10:  "shjuyrtgfh",
	12:  "shjuyrtgfher",
	25:  "asdklnleinvleirnvlerinvrr",
	50:  "vmlekrmvelkrmvearvmsrjnvtasdklnleinsssirnvlerinvrr",
	75:  "vmlekrmvelkrmvearvmsrjnvtsdkfbsbdvameprvperovnperonvprvnprnvpernvpernvpenrp",
	100: "vmlekrmvelkrmvearvmsrjnvtasdklnleinsssirnvlerinvrrsruburuhfhfhlshcoihecoaqbnocwbuqowucbobcouewbcoubw",
}

var strings2 = map[int]string{
	4:   "укеу",
	7:   "trgtyhj",
	10:  "djuirkueyr",
	12:  "djuirkueyrgr",
	25:  "vmlekrmvelkrmvearvmsrjnvt",
	50:  "asdklnleinvleirnvlerinvrrvmlekrmfffkrmvearvmsrjnvt",
	75:  "asdklnleinvleirnvlerinvrrdkrivmorvcsnsoiuhfskdbsdkfbsbfskudfbskuebfksuefbsk",
	100: "asdklnleinvleirnvlerinvrrvmlekrmfffkrmvearvmsrjnvtvmlekrmvelkrmvearvmsrjnvtasdklnleinsssirnvlerinvrr",
}

func EdTimeRec() error {
	recSizes := []int{4, 7, 10, 12}
	f1, err := os.Create("report/f3.csv")
	if err != nil {
		return err
	}
	defer f1.Close()
	w1 := csv.NewWriter(f1)
	w1.Write([]string{"size", "time"})

	f2, err := os.Create("report/f4.csv")
	if err != nil {
		return err
	}
	defer f2.Close()
	w2 := csv.NewWriter(f2)
	w2.Write([]string{"size", "time"})

	for _, sz := range recSizes {
		s1 := []rune(strings1[sz])
		s2 := []rune(strings2[sz])

		t1 := C.getThreadCpuTimeNs()
		DamerauLevenshteinRecRus(s1, s2)
		t2 := C.getThreadCpuTimeNs()
		err = w1.Write([]string{sc.FormatInt(int64(sz), 10), sc.FormatInt(int64(t2-t1), 10)})

		t1 = C.getThreadCpuTimeNs()
		DamerauLevenshteinRecCacheRus(s1, s2)
		t2 = C.getThreadCpuTimeNs()
		err = w2.Write([]string{sc.FormatInt(int64(sz), 10), sc.FormatInt(int64(t2-t1), 10)})
	}
	w1.Flush()
	w2.Flush()

	return nil
}

func EdTimeMatr() error {
	commonSizes := []int{25, 50, 75, 100}

	f1, err := os.Create("f1.csv")
	if err != nil {
		return err
	}
	defer f1.Close()
	w1 := csv.NewWriter(f1)
	w1.Write([]string{"size", "time"})

	f2, err := os.Create("f2.csv")
	if err != nil {
		return err
	}
	defer f2.Close()
	w2 := csv.NewWriter(f2)
	w2.Write([]string{"size", "time"})

	f3, err := os.Create("f5.csv")
	if err != nil {
		return err
	}
	defer f3.Close()
	w3 := csv.NewWriter(f3)
	w3.Write([]string{"size", "time"})

	for _, sz := range commonSizes {
		s1 := []rune(strings1[sz])
		s2 := []rune(strings2[sz])

		t1 := C.getThreadCpuTimeNs()
		LevenshteinMatrixRus(s1, s2)
		t2 := C.getThreadCpuTimeNs()
		err = w1.Write([]string{sc.FormatInt(int64(sz), 10), sc.FormatInt(int64(t2-t1), 10)})

		t1 = C.getThreadCpuTimeNs()
		DamerauLevenshteinMatrixRus(s1, s2)
		t2 = C.getThreadCpuTimeNs()
		err = w2.Write([]string{sc.FormatInt(int64(sz), 10), sc.FormatInt(int64(t2-t1), 10)})

		t1 = C.getThreadCpuTimeNs()
		DamerauLevenshteinRecCacheRus(s1, s2)
		t2 = C.getThreadCpuTimeNs()
		err = w3.Write([]string{sc.FormatInt(int64(sz), 10), sc.FormatInt(int64(t2-t1), 10)})
	}
	w1.Flush()
	w2.Flush()
	w3.Flush()

	return nil
}
