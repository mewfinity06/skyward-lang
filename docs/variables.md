# Variables

```rust
mut best_drink : String;
best_drink = "Well, it's not Java 😛";

// Constant cannot be changed (They're constant)
const what_is_the_best_langauge : String = "Skyward ⚔️";

// Mutable
mut is_day : Bool = True;

// Type inferance
const days_of_week := 7; // Will be inferred as 'Int'

```

## Types

### Basic types

#### Int

`Int` type defaults to Int32 but can be followed by any whole number to dictate the bits included

```rust

const very_large_number : Int256 = 1.157e77;

// Unsigned 8 bit integer
const red_value : unsigned Int8 = 32;

// Explicitly signed 
const weird_int : signed Int2 = 1; // Can literally only be 1, -1, 0

```

#### Float

`Float` type defaults to Float32 but can be followed by any whole number to dictate the bits included

```rust

const actual_day_in_a_year := 365.25;

```

#### Char

A `Char` is a single character

```rust

const first_letter_of_this_language := "Skyward".first();

const c_like_string : Char* = "This is just like the olden days!";

```

#### String

Your typical `String`

```rust

const dog_name := "Nova"

const dog_breed : String = "American Staffordshire Terrier";

```

#### Byte

`Bytes` can be represented as numbers or hex values

```rust

const hex_max := 0xfff; // Hex will defauly to a Byte

const blue_value : Byte = 255;

```

#### Bool

`Bools` can be `True` or `False`

```rust

const is_the_sky_green := False;

const party_time : Bool = True;

```

#### Usize & Isize

`Usize` and `Isize` are based on your computer. If you have a 64 bit computer, `Usize` and `Isize` will be 64 bits

```rust

const length : Usize = "Hello, Swordsman!".len();

```

### Special types

#### Void*

A `Void*` is a pointer to memory that doesn't care what type it is. All pointers can be converted to a `Void*` and a `Void*` can be converted to any type

#### None -> Function type

`None` is used to denote that a function does not return any value

```rust

func foo : None {
    print("This function returns nothing!");
}

```

#### Enum -> Struct type

An `Enum` declares a struct as an Enumeration

#### Compact -> Struct type

`Compact` declares the struct's memory layout. Compact structs are like structs in C

#### Loose -> Struct type

`Loose` declares the struct's memory layout. All data stored within this struct is converted to a pointer of that type. 
A common mistake is to already cast an member to a pointer. This would make that member a pointer to a pointer

#### Union -> Struct type

`Union` allows for multiple data types to be stored at the same memory location

#### Vector

A `Vector` is a mathematical vector. So like x, y, z, etc.

#### Matrix

#### Error

#### Complex

#### SizeableArray

#### FixedArray

#### HashMap
