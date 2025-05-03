# KKReshade

A Reshade addon for facilitating interaction between Reshade and KK/KKS/HS2/AI.

## Installation

Build the solution and copy `KKReshade.addon` to Reshade's addon directory (default path is next to `dxgi.dll`).

## What it does

### Screenshot

* Stores the current frame after it finishes rendering effects in shared memory at `KKReshade_Screenshot_SHM`.
