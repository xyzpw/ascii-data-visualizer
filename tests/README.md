### Usage Testing
This directory is intended for testing, tests will ensure the program works as intended.

Before testing, navigate into the `tests/` folder:
```bash
$ cd tests/
```

#### Chart Testing
Chart testing will ensure the charts are properly created, e.g. CSV parsing:
```bash
$ make
$ ./test-charts
```

### Cleaning Up
After finishing the tests, you should cleanup the directory:
```bash
$ make clean
```
