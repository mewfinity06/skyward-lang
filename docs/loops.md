# Loops

## For loops

```rust

for i : Int = 0; i < 100; i++ {
    print("Loop has been printed <> times!\n", i);
}

```

## While loops

```rust
use std.randomInt as Random;

const target := 69;
mut guess : Int; // Initiaized to zero

while guess != target {
    guess := Random(0, 100); // create a random number between 0 and 100, inclusive
    print("Guessing <>\n", guess);
}

print("Congrats you guessed correctly! The target was <>!\n", target);

```

## Loop loops

```rust

mut name := "Skyward";
mut i := name.len();

loop {
    print("<>", name);
    i--;
    name := name[0:i];
    if name == "" : break;
}

```
