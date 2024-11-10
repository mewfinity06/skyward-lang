# Functions

All functions must have a return type (See [Variables](variables.md) for more)

## Signed functions

```rust

func foo(a: Int, b: Int) : Int {
    return a + b;
}

func buzz(greeting: String) : None {
    switch greeting.lowercase() {
        "hello" | "hey" | "hi" => {
            print("What's up, man?\n");
        } break;
        "bye" | "seeya" | "tchau" => {
            print("I hope to hear from you again!\n");
        } break;
        else => {
            print("I have no clue what you just said!\n");
        }
    }
}

```

## Unsigned functions

```rust

const what_is_the_best_langauge := "Skyward";

func baz : Char {
    return what_is_the_best_langauge.first().lower();
}

```

## Function calling

```rust

foo(1, 6); // -> returns 7

foo(b: 6, a: 10); // -> returns 16

buzz("HEY"); // -> prints "What's up, man?"

// Unsigned function calling is just the same
baz(); // -> returns 's'

```

## Pipeline

Pipelines are used to pipe a return value into another function. This allows for cleaner, more readable code. No more functions wrapped in functions wrapped in functions!

```rust

func first_call(a: Int, b: Int) : Int {
    return a + b - 3;
}

func second_call(a: Int) {
    return a ** 2; 
}

// Implicit pipelines
first_call(1, 2)
|> second_call()
|> print("Final <>");

// Explicit pipelines
first_call(9, 2) as x
|> second_call(x) as y
|> print("First <>, Second <>", x, y); // Note, this isn't possible with implicit pipeline

```

But what if your function returns multiple variables?

```rust

func name_and_age(name: String, age: Int) : (String, Int) {
    return (name, age);
}

func age_in_3_years(mut age: Int) : None {
    age += 3;
}

name_and_age("Ashton", 18) as (name, age)
|> age_in_3_years(age)
|> print("<> will be <> in three years!", name, age);

```
