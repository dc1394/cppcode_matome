# Usage

## Setup

```sh
$ julia --project -e 'using Pkg; Pkg.instantiate()'
```

## Runings tests

```sh
$ julia --project runtests.jl
```

## Creating a new output txt for a new problem

```sh
$ JULIA_REFERENCETESTS_UPDATE=true julia runtests.jl
```

See [Updating References within Package Tests](https://github.com/JuliaTesting/ReferenceTests.jl?tab=readme-ov-file#updating-references-within-package-tests) to learn more.