# 🐾 Veterinary Management System (C++)

A simple robust terminal-based management solution developed as part of a **First-Year Software Development module**. This project demonstrates core competencies in C++, object-oriented logic, and secure data handling.

---

## 🚀 Skills Showcased
* **Language:** C++
* **Paradigm:** Object-Oriented Programming (Classes, Inheritance, and Encapsulation)
* **Data Management:** File I/O for persistent storage (`.txt` database)
* **Security:** Role-Based Access Control (RBAC) and credential validation
* **Software Design:** Input validation and modular code structure

---

## 🔐 Access Control & Roles

The system mimics professional software by implementing specific user privileges:

| Role | Permissions |
| :--- | :--- |
| **Admin** | Full system access: manage staff, owners, pets, and appointments. |
| **Vet** | Clinical focus: full pet/appointment management; view/update owners. |
| **Staff** | Administrative focus: manage appointments; view-only for owners/pets. |
| **Guest (Owner)** | Privacy-focused: read-only access to personal and pet data. |

---

## 🛠️ Implementation Details

### Data Persistence
The system utilizes local file handling to simulate a database. This ensures that user and animal records are preserved between sessions:
* `staffacc.txt`: Encrypted-style logic for staff credentials.
* `owner.txt`: Record management for pet owners and guests.

### User Experience
* **Robust Input Handling:** The menu uses integer-driven navigation with a loop-back mechanism to handle invalid inputs gracefully.
* **Account Safety:** To maintain data integrity, the system requires a structured **Sign Up** process for new users (min. 4 characters for names/usernames).

---

## 📖 How to Use

1. **Authentication:** Select **Sign In** and choose your role.
2. **Staff Management:** Admins can create specialized accounts for Vets and Staff.
3. **Data Operations:**
   - **Add:** Follow step-by-step guides for Pets, Owners, or Appointments.
   - **View:** Search for specific records (e.g., by Pet Name) or view full lists.
   - **Update/Delete:** Modify or remove existing records through the management dashboard.



