# Commit Messages
Commit messages should follow the rules of "Conventional Commits", to be read at https://www.conventionalcommits.org/en/v1.0.0/

A short summary:

&lt;type>[optional scope]: &lt;description>

[optional body]

[optional footer(s)]
  
1. **fix:** a commit of the type `fix` patches a bug in your codebase (this correlates with PATCH in Semantic Versioning).
2. **feat:** a commit of the type feat introduces a new feature to the codebase (this correlates with MINOR in Semantic Versioning).
3. **BREAKING CHANGE:** a commit that has a footer BREAKING CHANGE:, or appends a ! after the type/scope, introduces a breaking API change (correlating with MAJOR in Semantic Versioning). A BREAKING CHANGE can be part of commits of any type.
4. types other than fix: and feat: are allowed, for example @commitlint/config-conventional (based on the the Angular convention) recommends build:, chore:, ci:, docs:, style:, refactor:, perf:, test:, and others.
5. footers other than BREAKING CHANGE: &lt;tdescription> may be provided and follow a convention similar to git trailer format.
Additional types are not mandated by the Conventional Commits specification, and have no implicit effect in Semantic Versioning (unless they include a BREAKING CHANGE). A scope may be provided to a commit’s type, to provide additional contextual information and is contained within parenthesis, e.g., feat(parser): add ability to parse arrays.
