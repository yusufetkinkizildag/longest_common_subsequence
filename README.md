# longest_common_subsequence

Different solutions to longest common subsequence problem.

To understand the problem and the code examples that inspired the source code in this repository, see the links down below.
## Links
- [GeeksForGeeks](https://www.geeksforgeeks.org/printing-longest-common-subsequence/)
- [wikipedia](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem#Reading_out_a_LCS)
- [codeburps](https://www.codeburps.com/dsa/print-longest-common-subsequence)
- [Meteorix/pylcs](https://github.com/Meteorix/pylcs)
- [Fibird/Longest-common-subsequence](https://github.com/Fibird/Longest-common-subsequence)
- [lukeflima/Longest-Common-Subsequence](https://github.com/lukeflima/Longest-Common-Subsequence)


## Requirements
gcc 9.4.0 

More info on [compiler](#compiler)

## How to compile
```console
root@docker-desktop:/# cd /path/to/longest_common_subsequence
root@docker-desktop:/longest_common_subsequence# bash clean_build.sh
```

## How to run
```console
root@docker-desktop:/# cd /path/to/longest_common_subsequence
root@docker-desktop:/longest_common_subsequence# ./build/longest_common_subsequence
```

## clean_build.sh
A trivial shell script that checks and deletes if `build` folder exists.
Calls the cmake and make to build and compile the source code

## CMakeLists.txt
A basic cmake file to specify C++ standard, build type and compile options

## longest_common_subsequence.cpp
The algorithm first checks that if the compared strings are empty or not. If they at least one of them is empty, the algorithm returns/adds 0 or an empty string depending on the purpose of the function. Then if the pointed elements of the two strings are equal then the answer is the accumulated answer so far plus 1 (or plus the element if constructing the sequence itself)

Let $$X = (x_1x_2\dots x_m)$$
    $$Y = (y_1y_2\dots y_n)$$
    $$X_i = (x_1x_2\dots x_i)$$
    $$Y_j = (y_1y_2\dots y_j)$$
    $$i \leq m$$
    $$j \leq n$$

$$ LCS(X_i, Y_j) =
  \begin{cases}
    \emptyset & \quad \text{if } X_i=\emptyset \text{ or } Y_j=\emptyset \\
    LCS(X_{i-1}, Y_{j-1}) + 1  & \quad \text{if } x_i = y_j \\
    max \\{ LCS(X_i, Y_{j-1}), \ LCS(X_{i-1}, Y_j) \\}  & \quad \text{if } x_i \neq y_j
  \end{cases}
$$

|             | $\emptyset$ |      a      |      a      |      b      |      d      |      l      |      l      |      e      |      o      |      g      |
|:-----------:|:-----------:|:-----------:|:-----------:|:-----------:|:-----------:|:-----------:|:-----------:|:-----------:|:-----------:|:-----------:|
| $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ | $\emptyset$ |
|      a      | $\emptyset$ |      1      |      1      |      1      |      1      |      1      |      1      |      1      |      1      |      1      |
|      z      | $\emptyset$ |      1      |      1      |      1      |      1      |      1      |      1      |      1      |      1      |      1      |
|      b      | $\emptyset$ |      1      |      1      |      2      |      2      |      2      |      2      |      2      |      2      |      2      |
|      a      | $\emptyset$ |      1      |      2      |      2      |      2      |      2      |      2      |      2      |      2      |      2      |
|      s      | $\emptyset$ |      1      |      2      |      2      |      2      |      2      |      2      |      2      |      2      |      2      |
|      d      | $\emptyset$ |      2      |      2      |      2      |      3      |      3      |      3      |      3      |      3      |      3      |
|      l      | $\emptyset$ |      2      |      2      |      2      |      3      |      4      |      4      |      4      |      4      |      4      |
|      l      | $\emptyset$ |      2      |      2      |      2      |      3      |      4      |      5      |      5      |      5      |      5      |
|      g      | $\emptyset$ |      2      |      2      |      2      |      3      |      4      |      5      |      5      |      5      |      6      |
|      n      | $\emptyset$ |      2      |      2      |      2      |      3      |      4      |      5      |      5      |      5      |      6      |
|      e      | $\emptyset$ |      2      |      2      |      2      |      3      |      4      |      5      |      6      |      6      |      6      |

There are 3 approaches to the problem.

### Recursion
The methods are in the `recursive` namespace. The first one `lcs_length` directly implements the formula above. It takes two strings by copy and copies them throughout the recursive calls. If the input strings are too long, the excessive and consecutive string copying may cause overflows.

The second one is `lcs_sequence` is just like the first one but the difference is that it accumulates a string by concatenating the results from the recursive calls.
While $\emptyset$ symbol in the formula corresponds to $0$ in `lcs_length`, it corresponds to "" in `lcs_sequence`. The $tr+1$ is changed to elements that gets compared and returned with the `s1.back()` expression in the code, which means get the last element of the string `s1`. Choosing the maximum length is modified to return the string that is longer than the other one. To retrieve the longer string, a lambda is constructed in place and called immediately after construction. The lambda calls the `length` functions of the strings to decide which one is longer.

### Dynamic Programming
The methods are in the `dynamic_programming` namespace. This namespace has one labmda and one class to solve the longest common subsequence problem. The labmda only returns the length of the subsequence's length but the `class LCS` can return both the length and the sequence itself.

The lambda cosntructs a cache matrix to store the previous results and with that, the redundant computations are eliminated. It takes `string_view` objects to avoid copying of the strings. The complexity of the dynamic programming approach is $O\\{mn \\}$ in where the length of the strings are $m$ and $n$. The value of the $cache[i][j]$ depends on the compared elements. If the elements are the same than the value is $1 + cache[i - 1][j - 1]$. Else the value is the maximum of the two values from the same row but preceding column and preceding row and the same column. When all the values of the cache is filled, the length of the longest common subsequence is stored in the last column of the last row of the cache.

`class LCS` has the same algorithm as the lambda in the same namspace. It also takes two string_view objects. The cache is stored in the class scope and filled in the constructor of the object. The `get_length()` function returns the value in the last column of the last row of the cache. `get_sequence()` function returns the sequence itself. The algorithms starts from the last column of the last row of the cache. The index variables (i and j) represents the indices of the characters to be compared. If the characters are the same, then the characters is appended to results string and both of the indexes are decremented. Else, if the value in the preceding row is greater than the value in the preceding column the i index is decremented. Other wise the j is decremented. Finally, the result string is returned.

### Using stack
This method is not working right now. It is marked as TODO!

## Compiler
```console
root@docker-desktop:/longest_common_subsequence$ g++ -v
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 9.4.0-1ubuntu1~20.04.1' --with-bugurl=file:///usr/share/doc/gcc-9/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++,gm2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-9 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-9-Av3uEd/gcc-9-9.4.0/debian/tmp-nvptx/usr,hsa --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
```

```console
root@docker-desktop:/longest_common_subsequence$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 9.4.0-1ubuntu1~20.04.1' --with-bugurl=file:///usr/share/doc/gcc-9/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++,gm2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-9 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-9-Av3uEd/gcc-9-9.4.0/debian/tmp-nvptx/usr,hsa --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)
```
