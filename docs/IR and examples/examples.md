# Examples
There are 4 different types of IR program shapes that a CFG solver needs to be able to handle. All shapes are provided in both C and iON IR.

> Each C program only uses `goto` statements rather than using conditionals. This is because iON IR only has `BEQ` so to demonstrate the C program equivelant of each IR program, we only use `goto` to simulate using conditionals.
## Straight-line DAG
```c
// Block A (entry)
int x = 10;
int y = 20;
goto block_B;

// Block B
block_B:
    int z = x + y;
    if (z == 30)
        goto block_C;

block_C:
    return z;
```

```plaintext
INIT_BLOCK:
    MOV %1, 10
    MOV %2, 20
    JMP BLOCK_B

BLOCK_B:
    ADD %3, %1, %2
    BEQ %3, 30, BLOCK_C

BLOCK_C:
    RET %3
```


## Simple Loop
```c
int a = 0;

main_block:
    if (a == 40)
        goto block_C;
    else
        goto block_A;

block_A:
    a++;
    goto main_block;


block_C:
    return a;
```

```plaintext
INIT_BLOCK:
    MOV %1, 0

main_block:
    BEQ %1, 40, BLOCK_C
    JMP BLOCK_A

BLOCK_A:
    ADD %1, %1, 1
    JMP main_block

BLOCK_C:
    RET %1
```


## Nested Loop
```c
int a = 0, b = 0;

outer_block:
    if (a == 10) {
        inner_block:
            if (b == 5) {
                goto ret_block;
            } else {
                b++;
                goto inner_block;
            }
    } else {
        a++;
        goto outer_block;
    }

ret_block:
    return a + b;
```

```plaintext
INIT_BLOCK:
    MOV %1, 0
    MOV %2, 0

OUTER_BLOCK:
    BEQ %1, 10, INNER_BLOCK

OUTER_BODY:
    ADD %1, %1, 1
    JMP OUTER_BLOCK

INNER_BLOCK:
    BEQ %2, 5, RET_BLOCK

INNER_BODY:
    ADD %2, %2, 1
    JMP INNER_BLOCK

RET_BLOCK:
    ADD %3, %1, %2
    RET %3
```


## Diamond
```c
int a = 5;

if (a == 5) {
    a = 1;
    goto exit;
} else {
    a = -1;
    goto exit;
}

exit:
    return a;
```

```plaintext
INIT_BLOCK: 
    MOV %1, 5

MAIN_BLOCK:
    BEQ %1, 5, COND_1
    JMP COND_2

COND_1:
    MOV %1, 1
    JMP RET_BLOCK

COND_2:
    MOV %1, -1
    JMP RET_BLOCK

RET_BLOCK:
    RET %1
```