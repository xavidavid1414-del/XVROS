# XVROS firmware targets

XVROS is being developed toward two firmware deliverables:

- `.firm` — a genuine Nintendo 3DS FIRM-format image intended for a documented, compatible boot path.
- `.bin` — the project-defined XVROS BIN v1 container, specified in [XVROS_BIN_FORMAT.md](../docs/XVROS_BIN_FORMAT.md). It is a packaging format, not a Nintendo 3DS boot format.

Neither deliverable is implemented as an executable/bootable release yet. The current homebrew build is only a development harness and must not be presented as the final XVROS product.

## Intended startup behavior

**User-facing goal:** on a New Nintendo 2DS XL, holding **START** while pressing **POWER** should enter the XVROS boot path. Starting the console without START should continue through the user's normal boot path.

### Existing boot-chain behavior

On a console already using Luma3DS, holding START during power-on opens Luma3DS's FIRM payload chainloader. FIRM payloads are discovered in `/luma/payloads/`. With multiple payloads, the user selects one from the chainloader; with only one payload, Luma3DS skips the selection menu and launches that payload. This is Luma3DS behavior, not code XVROS has implemented.

Reference: [Luma3DS README — basic usage and chainloader](https://github.com/LumaTeam/Luma3DS#basic-usage).

### XVROS integration requirement

The first supported route will be a valid XVROS `.firm` payload launched by the existing Luma3DS chainloader. This provides the requested START-at-boot entry without replacing the console's existing boot manager.

A later, separately reviewed boot-manager integration may be considered, but XVROS must not silently replace the user's existing boot path. Normal startup must remain recoverable, and the user must retain a clear way to return to their regular system.

The exact one-button behavior depends on the payload arrangement and Luma3DS configuration. XVROS will document the tested setup; it will not claim that START directly launches XVROS until that behavior is verified on the target console.

## Hardware target

Initial target: New Nintendo 2DS XL (Nintendo 3DS family), with compatibility claims limited to hardware and boot environments that have actually been tested.

## Engineering milestones

1. **Boot-chain research:** verify the supported FIRM boot path, headers, section layout, load addresses, entry points and hardware initialization responsibilities.
2. **Binary specification:** define the XVROS BIN container, versioning, alignment and validation rules. The v1 draft is now published in `docs/XVROS_BIN_FORMAT.md`.
3. **Minimal core:** create a small, auditable startup component that can initialize only the hardware services required for a safe diagnostic screen.
4. **FIRM packaging:** implement a standards-compatible FIRM container only after its format and execution requirements are verified against reliable documentation and test fixtures.
5. **Automated validation:** validate FIRM structure and XVROS BIN structure independently.
6. **Non-destructive testing:** test through a documented chainloading/development path that leaves the console's existing firmware and recovery options intact.
7. **Release qualification:** publish `.firm` and `.bin` only after independent structural validation and successful tests on the stated hardware.

## XVROS BIN v1 validator

A structural validator is available at `tools/validate_xvbin.py`. Its unit tests are in `tools/test_validate_xvbin.py`, and GitHub Actions runs them through `.github/workflows/validate.yml`.

The validator checks the v1 header, bounds, entry offset, exact file length and payload CRC-32. CRC-32 detects accidental corruption; it is not a signature. Passing validation does not mean a payload is executable or bootable.

## Safety and release rules

- Never rename an ELF, `.3dsx` or arbitrary file to `.firm` or `.bin` and call it firmware.
- Never overwrite boot-critical files or the console's existing firmware as part of development testing.
- Do not distribute an image as bootable until its format, target, loading method and recovery procedure are documented and tested.
- Keep experimental images clearly marked as non-release until qualification is complete.

## Current status

- [x] Firmware target directory and initial format boundary documented
- [x] Separate `.firm` and `.bin` deliverables identified
- [x] START-at-power-on chainloader goal documented
- [x] XVROS BIN v1 draft format specified
- [x] Initial BIN structural validator and unit tests added
- [ ] GitHub Actions validator run verified
- [ ] Verified FIRM format specification and boot-path reference
- [ ] Minimal diagnostic core
- [ ] FIRM packer and structural validator
- [ ] Non-destructive hardware testing
- [ ] Qualified release artifacts

The existing `.3dsx` build, if retained, is only a temporary development harness. It is not the requested final release format.
