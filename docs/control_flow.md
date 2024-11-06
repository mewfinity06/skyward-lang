# Control Flow

## If statement

```rust
const a := 69;
const b := 420;

print("A: <> B: <>\n", a, b);
if a < b {
    print("A is bigger than B\n");
} else if a == b {
    print("A and B are the same\n");
} else {
    print("B is bigger than A\n");
}

const z := 10;

// Non-else'd if statement
if z > 10 : print("Hey, that's above the maximum!\n");

```

## Switch statement

```rust

const greeting := "Hello!";

// Switching on greeting
switch greeting {
    "Hello" => print("Say hello!"); break;
    "Bye" | "Goodbye" => print("Say goodbye!"); break;
    else => print("That's not a valid greeting!");
    finally => print("\n"); // This will execute no matter what!
}

const name := "Skyward";

// Switching on the first letter of the name
switch letter := name.first() {
    'A'..'Z' => print("<> is capitalized!", letter); break;
    'a'..'z' => print("<> is lower case.", letter); break;
    else => print("<> is not a letter...", letter); break;
    finally => print("\n");
}

```
