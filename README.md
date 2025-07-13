# Latency Arbitrage Backtest System

This repository implements a latency-sensitive arbitrage detection and execution model designed to simulate and evaluate trading opportunities across fragmented electronic markets.

---

### 🔧 **Overview**

- **Model**: `NascentLatencyArbitrage`
- **Purpose**: Detect and exploit fleeting price disparities between broker and exchange feeds while managing detection risk and execution latency.
- **Core Features**:
  - Dual Kalman filters (price and latency)
  - GARCH volatility modeling
  - Bayesian + Kalman blending for latency estimation
  - Multi-source price triangulation
  - Change-point detection (sub-threshold shifts)
  - Kelly criterion sizing with adaptive risk control
  - Quote intensity modeling using a custom point process
  - Simulated exchange + broker price feeds with configurable latency noise

---

### ✅ **Execution**

Run the backtest using:

```bash
python your_script_name.py
