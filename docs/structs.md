# Structs and Impls

## Struct types

- Compact | Compact structs have all of the data stored in a block, much like the structs in popular languages like C, Rust, and C++
- Loose | Loose structs consists of pointers to it's data. This is allows the programmer to take control of the memory layout
- Enum | Enums are much like any other struct type. They can have member functions.
- Union

### Compact

```rust

struct Employee : Compact {
    Status: EmployeeStatus,
    Name:   String,
    ID:     Int,
}

```

### Loose

```rust

struct Animal : Loose {
    Species: String,
    ScientificName: String,
}

```

### Enum

```rust

struct EmployeeStatus : Enum {
    // Declares the start of the enum (optional, will use default)
    @start 0;
    // Declares the step between each element
    @step 1000;

    ADMIN,   // 0000
    MANAGER, // 1000
    ENTRY,   // 2000
    GUEST,   // 3000
}

```

## Impl Blocks

Impl blocks allow the user to define member functions and variables

```rust

Employee : impl {
    // A member variable
    // Private member variables can only be used within scope
    private mut seed : Int = 0;

    public func new(status: EmployeeStatus, name: String) : Employee {
        defer seed++; // Defer seed++ until end of scope
        return Employee {
            Status: status,
            Name: name,
            ID: status + seed,
        };
    }

    // Note: Unsigned functions inside of Impl blocks assume `self`
    //       Signed functions must have self declared as the first signature
    public func print : None {
        print("Employee:\n");
        print("Name: <>\n", self.Name);
        print("Status: <>\n", self.Status);
        print("ID: <>\n", self.ID.human());
    }
}

EmployeeStatus : impl {
    public func human : String {
        switch self {
            ADMIN   => return "Admin";
            MANAGER => return "Manager";
            ENTRY   => return "Entry";
            GUEST   => return "Guest";
            else    => return "Unknown";
        }
    }
}

```
