# Skyward - Syntax of Rust, Simplicity of C

## Why?

Simple reason? I was bored.

## Design Philosophy

Skyward takes great inspiration from greats like C and Rust. I want to create a langauge that works close to the metal--allowing for users to actually interface with the systems that they love to use! I believe that speed and effience is key to a good language and it should be ergonomic.

Langauges like C++ are too bloated for average use. Skyward strives to have a small and reliable core library that is easy for anyone to memorize. Every user should know what their langauge can do.

Just becuase Skyward works close to the hardware, doesn't mean that you are limited by little features. Skyward is packed with everyday features that modern languages should have. Vectors, Matrixes, and different sized Structs barely scratch the surface of what Skyward is capable of.

## Usage

```bash
./skyward <path_to_file>
```

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

    // Declare an untyped function (working name)
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

    return 0;
}
```
