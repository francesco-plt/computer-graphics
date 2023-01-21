# Computer Graphics

## Introduction

- `assignments`: it contains the solution to all the assignments given during the course, complete with `.pdf` description of the problem. Some assignments also include a `notes.md` file which explains a bit the theory behind the code used to solve the assignment.
- `project`: code of the final project. The project itself is a [submodule](https://github.blog/2016-02-01-working-with-submodules/), hosted [here](https://github.com/francesco-plt/boat-runner).

## Running the code

To run anything, you need to follow this tutorial: [Development environment - Vulkan Tutorial (vulkan-tutorial.com)](https://vulkan-tutorial.com/Development_environment).

Once you're done, you can `cd` into any folder and run the following if you're on Linux:

```shell
$ make -j$(nproc) clean build
```

Or, if you're on macOS:

```shell
$ make -j(sysctl -a | grep machdep.cpu | awk '/machdep.cpu.core_count/ {print $2}')
```

If you're on Windows, you may need to reevaluate your priorities.
