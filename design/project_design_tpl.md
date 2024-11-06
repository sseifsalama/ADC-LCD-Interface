# Detailed Design Document

| **Author**              | `Authors Name`                                       |
|:------------------------|:-----------------------------------------------------|
| **Status**              | `Draft/Inspection/Approved`                          |
| **Version**             | `1.0`                                                |
| **Date**                | `dd/mm/yyyy`                                         |

## Introduction

Provide an overview of the entire document:

* Identify the system/product using any applicable names and/or version numbers.

### Purpose
This low-level design specification describes the internal structure and the functions of the software module. It describes the interaction, data structures, specific embedded constraints and background information about design. This specification is the basis for coding and is an input document for the corresponding module test specification. The terms Low-level design specification and module specification are used interchangeably in Valeo to refer to documents of this type.

### Scope
Explanation:-
* Give information on project context, where this document applies.
* Also a reference for more project information can be given.
* Classification for P2, P1, and P0. shall be given.

### Defnitions and Acronym
| **Abbreviation** |             **Meaning**             |
|:----------------:|:-----------------------------------:|
|      (RT)OS      |    (Real-Time) Operating System     |
|       API        |    Application Program Interface    |
|       CDD        |      Component Design Document      |
|       HWI        |         HardWare Interfaces         |
|       NVM        |         Non Volatile Memory         |
|       SRS        | Software Requirements Specification |

## Architectural Overview

This section describes where this module resides in the context of the software architecture
```plantuml
@startuml
rectangle StaticArchi #orange {
    rectangle System #orange {
        rectangle EcuM
        rectangle BAT
        rectangle VEM
        rectangle WdgM
    }
    rectangle Config #lightgreen {
        rectangle CAR #lightgreen
        rectangle CFG #lightgreen
    }

    rectangle BSW_Abstraction_Layer #skyblue {
            rectangle IPC
            rectangle DMA
            rectangle DSI
            rectangle FSM
    }
}
@enduml

```

### Assumptions & Constraints
Indicate constraints of the low level design and any assumptions appropriate for the design.

```plantuml
@startuml
(*) --> init
--> configure
if value > 15
  --> increment value
  --> (*)
else
  --> decrement value
  --> (*)
endif
@enduml
```

## Functional Description
The following chapter describes the software functionality.  The following is a list of suggested sections to be considered for inclusion.

## Implementation of the Module
This chapter discusses the detailed design of the module.

## Integration and Configuration
### Static Files
Typically a module consists of C and H files but other file types may exist. List all files that form this module

| File name | Contents                             |
|-----------|--------------------------------------|
| abc_xxx.c | Source code file, add detail         |
| abc.h     | Export Interface file                |
| abci.h    | Import and Module Configuration file |
### Include Structure

If there is a complex file structure e.g. more than one c-file or more than two h-files use a diagram to explain the relationship between the source and dependent include files.

```plantuml
@startuml
package "pkg" {
    [ABC_Init.c].>[ADC.h] : includes
    [ABC_Init.c]...>[ABCi.h]
    [ABC_Task.c]...>[ADC.h]
    [ABC_Task.c]...>[ABCi.h] : includes
    interface Interf3
    note left of ABC_Task.c: A top note
    ABC_Init.c ..> Interf3 : internal interface
}
@enduml
```

### Configuration
Any required hardware/software or system configuration that can be adjusted a header file shall be detailed in this section. This can be placed in the table below.
| Name | Value range | Description |
|------|-------------|-------------|
|      |             |             |
