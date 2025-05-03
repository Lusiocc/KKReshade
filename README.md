# KKReshade

A Reshade addon for facilitating interaction between Reshade and KK/KKS/HS2/AI.

## Installation

Build the dll and rename it to `KKReshade.addon`. Copy to Reshade's addon directory (default is next to `dxgi.dll`).

## What it does

### Screenshot

* Stores the current frame after it finishes rendering effects in shared memory at `KKReshade_Screenshot_SHM`.
