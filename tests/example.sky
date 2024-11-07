use io; // Import the IO library

// Struct definition
struct Employee : Compact {
    Status: struct EmployeeStatus : Enum {
        @start 0;
        @step  1000;

        ADMIN,   // 0000
        MANAGER, // 1000
        ENTRY,   // 2000
        GUEST,   // 3000
    },
    Name: String,
    ID:   Int,
}

// Define member functions for Employee
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

    public func print : None {
        print("Employee:\n");
        print("Name: <>\n", self.Name);
        print("Status: <>\n", self.Status);
        print("ID: <>\n", self.ID.human());
    }
}

// Define member functions for Employee::EmployeeStatus
Employee::EmployeeStatus : impl {
    // Declare an unsigned function (working name)
    // With untyped functions, self is assumed.
    // Traditional functions must explicitly call
    // self as the fist parameter.
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

func main() : Int {
    // Declares a new Employee named Steve
    const employee : Employee = Employee.new(ADMIN, "Steve");

    employee.print();

    return 0;
}