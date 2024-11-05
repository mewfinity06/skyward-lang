# Skyward - Syntax of Rust, Simplicity of C

## Why?

Simple reason? I was bored.

## Inspiration

### Youtubers

- [Lens_r's FUNCompiler]((https://github.com/LensPlaysGames/LensorCompilerCollection))
- [Tsoding's Porth](https://gitlab.com/tsoding/porth)

### Languages

- [Rust]((https://www.rust-lang.org/))
- [C](https://en.cppreference.com/w/c)
- [Odin](https://odin-lang.org/)
- [Gleam](https://gleam.run/)
- [Go](https://go.dev/)

## Design Philosophy

Skyward draws significant inspiration from established languages like C and Rust, aiming to operate close to the hardware and provide developers with direct access to the systems they value. Prioritizing speed and efficiency, Skyward is designed to be both high-performing and ergonomic.

In contrast to languages like C++, which can feel bloated for general use, Skyward is built around a lean and reliable core library that's intuitive and easy to master. We believe every developer should have a comprehensive understanding of what their language can accomplish.

Although Skyward operates close to the hardware, it remains feature-rich and versatile. Packed with essential modern features, Skyward supports vectors, matrices, and various structured data types, providing a powerful foundation for a broad range of applications.

## Usage

```bash
./skyward <path_to_file>
```

## Features

### Structs, Enums, Etc

- C like structs, called Compact
- Class like structs, called Loose.
  - Loose Structs' memory isn't all stored in one place. A Loose Struct is made up of pointers to memory that is stored in a different place.
- Rust like Enums, just an extention of Structs.

### Functions

- Signed and Unsigned Function calls
  - Signed functions are just like in any other function!
    - Signed functions must declare `self` as a parameter
  - Unsigned functions are specific to Skyward. These functions allows the programmer to not be forced to provide a signature.
    - All unsigned member functions ASSUME `self`

## Basic Syntax

```rust
use io; // Import the IO library

// Declare an Enum Struct
struct EmployeeStatus : Enum {
    @start 0; // Has the first element (ADMIN) start at 0
    @step 1000; // Each element increases by 1000

    ADMIN,   // 0000
    MANAGER, // 1000
    ENTRY,   // 2000
    GUEST,   // 3000
}

// Member functions for EmployeeStatus
EmployeeStatus : impl {

    // Declare an unsigned function
    // With untyped functions, self is assumed.
    // Traditional functions must explicitly call
    // self as the fist parameter.
    public func human : Char* {
        switch(self) {
        ADMIN   => return "Admin";
        MANAGER => return "Manager";
        ENTRY   => return "Entry";
        GUEST   => return "Guest";
        else    => return "Unknown";
        }
    }
}

// Declare a Compact Struct
struct Employee : Compact {
    Status: EmployeeStatus,
    Name:   Char*,
    ID:     Int,
}

// Member functions for Employee
Employee : impl {

    // A member variable
    private mut seed : Int = 0;

    public func new(status: EmployeeStatus, name: Char*) : Employee {
        defer seed++; // Defer seed++ until end of scope
        return Employee {
            Status: status,
            Name: name,
            ID: status + seed,
        }
    }

    public func print : None {
        io.print("Employee:\n");
        io.print("Name: <>\n", self.Name);
        io.print("Status: <>\n", self.Status);
        io.print("ID: <>\n", self.ID.human());
    }

}

func main() : Int {
    // Declares a new Employee named Steve
    const employee : Employee = Employee.new(ADMIN, "Steve");

    employee.print();
    // Prints:
    //
    //  Employee:
    //  Name: Steve
    //  Status: Admin
    //  ID: 0000
    //
    return 0;
}
```
