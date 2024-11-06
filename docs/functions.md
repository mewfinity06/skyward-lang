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

buzz("HEY"); // -> prints "What's up, man?"

// Unsigned function calling is just the same
baz(); // -> returns 's'

```
