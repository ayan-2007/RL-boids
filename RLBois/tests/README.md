# Observation tests (Step 1)

There is no compiled test target yet. Use these checks while implementing `BuildState` in `src/Observation.cpp`.

## Shape / dtype

```text
sizes() == [1, 14]
dtype() == float32
device() == cpu
```

## Known-value scenario

Set `kVisionRadius = 200` and construct:

- self at `(640, 360)`, velocity `(2, 0)`
- enemy at `(740, 360)`, velocity `(5.5, 0)`
- ally at `(540, 360)`, velocity `(-4, 0)`
- the prey vector includes self, so the ally search must skip it

Expected feature vector:

```text
[0.5, 0.0,
 0.5, 0.5, 0.5, 0.5,
 0.5, 0.0, 1.0, 0.0,
 -0.5, 0.0, -1.0, 0.0]
```

## Edge cases

- [ ] Agent at `(0, 0)` and at `(1280, 720)`.
- [ ] No predator within `kVisionRadius` → features 6–9 are zero.
- [ ] No living ally within `kVisionRadius` → features 10–13 are zero.
- [ ] Dead prey is not selected as the nearest ally.
- [ ] Self is not selected as the nearest ally.
- [ ] Enemy exactly at `kVisionRadius` → relative-position magnitude ≈ 1.
- [ ] No `NaN` or `inf` values.

## Range checks

- Features 0–1, 6–13: `[-1, 1]`
- Features 2–5: `[0, 1]`
