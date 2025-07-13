# Latency Arbitrage Backtest System

This repository implements a latency-sensitive arbitrage detection and execution model designed to simulate and evaluate trading opportunities across fragmented electronic markets.

---

### **Overview**

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
file BaseSIM will:
Simulate 3 hours of exchange and broker feed latency

Evaluate arbitrage opportunities

Log trades and position details

Generate a plot with equity curve and execution triggers
---
### References 
-[1] Karatzas, I., & Shreve, S. (1991). Brownian Motion and Stochastic Cal-
culus. Springer-Verlag.
-[2] A¨ıt-Sahalia, Y., & Sa˘glam, M. (2016). High frequency market making:
Optimal quoting. Working Paper, Princeton University.
-[3] Cartea,A., Jaimungal, S., & Penalva, J. (2015). Algorithmic and High-
Frequency Trading. Cambridge University Press.
-[4] Menkveld, A. J. (2013). High frequency trading and the new market
makers. Journal of Financial Markets, 16(4), 712-740.
-[5] Budish, E., Cramton, P., & Shim, J. (2015). The high-frequency trad-
ing arms race: Frequent batch auctions as a market design response.
Quarterly Journal of Economics, 130(4), 1547-1621.
-[6] Brogaard, J., Hendershott, T., & Riordan, R. (2014). High-frequency
trading and price discovery. Review of Financial Studies, 27(8), 2267-
2306.
-[7] Hasbrouck, J., & Saar, G. (2013). Low-latency trading. Journal of Fi-
nancial Markets, 16(4), 646-679.
-[8] Foucault, T., Pagano, M., & Roell, A. (2013). Market Liquidity: Theory,
Evidence, and Policy. Oxford University Press.

🛠️ Planned Updates & Future Additions
This section tracks ongoing improvements and ideas for future development:

🔄 Upcoming Features
Interactive dashboard for trade inspection and latency diagnostics

Enhanced volatility regime classification (e.g., using HMM or clustering)

Live paper-trading integration via broker API

🧪 Experimental Ideas
Reinforcement learning for order timing under latency constraints

Latency anomaly detection using autoencoders

Entropy-based signal filtering for multi-source confirmation

📌 Change Log
JULY 12, 2025: Base framework tested; visualizations pending

(Add new changes below as updates are made)

Maintained by: Bishwa 
License: MIT (or specify another license)
Last updated: JULY 12, 2025



Run the backtest using:

```bash
python your_script_name.py
