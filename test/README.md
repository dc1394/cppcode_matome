# Usage

## Setup

Install Julia using the following command:

```sh
$ curl -fsSL https://install.julialang.org | sh -- yes
$ juliaup add lts
$ julia +lts --version
julia version 1.10.6
```

## Resolve dependencies for testing

```sh
$ julia +lts --project -e 'using Pkg; Pkg.instantiate()'
```

## Running tests

```sh
$ julia +lts --project runtests.jl
```

On Apple silicon device, You may want to add `CPATH=/opt/homebrew/include/`. Namely:

```sh
$ brew install boost
$ CPATH=/opt/homebrew/include/ julia +lts --project runtests.jl
```

## Creating a new output txt for a new problem

```sh
$ JULIA_REFERENCETESTS_UPDATE=true julia +lts --project runtests.jl
$ julia +lts --project runtests.jl # Repeat the tests to check for reproducibility.
```

See [Updating References within Package Tests](https://github.com/JuliaTesting/ReferenceTests.jl?tab=readme-ov-file#updating-references-within-package-tests) to learn more.
