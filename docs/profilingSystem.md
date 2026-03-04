# Profiling and Logging

## Purpose

The idea of this system is to make the project **debuggable** and to be able to **benchmark** it in order to find hotspots and optimize performance efficiently.

---

## Logger Usage

- Loggers should be used throughout the entire project for:
  - **Critical parts of the code**
  - **Important events**
  - **Informative messages**

- Initially, global C-style logging functions were considered, but:
  - This approach becomes **crowded**
  - Lacks **structure**
  
- Instead, each logger is implemented as a **class inheriting from the `ILogger` interface** with the function:

```cpp
void Log(const std::string& message, LogLevel loggerType);

- Meanwhile, the LoggerManager brings all loggers together and provides developers with a single point of access for logging throughout the project.  