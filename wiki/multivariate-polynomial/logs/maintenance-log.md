# maintenance-log

## 2026-05-22

initial wiki population from full codebase read

### pages created
- wiki.config.md — updated with project-specific config
- sources.md — all active src files logged, OLD/ excluded
- wiki/index.md — entry point with page map + quick facts
- wiki/structure.md — repo layout, build system, deps, header chain
- wiki/classes.md — all 7 classes documented: fields, methods, constructors
- wiki/data-flow.md — full pipeline: inputs → elimination → roots; data type flow
- wiki/api.md — 7 usage examples: basic solve, 3-var, coeff access, det methods
- wiki/concepts/sylvester.md — Sylvester matrix algo, construction, code path
- wiki/concepts/dcei.md — DCEI/DCEIC algo, Newton interp, method selection table
- wiki/concepts/coeff-indexing.md — lex order storage, binomial size, idx↔exp math

### notes
- OLD/ folder excluded per user instruction
- coeff-indexing page flags doc inconsistency: USAGE.md says (deg+1)^vars, actual impl uses binomial
- [TODO] backSolve not yet implemented in PolyGraph (stub exists)
- [TODO] lazy execution (realtime flag in PolySystemConfig) not implemented
