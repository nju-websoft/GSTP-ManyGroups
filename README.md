# Efficient Algorithms for the Group Steiner Tree Problem with Many Groups

This is the source code of the paper 'Efficient Algorithms for the Group Steiner Tree Problem with Many Groups'.

## Table of contents

- Environment
- Data and Compile Command
- Experiment 1 : KG Summarization
- Experiment 2 : VLSI Design
- Experiment 3 : Keyword-Based KG Search
- Experiment 4 : Parameter Study
- - Experiment 4.1 parameter study on PCSG
  - Experiment 4.2 parameter study on VLSI
- Citation

## Environment

C++ (need to support C++11)

Python 3

600G Memory

## Data and Compile Command

Our datasets is available on [datasets_part1](https://doi.org/10.6084/m9.figshare.24306124.v1) and [datasets_part2](https://doi.org/10.6084/m9.figshare.24307114.v1).

If you want to run our algorithms on a new graph, please build Hub Labeling following [KeyKG](https://github.com/nju-websoft/KeyKG "KeyKG") by yourself.

The compile command for our C++ source codes is shown below: for `A.cpp`, we use `g++ A.cpp -o A -std=c++11` to compile it.

## Experiment 1: KG Summarization

This experiment is based on [PCSG](https://github.com/nju-websoft/PCSG "PCSG").

We provide the input we need in the dataset. 

Our source code is in  `src/PCSG`. 

You need to compile `src/PCSG/GSTGrow.cpp` ,`src/PCSG/GSTMerge.cpp` and  `src/PCSG/KeyKG.cpp` first. 

Then, you need to put the executable file, `newhublabel.txt` and `invertedTable.txt` into a folder. These dataset are in `PCSG_dataset.zip` on our datasets.

Now, you can run the executable file to get a result.

If you want to run our algorithms on more KGs, please following the code in [PCSG](https://github.com/nju-websoft/PCSG "PCSG") to get the HubLabel and invertedTable. Then, you can use `src/PCSG/change_hublabel.cpp` to transform the hublabel into the new hublabel (which records the address of the precursor of each hub).



## Experiment 2: VLSI Design

The source code of this experiment is in `src/VLSI`.

Please compile `auto.cpp`,`gen.cpp`,`GSTGrow.cpp`,`GSTMerge.cpp`,`KeyKG.cpp`.

Then use `./auto` to get the result. The result is in `table.txt`.

## Experiment 3: Keyword-Based KG Search

The source code of this experiment is in `src/KeywordSearch`.

You should  download the dataset from `KeywordSearch_dataset.zip` in our datasets, then put `WeightPLLlabel.txt`, `kwName.txt`, `kwMap.txt` and `query.txt` into the source code folder.

First, please compile and use `change_hublabel.cpp` to change `WeightPLLlabel.txt` to `newhublabel.txt`.

Then, please use `query_change.py` to change `kwName.txt`, `kwMap.txt` and `query.txt` to `newquery.txt`.

Next, please compile and run `GSTGrow.cpp`, `GSTMerge.cpp` and `KeyKG.cpp`. 

We record the exact solution in `/exact_result`. There are 4 files `DBpedia_iw.txt`, `DBpedia_uw.txt`, `LinkedMDB_iw.txt`, `LinkedMDB_uw.txt` . Put the exact solution file, `KeyKG_result.txt`, `Grow_result.txt` and `Merge_result.txt` into a folder, and change the exact solution file name to `exact_result.txt`, then compile `calc.cpp` and run it. You can get a result file `count.txt`, and it will show you the approximation ratio.

## Experiment 4: Parameter Study

### Experiment 4.1 Parameter Study on PCSG

The source code is in `src/parameter/PCSG`.

Please download the `newhublabel.txt` and `invertedTable.txt` of ID from `PCSG_dataset.zip` in our datasets.

Then compile and run `KeyKG.cpp` to get the baseline result.

Next adjust the global variable `tau` from 1 to 9 in `GSTMerge.cpp`, compile and run it to get the result of different $\tau$.

### Experiment 4.2 Parameter Study on VLSI

The source code is in `src/parameter/VLSI`.

Please compile all C++ source code, and use `./auto` to get the result. The result is in `table_tau.txt`.

## Citation

If you think our algorithms or our experimental results are useful, please kindly cite our paper.



