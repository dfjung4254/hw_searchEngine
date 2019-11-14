# 정보검색(SearchEngine) IR 실습 및 과제
- 학번 : B354025
- 이름 : 정근화

## 동작 원리 정리
### STEP 1.
- `step1.cpp`
```
$ make step1
$ ./step1

1. ir.docnames 파일을 읽는다. - ir.docnames 파일에는 읽어야할 문서 파일들의 이름이 기록되어 있다.
2. getDocNamenDocpos 를 통해 ir.docnames 의 문서 이름 하나와 위치를 가져온다.
3. 가져온 문서 이름 하나를 읽는다.
4. printAllWordsWithDocpos 를 통해 해당 문서를 단어 단위로 끊고 각 단어를 문서의 위치와 함께 출력한다.
```
- **Result**
```
mit            0
university            0
is            0
located            0
very            0
near            0
harvard            0
university            0
harvard            5
university            5
is            5
in            5
the            5
city            5
of            5
boston            5
mit           10
is           10
in           10
the           10
city           10
of           10
boston           10
nonamein ir.docnames does not exist. 
baltimore           22
has           22
johns           22
hopkins           22
university           22
find           27
bwi           27
airport           27
near           27
baltimore           27
and           27
johns           27
hopkins           27
university           27
int           32
main           32
int           32
i           32
j           32
cout           32
i           32
j           32
int           41
main           41
int           41
argc           41
char           41
argv           41
string           41
s           41
int           41
i           41
cout           41
s           41
i           41
홍익대학교는           50
마포구에           50
있다           50
mit           59
is           59
in           59
boston           59
홍익대학교는           59
마포구에           59
있다           59
```

### STEP 2.
- `sort`
```
$ ./step1 | sort

1. STEP 1. 의 출력 결과를 Pipe redirection 을 통해 sort 한다.
2. 단어를 기준으로 오름차순 정렬된 결과가 출력된다.
```
- **Result**
```
nonamein ir.docnames does not exist. 
airport           27
and           27
argc           41
argv           41
baltimore           22
baltimore           27
boston            5
boston           10
boston           59
bwi           27
char           41
city            5
city           10
cout           32
cout           41
find           27
harvard            0
harvard            5
has           22
hopkins           22
hopkins           27
i           32
i           32
i           41
i           41
in            5
in           10
in           59
int           32
int           32
int           41
int           41
int           41
is            0
is            5
is           10
is           59
j           32
j           32
johns           22
johns           27
located            0
main           32
main           41
mit            0
mit           10
mit           59
near            0
near           27
of            5
of           10
s           41
s           41
string           41
the            5
the           10
university            0
university            0
university            5
university           22
university           27
very            0
마포구에           50
마포구에           59
있다           50
있다           59
홍익대학교는           50
홍익대학교는           59
```

### STEP 3.
- step3.cpp
```
$ make step3
$ ./step1 | sort | ./step3

1. step3 은 ./step1 | sort 의 결과가 stdout 으로 나온다는 가정 하에
   Pipe redirection 을 사용하여 cin(stdin) 입력을 받는 것으로 시작한다.
2. step2 의 결과를 각 Line 별로 단어와 문서 위치를 읽는다.
3-1. 정렬이 되어 있으므로 이전 라인과 단어와 문서 위치가 같다면 해당 포스팅에서 해당 단어의 빈도 만++ 해준다.
3-2. 만약 이전 라인과 단어는 같지만 문서 위치가 다르다면 이전까지의 문서(Posting)를 라인에 추가하고 새 포스팅을 초기화한다.
3-3. 만약 단어가 바뀌었다면 해당 단어의 line의 문서(Posting) 을 추가한 후 출력한다. 또한 새 단어와 포스팅을 초기화한다.
4. 3.의 과정을 모두 마치면 (단어, 관련 문서 수, 총 빈도, 각 문서의 위치와 문서내 빈도) 정보가 출력된다.
```
- **Result**
```
nonamein ir.docnames does not exist. 
airport 1 1  27 1
and 1 1  27 1
argc 1 1  41 1
argv 1 1  41 1
baltimore 2 2  22 1 27 1
boston 3 3  5 1 10 1 59 1
bwi 1 1  27 1
char 1 1  41 1
city 2 2  5 1 10 1
cout 2 2  32 1 41 1
find 1 1  27 1
harvard 2 2  0 1 5 1
has 1 1  22 1
hopkins 2 2  22 1 27 1
i 2 4  32 2 41 2
in 3 3  5 1 10 1 59 1
int 2 5  32 2 41 3
is 4 4  0 1 5 1 10 1 59 1
j 1 2  32 2
johns 2 2  22 1 27 1
located 1 1  0 1
main 2 2  32 1 41 1
mit 3 3  0 1 10 1 59 1
near 2 2  0 1 27 1
of 2 2  5 1 10 1
s 1 2  41 2
string 1 1  41 1
the 2 2  5 1 10 1
university 4 5  0 2 5 1 22 1 27 1
very 1 1  0 1
마포구에 2 2  50 1 59 1
있다 2 2  50 1 59 1
홍익대학교는 2 2  50 1 59 1
```

### STEP 4.
- step4.cpp
```
$ make step4
$ 
```