<b>Repository tree:</b><br/>

<pre>
.
├── Presentation                        /* Presentation slides          */
├── bin                                 /* time performances binaries   */
│   ├── benchmark_bucket_o0
│   ├── benchmark_bucket_o1
│   ├── benchmark_bucket_o2
│   └── benchmark_bucket_o3
├── lib
│   ├── bucket_sorting.cpp              /*  Ex.12 - bucket serial sorting algorithm */
│   ├── parallel_sort.cpp               /*  Ex.11 - parallel sorting optimized with Ex. 12 */
│   ├── test_utils.cpp                  /*  Utils functions for testing correctness *
│   └── utils.cpp                       /*  Other utils functions */
├── output
│   └── output.txt                      /*  Output of time benchmarks */
├── test
│   └── run_test                        /*  Execute to test correctness of the algorithm */
├── memory_usage_analysis.cpp           /*  Memory usage test source file - need to be compiled modifying instance size and using valgrind*/
├── correctness_test.cpp                /*  Source file of test/run_test */
└── time_performance_analysis.cpp       /*  Source file of bin/benchmark_bucket_oX */
 
</pre>

<b>
Requirements:
</b>

To compile `time_performance_analysis.cpp` the installation of https://github.com/google/benchmark is required. 

<b>Headers</b>

Important functions:

In utils.cpp 
<br>
<span style="color:green">
// function to print a vector 
</span></br>
`void print_vector(std::vector<int> &vec)`<br>
<span style="color:green">
// this pads the vector using r. Being n the size of the vector it pads the vecotr with r-(nmodr) elements of key r-1 (at the end) and returns how many elements have been added 
</span></br>
`int padding(std::vector<int> &vec, int r)`<br>
<span style="color:green">
// delete the elements added from the padding (padded is r-(nmodr))
</span></br>
`void reset_vec(std::vector<int> &vec, int padded)`

In test_utils.cpp
<br>
<span style="color:green">
// functions that check if the vector is sorted or not
</span></br>
`int check_ordered(std::vector<int> &vec)`
<br>
<span style="color:green">
// function that check if parallel_sort is correct: calls the sorting algorithm, count if number of elements its equal and call `check_ordered`
</span></br>
`int test_correctness(std::vector<int> &vec, int r)`
<br>

In parallel_sort.cpp <br>
<span style="color:green">
// This function is a wrapper function: it pads the array (if needed) and sort it calling another function (parallel_sort)
</span></br>
`std::vector<int> sort(std::vector<int> &a, int r)`