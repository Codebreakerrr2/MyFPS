# Profiling and Logging

The idea of *Profiling and Logging* is to make the system:

- Debuggable
- Benchmarkable
- Able to identify hotspots for optimization

To achieve this, loggers should be used throughout the project for **critical, important, and informative parts** of the code.

## Logger Design

Initially, I considered using **C-style global functions** for logging, but this approach quickly became **crowded and unstructured**.  

Instead, the current design uses **classes** that:

- Inherit from an interface `ILogger`
- Implement a function `Log(message, loggerType)`

### Considerations

- Using classes with virtual functions introduces **overhead** due to:
  - Virtual table lookup
  - Pointer dereferencing
- However, logging is only enabled in **Dev Mode**, so performance impact in production is minimized.

### Logger Types

`LoggerType` is implemented as an **enum class** with values such as:

- `ERROR`
- `INFO`
- `WARNING`

This allows logging to be categorized depending on the usage in specific code snippets.

## Logger Manager

The **LoggerManager** acts as a **user interface for developers**:

- Holds all the loggers together
- Can be **turned on or off** depending on the mode (Dev vs. Deployed)

This structure allows for organized, flexible logging while minimizing performance overhead in production.