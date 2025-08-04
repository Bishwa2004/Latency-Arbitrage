# Python for Capacity Analytics — Proof of Concept
**Small Business Credit | Benefit Time Usage**

**Project Update:** _{{ replace with date }}_

**Contents**
1. Executive Summary  
2. **Innovation in Reporting & Analytics**  
3. Data Sources & Definitions  
4. Key Questions & Method  
5. Findings (KPIs)  
6. Charts  
7. Recommendations  
8. Appendix (Risks, Assumptions)

------
## Executive Summary
<div class="callout callout-strong">
<p>We built a repeatable Python workflow (Jupyter + pandas + matplotlib) to analyze IEX benefit time (Vacation, Sick+Personal, Paid Leave) at a monthly cadence, with outputs designed for easy peer review and audit.</p>
<ul>
<li>Monthly trends, % of Paid Hours, and business/region splits</li>
<li>Associate-level entitlement checks for Vacation and Sick+Personal</li>
<li>Charts and KPI callouts for leadership consumption</li>
</ul>
</div>
-----
## Innovation in Reporting & Analytics

### What’s new
- **One-click reproducibility:** A single notebook runs end-to-end and documents each step with markdown.
- **Auditability:** Calculations and assumptions are visible in-line; peers can validate logic quickly.
- **Consistency:** Standard definitions (e.g., % of Paid Hours) applied the same way every month.
- **Shareable visuals:** Charts render within the notebook; optional export to HTML/PDF for decks.

### Why it matters
- **Less manual effort** vs. spreadsheets and ad-hoc SQL pulls.
- **Fewer errors** through codified transformations and tests.
- **Faster reviews**: stakeholders see the math, not just the final numbers.

### How it works (at a glance)
1. **Load & Clean:** Normalize headers, convert dates, coerce numerics.
2. **Compute:** Vacation (earned+purchase), Sick+Personal, Paid Leave, and **Paid Hours**.
3. **Aggregate:** Monthly totals and **% of Paid Hours**; business/region splits as needed.
4. **Present:** KPI callouts + charts with labeled monthly axes.

> **Design note:** We hide complexity in helper functions so the narrative stays readable while the logic remains transparent.
## Data Sources & Definitions

**Sources**
- IEX “Daily Table” export (2024)
- Optional: People History (Region, hire/term for proration)

**Key Definitions**
- **Vacation_Total** = Vacation_Earned + Vacation_Purchase  
- **SickPersonal** = OI-Sick + OI-Personal Day  
- **Paid Hours** = 8 × (paid days) + Overtime − Unpaid  
- **% of Paid Hours** (for a category) = Category Hours ÷ Paid Hours

**Assumptions**
- Vacation entitlement: 20 days/year; Sick+Personal: 10 days/year (8 hours/day).
- If no explicit paid-day flag exists, a paid day is inferred when any tracked time exists.
#######
  import numpy as np
from IPython.display import Markdown, display

assert 'monthly' in globals(), "Run the analysis cell that creates `monthly` first."

m = monthly.sort_values('Month').copy()
latest = m['Month'].max()
row = m.loc[m['Month']==latest].iloc[0]

kpi_html = f"""
<div class="kpi"><span class="v">{row['Vacation_Total']:.0f} hrs</span><br><span class="l">Vacation (latest)</span></div>
<div class="kpi"><span class="v">{row['SickPersonal']:.0f} hrs</span><br><span class="l">Sick + Personal (latest)</span></div>
<div class="kpi"><span class="v">{row['PaidLeave']:.0f} hrs</span><br><span class="l">Paid Leave (latest)</span></div>
<div class="kpi"><span class="v">{row['Vacation_Total_PctPaid']:.1f}%</span><br><span class="l">% of Paid — Vacation</span></div>
<div class="kpi"><span class="v">{row['SickPersonal_PctPaid']:.1f}%</span><br><span class="l">% of Paid — Sick+Personal</span></div>
<div class="kpi"><span class="v">{row['PaidLeave_PctPaid']:.1f}%</span><br><span class="l">% of Paid — Paid Leave</span></div>
"""
display(HTML(kpi_html))




  import matplotlib.pyplot as plt
import numpy as np

mm = monthly.sort_values('Month').copy()
x = mm['Month']
xt = mm['Month'].dt.strftime('%b-%Y')

# Chart 1: % of Paid Hours by category
plt.figure()
plt.plot(x, mm['Vacation_Total_PctPaid'], marker='o', label='Vacation')
plt.plot(x, mm['SickPersonal_PctPaid'], marker='o', label='Sick+Personal')
plt.plot(x, mm['PaidLeave_PctPaid'], marker='o', label='Paid Leave')
plt.title('% of Paid Hours by Category (Monthly)')
plt.xlabel('Month'); plt.ylabel('% of Paid Hours')
plt.xticks(x, xt, rotation=45)
plt.legend()
plt.tight_layout()
plt.show()

# Chart 2: Vacation Earned vs Purchased (stacked)
if 'Vacation_Earned' in mm.columns and 'Vacation_Purchase' in mm.columns:
    plt.figure()
    idx = np.arange(len(mm))
    plt.bar(idx, mm['Vacation_Earned'])
    plt.bar(idx, mm['Vacation_Purchase'], bottom=mm['Vacation_Earned'])
    plt.title('Vacation Earned vs Purchased (Monthly)')
    plt.xlabel('Month'); plt.ylabel('Hours')
    plt.xticks(idx, xt, rotation=45)
    plt.tight_layout()
    plt.show()

# Chart 3: Total Paid Hours
plt.figure()
plt.plot(x, mm['Paid_Hours'], marker='o')
plt.title('Total Paid Hours (Monthly)')
plt.xlabel('Month'); plt.ylabel('Hours')
plt.xticks(x, xt, rotation=45)
plt.tight_layout()
plt.show()

  ## Recommendations
1. **Standardize** monthly reporting through this notebook; keep logic/version under source control.
2. **Automate** region and business splits; add proration using hire/term for entitlement accuracy.
3. **Explainability**: add short comments to each calc cell; link to data dictionary.
4. **Adopt** the HTML export for sharing with partners (keeps code hidden, story visible).
## Appendix
**Risks**
- Source data quality (missing/incorrect columns; unpaid variants)
- Sheet name drift and header changes

**Next Steps**
- Add effective-dated region mapping
- Integrate queue/associate performance overlays
- Parameterize date range and business filters
# Set to True only if you want an HTML file; otherwise ignore.
EXPORT_HTML = False
if EXPORT_HTML:
    import os
    os.system("jupyter nbconvert --to html --TemplateExporter.exclude_input=True --no-input --output capacity_report.html $(basename $PWD).ipynb")
