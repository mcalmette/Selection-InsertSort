# Selection-Insert Sort


## Class Setup
```
cmake CMakeLists.txt
make
```

To use selection sort:
```
./sort s rand-10k.txt
```
To use insertion sort:
```
./sort i rand-10k.txt
```
Note: can switch out different random text files with files that sort a descending listed file i.e. desc-10k.txt 

## About this project
An implementation of selection sort / insertion sort of a linked list with each node holding a key-value pair.  The project also uses these functions:
- add
- remove
- find
- range find
- keys (returns all keys by reference)
- sort (ascending order)
- size

Selection sort and insertion sort are not the most efficient sorting algorithms for randomly generated key value pairs.


<img width="450" alt="Screen Shot 2020-05-20 at 5 25 30 PM" src="https://user-images.githubusercontent.com/56742122/82510280-074ae000-9abf-11ea-8453-8ffa63e5c6ce.png">


Note: Need to have Cmake installed
