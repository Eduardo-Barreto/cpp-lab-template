# cpp-lab-template

[![C++26](https://img.shields.io/badge/C%2B%2B-26-blue?logo=cplusplus)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-4.2.3-blue?logo=cmake)](https://cmake.org/)
[![GoogleTest](https://img.shields.io/badge/GoogleTest-1.17.0-blue?logo=google)](https://github.com/google/googletest)
[![CI](https://img.shields.io/github/actions/workflow/status/Eduardo-Barreto/cpp-lab-template/ci.yml?label=CI&logo=github)](https://github.com/SEU-USUARIO/cpp-lab-template/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

Template de exercícios em C++ com testes automatizados, formatação e linting configurados.

## Requisitos

- [CMake](https://cmake.org/) >= 4.2.3
- [Ninja](https://ninja-build.org/)
- Compilador com suporte a C++26 (GCC >= 15, Clang >= 20)
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html) e [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) (opcionais, para code style)

## Estrutura

- `src/`: Exercícios organizados por módulo. Cada subpasta com `main.cpp` vira um executável.
- `tests/`: Testes automatizados (GoogleTest). Cada `test_*.cpp` valida um exercício.
- `tests/helpers/`: Utilitário para testes de I/O. Roda o executável do aluno e compara a saída.
- `.github/workflows/`: CI que roda testes, formatação e linting a cada Pull Request.

## Compilando

```bash
cmake --preset dev
cmake --build build
```

Cada exercício gera um executável em `build/` com o nome da pasta (ex: `ola-mundo`, `soma-dois-numeros`).

## Rodando

```bash
./build/ola-mundo
```

## Testando

Os testes usam [GoogleTest](https://github.com/google/googletest) e são baixados automaticamente via FetchContent.

```bash
cmake --preset test
cmake --build build/test
ctest --test-dir build/test --output-on-failure
```

Dois tipos de teste:

- **I/O (stdout):** roda o executável como subprocesso e compara a saída esperada.
- **Unitário:** importa diretamente o `.hpp` do aluno e testa as funções.

## Code style

### Formatação

O projeto usa [clang-format](https://clang.llvm.org/docs/ClangFormat.html) com base LLVM (4 espaços, 120 colunas).

```bash
# verificar
find src tests -name '*.cpp' -o -name '*.hpp' | xargs clang-format --dry-run --Werror

# aplicar
find src tests -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
```

### Linter

O projeto usa [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) com checks de bugprone, performance e readability.

```bash
cmake --preset dev
find src -name '*.cpp' | xargs clang-tidy -p build
```

## Adicionando exercícios

1. Crie a pasta do exercício dentro do módulo correspondente:

```
src/XX-modulo/nome-exercicio/main.cpp
```

2. Crie o teste correspondente:

```
tests/XX-modulo/test_nome_exercicio.cpp
```

3. Rebuild. O CMake descobre tudo automaticamente.

Para exercícios de **I/O**, o teste roda o executável e compara stdout:

```cpp
#include <gtest/gtest.h>
#include "helpers/subprocess.hpp"

TEST(NomeExercicio, CasoBasico) {
    auto result = run("nome-exercicio", "entrada\n");
    EXPECT_EQ(result.stdout_output, "saida esperada\n");
}
```

Para exercícios com **função/classe**, o teste importa o `.hpp` diretamente:

```cpp
#include <gtest/gtest.h>
#include "XX-modulo/nome-exercicio/arquivo.hpp"

TEST(NomeExercicio, CasoBasico) {
    EXPECT_EQ(funcao(5), 10);
}
```

## Contribuindo

1. Crie uma branch a partir de `main`
2. Faça suas alterações
3. Abra um Pull Request
4. O CI roda os testes automaticamente. Formatação e linting são informativos (não bloqueiam).
