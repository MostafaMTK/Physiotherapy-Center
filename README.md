# Physiotherapy Center Management Simulator

## 📖 Project Overview

This C++ simulator models the end‑to‑end workflow of a physiotherapy clinic. It demonstrates core data‑structure concepts by accurately scheduling patients, allocating resources, and tracking multiple sequential treatments in real time.

---

## ✅ Key Features

- **Unique Appointments & Arrivals**  
  Each patient has a distinct appointment time and actual arrival; they may arrive early, on time, or late.

- **Up to Three Sequential Treatments**  
  Patients can receive up to three therapies—Electrotherapy, Ultrasound, and Gym—in sequence, each with its own prescribed duration.

- **Flexible Resource Configuration**  
  Reads from input:  
  - Number of electrotherapy and ultrasound devices  
  - Number of gym rooms and each room’s capacity  
  Dynamically allocates and releases equipment as treatments begin and end.

- **Precise Data‑Structure Control**  
  Implements pointer‑based queues, stacks, and priority queues (no STL) to manage:  
  - Waiting lists  
  - In‑treatment sessions  
  - Recovery flows  
  All enqueues and dequeues occur at exact simulation timesteps.

- **Real‑Time Patient Flow**  
  - On‑time patients start immediately; late arrivals wait.  
  - Recovering patients always join the shortest available queue.  
  - Supports probabilistic cancellations and rescheduling before treatment.

- **Two Modes of Operation**  
  - **Interactive Mode**: Step through each minute with live console updates.  
  - **Batch Mode**: Run end-to-end and write detailed per‑patient logs and aggregate statistics to file.

---


## 🧾 Input Format

1. **Device Counts:** Number of electrotherapy and ultrasound devices  
2. **Gym Rooms:** Number of gym rooms and each room’s capacity  
3. **Probabilities:** Cancellation and rescheduling rates (percentages)  
4. **Patient List:** One line per patient in the form:  
   ```
   [N/R] PT VT NT [Type Duration]×NT
   ```  
   - **N/R:** New or Recovering  
   - **PT:** Prescribed appointment time  
   - **VT:** Actual arrival time  
   - **NT:** Number of treatments  
   - **Type Duration:** Sequence of treatment types and durations

---

## 📊 Output

- **Per‑Patient Logs:** Start/end times, waiting times, treatment durations, cancellation/reschedule status  
- **Summary Statistics:** Averages, utilization rates, cancellation and rescheduling percentages



---

## 🤝 Contributors

- [Mostafa Mohammed](https://www.linkedin.com/in/mostafamohammed2005/)  
- [Mariam Mohamed](https://www.linkedin.com/in/mariam-mohamed-923025335/)  
- [Mariam Sameh](https://www.linkedin.com/in/mariam-sameh-1b726a335/)

---

## 🎓 Acknowledgments

Thank you to Cairo University’s Data Structures course team and our instructor for guidance and support throughout this project.
