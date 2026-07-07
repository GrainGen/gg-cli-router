# GG CLIRouter

## What's this

This is the core parameter routing component for a Linux command-line tool implemented in C++\
It provides command registration, dispatch, error handlling capabilities

Here is the CLIRouter core schematic diagram

```mermaid
graph TD
    %% Style Definitions
    classDef phase fill:#f9f9f9,stroke:#333,stroke-width:2px;
    classDef memory fill:#e1f5fe,stroke:#0288d1,stroke-width:2px;
    classDef process fill:#fff3e0,stroke:#f57c00,stroke-width:1px;
    classDef error fill:#ffebee,stroke:#c62828,stroke-width:1px;

    %% 1. Setup Phase
    subgraph Setup["1. Initialization & Registration Phase"]
        A[User Code: main] -->|1.1 reg_cmd| B(CLIRouter::reg_cmd)
        A -->|1.2 set_error_handler| C(CLIRouter::set_error_handler)
    end

    %% Memory Core
    subgraph Memory["CLIRouter Memory Storage"]
        M1["std::map&lt;string, CommandCallback&gt; commands"]
        M2["ErrorCallback error_handler"]
    end
    B -->|Insert Key-Value| M1
    C -->|Store Lambda Pointer| M2

    %% 2. Dispatch Phase
    subgraph Dispatch["2. Runtime Dispatch Phase"]
        Input["Terminal Input: $ f2l fetch cf 1A"] -->|Parsed by OS| Main["main(argc, argv)"]
        Main -->|2.1 Invoke| Disp["router.dispatch(argc, argv)"]
        
        %% Arguments Validation
        Disp --> CheckArg{"2.2 Validate: argc &lt; 2 ?"}
        CheckArg -->|Yes: Empty Input| Err1["handle_error('No command provided.')"]
        
        %% Parsing
        CheckArg -->|No: Valid count| Parse["2.3 Extract & Convert<br/>cmd = argv[1]<br/>args = [ argv[2] ... argv[argc-1] ]"]
        
        %% Routing Match
        Parse --> FindCmd{"2.4 commands.find(cmd)"}
        FindCmd -->|Map Miss| Err2["handle_error('Unknown command: ' + cmd)"]
        FindCmd -->|Map Hit| Exec["2.5 Execute: it->second(args)"]
    end

    %% 3. Error Handling
    subgraph ErrorHandling["3. Centralized Error Defenses"]
        Err1 --> CheckHandler
        Err2 --> CheckHandler
        CheckHandler{"error_handler == nullptr ?"}
        CheckHandler -->|No: Custom Handler Set| Intercept["Trigger Unit Test Interceptor<br/>(error_triggered = true)"]
        CheckHandler -->|Yes: Default Fallback| DefaultErr["std::cerr &lt;&lt; error_msg<br/>print_default_help()"]
    end

    %% Internal Dependencies
    M1 -.-> FindCmd
    M2 -.-> CheckHandler

    %% Apply Styles
    class Setup,Dispatch,ErrorHandling phase;
    class Memory memory;
    class Disp,Parse,Exec process;
    class Err1,Err2,CheckHandler,DefaultErr,Intercept error;
```

## Why do this

## How to install

## How to use

## Structure of this

## License
